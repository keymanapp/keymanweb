#
# TSysInfox64 Makefile
#

!include ..\..\Defines.mak

build: version.res manifest.res dirs
    $(DELPHI_MSBUILD) tsysinfox64.dproj /p:Platform=Win64
    #$(SENTRYTOOL_DELPHIPREP) $(WIN64_TARGET_PATH)\tsysinfox64.exe -dpr tsysinfox64.dpr
    $(COPY) $(WIN64_TARGET_PATH)\tsysinfox64.exe $(PROGRAM)\engine

clean: def-clean

signcode:
    $(SIGNCODE) /d "Keyman Engine x64 Diagnostics" $(PROGRAM)\engine\tsysinfox64.exe

wrap-symbols:
    $(SYMSTORE) $(PROGRAM)\engine\tsysinfox64.exe /t keyman-engine-windows
    #$(SYMSTORE) $(DEBUGPATH)\engine\tsysinfox64.dbg /t keyman-engine-windows

install:
    echo Nothing to do.

test-manifest:
    # test that linked manifest exists and correct
    $(MT) -nologo -inputresource:$(PROGRAM)\engine\tsysinfox64.exe -validate_manifest

!include ..\..\Target.mak
