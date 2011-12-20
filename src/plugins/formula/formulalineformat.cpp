/******************************************************************************
**
** Copyright (C) 2009-2011 Kyle Lutz <kyle.r.lutz@gmail.com>
** All rights reserved.
**
** This file is a part of the chemkit project. For more information
** see <http://www.chemkit.org>.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in the
**     documentation and/or other materials provided with the distribution.
**   * Neither the name of the chemkit project nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
******************************************************************************/

#include "formulalineformat.h"

#include <chemkit/molecule.h>

FormulaLineFormat::FormulaLineFormat()
    : chemkit::LineFormat("formula")
{
}

bool FormulaLineFormat::read(const std::string &formula, chemkit::Molecule *molecule)
{
    bool inSymbol = false;
    bool inNumber = false;
    QString symbol;
    QString number;

    foreach(const char &c, formula){
        if(isspace(c)){
            continue;
        }
        else if(isdigit(c)){
            if(inSymbol){
                inSymbol = false;
            }

            if(inNumber){
                number += c;
            }
            else{
                inNumber = true;
                number = c;
            }
        }
        else if(isalpha(c)){
            if(inNumber){
                for(int i = 0; i < number.toInt(); i++){
                    molecule->addAtom(symbol.toStdString());
                }

                number.clear();
                inNumber = false;
            }

            if(inSymbol && islower(c)){
                symbol += c;
            }
            else if(inSymbol && isupper(c)){
                molecule->addAtom(symbol.toStdString());
                symbol = c;
            }
            else{
                symbol = c;
                inSymbol = true;
            }
        }
    }

    if(!symbol.isEmpty()){
        if(number.isEmpty()){
            number = "1";
        }

        for(int i = 0; i < number.toInt(); i++){
            molecule->addAtom(symbol.toStdString());
        }
    }

    return true;
}

std::string FormulaLineFormat::write(const chemkit::Molecule *molecule)
{
    return molecule->formula();
}

