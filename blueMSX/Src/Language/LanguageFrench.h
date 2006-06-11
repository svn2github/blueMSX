/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageFrench.h,v $
**
** $Revision: 1.22 $
**
** $Date: 2006-06-11 19:02:48 $
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
#ifndef LANGUAGE_FRENCH_H
#define LANGUAGE_FRENCH_H

#include "LanguageStrings.h"

void langInitFrench(LanguageStrings* ls)
{
    //----------------------
    // Generic lines
    //----------------------

    ls->textDevice              = "Type:";
    ls->textFilename            = "Fichier:";
    ls->textFile                = "Fichier";
    ls->textNone                = "Aucun";
    ls->textUnknown             = "Unknown";                            // New in 2.5


    //----------------------
    // Warning and Error lines
    //----------------------

    ls->warningTitle             = "blueMSX - Avertissement";
    ls->warningDiscardChanges   = "Voulez-vous ignorer les changements apport�s � cette configuration ?"; 
    ls->warningOverwriteFile    = "Do you want to overwrite the file:"; // New in 2.5
    ls->errorTitle              = "blueMSX - Erreur";
    ls->errorEnterFullscreen    = "Impossible de passer en mode plein �cran.              \n";
    ls->errorDirectXFailed      = "Impossible de cr�er les objets DirectX.              \nUVeuillez s�lectionner GDI � la place.\ndans le menu \"Video\".";
    ls->errorNoRomInZip         = "Il n'y a pas de fichier .rom dans votre archive zip.";
    ls->errorNoDskInZip         = "Il n'y a pas de fichier .dsk dans votre archive zip.";
    ls->errorNoCasInZip         = "Il n'y a pas de fichier .cas dans votre archive zip";
    ls->errorNoHelp             = "Impossible de trouver le fichier d'aide.";
    ls->errorStartEmu           = "Erreur lors du lancement de l'�mulateur.";
    ls->errorPortableReadonly   = "Portable device is readonly";        // New in 2.5


    //----------------------
    // File related lines
    //----------------------

    ls->fileRom                 = "Image-ROM";
    ls->fileAll                 = "Tous les fichiers";
    ls->fileCpuState            = "Image du CPU";
    ls->fileDisk                = "Image-disque";
    ls->fileCas                 = "Image-cassette";


    //----------------------
    // Menu related lines
    //----------------------

    ls->menuNoRecentFiles       = "- pas de fichier r�cent -";
    ls->menuInsert              = "Ins�rer";
    ls->menuEject               = "Ejecter";

    ls->menuCartGameReader      = "Game Reader";                        // New in 2.5
    ls->menuCartIde             = "IDE";                                // New in 2.5
    ls->menuCartBeerIde         = "Beer";                               // New in 2.5
    ls->menuCartGIde            = "GIDE";                               // New in 2.5
    ls->menuCartSunriseIde      = "Sunrise";                            // New in 2.5
    ls->menuCartSCC             = "Cartouche SCC";
    ls->menuCartSCCPlus         = "Cartouche SCC+";
    ls->menuCartFMPac           = "Cartouche FM-PAC";
    ls->menuCartPac             = "Cartouche PAC";
    ls->menuCartHBI55           = "Cartouche Sony HBI-55"; 
    ls->menuCartInsertSpecial   = "Insert Special";                     // New in 2.5
    ls->menuCartMegaRam         = "MegaRAM";                            // New in 2.5
    ls->menuCartExternalRam     = "RAM externe";

    ls->menuDiskInsertNew       = "Insert New Disk Image";              // New in 2.5
    ls->menuDiskDirInsert       = "Ins�rer r�pertoire"; 
    ls->menuDiskAutoStart       = "Reset apr�s insertion";
    ls->menuCartAutoReset       = "Reset apr�s ins�rer/�jecter";

    ls->menuCasRewindAfterInsert= "Rembobiner apr�s insertion";
    ls->menuCasUseReadOnly      = "Utiliser l'image de la cassette en mode lecture seule";
    ls->lmenuCasSaveAs          = "Sauver l'image de la cassette sous...";
    ls->menuCasSetPosition      = "D�finir la position";
    ls->menuCasRewind           = "Rembobiner ";

    ls->menuPrnFormfeed         = "Page suivante"; 

    ls->menuZoomNormal          = "Taille normale";
    ls->menuZoomDouble          = "Double de la taille";
    ls->menuZoomFullscreen      = "Plein �cran";

    ls->menuPropsEmulation      = "Emulation";
    ls->menuPropsVideo          = "Video";
    ls->menuPropsSound          = "Son";
    ls->menuPropsControls       = "Contr�les";
    ls->menuPropsPerformance    = "Performances";
    ls->menuPropsSettings       = "R�glages";
    ls->menuPropsFile           = "Fichiers";
    ls->menuPropsLanguage       = "Langue";
    ls->menuPropsPorts          = "Ports";

    ls->menuVideoChipAutodetect = "D�tection automatique"; 
    ls->menuVideoSource         = "Video Out Source";                   // New in 2.5
    ls->menuVideoSourceDefault  = "No Video Out Source Connected";      // New in 2.5
    ls->menuVideoInSource       = "Video In Source";                    // New in 2.5
    ls->menuVideoInBitmap       = "Bitmap File";                        // New in 2.5

    ls->menuHelpHelp            = "Rubriques d'aide";
    ls->menuHelpAbout           = "A propos de blueMSX";

    ls->menuFileCart            = "Port cartouche";
    ls->menuFileDisk            = "Lecteur de disquettes";
    ls->menuFileCas             = "Lecteur de cassettes";
    ls->menuFilePrn             = "Imprimante"; 
    ls->menuFileLoadState       = "Charger une image du CPU";
    ls->menuFileSaveState       = "Sauver une image du CPU";
    ls->menuFileQLoadState      = "Acc�s instantan� � l'image du CPU";
    ls->menuFileQSaveState      = "Sauvegarde instantan�e de l'image du CPU";
    ls->menuFileCaptureAudio    = "Capture du son";
    ls->menuFileScreenShot      = "Capture d'�cran";
    ls->menuFileExit            = "Quitter";

    ls->menuFileHarddisk        = "Hard Disk";                          // New in 2.5
    ls->menuFileHarddiskNoPesent= "No Controllers Present";             // New in 2.5

    ls->menuRunRun              = "Lancer";
    ls->menuRunPause            = "Pause";
    ls->menuRunStop             = "Arr�t";
    ls->menuRunSoftReset        = "Reset logiciel";
    ls->menuRunHardReset        = "Reset mat�riel";
    ls->menuRunCleanReset       = "Reset g�n�ral";

    ls->menuToolsMachine         = "Editeur de machine";
    ls->menuToolsShortcuts      = "Editeur de raccourcis";
    ls->menuToolsKeyboard       = "Editeur de clavier"; 
    ls->menuToolsMixer          = "M�langeur audio";
    ls->menuToolsDebugger       = "Debugger";               // New in 2.5
    ls->menuToolsTrainer        = "Trainer";                // New in 2.5
    ls->menuToolsTraceLogger    = "Trace Logger";           // New in 2.5

    ls->menuFile                = "Fichiers";
    ls->menuRun                 = "Fonctions";
    ls->menuWindow              = "Fen�tre";
    ls->menuOptions             = "Options";
    ls->menuTools                = "Outils";
    ls->menuHelp                = "Aide";


    //----------------------
    // Dialog related lines
    //----------------------

    ls->dlgOK                   = "OK";
    ls->dlgOpen                 = "Ouvrir";
    ls->dlgCancel               = "Annuler";
    ls->dlgSave                 = "Sauver";
    ls->dlgSaveAs               = "Sauver Sous...";
    ls->dlgRun                  = "Lancer";
    ls->dlgClose                = "Fermer";

    ls->dlgLoadRom              = "blueMSX - Choisissez une rom � charger";
    ls->dlgLoadDsk              = "blueMSX - Choisissez une disquette � charger";
    ls->dlgLoadCas              = "blueMSX - Choisissez une cassette � charger";
    ls->dlgLoadRomDskCas        = "blueMSX - Choisissez un fichier rom, dsk, ou cas � charger";
    ls->dlgLoadRomDesc          = "Choisissez une rom � charger:";
    ls->dlgLoadDskDesc          = "Choisissez une disquette � charger:";
    ls->dlgLoadCasDesc          = "Choisissez une cassette � charger:";
    ls->dlgLoadRomDskCasDesc    = "Choisissez un fichier rom, dsk, ou cas � charger:";
    ls->dlgLoadState            = "Charger une image du CPU";
    ls->dlgSaveState            = "Sauver une image du CPU";
    ls->dlgSaveCassette         = "blueMSX - Sauver une image de cassette";
    ls->dlgInsertRom1           = "Ins�rer une cartouche dans le port 1";
    ls->dlgInsertRom2           = "Ins�rer une cartouche dans le port 2";
    ls->dlgInsertDiskA          = "Ins�rer une disquette dans le lecteur A";
    ls->dlgInsertDiskB          = "Ins�rer une disquette dans le lecteur B";
    ls->dlgInsertHarddisk       = "Insert Hard Disk";                   // New in 2.5
    ls->dlgInsertCas            = "Ins�rer une cassette dans le lecteur";
    ls->dlgRomType              = "Type de Rom:"; 

    ls->dlgTapeTitle            = "blueMSX - position de la bande";
    ls->dlgTapeFrameText        = "Position de la bande";
    ls->dlgTapeCurrentPos       = "Position actuelle";
    ls->dlgTapeTotalTime        = "Dur�e totale";
    ls->dlgTapeCustom           = "Visualiser les Fichiers Personnalis�s";
    ls->dlgTapeSetPosText       = "Position de la cassette:";
    ls->dlgTabPosition          = "Position";
    ls->dlgTabType              = "Type";
    ls->dlgTabFilename          = "Nom du fichier";
    ls->dlgZipReset             = "Reset apr�s l'insertion";

    ls->dlgAboutTitle           = "blueMSX - A propos";

    ls->dlgLangLangText         = "Choisissez la langue utilis�e par blueMSX";
    ls->dlgLangLangTitle        = "blueMSX - Langue";

    ls->dlgAboutAbout           = "A PROPOS\r\n====";
    ls->dlgAboutVersion         = "Version:";
    ls->dlgAboutBuildNumber     = "Build:";
    ls->dlgAboutBuildDate       = "Date:";
    ls->dlgAboutCreat           = "Cr�� par Daniel Vik";
    ls->dlgAboutDevel           = "DEVELOPPEURS\r\n========";
    ls->dlgAboutThanks          = "Un grand merci �\r\n============";
    ls->dlgAboutLisence         = "LICENCE\r\n"
                                  "======\r\n\r\n"
                                  "Ce logiciel est livr� \"tel quel\" sans garantie. "
                                  "L'auteur d�cline toute responsabilit� en cas de dommages "
                                  "li�s � son utilisation.\r\n\r\n"
                                  "Pour plus d'informations, consultez www.bluemsx.com.";

    ls->dlgSavePreview          = "Pr�visualiser"; 
    ls->dlgSaveDate             = "Date:";


    //----------------------
    // Properties related lines
    //----------------------

    ls->propTitle               = "blueMSX - Configuration";
    ls->propEmulation           = "Emulation";
    ls->propVideo               = "Video";
    ls->propSound               = "Son";
    ls->propControls            = "Contr�les";
    ls->propPerformance         = "Performances";
    ls->propSettings             = "R�glages";
    ls->propFile                = "Fichiers"; 
    ls->propPorts               = "Ports";

    ls->propEmuGeneralGB        = "G�n�ral ";
    ls->propEmuFamilyText       = "Type de MSX:";
    ls->propEmuMemoryGB         = "Memoire ";
    ls->propEmuRamSizeText      = "Taille de la RAM:";
    ls->propEmuVramSizeText     = "Taille de la VRAM:";
    ls->propEmuSpeedGB          = "Vitesse de l'�mulation ";
    ls->propEmuSpeedText        = "Vitesse de l'�mulation:";
    ls->propEmuFrontSwitchGB    = "Commutateurs Panasonic "; 
    ls->propEmuFrontSwitch      = " Commutateur frontal"; 
    ls->propEmuFdcTiming        = "Ne pas synchroniser le lecteur de disquettes"; 
    ls->propEmuPauseSwitch      = " Commutateur Pause";
    ls->propEmuAudioSwitch      = " Commutateur MSX-AUDIO"; 
    ls->propVideoFreqText       = "Fr�quence Vid�o:";
    ls->propVideoFreqAuto       = "Auto";
    ls->propSndOversampleText   = "Sur�chantillonner:";
    ls->propSndYkInGB           = "YK-01/YK-10/YK-20 In ";                // New in 2.5
    ls->propSndMidiInGB         = "Entr�e MIDI ";
    ls->propSndMidiOutGB        = "Sortie MIDI ";
    ls->propSndMidiChannel      = "MIDI Channel:";                      // New in 2.5
    ls->propSndMidiAll          = "All";                                // New in 2.5

    ls->propMonMonGB            = "Moniteur ";
    ls->propMonTypeText         = "Type de moniteur:";
    ls->propMonEmuText          = "Emulation du moniteur:";
    ls->propVideoTypeText       = "Mode:";
    ls->propWindowSizeText      = "Taille de la fen�tre:";
    ls->propMonHorizStretch     = " Etirement Horizontal";
    ls->propMonVertStretch      = " Etirement Vertical "; 
    ls->propMonDeInterlace      = " D�-entrelac�";
    ls->propMonBrightness       = "Brillance:";
    ls->propMonContrast         = "Contraste:";
    ls->propMonSaturation       = "Saturation:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = "Lignes de scannage:";
    ls->propMonColorGhosting    = "Modulateur RF"; 
    ls->propMonEffectsGB        = "Effets ";

    ls->propPerfVideoDrvGB      = "Video ";
    ls->propPerfVideoDispDrvText= "Pilote d'affichage:";
    ls->propPerfFrameSkipText   = "Images ignor�es:";
    ls->propPerfAudioDrvGB      = "Audio ";
    ls->propPerfAudioDrvText    = "Pilote audio:";
    ls->propPerfAudioBufSzText  = "Taille du buffer:";
    ls->propPerfEmuGB           = "Emulation ";
    ls->propPerfSyncModeText    = "Synchronisation:";
    ls->propFullscreenResText   = "R�solution plein �cran:"; 

    ls->propSndChipEmuGB        = "Emulation du son ";
    ls->propSndMsxMusic         = " MSX-MUSIC";
    ls->propSndMsxAudio         = " MSX-AUDIO";
    ls->propSndMoonsound        = " Moonsound";
    ls->propSndMt32ToGm         = " Accorder les instruments MT-32 � General MIDI";

    ls->propPortsLptGB          = "Port parall�le ";
    ls->propPortsComGB          = "Ports s�rie ";
    ls->propPortsLptText        = "Port:";
    ls->propPortsCom1Text       = "Port 1:";
    ls->propPortsNone           = "Aucun";
    ls->propPortsSimplCovox     = "SiMPL / Covox DAC"; 
    ls->propPortsFile           = "Imprimer dans fichier"; 
    ls->propPortsComFile        = "Envoyer vers fichier";
    ls->propPortsOpenLogFile    = "Ouvrir un fichier de donn�es"; 
    ls->propPortsEmulateMsxPrn  = "Emulation:"; 

    ls->propSetFileHistoryGB     = "Historique des fichiers ";
    ls->propSetFileHistorySize   = "Nombre d'�l�ments dans l'historique";
    ls->propSetFileHistoryClear  = "Purger l'historique";
    ls->propFileTypes            = " Associer certains types de fichiers avec blueMSX"; 
    ls->propWindowsEnvGB         = "Environnement Windows "; 
    ls->propSetScreenSaver       = " D�sactiver l'�conomiseur d'�cran quand blueMSX est lanc�";
    ls->propDisableWinKeys       = " Fonction MSX automatique pour les touches Windows"; 
    ls->propPriorityBoost       = " Donner � blueMSX une priorit� �lev�e";
    ls->propScreenshotPng       = " Use Portable Network Graphics (.png) screenshots";  // New in 2.5
    ls->propClearHistory         = "D�sirez-vous vraiment purger l'historique ?";
    ls->propOpenRomGB           = "Ouvrir un fichier Rom"; 
    ls->propDefaultRomType      = "Type par d�faut:"; 
    ls->propGuessRomType        = "Deviner le type"; 

    ls->propSettDefSlotGB       = "Glisser et d�poser "; 
    ls->propSettDefSlots        = "Ins�rer la cartouche dans:"; 
    ls->propSettDefSlot         = " Port"; 
    ls->propSettDefDrives       = "Ins�rer la disquette dans:"; 
    ls->propSettDefDrive        = " Lecteur"; 
    
    ls->propThemeGB             = "Th�me ";
    ls->propTheme               = "Th�me";


    //----------------------
    // Dropdown related lines
    //----------------------

    ls->enumVideoMonColor       = "Couleur";
    ls->enumVideoMonGrey        = "Noir et blanc";
    ls->enumVideoMonGreen       = "Monochrome vert";
    ls->enumVideoMonAmber       = "Ambre";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "Aucune";
    ls->enumVideoEmuYc          = "Cable Y/C (pr�cis)";
    ls->enumVideoEmuMonitor     = "Moniteur";
    ls->enumVideoEmuYcBlur      = "Cable Y/C avec bruit (pr�cis)";
    ls->enumVideoEmuComp        = "Composite (flou)";
    ls->enumVideoEmuCompBlur    = "Composite avec bruit (flou)";
    ls->enumVideoEmuScale2x     = "Echelle 2x";
    ls->enumVideoEmuHq2x        = "Hq2x"; 

    ls->enumVideoSize1x         = "Normal - 320x200";
    ls->enumVideoSize2x         = "Double - 640x400";
    ls->enumVideoSizeFullscreen = "Plein �cran";

    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW acc�l.";
    ls->enumVideoDrvDirectDraw  = "DirectDraw";
    ls->enumVideoDrvGDI         = "GDI";

    ls->enumVideoFrameskip0     = "Aucune";
    ls->enumVideoFrameskip1     = "1 image";
    ls->enumVideoFrameskip2     = "2 images";
    ls->enumVideoFrameskip3     = "3 images";
    ls->enumVideoFrameskip4     = "4 images";
    ls->enumVideoFrameskip5     = "5 images";

    ls->enumSoundDrvNone        = "Pas de son";
    ls->enumSoundDrvWMM         = "Pilote WMM";
    ls->enumSoundDrvDirectX     = "Pilote DirectX";

    ls->enumEmuSync1ms          = "Sync sur MSX refresh";
    ls->enumEmuSyncAuto         = "Auto (rapide)";
    ls->enumEmuSyncNone         = "Aucune";
    ls->enumEmuSyncVblank       = "Sync sur PC Vertical Blank";
    ls->enumEmuAsyncVblank      = "Asynchronous PC Vblank";             // New in 2.5

    ls->enumControlsJoyNone     = "Aucune";
    ls->enumControlsJoyMouse    = "Souris";
    ls->enumControlsJoyTetris2Dongle = "Tetris 2 Dongle"; 
    ls->enumControlsJoyTMagicKeyDongle = "MagicKey Dongle";             // New in 2.5
    ls->enumControlsJoy2Button = "2-button Joystick";                   // New in 2.5
    ls->enumControlsJoyGunstick  = "Gun Stick";                         // New in 2.5
    ls->enumControlsJoyAsciiLaser="ASCII Plus-X Terminator Laser";      // New in 2.5
    ls->enumControlsJoyColeco = "ColecoVision Joystick";                // New in 2.5


    //----------------------
    // Configuration related lines
    //----------------------

    ls->confTitle               = "blueMSX - Editeur de machine";
    ls->confConfigText          = "Configuration";
    ls->confSlotLayout          = "Disposition des ports";
    ls->confMemory              = "M�moire";
    ls->confChipEmulation       = "Emulation de la puce";
    ls->confChipExtras          = "Extras";

    ls->confOpenRom             = "Ouvrir une image-ROM";
    ls->confSaveTitle           = "blueMSX - Sauver la configuration";
    ls->confSaveText            = "Voulez-vous remplacer cette configuration ? :";
    ls->confSaveAsTitle         = "Sauver sous..."; 
    ls->confSaveAsMachineName   = "Nom de la machine:";
    ls->confDiscardTitle        = "blueMSX - Configuration";
    ls->confExitSaveTitle       = "blueMSX - Quitter l'�diteur de machine";
    ls->confExitSaveText        = "Voulez-vous ignorer les changements apport�s � la configuration actuelle ?";

    ls->confSlotLayoutGB        = "Disposition des ports ";
    ls->confSlotExtSlotGB       = "Ports externes ";
    ls->confBoardGB             = "Syst�me ";
    ls->confBoardText           = "Type de syst�me:";
    ls->confSlotPrimary         = "Primaire";
    ls->confSlotExpanded        = "Etendu (4 sous-ports)";

    ls->confSlotCart            = "Cartouche";
    ls->confSlot                = "Slot";
    ls->confSubslot             = "Sous-slot";

    ls->confMemAdd              = "Ajouter...";
    ls->confMemEdit             = "Editer...";
    ls->confMemRemove           = "Supprimer";
    ls->confMemSlot             = "Port";
    ls->confMemAddresss         = "Adresses";
    ls->confMemType             = "Type";
    ls->confMemRomImage         = "Image de la ROM";

    ls->confChipVideoGB         = "Video ";
    ls->confChipVideoChip       = "Puce Video:";
    ls->confChipVideoRam        = "Video RAM:";
    ls->confChipSoundGB         = "Son ";

    ls->confCmosGB                = "CMOS "; 
    ls->confCmosEnable            = " Activer la CMOS"; 
    ls->confCmosBattery           = " Utiliser une Pile Charg�e";

    ls->confCpuFreqGB            = "Fr�quence CPU ";
    ls->confZ80FreqText          = "Fr�quence Z80:";
    ls->confR800FreqText         = "Fr�quence R800:";
    ls->confFdcGB                = "Contr�leur de lecteur de disquettes ";
    ls->confCFdcNumDrivesText    = "Nombre de lecteurs:";

    ls->confEditMemTitle        = "blueMSX - Editer le Mapper";
    ls->confEditMemGB           = "Details du Mapper ";
    ls->confEditMemType         = "Type:";
    ls->confEditMemFile         = "Fichier:";
    ls->confEditMemAddress      = "Adresse";
    ls->confEditMemSize         = "Taille";
    ls->confEditMemSlot         = "Port";


    //----------------------
    // Shortcut lines
    //----------------------

    ls->shortcutKey             = "Touche rapide";
    ls->shortcutDescription     = "Raccourci";

    ls->shortcutSaveConfig      = "blueMSX - Sauver la configuration";
    ls->shortcutOverwriteConfig = "Voulez-vous remplacer cette configuration ?:";
    ls->shortcutExitConfig      = "blueMSX - Quitter l'�diteur de raccourcis";
    ls->shortcutDiscardConfig   = "Voulez-vous ignorer les changements apport�s � la configuration actuelle ?";
    ls->shortcutSaveConfigAs    = "blueMSX - Sauver la configuration comme....";
    ls->shortcutConfigName      = "Nom de la configuration:";
    ls->shortcutNewProfile      = "< Nouveau profil >";
    ls->shortcutConfigTitle     = "blueMSX - Editeur de la carte des raccourcis";
    ls->shortcutAssign          = "Assigner";
    ls->shortcutPressText       = "Appuyer sur la (les) touche(s):";
    ls->shortcutScheme          = "Agencement:";
    ls->shortcutCartInsert1     = "Ins�rer une cartouche dans le port 1";
    ls->shortcutCartRemove1     = "Ejecter la cartouche du port 1";
    ls->shortcutCartInsert2     = "Ins�rer la cartouche dans le port 2";
    ls->shortcutCartRemove2     = "Ejecter la cartouche du port 2";
    ls->shortcutSpecialMenu1    = "Acc�der au menu sp�cial pour les cartouches en port 1";
    ls->shortcutSpecialMenu2    = "Acc�der au menu sp�cial pour les cartouches en port 2";
    ls->shortcutCartAutoReset   = "Reset apr�s insertion d'une cartouche";
    ls->shortcutDiskInsertA     = "Ins�rer une disquette dans le lecteur A";
    ls->shortcutDiskDirInsertA  = "Ins�rer un r�pertoire comme disquette A"; 
    ls->shortcutDiskRemoveA     = "Ejecter la disquette du lecteur A";
    ls->shortcutDiskChangeA     = "Changer rapidement de disquette dans le lecteur A";
    ls->shortcutDiskAutoResetA  = "Reset apr�s insertion d'une disquette dans le lecteur A";
    ls->shortcutDiskInsertB     = "Ins�rer une disquette dans le lecteur B";
    ls->shortcutDiskDirInsertB  = "Ins�rer un r�pertoire comme disquette B"; 
    ls->shortcutDiskRemoveB     = "Ejecter la disquette du lecteur B";
    ls->shortcutCasInsert       = "Ins�rer une cassette";
    ls->shortcutCasEject        = "Ejecter la cassette";
    ls->shortcutCasAutorewind   = "Rembobinage automatique ou non de la cassette";
    ls->shortcutCasReadOnly     = "Cassette en mode lecture seule ou non";
    ls->shortcutCasSetPosition  = "D�finir la position";
    ls->shortcutCasRewind       = "Rembobiner la cassette";
    ls->shortcutCasSave         = "Sauver l'image de la cassette";
    ls->shortcutPrnFormFeed     = "Passage � la page suivante"; 
    ls->shortcutCpuStateLoad    = "Charger une image du CPU";
    ls->shortcutCpuStateSave    = "Sauver une image du CPU";
    ls->shortcutCpuStateQload   = "Acc�s instantan� � l'image du CPU";
    ls->shortcutCpuStateQsave   = "Sauvegarde instantan�e de l'image du CPU";
    ls->shortcutAudioCapture    = "D�marrer/arr�ter la capture du son";
    ls->shortcutScreenshotOrig  = "Capture d'�cran";
    ls->shortcutScreenshotSmall = "Petite capture d'�cran sans filtre";
    ls->shortcutScreenshotLarge = "Grande capture d'�cran sans filtre";
    ls->shortcutQuit            = "Quitter blueMSX";
    ls->shortcutRunPause        = "D�marrer/geler l'�mulation";
    ls->shortcutStop            = "Arr�ter l'�mulation";
    ls->shortcutResetHard       = "Reset mat�riel";
    ls->shortcutResetSoft       = "Reset logiciel";
    ls->shortcutResetClean      = "Reset g�n�ral";
    ls->shortcutSizeSmall       = "Passer en mode fen�tre normal";
    ls->shortcutSizeNormal      = "Passer en mode double de la fen�tre";
    ls->shortcutSizeFullscreen  = "Passer en mode plein �cran";
    ls->shortcutSizeMinimized   = "R�duire la fen�tre";
    ls->shortcutToggleFullscren = "Balance mode fen�tre/mode plein �cran";
    ls->shortcutVolumeIncrease  = "Augmenter le volume sonore";
    ls->shortcutVolumeDecrease  = "Diminuer le volume sonore";
    ls->shortcutVolumeMute      = "Arr�ter le son";
    ls->shortcutVolumeStereo    = "Balance mono/st�r�o";
    ls->shortcutSwitchMsxAudio  = "Actionner le commutateur MSX-AUDIO";
    ls->shortcutSwitchFront     = "Actionner le commutateur frontal Panasonic";
    ls->shortcutSwitchPause     = "Actionner le commutateur Pause";
    ls->shortcutToggleMouseLock = "Activer/d�sactiver le blocage de la souris";
    ls->shortcutEmuSpeedMax     = "Vitesse maximale d'�mulation";
    ls->shortcutEmuSpeedToggle  = "Balance vitesse maximale d'�mulation";
    ls->shortcutEmuSpeedNormal  = "Vitesse normale d'�mulation";
    ls->shortcutEmuSpeedInc     = "Augmenter la vitesse d'�mulation";
    ls->shortcutEmuSpeedDec     = "Diminuer la vitesse d'�mulation";
    ls->shortcutThemeSwitch     = "Changer de th�me";
    ls->shortcutShowEmuProp     = "Acc�der au menu Emulation";
    ls->shortcutShowVideoProp   = "Acc�der au menu Video";
    ls->shortcutShowAudioProp   = "Acc�der au menu Son";
    ls->shortcutShowCtrlProp    = "Acc�der au menu Contr�les";
    ls->shortcutShowPerfProp    = "Acc�der au menu Performances";
    ls->shortcutShowSettProp    = "Acc�der au menu R�glages";
    ls->shortcutShowPorts       = "Acc�der au menu Ports";
    ls->shortcutShowLanguage    = "Acc�der au menu Langue";
    ls->shortcutShowMachines    = "Acc�der � l'�diteur de machines";
    ls->shortcutShowShortcuts   = "Acc�der � l'�diteur de raccourcis";
    ls->shortcutShowKeyboard    = "Acc�der � l'�diteur de clavier"; 
    ls->shortcutShowMixer       = "Acc�der au M�langeur audio";
    ls->shortcutShowDebugger    = "Acc�der au Debugger"; 
    ls->shortcutShowTrainer     = "Acc�der au Trainer"; 
    ls->shortcutShowHelp        = "Acc�der aux rubriques d'aide ";
    ls->shortcutShowAbout       = "Voir la rubrique A propos de blueMSX ";
    ls->shortcutShowFiles       = "Acc�der au menu Fichiers";
    ls->shortcutToggleSpriteEnable = "Montrer/Cacher les sprites";
    ls->shortcutToggleFdcTiming = "Synchroniser ou non le lecteur de disquettes"; 
    ls->shortcutToggleCpuTrace  = "Valider/Invalider la trace du CPU";


    //----------------------
    // Keyboard config lines
    //----------------------

    ls->keyconfigSelectedKey    = "Touche MSX s�lectionn�e:"; 
    ls->keyconfigMappedTo       = "Assign�e � la touche PC :"; 
    ls->keyconfigMappingScheme  = "Configuration du clavier:"; 
};

#endif
