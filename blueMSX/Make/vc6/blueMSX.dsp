# Microsoft Developer Studio Project File - Name="blueMSX" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=blueMSX - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "blueMSX.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "blueMSX.mak" CFG="blueMSX - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "blueMSX - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "blueMSX - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "blueMSX - Win32 Final" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "blueMSX - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\..\Src\Bios" /I "..\..\..\Src\BuildInfo" /I "..\..\..\Src\Common" /I "..\..\..\Src\IODevice" /I "..\..\..\Src\Language" /I "..\..\..\Src\Memory" /I "..\..\..\Src\Resources" /I "..\..\..\Src\SoundChips" /I "..\..\..\Src\VideoRender" /I "..\..\..\Src\VideoChips" /I "..\..\..\Src\Win32" /I "..\..\Src\Bios" /I "..\..\Src\BuildInfo" /I "..\..\Src\Common" /I "..\..\Src\IODevice" /I "..\..\Src\Language" /I "..\..\Src\Memory" /I "..\..\Src\Resources" /I "..\..\Src\SoundChips" /I "..\..\Src\VideoChips" /I "..\..\Src\VideoRender" /I "..\..\Src\Win32" /I "..\..\Src\Z80" /I "..\..\Src\Unzip" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "WINDOWS" /D "LSB_FIRST" /D "SOUND" /D "DISK" /D "FMSX" /D "PROPERTIES_LOCAL_INI_FILE" /D WINVER=0x0500 /FR /YX /FD /Zm800 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib dxguid.lib winmm.lib ComCtl32.Lib ddraw.lib dsound.lib dinput.lib ..\..\Src\Unzip\zlibstat.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "blueMSX - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\..\..\Src\Bios" /I "..\..\..\Src\BuildInfo" /I "..\..\..\Src\Common" /I "..\..\..\Src\IODevice" /I "..\..\..\Src\Language" /I "..\..\..\Src\Memory" /I "..\..\..\Src\Resources" /I "..\..\..\Src\SoundChips" /I "..\..\..\Src\VideoRender" /I "..\..\..\Src\VideoChips" /I "..\..\..\Src\Win32" /I "..\..\Src\Bios" /I "..\..\Src\BuildInfo" /I "..\..\Src\Common" /I "..\..\Src\IODevice" /I "..\..\Src\Language" /I "..\..\Src\Memory" /I "..\..\Src\Resources" /I "..\..\Src\SoundChips" /I "..\..\Src\VideoChips" /I "..\..\Src\VideoRender" /I "..\..\Src\Win32" /I "..\..\Src\Z80" /I "..\..\Src\Unzip" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "WINDOWS" /D "_MBCS" /D "LSB_FIRST" /D "SOUND" /D "DISK" /D "FMSX" /D "PROPERTIES_LOCAL_INI_FILE" /D WINVER=0x0500 /FR /YX /FD /GZ /Zm800 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib dxguid.lib winmm.lib ComCtl32.Lib ddraw.lib dsound.lib dinput.lib ..\..\Src\Unzip\zlibstat.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "blueMSX - Win32 Final"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "blueMSX___Win32_Final"
# PROP BASE Intermediate_Dir "blueMSX___Win32_Final"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Final"
# PROP Intermediate_Dir "Final"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "Bios" /I "BuildInfo" /I "Common" /I "IODevice" /I "Language" /I "Memory" /I "Resources" /I "SoundChips" /I "Unzip" /I "VideoRender" /I "VideoChips" /I "Win32" /I "Z80" /I "Zlib" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "WINDOWS" /D "LSB_FIRST" /D "SOUND" /D "DISK" /D "FMSX" /D "PROPERTIES_LOCAL_INI_FILE" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\Src\Bios" /I "..\..\Src\BuildInfo" /I "..\..\Src\Common" /I "..\..\Src\IODevice" /I "..\..\Src\Language" /I "..\..\Src\Memory" /I "..\..\Src\Resources" /I "..\..\Src\SoundChips" /I "..\..\Src\VideoChips" /I "..\..\Src\VideoRender" /I "..\..\Src\Win32" /I "..\..\Src\Z80" /I "..\..\Src\Unzip" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "WINDOWS" /D "LSB_FIRST" /D "SOUND" /D "DISK" /D "FMSX" /D "PROPERTIES_LOCAL_INI_FILE" /D WINVER=0x0500 /YX /FD /Zm800 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib dxguid.lib winmm.lib ComCtl32.Lib ddraw.lib dsound.lib dinput.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib dxguid.lib winmm.lib ComCtl32.Lib ddraw.lib dsound.lib dinput.lib ..\..\Src\Unzip\zlibstat.lib /nologo /subsystem:windows /machine:I386
# Begin Special Build Tool
OutDir=.\Final
TargetName=blueMSX
SOURCE="$(InputPath)"
PostBuild_Desc=Pack executable
PostBuild_Cmds=upx --best $(OutDir)\$(TargetName).exe
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "blueMSX - Win32 Release"
# Name "blueMSX - Win32 Debug"
# Name "blueMSX - Win32 Final"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Bios"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Src\Bios\Patch.c
# End Source File
# End Group
# Begin Group "BuildInfo"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Src\BuildInfo\build_number.h
# End Source File
# End Group
# Begin Group "Common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Src\Common\AudioMixer.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Common\AudioMixer.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Common\Machine.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Common\Machine.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Common\MSX.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Common\MSX.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Common\MsxTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Common\RomMapper.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Common\RomMapper.h
# End Source File
# End Group
# Begin Group "IODevice"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Src\IoDevice\Casette.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\IoDevice\Casette.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\IoDevice\Disk.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\IoDevice\Disk.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\IoDevice\DiskUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\IoDevice\JoystickIO.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\IoDevice\JoystickIO.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\IoDevice\RTC.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\IoDevice\RTC.h
# End Source File
# End Group
# Begin Group "Language"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Src\Language\Language.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Language\Language.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Language\LanguageDutch.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Language\LanguageEnglish.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Language\LanguageFrench.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Language\LanguageItalian.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Language\LanguageJapanese.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Language\LanguagePortuguese.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Language\LanguageSpannish.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Language\LanguageStrings.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Language\LanguageSwedish.h
# End Source File
# End Group
# Begin Group "Memory"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Src\Memory\IoPort.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\IoPort.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\MegaromCartridge.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\MegaromCartridge.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\ramMapper.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\ramMapper.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\ramNormal.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\ramNormal.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\RomLoader.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\RomLoader.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperASCII16.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperASCII16.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperASCII16nf.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperASCII16nf.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperASCII16sram.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperASCII16sram.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperASCII8.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperASCII8.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperASCII8sram.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperASCII8sram.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperBasic.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperBasic.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperBunsetu.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperBunsetu.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperCrossBlaim.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperCrossBlaim.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperDisk.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperDisk.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperF4device.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperF4device.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperFMPAC.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperFMPAC.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperGameMaster2.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperGameMaster2.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperHalnote.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperHalnote.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperHarryFox.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperHarryFox.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperHolyQuran.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperHolyQuran.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperKanji.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperKanji.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperKanji12.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperKanji12.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperKoei.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperKoei.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperKonami4.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperKonami4.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperKonami4nf.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperKonami4nf.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperKonami5.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperKonami5.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperKorean126.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperKorean126.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperKorean80.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperKorean80.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperKorean90.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperKorean90.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperLodeRunner.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperLodeRunner.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperMegaRAM.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperMegaRAM.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperMsxAudio.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperMsxAudio.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperMsxDos2.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperMsxDos2.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperNational.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperNational.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperNormal.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperNormal.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperPAC.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperPAC.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperPanasonic.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperPanasonic.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperPlain.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperPlain.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperRType.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperRType.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperSCCplus.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperSCCplus.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperStandard.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\romMapperStandard.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\SlotManager.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\SlotManager.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\sramLoader.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\sramLoader.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\sramMapperMatsuchita.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\sramMapperMatsuchita.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\sramMapperS1985.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Memory\sramMapperS1985.h
# End Source File
# End Group
# Begin Group "Resources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Src\Resources\blueMSX.rc
# End Source File
# Begin Source File

