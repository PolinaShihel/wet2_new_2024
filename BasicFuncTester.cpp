

#include "olympics24a2.h"
#include <iostream>
#include <string>

using namespace std;
static const char *StatusTypeStr[] =
{
   	"SUCCESS",
	"ALLOCATION_ERROR",
	"INVALID_INPUT",
	"FAILURE"
};

void print( StatusType res)
{
	cout <<   StatusTypeStr[(int) res] ;
}

void print( output_t<int> res)
{
    if (res.status() == StatusType::SUCCESS) {
	    cout  << StatusTypeStr[(int) res.status()] << ", " << res.ans() ;
    } else {
	    cout  << StatusTypeStr[(int) res.status()] ;
    }
}

int main() {
    olympics_t ol = olympics_t();
    olympics_t ol2 = olympics_t();
    cout << "checking the basics of team: adding,removing : " << endl;
    print(ol.add_team(1)); cout << " == SUCCESS" <<endl;
    print(ol.add_team(1)); cout << " == FAILURE" <<endl;      // team exist
    print(ol.add_team(0)); cout << " == INVALID_INPUT" <<endl;   // teamid <=0
    print(ol.remove_team(1)); cout << " == SUCCESS" <<endl;
    print(ol.remove_team(1)); cout << " == FAILURE" <<endl;   // team doesnt exist
    print(ol.add_team(1)); cout << " == SUCCESS" <<endl;
    print(ol.add_team(2)); cout << " == SUCCESS" <<endl;
    print(ol.add_team(3)); cout << " == SUCCESS" <<endl;

    cout<< endl << "checking the basics of team: adding players,highest rank: " << endl;
    print(ol.get_highest_ranked_team()); cout << " == SUCCESS , 0" <<endl;    // empty teams
    print(ol2.get_highest_ranked_team()); cout << " == SUCCESS , -1" <<endl;  // no teams
    print(ol.add_player(1,11)); cout << " == SUCCESS" <<endl;
    print(ol.add_player(1,0)); cout << " == INVALID_INPUT" <<endl;   // str <=0
    print(ol.add_player(6,10)); cout << " == FAILURE" <<endl;         // team doesnt exist
    print(ol.add_player(0,10)); cout << " == INVALID_INPUT" <<endl;   //teamid <=0
    print(ol.get_highest_ranked_team());cout << " == SUCCESS , 11" <<endl;  // only 1 player
    print(ol.add_player(1,10)); cout << " == SUCCESS" <<endl;
    print(ol.add_player(1,9)); cout << " == SUCCESS" <<endl;
    print(ol.get_highest_ranked_team());cout << " == SUCCESS , 27" <<endl;  // 9*3
    print(ol.add_player(1,16)); cout << " == SUCCESS" <<endl;
    print(ol.get_highest_ranked_team());cout << " == SUCCESS , 40" <<endl;  // 10*4
    print(ol.add_player(2,11)); cout << " == SUCCESS" <<endl;
    print(ol.add_player(2,7)); cout << " == SUCCESS" <<endl;
    print(ol.add_player(2,13)); cout << " == SUCCESS" <<endl;
    print(ol.get_highest_ranked_team());cout << " == SUCCESS , 40" <<endl;  // 10*4
    print(ol.add_player(2,12)); cout << " == SUCCESS" <<endl;
    print(ol.get_highest_ranked_team());cout << " == SUCCESS , 44" <<endl;  // 11*4

    cout<< endl << "checking the basics of team: remove_newest player and highest ranked: " << endl;
    // in team 1 : 11,10,9,16
    // in team 2 : 11,7,13,12
    print(ol.remove_newest_player(7)); cout << " == FAILURE" <<endl; // team doesnt exist
    print(ol.remove_newest_player(0)); cout << " == INVALID_INPUT" <<endl; // team <=0
    print(ol.remove_newest_player(2)); cout << " == SUCCESS" <<endl; //team2: 11,7,13    team1:11,10,9,16
    print(ol.get_highest_ranked_team()); cout << " == SUCCESS , 40" <<endl;  // 10*4 teamid : 1
    print(ol.remove_newest_player(1)); cout << " == SUCCESS" <<endl;   //team2: 11,7,13    team1:11,10,9
    print(ol.get_highest_ranked_team()); cout << " == SUCCESS , 27" <<endl;  // 9*3 teamid : 1
    print(ol.remove_newest_player(1)); cout << " == SUCCESS" <<endl; //team2: 11,7,13    team1:11,10
    print(ol.get_highest_ranked_team()); cout << " == SUCCESS , 21" <<endl;  // 7*3 teamid : 2
    print(ol.remove_newest_player(2)); cout << " == SUCCESS" <<endl;  //team2: 11,7    team1:11,10
    print(ol.get_highest_ranked_team()); cout << " == SUCCESS , 20" <<endl;  // 10*2 teamid : 1
    print(ol.remove_newest_player(2)); cout << " == SUCCESS" <<endl;  //team2: 11    team1:11,10
    print(ol.get_highest_ranked_team()); cout << " == SUCCESS , 20" <<endl;  // team2 rank: 11 ,team1 rank :20
    print(ol.remove_newest_player(1)); cout << " == SUCCESS" <<endl; //team2: 11    team1:11
    print(ol.get_highest_ranked_team()); cout << " == SUCCESS , 11" <<endl;  // team2rank: 11 ,team1rank:11
    print(ol.remove_newest_player(1)); cout << " == SUCCESS" <<endl;    //team2: 11    team1:0
    print(ol.get_highest_ranked_team()); cout << " == SUCCESS , 11" <<endl;  // team2rank: 11 ,team1rank:0
    print(ol.remove_newest_player(2)); cout << " == SUCCESS" <<endl;    //team2: 0    team1:0
    print(ol.get_highest_ranked_team()); cout << " == SUCCESS , 0" <<endl;  // team2rank: 0 ,team1rank:0



    //adding players to the next test
    print(ol.add_player(2,11)); cout << " == SUCCESS" <<endl;
    print(ol.add_player(2,5)); cout << " == SUCCESS" <<endl;
    print(ol.add_player(2,16)); cout << " == SUCCESS" <<endl;
    print(ol.add_player(2,10)); cout << " == SUCCESS" <<endl;
    print(ol.add_player(1,10)); cout << " == SUCCESS" <<endl;
    print(ol.add_player(1,6)); cout << " == SUCCESS" <<endl;
    print(ol.add_player(1,8)); cout << " == SUCCESS" <<endl;
    print(ol.add_player(1,9)); cout << " == SUCCESS" <<endl;
    print(ol.add_player(3,20)); cout << " == SUCCESS" <<endl;
    print(ol.add_player(3,21)); cout << " == SUCCESS" <<endl;



    cout<< endl << "checking the basics of team: play match and number of wins: " << endl;
    //team1 players: 10,6,8,9     power:8*4=32
    //team2 players: 11,5,16,10   power 10*4 = 40
    //team3 players: 20,22        power 20*2 = 40
    print(ol.get_highest_ranked_team()); cout << " == SUCCESS , 40 "<<endl;
    print(ol.num_wins_for_team(1)); cout << " == SUCCESS , 0"<<endl;
    print(ol.num_wins_for_team(9)); cout << " == FAILURE" <<endl;  //  team doest exist
    print(ol.num_wins_for_team(0)); cout << " == INVALID_INPUT" <<endl; // teamid <= 0
    print(ol.play_match(1,0));cout << " == INVALID_INPUT" <<endl; // team2 <=0
    print(ol.play_match(0,1));cout << " == INVALID_INPUT" <<endl; // team1 <=0
    print(ol.play_match(1,1));cout << " == INVALID_INPUT" <<endl; //team1==team2
    print(ol.play_match(1,8)); cout << " == FAILURE" <<endl; // team2 doesnt exist
    print(ol.play_match(7,2)); cout << " == FAILURE" <<endl; // team1 doesnt exist
    print(ol.play_match(7,8)); cout << " == FAILURE" <<endl; // team2 and 1 doesnt exist
    print(ol.play_match(1,2)); cout << " == SUCCESS" <<endl;  //team1 wins : 0      , team2 wins : 1
    print(ol.num_wins_for_team(1)); cout << " == SUCCESS , 0"<<endl;
    print(ol.num_wins_for_team(2)); cout << " == SUCCESS , 1"<<endl;
    print(ol.play_match(1,2)); cout << " == SUCCESS" <<endl;  //team1 wins : 0      , team2 wins : 2
    print(ol.num_wins_for_team(1)); cout << " == SUCCESS , 0"<<endl;
    print(ol.num_wins_for_team(2)); cout << " == SUCCESS , 2"<<endl;
    print(ol.get_highest_ranked_team()); cout << " == SUCCESS , 42 "<<endl;
    print(ol.play_match(3,1)); cout << " == SUCCESS" <<endl;  //team1 wins : 0      , team3 wins : 1
    print(ol.num_wins_for_team(3)); cout << " == SUCCESS , 1"<<endl;
    print(ol.num_wins_for_team(1)); cout << " == SUCCESS , 0"<<endl;
    print(ol.play_match(2,3)); cout << " == SUCCESS" <<endl; //team2 wins : 3      , team3 wins : 1
    print(ol.num_wins_for_team(3)); cout << " == SUCCESS , 1"<<endl;
    print(ol.num_wins_for_team(2)); cout << " == SUCCESS , 3"<<endl;
    print(ol.get_highest_ranked_team()); cout << " == SUCCESS , 43 "<<endl;

    cout<< endl << "checking the basics of unite team " << endl;
    //team1 players: 10,6,8,9     power:8*4=32
    //team2 players: 11,5,16,10   power 10*4 = 40 + 3
    //team3 players: 20,22        power 20*2 = 40 + 1
    print(ol.unite_teams(1,0));cout << " == INVALID_INPUT" <<endl; // team2 <=0
    print(ol.unite_teams(0,1));cout << " == INVALID_INPUT" <<endl; // team1 <=0
    print(ol.unite_teams(1,1));cout << " == INVALID_INPUT" <<endl; //team1==team2
    print(ol.unite_teams(1,8)); cout << " == FAILURE" <<endl; // team2 doesnt exist
    print(ol.unite_teams(7,2)); cout << " == FAILURE" <<endl; // team1 doesnt exist
    print(ol.unite_teams(7,8)); cout << " == FAILURE" <<endl; // team2 and 1 doesnt exist
    print(ol.unite_teams(1,3)); cout << " == SUCCESS" <<endl;  // unite team3 into team1   TODO fails here
    //team1 players: 10,6,8,9,20,22     power:9*6=54
    //team2 players: 11,5,16,10    power 10*4 = 40 + 3
    print(ol.unite_teams(1,3)); cout << " == FAILURE" <<endl;  // team3 doesnt exist anymore
    print(ol.num_wins_for_team(1)); cout << " == SUCCESS , 0 "<<endl;
    print(ol.get_highest_ranked_team()); cout << " == SUCCESS , 54 "<<endl;

//
//    cout<< endl << "some more tests: " << endl;
//    print(ol.remove_newest_player(2));
//    print(ol.get_highest_ranked_team()); cout << " == SUCCESS , 41 "<<endl; // team3 rank 41
//    print(ol.remove_newest_player(3)); //team1 players: 10,6,8,9     power:8*4=32 //team2 players: 11,5,16   power 5*3 = 15 +3=18 //team3 players: 20, power 20*1 +1 = 21
//    print(ol.get_highest_ranked_team()); cout << " == SUCCESS , 32 "<<endl; // team1 rank 32
//    print(ol.remove_newest_player(1)); //team1 players: 10,6,8     power:6*3=18 //team2 players: 11,5,16   power 5*3 = 15 +3=18 //team3 players: 20, power 20*1 +1 = 21
//    print(ol.get_highest_ranked_team()); cout << " == SUCCESS , 21 "<<endl; // team1 rank 21
//

    return 0;
}