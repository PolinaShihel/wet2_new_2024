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

void Team::calc_team_power() { // TODO: implement select
    //TODO: check if tree empty or if size == 1
    //ContestantStr*  median_con = contestantTreeStr->select(number_of_players/2);
    //int power = number_of_players * median_con->conPtr->get_strength();
    this->set_power(power);
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

        StrCond strCond = StrCond(str,ent);
        contestantTreeStr->insert(strCond,toAddStr);

        this->calc_team_power();

    } catch (std::bad_alloc &error) {
        delete toAddEntry;
        throw;
    } catch (...) {
        delete toAddEntry;
        delete toAddStr;
        throw;
    }
    this->add_entry();
}

void Team::remove_newest_player() {
    Node<ContestantEntry*,int> *toDeleteNode = this->contestantTreeEntry->getSmallest();
    ContestantEntry* toDeleteEntry = toDeleteNode->getNodeData();
    int ent = toDeleteEntry->getConPtr()->get_entry();
    int str = toDeleteEntry->getConPtr()->get_strength();
    StrCond strCond = StrCond(str,ent);
    this->contestantTreeEntry->remove(ent);
    this->contestantTreeStr->remove(strCond);
    this->set_number_of_players(-1);


}
