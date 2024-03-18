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
    int entry;
    AVLTree<ContestantEntry*, int> *contestantTreeEntry;
    RankTree<ContestantStr*, StrCond>* contestantTreeStr;

public:
    Team(int teamId);
    Team(const Team &toCopy) = default;
    ~Team() = default;
    int get_power();
    int get_team_id();
    int get_number_of_players();
    int get_entry();
    void add_entry();
    void set_entry(int newEntry);
    void set_number_of_players(int toAdd);
    void set_power(int toSet);

    void calc_team_power();
    AVLTree<ContestantEntry*, int> *getEntryTree();
    RankTree<ContestantStr*, StrCond>* getStrTree();
    void setStrTree(RankTree<ContestantStr*, StrCond>* strTree);
    void setEntryTree(AVLTree<ContestantEntry*, int> *treeEntry);

    void destroy_players_trees(); //TODO
    void destroy_players_trees_with_con(); //TODO
    void destroyTra(Node<ContestantEntry*, int>* node);
    void add_contestant_to_team(Contestant * contestant);
    void remove_newest_player();
    void fillArray(Node<ContestantEntry*, int> *teamEntry[], RankNode<ContestantStr*, StrCond> *teamStr[], int size);
    void setTrees(Node<ContestantEntry*, int> *teamTotalEntry[],RankNode<ContestantStr*, StrCond> *teamTotalStr[],
                  int size, int lastestEntry);
};

#endif //WET2DS_2024_TEAM_H
