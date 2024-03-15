#include "Team.h"


Team::Team(int teamId) : teamId(teamId) , power(0) ,
                        number_of_players(0) , wins(0) , entry(0) ,
                        contestantTreeEntry( new AVLTree<ContestantEntry* , int>()) ,
                        contestantTreeStr( new RankTree<ContestantStr* , StrCond>()){}

int Team::get_power() { return power; }
int Team::get_team_id() { return teamId; }
int Team::get_wins() { return wins; }
int Team::get_number_of_players(){ return number_of_players; }
void Team::set_number_of_players(int toAdd) { this->number_of_players += toAdd; }
void Team::set_power(int toSet) { this->power = toSet; }
void Team::set_wins(int toAdd) { this->wins +=toAdd; }
int Team::get_entry() { return entry; }
void Team::add_entry() { this->entry +=1; }

void Team::calc_team_power() {
    if(contestantTreeStr->getSize() == 0 || this->get_number_of_players() == 0 ) {
        this->set_power(0);
        return;
    }
    if(this->get_number_of_players() == 1 ) {
        ContestantStr* toSet = *(contestantTreeStr->select(1));
        this->set_power(toSet->getConPtr()->get_strength());
    } else {
        ContestantStr*  median_con = *(contestantTreeStr->select(number_of_players/2));
        int power = this->get_number_of_players() * (median_con->getConPtr()->get_strength());
        this->set_power(power);
    }
}
void Team::destroy_players_trees() { //TODO

}

void Team::add_contestant_to_team(Contestant * contestant) {
    int str = contestant->get_strength();
    int ent = this->get_entry();
    ContestantEntry *toAddEntry = new ContestantEntry(contestant);
    ContestantStr *toAddStr;
    try {
        contestantTreeEntry->insert(ent, toAddEntry);
        toAddStr = new ContestantStr(contestant,toAddEntry);
        toAddEntry->setStrPtr(toAddStr);

        this->set_number_of_players(1);
        StrCond strCond = StrCond(str,ent);
        contestantTreeStr->insert(strCond,toAddStr);

        this->calc_team_power();

    } catch (std::bad_alloc &error) {
        delete toAddEntry;
        delete toAddStr;
        throw;
    } catch (...) {
        delete toAddEntry;
        delete toAddStr;
        throw;
    }
    this->add_entry();
}

void Team::remove_newest_player() {
    Node<ContestantEntry*,int> *toDeleteNode = this->contestantTreeEntry->getBiggest();
    ContestantEntry* toDeleteEntry = toDeleteNode->getNodeData();
    int ent = toDeleteEntry->getConPtr()->get_entry();
    int str = toDeleteEntry->getConPtr()->get_strength();
    StrCond strCond = StrCond(str,ent);
    this->contestantTreeEntry->remove(ent);
    this->contestantTreeStr->remove(strCond);
    this->set_number_of_players(-1);
    this->calc_team_power();
}

void Team::fillArray(Node<ContestantEntry*, int> *teamEntry[], RankNode<ContestantStr*, StrCond> *teamStr[], int size)
{
    this->contestantTreeEntry->fillArray(teamEntry,0);
    this->contestantTreeStr->fillArray(teamStr,0);
}

void Team::setTrees(Node<ContestantEntry*, int> *teamTotalEntry[],RankNode<ContestantStr*, StrCond> *teamTotalStr[],
                    int size, int latestEntry)
{
    AVLTree<ContestantEntry*, int> *Entry = new AVLTree<ContestantEntry*, int>(teamTotalEntry, size, 0, size - 1);
    RankTree<ContestantStr*, StrCond>* Str = new RankTree<ContestantStr*, StrCond>(teamTotalStr, size, 0, size -1);
    destroy_players_trees();
    this->contestantTreeEntry = Entry;
    this->contestantTreeStr = Str;
    this->entry = latestEntry;
    this->number_of_players = size;
    this->calc_team_power();
}

