#include "olympics24a2.h"

#define MAX 0x7fffffff

olympics_t::olympics_t(): teamsHash(), number_of_teams(0) ,teamsTree() {}

void deleteTrav(Node<Team*, int>* node){
    if (node == nullptr)
        return;
    deleteTrav(node->getLeft());
    Team* data = *(node->getNodeDataPointer());
    data->destroy_players_trees_with_con();
    delete data;
    deleteTrav(node->getRight());
}

olympics_t::~olympics_t()
{
    for (int i = 0; i < teamsHash.getSize(); ++i) {
        if(teamsHash.members[i].getSize() == 0)
            continue;
        deleteTrav(teamsHash.members[i].getRoot());
    }
}


StatusType olympics_t::add_team(int teamId)
{
    if (teamId <= 0)
        return StatusType::INVALID_INPUT;
    Team* toAdd;
    try {
        toAdd = new Team(teamId);
        teamsHash.insert(teamId,toAdd);


    }  catch (std::bad_alloc &error) {
         return StatusType::ALLOCATION_ERROR;
    }  catch (KeyExists &error) {
        toAdd->destroy_players_trees();
        delete toAdd;
        return StatusType::FAILURE;
    }
    number_of_teams++;
	return StatusType::SUCCESS;
}

StatusType olympics_t::remove_team(int teamId)
{
    if (teamId <= 0)
        return StatusType::INVALID_INPUT;
    try {

        Team* toDelete= *(teamsHash.find(teamId));

        if(toDelete->get_number_of_players() != 0) {
            int str = toDelete->get_power();
            StrTeamCond strCond = StrTeamCond(str, teamId);
            teamsTree.remove(strCond);
        }
        teamsHash.remove(teamId);
        toDelete->destroy_players_trees_with_con();
        delete toDelete;
        number_of_teams--;



    }  catch (std::bad_alloc &error) {
            return StatusType::ALLOCATION_ERROR;
    }   catch (KeyNotFound &error) {
            return StatusType::FAILURE;
    }

	return StatusType::SUCCESS;
}

StatusType olympics_t::add_player(int teamId, int playerStrength)
{
    if (teamId <= 0 || playerStrength <= 0 )
        return StatusType::INVALID_INPUT;
    try {

        Team* ptrTeam= *(teamsHash.find(teamId));
        Contestant* con = new Contestant(ptrTeam->get_entry(),playerStrength); // not sure about this maybe need to change the way we add contestant (ze tip tipa akum)
        int wins = this->num_wins_for_team(teamId).ans();
        StrTeamCond strCond1 = StrTeamCond(ptrTeam->get_power(),teamId); // before adding

        ptrTeam->add_contestant_to_team(con);

        StrTeamCond strCond2 = StrTeamCond(ptrTeam->get_power(),teamId); //after adding


        this->teamsTree.insert(strCond2,ptrTeam);

        if (ptrTeam->get_number_of_players() > 1) {
            this->teamsTree.remove(strCond1);
            this->teamsTree.addExtraSingle(strCond2, wins);
        } else {
            if (ptrTeam->get_wins() != 0)
                this->teamsTree.addExtraSingle(strCond2, ptrTeam->get_wins());
        }

        ptrTeam->set_wins(0);


    }  catch (std::bad_alloc &error) {
            return StatusType::ALLOCATION_ERROR;
    }   catch (KeyExists &error) {
            return StatusType::FAILURE;
    }   catch (KeyNotFound &error) {
            return StatusType::FAILURE;
    }


	return StatusType::SUCCESS;
}

StatusType olympics_t::remove_newest_player(int teamId)
{
    if (teamId <= 0 )
        return StatusType::INVALID_INPUT;
    try {
        Team* ptrTeam= *(teamsHash.find(teamId));
        if(ptrTeam->get_number_of_players() == 0)
            return StatusType::FAILURE;

        StrTeamCond strCond1 = StrTeamCond(ptrTeam->get_power(),teamId); // str cond before change
        int wins = this->num_wins_for_team(teamId).ans();

        ptrTeam->remove_newest_player();
        ptrTeam->calc_team_power();

        StrTeamCond strCond2 = StrTeamCond(ptrTeam->get_power(),teamId); // str cond after change

        this->teamsTree.remove(strCond1);

        if(ptrTeam->get_number_of_players() > 0) {
            this->teamsTree.insert(strCond2, ptrTeam);
            this->teamsTree.addExtraSingle(strCond2, wins);
        }

        ptrTeam->set_wins(wins);

    } catch (std::bad_alloc &error) {
        return StatusType::ALLOCATION_ERROR;
    } catch (KeyExists &error) {
        return StatusType::FAILURE;
    }catch (KeyNotFound &error) {
        return StatusType::FAILURE;
    }
	return StatusType::SUCCESS;
}

