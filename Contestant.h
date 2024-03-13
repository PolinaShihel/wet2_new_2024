#ifndef WET2DS_2024_CONTESTANT_H
#define WET2DS_2024_CONTESTANT_H


class Contestant {
    int entry;
    int strength;
public:
    Contestant(int entry, int strength):entry(entry), strength(strength){};
    ~Contestant()=default;
};


#endif //WET2DS_2024_CONTESTANT_H
