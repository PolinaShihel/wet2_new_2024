#ifndef WET1_StrCond_H
#define WET1_StrCond_H

class StrCond
{
    int Strength;
    int entry;
public:
    StrCond():Strength(0),entry(0){}
    StrCond(int Strength, int entry): Strength(Strength),entry(entry){}
    StrCond(const StrCond& other) = default;
    StrCond& operator=(const StrCond& other) = default;
    ~StrCond() = default;
    bool operator>(const StrCond& other) const;
    bool operator<(const StrCond& other) const;
    bool operator>=(const StrCond& other) const;
    bool operator<=(const StrCond& other) const;
    bool operator==(const StrCond& other) const;
    operator int() const;
};

#endif //WET1_StrCond_H
