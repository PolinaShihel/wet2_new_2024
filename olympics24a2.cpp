#include "olympics24a2.h"

olympics_t::olympics_t() : teamsHash(), highest_ranked_team_id(-1),highest_ranked_team_rank(-1), number_of_teams(0) ,teamsTree() {}

olympics_t::~olympics_t()
{
	// TODO: Your code goes here
}


StatusType olympics_t::add_team(int teamId)
{
    if (teamId <= 0)
        return StatusType::INVALID_INPUT;
    try {


        Team* toAdd = new Team(teamId);
        teamsHash.insert(teamId,toAdd);

        // only updates if it is the first team
        if (number_of_teams == 0) {
            highest_ranked_team_id = 0;
            highest_ranked_team_rank = 0;
        }

    }  catch (std::bad_alloc &error) {
         return StatusType::ALLOCATION_ERROR;
    }  catch (KeyExists &error) {
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
            StrCond strCond = StrCond(str, teamId);
            teamsTree.remove(strCond);
        }
        teamsHash.remove(teamId);

        number_of_teams--;

        if(highest_ranked_team_id == teamId){
            if(teamsTree.getSize() == 0 ) {
                highest_ranked_team_id = 0;
                highest_ranked_team_rank = 0;
            }
            else
                if (number_of_teams != 0) {
                    highest_ranked_team_id = teamsTree.getBiggest()->getNodeData()->get_team_id();
                    highest_ranked_team_rank = teamsTree.getBiggest()->getNodeData()->get_power() + teamsTree.getBiggest()->getNodeData()->get_wins() ;
                }
                else {
                    highest_ranked_team_id = -1;
                    highest_ranked_team_rank = 0;
                }
        }

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
        // need to test if team exists?

        Team* ptrTeam= *(teamsHash.find(teamId));
        Contestant* con = new Contestant(ptrTeam->get_entry(),playerStrength); // not sure about this maybe need to change the way we add contestant (ze tip tipa akum)

        StrCond strCond1 = StrCond(ptrTeam->get_power(),teamId); // before adding

        ptrTeam->add_contestant_to_team(con);

        StrCond strCond2 = StrCond(ptrTeam->get_power(),teamId); //after adding
        if (ptrTeam->get_number_of_players() > 1) {
            this->teamsTree.remove(strCond1);
        }
        this->teamsTree.insert(strCond2,ptrTeam);

        highest_ranked_team_compare(ptrTeam);

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

        StrCond strCond1 = StrCond(ptrTeam->get_power(),teamId); // str cond before change

        ptrTeam->remove_newest_player();
        ptrTeam->calc_team_power();

        StrCond strCond2 = StrCond(ptrTeam->get_power(),teamId); // str cond after change

        this->teamsTree.remove(strCond1);
        this->teamsTree.insert(strCond2,ptrTeam);

        if(teamId == highest_ranked_team_id)
        {
            highest_ranked_team_rank = ptrTeam->get_power()+ ptrTeam->get_wins();
            Team* current_highest = teamsTree.getBiggest()->getNodeData();
            highest_ranked_team_compare(current_highest); // also updates
        }


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

        if(power_team1 > power_team2){
            ptrTeam1->set_wins(1);
        }   else {
            if (power_team1 < power_team2) {
                ptrTeam2->set_wins(1);
            } else {
                if(ptrTeam1->get_team_id() > ptrTeam2->get_team_id()) {
                    ptrTeam2->set_wins(1);
                } else {
                    ptrTeam1->set_wins(1);
                }

            }
        }

        if(ptrTeam1->get_number_of_players() > 0 )
            highest_ranked_team_compare(ptrTeam1);
        if(ptrTeam2->get_number_of_players() > 0 )
            highest_ranked_team_compare(ptrTeam2);

    }  catch (std::bad_alloc &error) {
            return StatusType::ALLOCATION_ERROR;
    }   catch (KeyNotFound &error) {
             return StatusType::FAILURE;
    }
    return teamId;
}

void olympics_t::highest_ranked_team_compare(Team* toCompare) // also updates if higher
{
    if(highest_ranked_team_id == 0){
        highest_ranked_team_id = toCompare->get_team_id();
        highest_ranked_team_rank = toCompare->get_power() + toCompare->get_wins();

    } else {
        Team *currentHighest = *(teamsHash.find(highest_ranked_team_id));
        if (highest_ranked_team_rank < toCompare->get_power() + toCompare->get_wins()) {
            highest_ranked_team_id = toCompare->get_team_id();
            highest_ranked_team_rank = toCompare->get_power() + toCompare->get_wins();
        }
    }
}

output_t<int> olympics_t::num_wins_for_team(int teamId)
{
    if (teamId <= 0 )
        return StatusType::INVALID_INPUT;
    int wins=0;
    try {

        Team* ptrTeam= *(teamsHash.find(teamId));
        wins = ptrTeam->get_wins();

    } catch (std::bad_alloc &error) {
        return StatusType::ALLOCATION_ERROR;
    } catch (KeyNotFound &error) {
        return StatusType::FAILURE;
    }
    return wins;
}

output_t<int> olympics_t::get_highest_ranked_team()
{
    return highest_ranked_team_rank;
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
        //TODO:check if one (or both) of the teams is empty
        StrCond* team1cond = new StrCond(team1->get_power(),teamId1);
        StrCond* team2cond = new StrCond(team2->get_power(),teamId2);
        Node<ContestantEntry*, int> *team1Entry[team1Size];
        RankNode<ContestantStr*, StrCond> *team1Str[team1Size];
        Node<ContestantEntry*, int> *team2Entry[team2Size];
        RankNode<ContestantStr*, StrCond> *team2Str[team2Size];
        int totalSize = team1Size + team2Size;
        Node<ContestantEntry*, int> *teamTotalEntry[totalSize];
        RankNode<ContestantStr*, StrCond> *teamTotalStr[totalSize];
        team1->fillArray(team1Entry,team1Str,team1Size);
        team2->fillArray(team2Entry,team2Str,team2Size);
        int latestArrival = team1->get_entry();
        for(int i = 0; i < team2Size; i++)
        {
            int entry = team2Entry[i]->getNodeData()->getConPtr()->get_entry();
            team2Entry[i]->getNodeData()->getConPtr()->set_entry(entry + latestArrival);
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
            if((indexT2>=team2Size)||((indexT1<team1Size)&&
                    (team1Str[indexT1]->getKey()<team2Str[indexT2]->getKey())))
                teamTotalStr[currIndex++] = team1Str[indexT1++];
            else if((indexT1>=team1Size)||((indexT2<team2Size)&&
                                           (team2Str[indexT2]->getKey()<team1Str[indexT1]->getKey())))
                teamTotalStr[currIndex++] = team2Str[indexT2++];
        }
        team1->setTrees(teamTotalEntry,teamTotalStr,totalSize, latestTotal + 1);
        team2->destroy_players_trees();
        this->teamsTree.remove(*team1cond);
        this->teamsTree.remove(*team2cond);
        this->teamsHash.remove(*team2cond);
        delete team1cond;
        delete team2cond;
        StrCond* teamCond = new StrCond(team1->get_power(),teamId1);
        this->teamsTree.insert(*teamCond,team1);
        //TODO:NEED TO FINISH
    }
    catch(std::bad_alloc &error){
        return StatusType::ALLOCATION_ERROR;
    }catch(KeyNotFound &error){
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}

output_t<int> olympics_t::play_tournament(int lowPower, int highPower)
{
    // TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}
