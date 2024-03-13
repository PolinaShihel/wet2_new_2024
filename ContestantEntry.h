
#ifndef WET2_NEW_2024_CONTESTANTENTRY_H
#define WET2_NEW_2024_CONTESTANTENTRY_H

#include "Contestant.h"
#include "ContestantStr.h"

class ContestantEntry {
private:
    Contestant* conPtr;
    ContestantStr* conStrPtr;
public:
    ContestantEntry() = default;
    ContestantEntry(Contestant* conPtr);
    ContestantEntry(const ContestantEntry &toCopy) = default;
    ~ContestantEntry()=default;
    void setStrPtr(ContestantStr* conStrPtr);
    ContestantStr* getConStrPtr();
    Contestant* getConPtr();
};



#endif //WET2_NEW_2024_CONTESTANTENTRY_H
