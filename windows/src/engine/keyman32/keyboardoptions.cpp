/*
  Name:             keyboardoptions
  Copyright:        Copyright (C) SIL International.
  Documentation:
  Description:
  Create Date:      25 May 2010

  Modified Date:    28 Nov 2012
  Authors:          mcdurdin
  Related Files:
  Dependencies:

  Bugs:
  Todo:
  Notes:
  History:          25 May 2010 - mcdurdin - I1632 - Keyboard Options
                    31 May 2010 - mcdurdin - I2397 - Assertion failure - keyboard options loading twice
                    28 Nov 2012 - mcdurdin - I3594 - V9.0 - Remove old SelectKeyboard code and related messages
*/
#include "pch.h"
#include "registry.h"
#include <string>

void IntSaveKeyboardOption(LPCSTR key, LPINTKEYBOARDINFO kp, int nStoreToSave);
BOOL IntLoadKeyboardOptions(LPCSTR key, LPINTKEYBOARDINFO kp);
BOOL IntLoadKeyboardOptionsCore(LPCSTR key, LPINTKEYBOARDINFO kp, km_kbp_state* const state);
void IntSaveKeyboardOptionREGCore(LPCSTR REGKey, LPINTKEYBOARDINFO kp, LPCWSTR key, LPCWSTR value);

void LoadKeyboardOptions(LPINTKEYBOARDINFO kp)
{   // I3594
  IntLoadKeyboardOptions(REGSZ_KeyboardOptions, kp);
}

void LoadSharedKeyboardOptions(LPINTKEYBOARDINFO kp)
{
  if (Globals::get_CoreIntegration())
  {
    return; // should never be called if using core processor
  }
  // Called when another thread changes keyboard options and we are sharing keyboard settings
  assert(kp != NULL);
  assert(kp->Keyboard != NULL);

  if(kp->KeyboardOptions != NULL) FreeKeyboardOptions(kp);

  IntLoadKeyboardOptions(REGSZ_SharedKeyboardOptions, kp);
}

void FreeKeyboardOptions(LPINTKEYBOARDINFO kp)
{
  if (Globals::get_CoreIntegration())
  {
    return; // should never be called if using core processor
  }
  // This is a cleanup routine; we don't want to precondition all calls to it
  // so we do not assert
  if (kp == NULL || kp->Keyboard == NULL || kp->KeyboardOptions == NULL)
    return;

  for(DWORD i = 0; i < kp->Keyboard->cxStoreArray; i++)
    if(kp->KeyboardOptions[i].Value)
    {
      kp->Keyboard->dpStoreArray[i].dpString = kp->KeyboardOptions[i].OriginalStore;
      delete kp->KeyboardOptions[i].Value;
    }
  delete kp->KeyboardOptions;
  kp->KeyboardOptions = NULL;
}

void SetKeyboardOption(LPINTKEYBOARDINFO kp, int nStoreToSet, int nStoreToRead)
{
  if (Globals::get_CoreIntegration())
  {
    return; // should never be called if using core processor
  }

  assert(kp != NULL);
  assert(kp->Keyboard != NULL);
  assert(kp->KeyboardOptions != NULL);
  assert(nStoreToSet >= 0);
  assert(nStoreToSet < (int) kp->Keyboard->cxStoreArray);
  assert(nStoreToRead >= 0);
  assert(nStoreToRead < (int) kp->Keyboard->cxStoreArray);

  LPSTORE sp = &kp->Keyboard->dpStoreArray[nStoreToRead];
  if(kp->KeyboardOptions[nStoreToSet].Value)
  {
    delete kp->KeyboardOptions[nStoreToSet].Value;
  }
  else
  {
    kp->KeyboardOptions[nStoreToSet].OriginalStore = kp->Keyboard->dpStoreArray[nStoreToSet].dpString;
  }

  kp->KeyboardOptions[nStoreToSet].Value = new WCHAR[wcslen(sp->dpString)+1];
  wcscpy_s(kp->KeyboardOptions[nStoreToSet].Value, wcslen(sp->dpString)+1, sp->dpString);
  kp->Keyboard->dpStoreArray[nStoreToSet].dpString = kp->KeyboardOptions[nStoreToSet].Value;
}

