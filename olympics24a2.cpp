#include "olympics24a2.h"

olympics_t::olympics_t() : teamsHash(), highest_ranked_team_id(-1), number_of_teams(0) ,teamsTree() {}

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

        Team toAdd = Team(teamId);
        teamsHash.insert(teamId,toAdd);
        if(number_of_teams==0)
            highest_ranked_team_id = teamId;

    }  catch (std::bad_alloc &error) {
         return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

StatusType olympics_t::remove_team(int teamId)
{
    if (teamId <= 0)
        return StatusType::INVALID_INPUT;
    try {
        if(teamsHash.find(teamId) == nullptr)
            return StatusType::FAILURE;

        //TODO: check if need to update highest ranked team if
        //if(highest_ranked_team_id == teamId)

        //TODO: remove team from teams tree

        teamsHash.remove(teamId);


    }  catch (std::bad_alloc &error) {
            return StatusType::ALLOCATION_ERROR;
    }   catch (KeyExists &error) {
            return StatusType::FAILURE;
    }

	return StatusType::SUCCESS;
}

StatusType olympics_t::add_player(int teamId, int playerStrength)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType olympics_t::remove_newest_player(int teamId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> olympics_t::play_match(int teamId1, int teamId2)
{
    // TODO: Your code goes here
    return 2008;
}

output_t<int> olympics_t::num_wins_for_team(int teamId)
{
    // TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}

output_t<int> olympics_t::get_highest_ranked_team()
{
    return highest_ranked_team_id;
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
