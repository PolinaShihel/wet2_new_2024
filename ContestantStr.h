

#ifndef WET2_NEW_2024_CONTESTANTSTR_H
#define WET2_NEW_2024_CONTESTANTSTR_H
#include "Contestant.h"
#include "ContestantEntry.h"

class ContestantStr {
private:
    Contestant* conPtr;
    ContestantEntry* conEntryPtr;
public:
    ContestantStr() = default;
    ContestantStr(Contestant* conPtr, ContestantEntry* conEntryPtr);
    ContestantStr(const ContestantStr &toCopy) = default;
    ~ContestantStr()=default;
    ContestantEntry* getConEntryPtr();
    Contestant* getConPtr();

};


#endif //WET2_NEW_2024_CONTESTANTSTR_H
