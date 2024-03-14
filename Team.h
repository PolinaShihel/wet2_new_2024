#ifndef WET2DS_2024_TEAM_H
#define WET2DS_2024_TEAM_H

#include "Contestant.h"
#include "AVL_tree.h"
#include "StrCond.h"
#include "RankTree.h"
#include "ContestantStr.h"
#include "ContestantEntry.h"

class Team
{
    int teamId;
    int power;
    int number_of_players;
    int wins;
    int entry;
    AVLTree<ContestantEntry*, int> *contestantTreeEntry;
    RankTree<ContestantStr*, StrCond>* contestantTreeStr;

public:
    Team(int teamId);
    Team(const Team &toCopy) = default;
    ~Team() = default;
    int get_power();
    int get_team_id();
    int get_wins();
    int get_number_of_players();
    int get_entry();
    void add_entry();
    void set_number_of_players(int toAdd);
    void set_power(int toSet);
    void set_wins(int toAdd);
    void calc_team_power();


    void destroy_players_trees(); //TODO
    void add_contestant_to_team(Contestant * contestant);
    void remove_newest_player();

};

#endif //WET2DS_2024_TEAM_H
