/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageFrench.h,v $
**
** $Revision: 1.6 $
**
** $Date: 2005-01-03 23:12:41 $
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
    ls->statusBarStopped        = "  Arr�t�";
    ls->statusBarPaused         = "  En Pause";
    ls->statusBarRunning        = "  En marche";

    ls->menuHardReset           = "Hard Reset";
    ls->menuSoftReset           = "Soft Reset";

    ls->menuCartInsert          = "Ins�rer";
    ls->menuCartRemove          = "Ejecter";
    ls->menuCartAutoReset       = "Reset apr�s ins�rer/�jecter";
    ls->menuCartNoRecentFiles   = "- pas de fichier r�cent -";
    ls->menuCartFMPac           = "Cartouche FM-PAC";
    ls->menuCartPac             = "Cartouche PAC";
    ls->menuCartSpecial         = "Sp�cial";

    ls->menuDiskInsert          = "Ins�rer";
    ls->menuDiskEject           = "Ejecter";
    ls->menuDiskAutoStart       = "Reset apr�s insertion";
    ls->menuDiskNoRecentFiles   = "- pas de fichier r�cent -";

    ls->menuCasInsert           = "Ins�rer";
    ls->menuCasEject            = "Ejecter";
    ls->menuCasSetPosition      = "D�finir la position";
    ls->menuCasRewind           = "Rembobiner ";
    ls->menuCasNoRecentFiles    = "- pas de fichier r�cent -";

    ls->menuZoomNormal          = "Taille normale";
    ls->menuZoomDouble          = "Double de la taille";
    ls->menuZoomFullscreen      = "Plein �cran";

    ls->menuPropsEmulation      = "Emulation";
    ls->menuPropsVideo          = "Video";
    ls->menuPropsSound          = "Son";
    ls->menuPropsControls       = "Contr�les";
    ls->menuPropsPerformance    = "Performances";
    ls->menuPropsLanguage       = "Langue";

    ls->menuHelpHelp            = "Rubriques d'aide";
    ls->menuHelpAbout           = "A propos de blueMSX";

    ls->menuFileCart1           = "Port cartouche 1";
    ls->menuFileCart2           = "Port cartouche 2";
    ls->menuFileDiskA           = "Lecteur de disquettes A";
    ls->menuFileDiskB           = "Lecteur de disquettes B";
    ls->menuFileCas             = "Lecteur de cassettes";
    ls->menuFileLoadState       = "Charger une image du CPU";
    ls->menuFileSaveState       = "Sauver une image du CPU";
    ls->menuFileQLoadState      = "Acc�s instantan� � l'image du CPU";
    ls->menuFileQSaveState      = "Sauvegarde instantan�e de l'image du CPU";
    ls->menuFileCaptureAudio    = "Capture du son";
    ls->menuFileScreenShot      = "Capture d'�cran";
    ls->menuFileExit            = "Quitter";

    ls->menuRunRun              = "Lancer";
    ls->menuRunPause            = "Pause";
    ls->menuRunStop             = "Arr�t";
    ls->menuRunSoftReset        = "Reset logiciel";
    ls->menuRunHardReset        = "Reset mat�riel";
    ls->menuRunCleanReset       = "Reset g�n�ral";

    ls->menuFile                = "Fichiers";
    ls->menuRun                 = "Fonctions";
    ls->menuWindow              = "Fen�tre";
    ls->menuOptions             = "Options";
    ls->menuHelp                = "Aide";

    ls->errorTitle              = "blueMSX - Erreur";
    ls->errorEnterFullscreen    = "Impossible de passer en mode plein �cran.              \n";
    ls->errorDirectXFailed      = "Impossible de cr�er les objets DirectX.              \nUVeuillez s�lectionner GDI � la place.\ndans le menu \"Video\".";
    ls->errorNoRomInZip         = "Il n'y a pas de fichier .rom dans votre archive zip.";
    ls->errorNoDskInZip         = "Il n'y a pas de fichier .dsk dans votre archive zip.";
    ls->errorNoCasInZip         = "Il n'y a pas de fichier .cas dans votre archive zip";
    ls->errorNoHelp             = "Impossible de trouver le fichier d'aide.";
    ls->errorStartEmu           = "Erreur lors du lancement de l'�mulateur.";

    ls->tooltipReset            = "Reset MSX";
    ls->tooltipCart1            = "Ins�rer une cartouche dans le port 1";
    ls->tooltipCart2            = "Ins�rer une cartouche dans le port 2";
    ls->tooltipDiskA            = "Ins�rer une disquette dans le lecteur A";
    ls->tooltipDiskB            = "Ins�rer une disquette dans le lecteur B";
    ls->tooltipCas              = "Ins�rer une cassette dans le lecteur";
    ls->tooltipStart            = "D�marrer l'�mulation";
    ls->tooltipResume           = "Restaurer l'�mulation";
    ls->tooltipPause            = "Mettre en pause";
    ls->tooltipWindowSize       = "Choisir la taille de la fen�tre";
    ls->tooltipProperties       = "Modifier la configuration";
    ls->tooltipHelp             = "Ouvrir l'aide";

    ls->dlgMainWindow           = "  blueMSX";
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
    ls->dlgInsertRom1           = "Ins�rer une cartouche dans le port 1";
    ls->dlgInsertRom2           = "Ins�rer une cartouche dans le port 2";
    ls->dlgInsertDiskA          = "Ins�rer une disquette dans le lecteur A";
    ls->dlgInsertDiskB          = "Ins�rer une disquette dans le lecteur B";
    ls->dlgInsertCas            = "Ins�rer une cassette dans le lecteur";

    ls->dlgOK                   = "OK";
    ls->dlgOpen                 = "Ouvrir";
    ls->dlgCancel               = "Annuler";

    ls->dlgTapeTitle            = "blueMSX - position de la bande";
    ls->dlgTapeFrameText        = "Position de la bande";
    ls->dlgTapeCurrentPos       = "Position actuelle";
    ls->dlgTapeTotalTime        = "Dur�e totale";

    ls->dlgZipReset             = "Reset apr�s l'insertion";

    ls->dlgAboutTitle           = "blueMSX - A propos";

    ls->dlgJoyTitle1            = "blueMSX - Joystick touches A";
    ls->dlgJoyTitle2            = "blueMSX - Joystick touches B";
    ls->dlgJoyUpText            = "Haut";
    ls->dlgJoyDownText          = "Bas";
    ls->dlgJoyLeftText          = "Gauche";
    ls->dlgJoyRightText         = "Droite";
    ls->dlgJoyButton1Text       = "Bouton 1";
    ls->dlgJoyButton2Text       = "Bouton 2";
    ls->dlgJoyGB                = "Configuration des touches";

    ls->dlgLangLangText         = "Choisissez la langue utilis�e par blueMSX";
    ls->dlgLangLangTitle        = "blueMSX - Langue";

    ls->propTitle               = "blueMSX - Configuration";
    ls->propEmulation           = "Emulation";
    ls->propVideo               = "Video";
    ls->propSound               = "Son";
    ls->propControls            = "Contr�les";
    ls->propPerformance         = "Performances";

    ls->propEmuGeneralGB        = "G�n�ral ";
    ls->propEmuFamilyText       = "Type de MSX:";
    ls->propEmuMemoryGB         = "Memoire ";
    ls->propEmuRamSizeText      = "Taille de la RAM:";
    ls->propEmuVramSizeText     = "Taille de la VRAM:";
    ls->propEmuSpeedGB          = "Vitesse de l'�mulation ";
    ls->propEmuSpeedText        = "Vitesse de l'�mulation:";

    ls->propMonMonGB            = "Moniteur ";
    ls->propMonTypeText         = "Type de moniteur:";
    ls->propMonEmuText          = "Emulation du moniteur:";
    ls->propVideoYypeText       = "Mode:";
    ls->propWindowSizeText      = "Taille de la fen�tre:";

    ls->propPerfVideoDrvGB      = "Video ";
    ls->propPerfVideoDispDrvText= "Pilote d'affichage:";
    ls->propPerfFrameSkipText   = "Images ignor�es:";
    ls->propPerfAudioDrvGB      = "Audio ";
    ls->propPerfAudioDrvText    = "Pilote audio:";
    ls->propPerfAudioBufSzText  = "Taille du buffer:";
    ls->propPerfEmuGB           = "Emulation ";
    ls->propPerfSyncModeText    = "Synchronisation:";

    ls->propSndChipEmuGB        = "Emulation du son ";
    ls->propSndMixerGB          = "M�langeur audio ";
    ls->propSndMonoText         = "mono";
    ls->propSndStereoText       = "st�r�o";
    ls->propSndMsxMusicText     = " MSX-MUSIC";
    ls->propSndMsxAudioText     = " MSX-AUDIO";
    ls->propSndMsxMasterText    = "MASTER";

    ls->propJoyPort1GB          = "Port #1 ";
    ls->propJoyPort2GB          = "Port #2 ";
    ls->propJoyAutofireText     = "Tir auto:";
    ls->propJoyKeysetGB         = "Configuration des touches Joystick ";
    ls->propJoyKeyest1          = "Jeu de touches A";
    ls->propJoyKeyest2          = "Jeu de touches B";

    ls->enumVideoMonColor       = "Couleur";
    ls->enumVideoMonGrey        = "Noir et blanc";
    ls->enumVideoMonGreen       = "Monochrome vert";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "Aucune";
    ls->enumVideoEmuYc          = "Cable Y/C (pr�cis)";
    ls->enumVideoEmuYcBlur      = "Cable Y/C avec bruit (pr�cis)";
    ls->enumVideoEmuComp        = "Composite (flou)";
    ls->enumVideoEmuCompBlur    = "Composite avec bruit (flou)";
    ls->enumVideoEmuScale2x     = "Echelle 2x";

    ls->enumVideoSize1x         = "Normal - 320x200";
    ls->enumVideoSize2x         = "Double - 640x400";
    ls->enumVideoSizeFullscreen = "Plein �cran";

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

    ls->enumEmuSync1ms          = "1ms (meilleure)";
    ls->enumEmuSyncAuto         = "Auto (rapide)";

    ls->enumControlsJoyNone     = "Aucune";
    ls->enumControlsJoyNumpad   = "Pav� num�rique";
    ls->enumControlsJoyKeysetA  = "Jeu de touches A";
    ls->enumControlsJoyKeysetB  = "Jeu de touches B";
    ls->enumControlsJoyPCjoy1   = "PC joystick #1";
    ls->enumControlsJoyPCjoy2   = "PC joystick #2";
    ls->enumControlsJoyMouse    = "Souris";

    ls->enumControlsAfOff       = "Arr�t�";
    ls->enumControlsAfSlow      = "Lent";
    ls->enumControlsAfMedium    = "Moyen";
    ls->enumControlsAfFast      = "Rapide";

    ls->dlgAboutAbout           = "A PROPOS\r\n====";
    ls->dlgAboutLisence         = "LICENCE\r\n"
                                  "======\r\n\r\n"
                                  "Ce logiciel est livr� \"tel quel\" sans garantie. "
                                  "L'auteur d�cline toute responsabilit� en cas de dommages "
                                  "li�s � son utilisation.\r\n\r\n"
                                  "Pour plus d'informations, consultez www.bluemsx.com.";


    ls->dlgAboutDevel           = "DEVELOPPEURS\r\n========";
    ls->dlgAboutThanks          = "Un grand merci �\r\n============";
    ls->dlgAboutVersion         = "Version:";
    ls->dlgAboutBuildNumber     = "Build:";
    ls->dlgAboutBuildDate       = "Date:";
    ls->dlgAboutCreat           = "Cr�� par Daniel Vik";

    // New entries
    ls->menuTools                = "Outils";
    ls->menuToolsMachine         = "Editeur de machine";
    ls->menuPropsSettings        = "R�glages";
    ls->menuCasRewindAfterInsert = "Rembobiner apr�s insertion";
    ls->menuCasUseReadOnly       = "Utiliser l'image de la cassette en mode lecture seule";
    ls->lmenuCasSaveAs           = "Sauver l'image de la cassette sous...";

    ls->dlgSaveCassette          = "blueMSX - Sauver une image de cassette";
    ls->dlgTapeCustom            = "Visualiser les Fichiers Personnalis�s";
    ls->dlgTapeSetPosText        = "Position de la cassette:";
    ls->dlgTabPosition           = "Position";
    ls->dlgTabType               = "Type";
    ls->dlgTabFilename           = "Nom du fichier";

    ls->propSettings             = "R�glages";

    ls->propSetFileHistoryGB     = "Historique des fichiers ";
    ls->propSetFileHistorySize   = "Nombre d'�l�ments dans l'historique";
    ls->propSetFileHistoryClear  = "Purger l'historique";
    ls->propSetScreenSaverGB     = "Economiseur d'�cran ";
    ls->propSetScreenSaver       = " D�sactiver l'�conomiseur d'�cran quand blueMSX est lanc�";

    ls->confTitle                = "blueMSX - Editeur de machine";
    ls->confSave                 = "Sauver";
    ls->confSaveAs               = "Sauver Sous...";
    ls->confRun                  = "Lancer";
    ls->confClose                = "Fermer";
    ls->confConfigText           = "Configuration";
    ls->confSlotLayout           = "Disposition des ports";
    ls->confMemory               = "M�moire";
    ls->confChipEmulation        = "Emulation de la puce";

    ls->confSlotLayoutGB         = "Disposition des ports ";
    ls->confSlotExtSlotGB        = "Ports externes ";
    ls->confSlotSlot0            = "Port 0";
    ls->confSlotSlot1            = "Port 1";
    ls->confSlotSlot2            = "Port 2";
    ls->confSlotSlot3            = "Port 3";
    ls->confSlotCart1            = "Cartouche 1:";
    ls->confSlotCart2            = "Cartouche 2:";
    ls->confSlotPrimary          = "Primaire";
    ls->confSlotExpanded         = "Etendu (4 sous-ports)";

    ls->confMemAdd               = "Ajouter...";
    ls->confMemEdit              = "Editer...";
    ls->confMemRemove            = "Supprimer";
    ls->confMemSlot              = "Port";
    ls->confMemAddresss          = "Adresses";
    ls->confMemType              = "Type";
    ls->confMemRomImage          = "Image de la ROM";

    ls->confChipVideoGB          = "Video ";
    ls->confChipVideoChip        = "Puce Video:";
    ls->confChipVideoRam         = "Video RAM:";
    ls->confChipSoundGB          = "Son ";

    ls->confSaveTitle            = "blueMSX - Sauver la configuration";
    ls->confSaveText             = "Voulez-vous remplacer cette configuration ? :";

    ls->slotEditMemTitle         = "blueMSX - Editer le Mapper";
    ls->slotEditMemGB            = "Details du Mapper ";
    ls->slotEditMemType          = "Type:";
    ls->slotEditMemFile          = "Fichier:";
    ls->slotEditMemAddress       = "Addresse";
    ls->slotEditMemSize          = "Taille";
    ls->slotEditMemSlot          = "Port";

    ls->confDiscardTitle         = "blueMSX - Configuration";
    ls->confExitSaveTitle        = "blueMSX - Quitter l'�diteur de machine";
    ls->confExitSaveText         = "Voulez-vous ignorer les changements apport�s � la configuration actuelle ?";


    ls->confSaveAsTitle          = "blueMSX - Sauver la configuration comme...";
    ls->confSaveAsMachineName    = "Nom de la machine:";
    
    ls->confEditMemInternalRoms  = "blueMSX - Roms internes"; 


    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypesGB          = "Types de fichiers ";
    ls->propFileTypes            = " Associer certains types de fichiers avec blueMSX"; 
    ls->propDisableWinKeys       = " Fonction MSX automatique pour les touches Windows"; 
    ls->propWindowsEnvGB         = "Environnement Windows "; 

    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW acc�l.";
    ls->enumVideoDrvDirectDrawHWSys = "DirectDraw mix."; 
    ls->propMonHorizStretch      = " Etirement Horizontal";
    ls->propClearHistory         = "D�sirez-vous vraiment purger l'historique ?";
    ls->propEmuFrontSwitchGB     = "Commutateurs Panasonic "; 
    ls->propEmuFrontSwitch      = " Commutateur frontal"; 
    ls->propEmuAudioSwitch       = " Commutateur MSX-AUDIO"; 
    ls->propMonVertStretch       = " Etirement Vertical "; 

    ls->dlgCmosGB                = "CMOS "; 
    ls->dlgCmosEnable            = " Activer la CMOS"; 
    ls->dlgCmosBattery           = " Utiliser une Pile Charg�e";

    ls->menuCartSnatcher        = "Cartouche The Snatcher";
    ls->menuCartSdSnatcher      = "Cartouche SD-Snatcher";
    ls->menuCartSCCMirrored     = "Cartouche SCC Mirrored";
    ls->menuCartSCCExpanded     = "Cartouche SCC Expanded";
    ls->menuCartSCCPlus         = "Cartouche SCC+";
    ls->menuCartSCC             = "Cartouche SCC";
    
    ls->warningTitle             = "blueMSX - Avertissement";
    ls->tooltipPause            = "Arr�t l'�mulation";


    // New entries in 1.5.1
    ls->enumControlsJoyKeyset   = "Jeu de touches";    
    ls->propJoyConfigKeyset     = "Configurer les touches";
    ls->propJoyControlText      = "Contr�le:";
    ls->propJoyButtonText       = "Bouton";
    ls->propJoyButtonAText      = "Bouton A:";
    ls->propJoyButtonBText      = "Bouton B:";

    ls->menuToolsShortcuts      = "Editeur de raccourcis";

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
    ls->shortcutCartAutoReset   = "Reset apr�s insertion d'une cartouche";
    ls->shortcutDiskInsertA     = "Ins�rer une disquette dans le lecteur A";
    ls->shortcutDiskRemoveA     = "Ejecter la disquette du lecteur A";
    ls->shortcutDiskChangeA     = "Changer rapidement de disquette dans le lecteur A";
    ls->shortcutDiskAutoResetA  = "Reset apr�s insertion d'une disquette dans le lecteur A";
    ls->shortcutDiskInsertB     = "Ins�rer une disquette dans le lecteur B";
    ls->shortcutDiskRemoveB     = "Ejecter la disquette du lecteur B";
    ls->shortcutCasInsert       = "Ins�rer une cassette";
    ls->shortcutCasEject        = "Ejecter la cassette";
    ls->shortcutCasAutorewind   = "Rembobinage automatique ou non de la cassette";
    ls->shortcutCasReadOnly     = "Cassette en mode lecture seule ou non";
    ls->shortcutCasSetPosition  = "D�finir la position";
    ls->shortcutCasRewind       = "Rembobiner la cassette";
    ls->shortcutCasSave         = "Sauver l'image de la cassette";
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
    ls->shortcutToggleFullscren = "Balance mode fen�tre/mode plein �cran";
    ls->shortcutVolumeIncrease  = "Augmenter le volume sonore";
    ls->shortcutVolumeDecrease  = "Diminuer le volume sonore";
    ls->shortcutVolumeMute      = "Arr�ter le son";
    ls->shortcutSwitchMsxAudio  = "Actionner le commutateur MSX-AUDIO";
    ls->shortcutSwitchFront     = "Actionner le commutateur frontal Panasonic";
    ls->shortcutToggleMouseLock = "Activer/d�sactiver le blocage de la souris";
    ls->shortcutEmuSpeedMax     = "Vitesse maximale d'�mulation";
    ls->shortcutEmuSpeedNormal  = "Vitesse normale d'�mulation";
    ls->shortcutEmuSpeedInc     = "Augmenter la vitesse d'�mulation";
    ls->shortcutEmuSpeedDec     = "Diminuer la vitesse d'�mulation";
    ls->shortcutShowEmuProp     = "Acc�der au menu Emulation";
    ls->shortcutShowVideoProp   = "Acc�der au menu Video";
    ls->shortcutShowAudioProp   = "Acc�der au menu Son";
    ls->shortcutShowCtrlProp    = "Acc�der au menu Contr�les";
    ls->shortcutShowPerfProp    = "Acc�der au menu Performances";

    ls->shortcutShowSettProp    = "Acc�der au menu R�glages";
    ls->shortcutShowLanguage    = "Acc�der au menu Langue";
    ls->shortcutShowMachines    = "Acc�der � l'�diteur de machines";
    ls->shortcutShowShortcuts   = "Acc�der � l'�diteur de raccourcis";
    ls->shortcutShowHelp        = "Acc�der aux rubriques d'aide ";
    ls->shortcutShowAbout       = "Voir la rubrique A propos de blueMSX ";

    ls->shortcutSpecialMenu1    = "Acc�der au menu sp�cial pour les cartouches en port 1";
    ls->shortcutSpecialMenu2    = "Acc�der au menu sp�cial pour les cartouches en port 2";
    ls->shortcutVolumeStereo    = "Balance mono/st�r�o";
    ls->shortcutThemeSwitch     = "Changer de th�me";
    ls->shortcutToggleSpriteEnable = "Montrer/Cacher les sprites";
    
    ls->shortcutShowApearProp   = "Show Appearance Properties";
    ls->menuPropsApearance      = "Appearance";
    ls->propApearance           = "Appearance";
    ls->propThemeGB             = "Th�me ";
    ls->propTheme               = "Th�me";
    ls->propThemeClassic        = "Classique";
    ls->propThemeBlue           = "DIGIblue";

    ls->propMonBrightness       = "Brillance:";
    ls->propMonContrast         = "Contraste:";
    ls->propMonSaturation       = "Saturation:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = "Lignes de scannage:";

    ls->dlgRomType              = "Type de Rom:"; 
    ls->propOpenRomGB           = "Ouvrir un fichier Rom"; 
    ls->propDefaultRomType      = "Type par d�faut:"; 
    ls->propGuessRomType        = "Deviner le type"; 

    ls->propFile                = "Fichiers"; 
    ls->propSettDefSlotGB       = "Glisser et d�poser "; 
    ls->propSettDefSlots        = "Ins�rer la cartouche dans:"; 
    ls->propSettDefSlot1        = " Port 1"; 
    ls->propSettDefSlot2        = " Port 2"; 
    ls->propSettDefDrives       = "Ins�rer la disquette dans:"; 
    ls->propSettDefDriveA       = " Lecteur A"; 
    ls->propSettDefDriveB       = " Lecteur B"; 
    ls->menuPropsFile           = "Fichiers";
    
    ls->shortcutShowFiles       = "Acc�der au menu Fichiers";

    // New entries in 1.6.1
    ls->menuDiskDirInsert       = "Ins�rer r�pertoire"; 
    ls->shortcutDiskDirInsertA  = "Ins�rer un r�pertoire comme disquette A"; 
    ls->shortcutDiskDirInsertB  = "Ins�rer un r�pertoire comme disquette B"; 
    ls->propMonDeInterlace      = " D�-entrelac�";

    // New entries in 2.0
    ls->shortcutSwitchPause     = "Actionner le commutateur Pause";
    ls->shortcutSizeMinimized   = "R�duire la fen�tre";
    ls->shortcutEmuSpeedToggle  = "Balance vitesse maximale d'�mulation";
    ls->shortcutToggleCpuTrace  = "Valider/Invalider la trace du CPU";

    ls->enumVideoEmuMonitor     = "Moniteur";

    ls->propEmuPauseSwitch      = " Commutateur Pause";
    ls->propVideoFreqText       = "Fr�quence Vid�o:";
    ls->propVideoFreqAuto       = "Auto";
    ls->propSndOversampleText   = "Sur�chantillonner:";

    ls->confChipExtras          = "Extras";
    ls->confBoardGB             = "Syst�me ";
    ls->confBoardText           = "Type de syst�me:";
    ls->dlgCpuFreqGB            = "Fr�quence CPU ";
    ls->dlgZ80FreqText          = "Fr�quence Z80:";
    ls->dlgR800FreqText         = "Fr�quence R800:";
    ls->dlgFdcGB                = "Contr�leur de lecteur de disquettes ";
    ls->dlgCFdcNumDrivesText    = "Nombre de lecteurs:";

    ls->propPriorityBoost       = " Donner � blueMSX une priorit� �lev�e";

    // New entries in 2.1
    ls->propEmuFdcTiming        = "Ne pas synchroniser le lecteur de disquettes"; 
    ls->shortcutToggleFdcTiming = "Synchroniser ou non le lecteur de disquettes"; 
    ls->propUseRegistry         = "Sauvegarder la configuration dans le Registre"; 

    // New entries in 2.2
    ls->menuCartHBI55           = "Cartouche Sony HBI-55";
    ls->propSndPcm              = " Turbo-R PCM";
    ls->propSndAY8910           = " AY8910 PSG";
    ls->propSndSN76489          = " SN76489 PSG";
    ls->enumVideoEmuHq2x        = "Hq2x";
};

#endif
