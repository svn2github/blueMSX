/*****************************************************************************
** File:
**      Language.h
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
#ifndef LANGUAGE_ITALIAN_H
#define LANGUAGE_ITALIAN_H

#include "LanguageEnglish.h"

class LanguageItalian : public LanguageEnglish
{
public:
    LanguageItalian() {
        trainerName             = "Trainer";
        trainerCaption          = "blueMSX - Trainer";
        saveCheatCaption        = "Salva Cheat";
        loadCheatCaption        = "Carica Cheat";
        pause                   = "Pausa";
        run                     = "Esegui";
        truncated               = "troncato...";
        newCheat                = "Nuovo Cheat";
        address                 = "Indirizzo";
        oldValue                = "Vecchio Valore";
        newValue                = "Nuovo Valore";
        change                  = "Modifica";
        disable                 = "Disattiva";
        enable                  = "Attiva";
        description             = "Descrizione";
        value                   = "Valore";
        activeCheats            = "Attivi Cheats ";
        findCheats              = "Trova Cheats ";
        removeAll               = "Tutto rimuovi";
        remove                  = "Rimuovi";
        addCheat                = "Aggiungi Cheat";
        cheatFile               = "Cheat File:";
        ok                      = "OK";
        cancel                  = "Annulla";
        displayValueAs          = "Mostri il valore ";
        decimal                 = "Decimale";
        hexadecimal             = "Hexadecimale";
        dataSize                = "Formato dei dati ";
        eightBit                = "8 bit";
        sixteenBit              = "16 bit";
        compareType             = "Tipo di raffronto ";
        equal                   = "Uguale";
        notEqual                = "Non uguale";
        lessThan                = "Meno che";
        lessOrEqual             = "Meno o uguale";
        greaterThan             = "Più grande che";
        greaterOrEqual          = "Più grande o uguale";
        display                 = "Mostra ";
        compareNewValueWith     = "Compara il nuovo valore a ";
        specificValue           = "Calore specifico: ";
        snapshot                = "Snapshot";
        search                  = "Ricerca";
        undo                    = "Annulla";
    }
};

#endif //LANGUAGE_FRENCH_H
