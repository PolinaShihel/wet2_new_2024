#ifndef WET2DS_2024_CONTESTANT_H
#define WET2DS_2024_CONTESTANT_H


class Contestant {
    int entry;
    int strength;
public:
    Contestant(int entry, int strength);
    ~Contestant()=default;
    Contestant(const Contestant &toCopy) = default;
    int get_strength();
    int get_entry();
    void set_entry(int entry);
};


#endif //WET2DS_2024_CONTESTANT_H
