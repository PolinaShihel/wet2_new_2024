#ifndef WET1_StrCond_H
#define WET1_StrCond_H

class StrTeamCond
{
    int Strength;
    int ID;
public:
    StrTeamCond():Strength(0),ID(0){}
    StrTeamCond(int Strength, int ID): Strength(Strength),ID(ID){}
    StrTeamCond(const StrTeamCond& other) = default;
    StrTeamCond& operator=(const StrTeamCond& other) = default;
    ~StrTeamCond() = default;
    bool operator>(const StrTeamCond& other) const;
    bool operator<(const StrTeamCond& other) const;
    bool operator>=(const StrTeamCond& other) const;
    bool operator<=(const StrTeamCond& other) const;
    bool operator==(const StrTeamCond& other) const;
    operator int() const;
};

#endif //WET1_StrCond_H