output_t<int> olympics_t::play_match(int teamId1, int teamId2)
{
    if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
        return StatusType::INVALID_INPUT;
    int teamId=0;
    try {
        if (teamsHash.find(teamId1) == nullptr || teamsHash.find(teamId2) == nullptr)
            return StatusType::FAILURE;
        Team* ptrTeam1= *(teamsHash.find(teamId1));
        Team* ptrTeam2= *(teamsHash.find(teamId2));
        int power_team1 = ptrTeam1->get_power();
        int power_team2 = ptrTeam2->get_power();
        StrTeamCond strCond1 =StrTeamCond(power_team1,teamId1);

        StrTeamCond strCond2 =StrTeamCond(power_team2,teamId2);

        if(ptrTeam1->get_number_of_players() == 0 || ptrTeam2->get_number_of_players() == 0)
            return StatusType::FAILURE;

        if(power_team1 > power_team2){
            teamsTree.addExtraSingle(strCond1,1);
            teamId=teamId1;
        }   else {
            if (power_team1 < power_team2) {
                teamsTree.addExtraSingle(strCond2,1);
                teamId=teamId2;
            } else {
                if(ptrTeam1->get_team_id() > ptrTeam2->get_team_id()) {
                    teamsTree.addExtraSingle(strCond2,1);
                    teamId=teamId2;
                } else {
                    teamsTree.addExtraSingle(strCond1,1);
                    teamId=teamId1;
                }
            }
        }


    }  catch (std::bad_alloc &error) {
            return StatusType::ALLOCATION_ERROR;
    }   catch (KeyNotFound &error) {
             return StatusType::FAILURE;
    }
    return teamId;
}



output_t<int> olympics_t::num_wins_for_team(int teamId)
{
    if (teamId <= 0 )
        return StatusType::INVALID_INPUT;
    int wins=0;
    try {

        Team* ptrTeam= *(teamsHash.find(teamId));
        StrTeamCond strCond = StrTeamCond(ptrTeam->get_power(),teamId);
        if(ptrTeam->get_wins() > 0) {
            int winsTeam = 0;
            wins = ptrTeam->get_wins();
            if(ptrTeam->get_number_of_players() > 0)
                winsTeam = teamsTree.findSum(strCond);
            return wins > winsTeam ? wins : winsTeam;
        }else {
            if(ptrTeam->get_number_of_players()==0)
                return 0;
            wins = teamsTree.findSum(strCond);
        }

    } catch (std::bad_alloc &error) {
        return StatusType::ALLOCATION_ERROR;
    } catch (KeyNotFound &error) {
        return StatusType::FAILURE;
    }
    return wins;
}