SOURCE=..\..\Src\Resources\Resource.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Resources\resrc1.h
# End Source File
# End Group
# Begin Group "SoundChips"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Src\SoundChips\AY8910.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\SoundChips\AY8910.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\SoundChips\Fmopl.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\SoundChips\Fmopl.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\SoundChips\KeyClick.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\SoundChips\KeyClick.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\SoundChips\Moonsound.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Src\SoundChips\Moonsound.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\SoundChips\OpenMsxYM2413.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Src\SoundChips\OpenMsxYM2413.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\SoundChips\OpenMsxYMF262.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Src\SoundChips\OpenMsxYMF262.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\SoundChips\OpenMsxYMF278.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Src\SoundChips\OpenMsxYMF278.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\SoundChips\SCC.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\SoundChips\SCC.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\SoundChips\Y8950.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\SoundChips\Y8950.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\SoundChips\YM2413.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Src\SoundChips\YM2413.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\SoundChips\Ymdeltat.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\SoundChips\Ymdeltat.h
# End Source File
# End Group
# Begin Group "VideoChips"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Src\VideoChips\Common.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\VideoChips\SpriteLine.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\VideoChips\V9938.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\VideoChips\V9938.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\VideoChips\VDP.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\VideoChips\VDP.h
# End Source File
# End Group
# Begin Group "VideoRender"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Src\VideoRender\Scale2x.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\VideoRender\Scale3x.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\VideoRender\Scalebit.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\VideoRender\Scalebit.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\VideoRender\VideoRender.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\VideoRender\VideoRender.h
# End Source File
# End Group
# Begin Group "Win32"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Src\Win32\Win32.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32directX.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32directx.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32directXSound.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32directXSound.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32file.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32file.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32FileHistory.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32FileHistory.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32Help.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32Help.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32joystick.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32joystick.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32keyboard.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32keyboard.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32machineConfig.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32machineConfig.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32Menu.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32Menu.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32MouseEmu.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32MouseEmu.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32properties.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32Properties.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32ScreenShot.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32ScreenShot.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32snd.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32Sound.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32StatusBar.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32StatusBar.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32SystemTime.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32Timer.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32Timer.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32ToolBar.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32ToolBar.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32WaveCapture.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32WaveCapture.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32wmmSound.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Win32\Win32wmmSound.h
# End Source File
# End Group
# Begin Group "Z80"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Src\Z80\Codes.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Z80\CodesCB.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Z80\CodesED.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Z80\CodesXCB.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Z80\CodesXX.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Z80\Tables.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Z80\Z80.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Z80\Z80.h
# End Source File
# End Group
# Begin Group "Unzip"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Src\Unzip\crypt.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Unzip\ioapi.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Unzip\ioapi.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Unzip\iowin32.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Unzip\iowin32.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Unzip\minizip.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Unzip\unzip.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Unzip\unzip.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Unzip\zconf.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Unzip\zip.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Unzip\zip.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Unzip\ziphelper.c
# End Source File
# Begin Source File

SOURCE=..\..\Src\Unzip\ziphelper.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\Unzip\zlib.h
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
