/*
  Name:             kmkey
  Copyright:        Copyright (C) SIL International.
  Documentation:
  Description:
  Create Date:      19 Jun 2007

  Modified Date:    28 Mar 2016
  Authors:          mcdurdin
  Related Files:
  Dependencies:

  Bugs:
  Todo:
  Notes:
  History:          19 Jun 2007 - mcdurdin - I890 - Deadkeys not working correctly in TSF
                    19 Jun 2007 - mcdurdin - I822 - TSF Addin not working
                    07 Sep 2009 - mcdurdin - I2095 - TSF addin is not threadsafe
                    07 Nov 2012 - mcdurdin - I3549 - V9.0 - x64 version of kmtip addin
                    17 Nov 2012 - mcdurdin - I3567 - V9.0 - KeymanProcessOutput and KeymanGetContext return S_OK but are declared as BOOL
                    17 Nov 2012 - mcdurdin - I3568 - V9.0 - Support legacy output by testing for transitory context
                    20 Nov 2012 - mcdurdin - I3581 - V9.0 - KMTip needs to pass activated profile guid through to Keyman32 to switch keyboards
                    20 Nov 2012 - mcdurdin - I3581 - V9.0 - KMTip needs to pass activated profile guid through to Keyman32 to switch keyboards
                    28 Nov 2012 - mcdurdin - I3588 - V9.0 - Use preserved keys in TSF to handle key combinations in Keyman
                    28 Nov 2012 - mcdurdin - I3589 - V9.0 - Handle key state for KeyUp events in TSF
                    28 Nov 2012 - mcdurdin - I3590 - V9.0 - Initialise keystroke sink after we know which keyboard to activate
                    01 Dec 2012 - mcdurdin - I3608 - V9.0 - Shortcut test for VK_PACKET in kmtip
                    01 May 2014 - mcdurdin - I4201 - V9.0 - Shift + Arrows do not select text (only move caret) in Win 8 when Keyman keyboard is active
                    10 Jun 2014 - mcdurdin - I4262 - V9.0 - TSF deadkeys do not function correctly
                    16 Jun 2014 - mcdurdin - I4274 - V9.0 - kmtip does not work if already active before KM starts
                    13 Aug 2014 - mcdurdin - I4375 - V9.0 - Add registry flag deep integration to allow us to disable TIP context
                    13 Aug 2014 - mcdurdin - I4370 - Deadkeys are still not working in Winword TIP mode
                    14 Aug 2014 - mcdurdin - I4378 - V9.0 - Rapid typing in legacy mode breaks Keyman input
                    28 Mar 2016 - mcdurdin - I4933 - Compat issue with Firefox 42 and IE and Keyman 9 TSF
*/

#include "pch.h"
#include "kmtip.h"
#include "editsess.h"
#include "Compiler.h"
#include "registry.h"
#include "..\keymanmc\keymanmc.h"

struct deadkeyinfo
{
  int pos, val;
};

class CKeymanEditSession : public CEditSessionBase
{
public:
  CKeymanEditSession(ITfContext *pContext, WPARAM wParam, LPARAM lParam, BOOL fUpdate, BOOL fPreserved, DWORD dwDeepIntegration) : CEditSessionBase(pContext)   // I3588   // I4375
  {
    _wParam = wParam;
    _lParam = lParam;   // I3589
    _fUpdate = fUpdate;
    _fPreserved = fPreserved;   // I3588
    _dwDeepIntegration = dwDeepIntegration;   // I4375
    _hr = S_FALSE;
    _ec = 0;
  }

  // ITfEditSession
  STDMETHODIMP DoEditSession(TfEditCookie ec);

  HRESULT WINAPI KeymanProcessOutput(int n, PWSTR buf, int nbuf);   // I3567
  HRESULT WINAPI KeymanGetContext(int n, PWSTR buf);   // I3567
  HRESULT GetResult() { return _hr; }

private:
  BOOL _fUpdate;
  BOOL _fPreserved;   // I3588
  HRESULT _hr;
  WPARAM _wParam;
  LPARAM _lParam;   // I3589
  DWORD _dwDeepIntegration;   // I4375
  TfEditCookie _ec;
};

#define KEYEVENT_EXTRAINFO_KEYMAN 0xF00F0000   // I4370

