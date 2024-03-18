#ifndef WET2_NEW_2024_STRPLAYERCOND_H
#define WET2_NEW_2024_STRPLAYERCOND_H

class StrPlayerCond
{
    int Strength;
    int Entry;
public:
    StrPlayerCond():Strength(0),Entry(0){}
    StrPlayerCond(int Strength, int Entry): Strength(Strength),Entry(Entry){}
    StrPlayerCond(const StrPlayerCond& other) = default;
    StrPlayerCond& operator=(const StrPlayerCond& other) = default;
    ~StrPlayerCond() = default;
    bool operator>(const StrPlayerCond& other) const;
    bool operator<(const StrPlayerCond& other) const;
    bool operator>=(const StrPlayerCond& other) const;
    bool operator<=(const StrPlayerCond& other) const;
    bool operator==(const StrPlayerCond& other) const;
    operator int() const;
};

#endif //WET2_NEW_2024_STRPLAYERCOND_H
