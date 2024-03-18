#include "StrPlayerCond.h"

bool StrPlayerCond::operator>(const StrPlayerCond& other) const
{
    if (this->Strength > other.Strength) {
        return true;
    }
    if (this->Strength == other.Strength) {
        if (this->Entry > other.Entry) {
            return true;
        }
    }
    return false;
}

bool StrPlayerCond::operator<(const StrPlayerCond& other) const
{
    return other > *this;
}

bool StrPlayerCond::operator==(const StrPlayerCond& other) const
{
    return ((Strength == other.Strength)&&(Entry == other.Entry));
}

bool StrPlayerCond::operator>=(const StrPlayerCond& other) const
{
    return *this > other || *this == other;
}

bool StrPlayerCond::operator<=(const StrPlayerCond& other) const
{
    return *this < other || *this == other;
}

StrPlayerCond::operator int() const
{
    return Strength;
}