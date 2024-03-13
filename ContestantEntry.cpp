//
// Created by Lotan Dahan on 13/03/2024.
//

#include "ContestantEntry.h"


ContestantEntry::ContestantEntry(Contestant* conPtr)
: conPtr(conPtr) , conStrPtr(nullptr) {}

ContestantStr* ContestantEntry::getConStrPtr() {
    return this->conStrPtr;
}
Contestant* ContestantEntry::getConPtr() {
    return this->conPtr;
}
void ContestantEntry::setStrPtr(ContestantStr* StrPtr)
{
    conStrPtr = StrPtr;
}