void ResetKeyboardOption(LPINTKEYBOARDINFO kp, int nStoreToReset)
{
  if (Globals::get_CoreIntegration())
  {
    return; // should never be called if using core processor
  }
  assert(kp != NULL);
  assert(kp->Keyboard != NULL);
  assert(kp->KeyboardOptions != NULL);
  assert(nStoreToReset >= 0);
  assert(nStoreToReset < (int) kp->Keyboard->cxStoreArray);

  if(kp->KeyboardOptions[nStoreToReset].Value)
  {
    kp->Keyboard->dpStoreArray[nStoreToReset].dpString = kp->KeyboardOptions[nStoreToReset].OriginalStore;
    delete kp->KeyboardOptions[nStoreToReset].Value;
    kp->KeyboardOptions[nStoreToReset].Value = NULL;

    if(kp->Keyboard->dpStoreArray[nStoreToReset].dpName == NULL) return;

    RegistryReadOnly r(HKEY_CURRENT_USER);
    if(r.OpenKeyReadOnly(REGSZ_KeymanActiveKeyboards) && r.OpenKeyReadOnly(kp->Name) && r.OpenKeyReadOnly(REGSZ_KeyboardOptions))
    {
      if(r.ValueExists(kp->Keyboard->dpStoreArray[nStoreToReset].dpName))
      {
        WCHAR val[256];
        if(!r.ReadString(kp->Keyboard->dpStoreArray[nStoreToReset].dpName, val, sizeof(val) / sizeof(val[0]))) return;
        if(!val[0]) return;
        val[255] = 0;
        kp->KeyboardOptions[nStoreToReset].Value = new WCHAR[wcslen(val)+1];
        wcscpy_s(kp->KeyboardOptions[nStoreToReset].Value, wcslen(val)+1, val);

        kp->KeyboardOptions[nStoreToReset].OriginalStore = kp->Keyboard->dpStoreArray[nStoreToReset].dpString;
        kp->Keyboard->dpStoreArray[nStoreToReset].dpString = kp->KeyboardOptions[nStoreToReset].Value;
      }
    }
  }
}


void SaveKeyboardOption(LPINTKEYBOARDINFO kp, int nStoreToSave)
{
  if (Globals::get_CoreIntegration())
  {
    return; // should never be called if using core processor
  }
  IntSaveKeyboardOption(REGSZ_KeyboardOptions, kp, nStoreToSave);
}

void SaveKeyboardOptionREGCore(LPINTKEYBOARDINFO kp, LPCWSTR key, LPCWSTR value)
{
  IntSaveKeyboardOptionREGCore(REGSZ_KeyboardOptions, kp, key, value);
}

void IntSaveKeyboardOptionREGCore(LPCSTR REGKey, LPINTKEYBOARDINFO kp, LPCWSTR key, LPCWSTR value)
{
  assert(REGKey != NULL);
  assert(kp != NULL);
  assert(kp->coreKeyboard != NULL);
  assert(kp->coreKeyboardOptions != NULL);
  // TODO: 5011 just check for yourself that the core processor now checks if there size limit of the keyboard store has been reached.
  RegistryFullAccess r(HKEY_CURRENT_USER);
  if (r.OpenKey(REGSZ_KeymanActiveKeyboards, TRUE) && r.OpenKey(kp->Name, TRUE) && r.OpenKey(REGKey, TRUE))
  {
    std::wstring tempValue(value);
    r.WriteString(key, &tempValue[0]);
  }
}