output_t<int> olympics_t::get_highest_ranked_team() {
    try {
        if (this->teamsTree.getSize() == 0) {
            if (this->number_of_teams != 0)
                return 0;
            return -1;
        }
        return this->teamsTree.getMaxRank();
    }
    catch (std::bad_alloc &error) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType olympics_t::unite_teams(int teamId1, int teamId2)
{
    if((teamId1 <=0)||(teamId2<=0)||(teamId1==teamId2))
        return StatusType::INVALID_INPUT;
    try{
        Team* team1 = *(teamsHash.find(teamId1));
        Team* team2 = *(teamsHash.find(teamId2));
        int team1Size = team1->get_number_of_players();
        int team2Size = team2->get_number_of_players();
        StrTeamCond team1cond = StrTeamCond(team1->get_power(),teamId1);
        StrTeamCond team2cond = StrTeamCond(team2->get_power(),teamId2);
        if(team2Size == 0){
            this->teamsHash.remove(teamId2);
            this->number_of_teams--;
            team2->destroy_players_trees();
            delete team2;
            return StatusType::SUCCESS;
        }
        if(team1Size == 0){
            int wins = this->num_wins_for_team(teamId1).ans();
            team1->setEntryTree(team2->getEntryTree());
            team1->setStrTree(team2->getStrTree());
            team1->set_power(team2->get_power());
            team1->set_number_of_players(team2->get_number_of_players());
            team1->set_entry(team2->get_entry());
            team1cond = StrTeamCond(team1->get_power(),teamId1);
            this->teamsHash.remove(teamId2);
            this->teamsTree.remove(team2cond);
            this->teamsTree.insert(team1cond, team1);
            this->teamsTree.addExtraSingle(team1cond, wins);
            this->number_of_teams--;
            delete team2;
            return StatusType::SUCCESS;
        }
        int wins = this->num_wins_for_team(teamId1).ans();
        Node<ContestantEntry*, int> *team1Entry[team1Size];
        RankNode<ContestantStr*, StrPlayerCond> *team1Str[team1Size];
        Node<ContestantEntry*, int> *team2Entry[team2Size];
        RankNode<ContestantStr*, StrPlayerCond> *team2Str[team2Size];
        int totalSize = team1Size + team2Size;
        Node<ContestantEntry*, int> *teamTotalEntry[totalSize];
        RankNode<ContestantStr*, StrPlayerCond> *teamTotalStr[totalSize];
        team1->fillArray(team1Entry,team1Str,team1Size);
        team2->fillArray(team2Entry,team2Str,team2Size);
        int latestArrival = team1->get_entry();
        for(int i = 0; i < team2Size; i++)
        {
            int entry = team2Entry[i]->getNodeData()->getConPtr()->get_entry();
            team2Entry[i]->getNodeData()->getConPtr()->set_entry(entry + latestArrival);
            team2Entry[i]->setKey(entry + latestArrival);
        }
        for(int i = 0; i < team2Size; i++)
        {
            StrPlayerCond newCond = StrPlayerCond(team2Str[i]->getNodeData()->getConPtr()->get_strength(),
                                                  team2Str[i]->getNodeData()->getConPtr()->get_entry());
            team2Str[i]->setKey(newCond);
        }
        for(int i = 0; i < team1Size;i++)
        {
            teamTotalEntry[i]=team1Entry[i];
        }
        for(int i = 0; i < team2Size;i++)
        {
            teamTotalEntry[team1Size + i]=team2Entry[i];
        }
        int latestTotal = teamTotalEntry[totalSize-1]->getNodeData()->getConPtr()->get_entry();
        int indexT1 = 0, indexT2 = 0, currIndex = 0;

        while((indexT1<team1Size)||(indexT2<team2Size))
        {
            if((indexT2>=team2Size) || ((indexT1<team1Size)&&
                    (team1Str[indexT1]->getKey()<team2Str[indexT2]->getKey())))
                teamTotalStr[currIndex++] = team1Str[indexT1++];
            else if((indexT1>=team1Size)||((indexT2<team2Size)&&
                                           (team2Str[indexT2]->getKey()<team1Str[indexT1]->getKey())))
                teamTotalStr[currIndex++] = team2Str[indexT2++];
        }
        team1->setTrees(teamTotalEntry,teamTotalStr,totalSize, latestTotal + 1);
        team2->destroy_players_trees();
        delete team2;
        this->teamsTree.remove(team1cond);
        this->teamsTree.remove(team2cond);
        this->teamsHash.remove(teamId2);
        StrTeamCond teamCond = StrTeamCond(team1->get_power(),teamId1);
        this->teamsTree.insert(teamCond,team1);
        this->teamsTree.addExtraSingle(teamCond,wins);
    }
    catch(std::bad_alloc &error){
        return StatusType::ALLOCATION_ERROR;
    }catch(KeyNotFound &error){
        return StatusType::FAILURE;
    }
    this->number_of_teams--;
    return StatusType::SUCCESS;
}

int PowerOfTwo(int n)
{
    if (n == 0)
        return -1;
    int i=0;
    while (n != 1) {
        if (n % 2 != 0)
            return -1;
        n = n / 2;
        i++;
    }
    return i;
}

output_t<int> olympics_t::play_tournament(int lowPower, int highPower)
{
    if(lowPower <= 0 || highPower <= 0 || highPower <= lowPower)
        return StatusType::INVALID_INPUT;
    int winner_id=0;
    try {
        StrTeamCond condLow = StrTeamCond(lowPower,MAX);
        StrTeamCond condHigh = StrTeamCond(highPower,-1);
        Team *rankLow = teamsTree.findClosestSmall(condLow)->getNodeData();
        Team *rankHigh = teamsTree.findClosestBig(condHigh)->getNodeData();
        if(rankLow == nullptr || rankHigh == nullptr)
            return StatusType::FAILURE;
        winner_id = rankHigh->get_team_id();

        condLow = StrTeamCond(rankLow->get_power(),rankLow->get_team_id());
        condHigh = StrTeamCond(rankHigh->get_power(),rankHigh->get_team_id());

        int lowRank = teamsTree.Rank(condLow);
        int highRank = teamsTree.Rank(condHigh);


        int wins =PowerOfTwo(highRank-lowRank+1);
        if(wins  < 0) {
            return StatusType::FAILURE;
        }

        teamsTree.addExtra(condHigh, wins);
        int i=1;
        while(wins > 1) {
            // example :  1 2 3 4 | 5 6 | 7 | 8    <- need to add +3 to 8 , +2 to 7 , +1 to 5 and 6
            //  so we add 3 to all of them , then sub 1 from all except 8, then sub 1 from all except 7 and 8
            // then sub 1 from all except 5 6 7 8
            Team* temp = *(teamsTree.select(highRank-1*i));
            StrTeamCond tempCond = StrTeamCond(temp->get_power(),temp->get_team_id());
            teamsTree.addExtra(tempCond, -1);
            wins--;
            i*=2;
        }
        Team* temp = *(teamsTree.select(highRank-1*i));
        StrTeamCond tempCond = StrTeamCond(temp->get_power(),temp->get_team_id());
        teamsTree.addExtra(tempCond, -1);



    } catch(std::bad_alloc &error) {
        return StatusType::ALLOCATION_ERROR;
    }catch(KeyNotFound &error){
        return StatusType::FAILURE;
    }
    return winner_id;
}
