/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Arch/ArchDialog.h,v $
**
** $Revision: 1.2 $
**
** $Date: 2004-12-06 08:04:33 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2004 Daniel Vik
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
******************************************************************************
*/
#ifndef ARCH_DIALOG_H
#define ARCH_DIALOG_H

char* archDirOpen(char* title, char* defaultDir);
char* archFileOpen(char* title, char* fileDescription, char* defaultDir, 
                   char* extensions, int* selectedExtension, char* defautExtension);
char* archFileRomOpen(char* title, char* fileDescription, char* defaultDir, 
                      char* extensions, int* selectedExtension, char* defautExtension, RomType* romType);
char* archFileSave(char* title, char* fileDescription, char* defaultDir, 
                   char* extensions, int* selectedExtension);
void archFileFromZipDialog(ZipFileDlgInfo* dlgInfo);

void archShowPropertiesDialog(PropPage page);
void archShowLanguageDialog();
void archShowHelpDialog();
void archShowAboutDialog();
void archShowCassettePosDialog();
void archShowShortcutsEditor();
void archShowMachineEditor();

#endif