BOOL CKMTipTextService::_KeymanProcessKeystroke(ITfContext *pContext, WPARAM wParam, LPARAM lParam, BOOL fUpdate, BOOL fPreserved)   // I3588
{
  CKeymanEditSession *pEditSession;
  HRESULT hr = S_OK;
  LogEnter();

  // Don't process Unicode characters injected or ProcessKey events which are generated by Windows
  if (wParam == VK_PACKET || wParam == VK_PROCESSKEY) return FALSE;   // I3608   // I4201

  Log(L"_KeymanProcessKeystroke (%x %x %s %s ex=%x)", wParam, lParam, fUpdate ? L"update" : L"", fPreserved ? L"preserved" : L"", GetMessageExtraInfo());   // I4378

  // Don't process keystrokes generated by Keyman (scan code = 0xFF)
  // But we need to pass Caps Lock through, even if we generated it, so we can track Caps Lock state.
  // TODO: This is done in multiple places, but we probably only need to do it once
  if ((lParam & 0xFF0000) == 0xFF0000 &&
    wParam != VK_CAPITAL) {
    return FALSE;   // I4378
  }

  if (!Keyman32Interface::TIPIsKeymanRunning()) {
    _TryAndStartKeyman();
    return FALSE;
  }

  // we'll insert a char ourselves in place of this keystroke
  if ((pEditSession = new CKeymanEditSession(pContext, wParam, lParam, fUpdate, fPreserved, _dwDeepIntegration)) == NULL) {  // I3588   // I3589   // I4375
    Log(L"_KeymanProcessKeystroke: new CKeymanEditSession failed, out of memory?");
    hr = E_OUTOFMEMORY;
  }
  else {
    HRESULT hrSession;
    if ((hr = pContext->RequestEditSession(_tfClientId, pEditSession,
      fUpdate ? TF_ES_SYNC | TF_ES_READWRITE : TF_ES_SYNC | TF_ES_READ, &hrSession)) != S_OK) {
      Log(L"_KeymanProcessKeystroke: RequestEditSession failed with %x (session hr=%x)", hr, hrSession);
      hr = E_FAIL;
    }
    else {
      if (hrSession == S_OK) {
        hr = pEditSession->GetResult();
        if (hr != S_OK) {
          Log(L"_KeymanProcessKeystroke: GetResult failed with %x", hr);
        }
        // GetResult will return E_FAIL when we don't process the keystroke
        // but this actually isn't a failure (it should return S_FALSE, but
        // that can be work for another day)
      }
      else {
        Log(L"_KeymanProcessKeystroke: RequestEditSession failed with session failure %x", hrSession);
        hr = E_FAIL;
      }
    }
    pEditSession->Release();
  }

  return hr == S_OK;
}

//+---------------------------------------------------------------------------
//
// CKeymanEditSession
//
//----------------------------------------------------------------------------

CKeymanEditSession *ExtEditSession = NULL;

extern "C" __declspec(dllexport) HRESULT WINAPI ExtKeymanProcessOutput(int n, WCHAR *buf, int nbuf)   // I3567
{
  LogEnter();
  HRESULT res;
  if (ExtEditSession) res = ExtEditSession->KeymanProcessOutput(n, buf, nbuf);
  else res = E_FAIL;   // I3567
  return res;
}

extern "C" __declspec(dllexport) HRESULT WINAPI ExtKeymanGetContext(int n, PWSTR buf)   // I3567
{
  LogEnter();
  HRESULT res;
  if (ExtEditSession) res = ExtEditSession->KeymanGetContext(n, buf);
  else res = E_FAIL;   // I3567
  return res;
}

