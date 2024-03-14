#include "olympics24a2.h"

olympics_t::olympics_t() : teamsHash(), highest_ranked_team_id(-1),highest_ranked_team_rank(0), number_of_teams(0) ,teamsTree() {}

olympics_t::~olympics_t()
{
	// TODO: Your code goes here
}


StatusType olympics_t::add_team(int teamId)
{
    if (teamId <= 0)
        return StatusType::INVALID_INPUT;
    try {
        if(teamsHash.find(teamId) != nullptr)
            return StatusType::FAILURE;

        Team* toAdd = new Team(teamId);
        teamsHash.insert(teamId,toAdd);

        // only updates if it is the first team
        if (number_of_teams == 0) {
            highest_ranked_team_id = 0;
            highest_ranked_team_rank = 0;
        }

    }  catch (std::bad_alloc &error) {
         return StatusType::ALLOCATION_ERROR;
    }
    number_of_teams++;
	return StatusType::SUCCESS;
}

StatusType olympics_t::remove_team(int teamId)
{
    if (teamId <= 0)
        return StatusType::INVALID_INPUT;
    try {
        if (teamsHash.find(teamId) == nullptr)
            return StatusType::FAILURE;

        Team* toDelete= *(teamsHash.find(teamId));

        if(toDelete->get_number_of_players() != 0) {
            int str = toDelete->get_power();
            StrCond strCond = StrCond(str, teamId);
            teamsTree.remove(strCond);
        }
        teamsHash.remove(teamId);

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
    number_of_teams--;
    if(number_of_teams == 0)
        highest_ranked_team_id = -1;
	return StatusType::SUCCESS;
}

StatusType olympics_t::add_player(int teamId, int playerStrength)
{
    if (teamId <= 0 || playerStrength <= 0 )
        return StatusType::INVALID_INPUT;
    try {
        if (teamsHash.find(teamId) != nullptr)
            return StatusType::FAILURE;

        Team* ptrTeam= *(teamsHash.find(teamId));
        Contestant* con = new Contestant(ptrTeam->get_entry(),playerStrength); // not sure about this maybe need to change the way we add contestant (ze tip tipa akum)
        ptrTeam->add_contestant_to_team(con);

        StrCond strCond = StrCond(ptrTeam->get_power(),teamId);

        if(teamsTree.find(strCond) == nullptr)
        {
            teamsTree.insert(strCond,ptrTeam);
        }

        highest_ranked_team_compare(ptrTeam);

    }  catch (std::bad_alloc &error) {
        return StatusType::ALLOCATION_ERROR;
    }   catch (KeyExists &error) {
        return StatusType::FAILURE;
    }


	return StatusType::SUCCESS;
}

StatusType olympics_t::remove_newest_player(int teamId)
{
    if (teamId <= 0 )
        return StatusType::INVALID_INPUT;
    try {
        if (teamsHash.find(teamId) == nullptr)
            return StatusType::FAILURE;
        Team* ptrTeam= *(teamsHash.find(teamId));
        if(ptrTeam->get_number_of_players() == 0)
            return StatusType::FAILURE;

        ptrTeam->remove_newest_player();
        ptrTeam->calc_team_power();

        if(teamId == highest_ranked_team_id)
        {
            Team* current_highest = teamsTree.getBiggest()->getNodeData();
            highest_ranked_team_compare(current_highest); // also updates
        }


    } catch (std::bad_alloc &error) {
        return StatusType::ALLOCATION_ERROR;
    } catch (KeyExists &error) {
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
    Team* currentHighest = *(teamsHash.find(highest_ranked_team_id));
    if (currentHighest->get_power() +currentHighest->get_wins() < toCompare->get_power() + toCompare->get_wins()) {
        highest_ranked_team_id = toCompare->get_team_id();
        highest_ranked_team_rank = toCompare->get_power() + toCompare->get_wins();
    }
}

output_t<int> olympics_t::num_wins_for_team(int teamId)
{
    if (teamId <= 0 )
        return StatusType::INVALID_INPUT;
    int wins=0;
    try {
        if (teamsHash.find(teamId) == nullptr)
            return StatusType::FAILURE;
        Team* ptrTeam= *(teamsHash.find(teamId));
        wins = ptrTeam->get_wins();

    } catch (std::bad_alloc &error) {
        return StatusType::ALLOCATION_ERROR;
    }
    return wins;
}

output_t<int> olympics_t::get_highest_ranked_team()
{
    return highest_ranked_team_rank;
}

StatusType olympics_t::unite_teams(int teamId1, int teamId2)
{
	// TODO: Your code goes here
    return StatusType::SUCCESS;
}

output_t<int> olympics_t::play_tournament(int lowPower, int highPower)
{
    // TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}