BOOL IntLoadKeyboardOptions(LPCSTR key, LPINTKEYBOARDINFO kp)
{
  assert(key != NULL);
  assert(kp != NULL);
  assert(kp->Keyboard != NULL);
  assert(kp->KeyboardOptions == NULL);

  kp->KeyboardOptions = new INTKEYBOARDOPTIONS[kp->Keyboard->cxStoreArray];
  memset(kp->KeyboardOptions, 0, sizeof(INTKEYBOARDOPTIONS) * kp->Keyboard->cxStoreArray);
  RegistryReadOnly r(HKEY_CURRENT_USER);
  if(r.OpenKeyReadOnly(REGSZ_KeymanActiveKeyboards) && r.OpenKeyReadOnly(kp->Name) && r.OpenKeyReadOnly(key))
  {
    WCHAR buf[256];
    int n = 0;
    while(r.GetValueNames(buf, sizeof(buf) / sizeof(buf[0]), n))
    {
      buf[255] = 0;
      WCHAR val[256];
      if(r.ReadString(buf, val, sizeof(val) / sizeof(val[0])) && val[0])
      {
        val[255] = 0;
        for(DWORD i = 0; i < kp->Keyboard->cxStoreArray; i++)
        {
          if(kp->Keyboard->dpStoreArray[i].dpName != NULL && _wcsicmp(kp->Keyboard->dpStoreArray[i].dpName, buf) == 0)
          {
            kp->KeyboardOptions[i].Value = new WCHAR[wcslen(val)+1]; // is this a memory leak as
            wcscpy_s(kp->KeyboardOptions[i].Value, wcslen(val)+1, val);

            kp->KeyboardOptions[i].OriginalStore = kp->Keyboard->dpStoreArray[i].dpString;
            kp->Keyboard->dpStoreArray[i].dpString = kp->KeyboardOptions[i].Value;

            break;
          }
        }
      }
      n++;
    }
    return TRUE;
  }
  return FALSE;
}

void IntSaveKeyboardOption(LPCSTR key, LPINTKEYBOARDINFO kp, int nStoreToSave)
{
  assert(key != NULL);
  assert(kp != NULL);
  assert(kp->Keyboard != NULL);
  assert(kp->KeyboardOptions != NULL);
  assert(nStoreToSave >= 0);
  assert(nStoreToSave < (int) kp->Keyboard->cxStoreArray);

  if(kp->Keyboard->dpStoreArray[nStoreToSave].dpName == NULL) return;

  RegistryFullAccess r(HKEY_CURRENT_USER);
  if(r.OpenKey(REGSZ_KeymanActiveKeyboards, TRUE) && r.OpenKey(kp->Name, TRUE) && r.OpenKey(key, TRUE))
  {
    r.WriteString(kp->Keyboard->dpStoreArray[nStoreToSave].dpName, kp->Keyboard->dpStoreArray[nStoreToSave].dpString);
  }
}

void LoadKeyboardOptionsREGCore(LPINTKEYBOARDINFO kp, km_kbp_state* const state)
{
  IntLoadKeyboardOptionsCore(REGSZ_KeyboardOptions, kp, state);
}

BOOL IntLoadKeyboardOptionsCore(LPCSTR key, LPINTKEYBOARDINFO kp, km_kbp_state* state)
{
  assert(key != NULL);
  assert(kp != NULL);
  assert(kp->Keyboard != NULL);
  assert(kp->KeyboardOptions == NULL); // not used for common core

  RegistryReadOnly r(HKEY_CURRENT_USER);
  if (r.OpenKeyReadOnly(REGSZ_KeymanActiveKeyboards) && r.OpenKeyReadOnly(kp->Name) && r.OpenKeyReadOnly(key))
  {
    WCHAR buf[256];
    int n = 0;
    // Get the list of default options to determine size of list
    const km_kbp_keyboard_attrs* keyboadAttrs;
    km_kbp_keyboard_get_attrs(kp->coreKeyboard, &keyboadAttrs);
    size_t listSize = km_kbp_options_list_size(keyboadAttrs->default_options);
    km_kbp_option_item* keyboardOpts = new  km_kbp_option_item[listSize+1];

    while (r.GetValueNames(buf, sizeof(buf) / sizeof(buf[0]), n))
    {
      buf[255] = 0;
      WCHAR val[256];
      if (r.ReadString(buf, val, sizeof(val) / sizeof(val[0])) && val[0])
      {
        val[255] = 0;
        keyboardOpts[n].scope = KM_KBP_OPT_KEYBOARD;

        std::wstring tempKey(buf);
        keyboardOpts[n].key = reinterpret_cast<char16_t*>(&tempKey[0]);

        std::wstring tempValue(value);
        keyboardOpts[n].value = reinterpret_cast<char16_t*>(&tempValue[0]);
      }
      n++;
    }
    /// once we have the option list we can then update the options using the public api call
    km_kbp_state_options_update(state, keyboardOpts);
   for (int i = 0; i < (int)listSize + 1; i++) {
      delete[] keyboardOpts[i].key;
      delete[] keyboardOpts[i].value;
    }
    delete keyboardOpts;
    return TRUE;
  }
  return FALSE;
}
