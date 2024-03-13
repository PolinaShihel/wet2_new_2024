

#include "ContestantStr.h"

ContestantStr::ContestantStr(Contestant* conPtr,ContestantEntry* conEntryPtr):
    conPtr(conPtr),conEntryPtr(conEntryPtr) {}

ContestantEntry* ContestantStr::getConEntryPtr() {
    return this->conEntryPtr;
}

Contestant* ContestantStr::getConPtr() {
    return this->conPtr;
}