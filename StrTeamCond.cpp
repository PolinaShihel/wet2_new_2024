#include "StrTeamCond.h"

bool StrTeamCond::operator>(const StrTeamCond& other) const
{
    if (this->Strength > other.Strength) {
        return true;
    }
    if (this->Strength == other.Strength) {
        if (this->ID < other.ID) {
            return true;
        }
    }
    return false;
}

bool StrTeamCond::operator<(const StrTeamCond& other) const
{
    return other > *this;
}

bool StrTeamCond::operator==(const StrTeamCond& other) const
{
    return ((Strength == other.Strength)&&(ID == other.ID));
}

bool StrTeamCond::operator>=(const StrTeamCond& other) const
{
    return *this > other || *this == other;
}

bool StrTeamCond::operator<=(const StrTeamCond& other) const
{
    return *this < other || *this == other;
}

StrTeamCond::operator int() const
{
    return Strength;
}