STDAPI CKeymanEditSession::DoEditSession(TfEditCookie ec)
{
  LogEnter();

  _ec = ec;
  _hr = S_OK;


  ExtEditSession = this;

  if (!Keyman32Interface::TIPProcessKey(_wParam, _lParam, ExtKeymanProcessOutput, ExtKeymanGetContext, _fUpdate, _fPreserved)) {
    SendDebugMessage(L"DoEditSession: TIPProcessKey did not handle the keystroke");
    _hr = E_FAIL; // TODO: use S_FALSE -> this tells _KeymanProcessKeystroke to pass keystroke on
  }

  ExtEditSession = NULL;

  // Call keyman32.processtipkey; this may call "KeymanGetContext(n, buf)";
  // keyman32.processtipkey this will call "KeymanProcessOutput"
  // which will delete n chrs from left of cursor and output a text string
  // beeps, deadkeys, etc. will be managed from within keyman32.dll itself

  // At this point, the text will already have been output
  // callback will have the information necessary
  // to know what is happening -- make sure that pContext is available globally

  // we need a lock to do our work
  // nb: this method is one of the few places where it is legal to use
  // the TF_ES_SYNC flag

  return S_OK;
}

char *debugstr(PWSTR buf);

HRESULT WINAPI CKeymanEditSession::KeymanProcessOutput(int n, WCHAR *buf, int nbuf)   // I3567
{
  LogEnter();

  if (ShouldDebug()) {
    char *p = debugstr(buf);
    SendDebugMessageFormat(L"KeymanProcessOutput: fUpdate = %d, deleting %d, inserting %d '%hs'", _fUpdate, n, nbuf, p);   // I4262
    delete[] p;
  }

  if (_fUpdate) {
    /* Delete characters left of selection */
    DeleteLeftOfSelection(_ec, _pContext, n);

    /* Add text to screen */

    InsertTextAtSelection(_ec, _pContext, buf, nbuf);   // I4262
  }
  return S_OK;
}


HRESULT WINAPI CKeymanEditSession::KeymanGetContext(int n, PWSTR buf)   // I3567
{
  LogEnter();

  HRESULT hr;
  TF_STATUS tfStatus;

  if (_dwDeepIntegration == DEEPINTEGRATION_DISABLE) {   // I4375
    Log(L"KeymanGetContext: Exit: deep integration disabled by registry (or default)");
    return S_FALSE;
  }

  if (!SUCCEEDED(hr = _pContext->GetStatus(&tfStatus)))   // I3568
  {
    Log(L"KeymanGetContext: Exit -- Failed GetStatus = %x", hr);
    return hr;
  }

  if (tfStatus.dwStaticFlags & TF_SS_TRANSITORY)   // I3568
  {
    Log(L"KeymanGetContext: Exit: Context does not support manipulation.  Using legacy interaction");
    return S_FALSE;
  }

  if (!GetLeftOfSelection(_ec, _pContext, buf, n)) {   // I4933
    return S_FALSE;   // I4933
  }

  return S_OK;
}

BOOL CKMTipTextService::TIPNotifyActivate(GUID *guidProfile)   // I3581   // I4274
{
  LogEnter();

  //_UninitKeystrokeSink();   // I3590
  if (!_InitKeystrokeSink()) {
    SendDebugMessage(L"TIPNotifyActivate: _InitKeystrokeSink failed");
    return FALSE;   // I3590
  }

  if (!Keyman32Interface::TIPActivateKeyboard(guidProfile)) {
    SendDebugMessage(L"TIPNotifyActivate: TIPActivateKeyboard failed");
    return FALSE;
  }

  if (!_InitPreservedKeys()) {
    SendDebugMessage(L"TIPNotifyActivate: _InitPreservedKeys failed");
    return FALSE;
  }
  return TRUE;
}

BOOL CKMTipTextService::_InitKeyman()   // I3590   // I4274
{
  LogEnter();

  if (!Keyman32Interface::TIPActivateEx(TRUE)) {
    return FALSE;
  }

  return TRUE;
}

void CKMTipTextService::_UninitKeyman() {
  LogEnter();

  Keyman32Interface::TIPActivateEx(FALSE);
}

void CKMTipTextService::_TryAndStartKeyman() {
#if 0
  // This has proven to be too troublesome so we will disable for 14.0.

  HANDLE hEventSource = RegisterEventSource(NULL, "Keyman");
  if (!hEventSource) {
    // This is unlikely to occur, but if it does, there's probably
    // not much we can do about it; it's not like we can report an event...
    return;
  }
  ReportEvent(hEventSource, EVENTLOG_INFORMATION_TYPE, SIMPLE_CATEGORY, MSG_START_KEYMAN_ON_DEMAND, NULL, 0, 0, NULL, NULL);
  DeregisterEventSource(hEventSource);
#endif
}
