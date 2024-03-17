

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
    print(ol.play_match(1,2)); cout << " == SUCCESS , 2" <<endl;  //team1 wins : 0      , team2 wins : 1
    print(ol.num_wins_for_team(1)); cout << " == SUCCESS , 0"<<endl;
    print(ol.num_wins_for_team(2)); cout << " == SUCCESS , 1"<<endl;
    print(ol.play_match(1,2)); cout << " == SUCCESS , 2" <<endl;  //team1 wins : 0      , team2 wins : 2
    print(ol.num_wins_for_team(1)); cout << " == SUCCESS , 0"<<endl;
    print(ol.num_wins_for_team(2)); cout << " == SUCCESS , 2"<<endl;
    print(ol.get_highest_ranked_team()); cout << " == SUCCESS , 42 "<<endl;
    print(ol.play_match(3,1)); cout << " == SUCCESS , 3" <<endl;  //team1 wins : 0      , team3 wins : 1
    print(ol.num_wins_for_team(3)); cout << " == SUCCESS , 1"<<endl;
    print(ol.num_wins_for_team(1)); cout << " == SUCCESS , 0"<<endl;
    print(ol.play_match(2,3)); cout << " == SUCCESS , 2" <<endl; //team2 wins : 3      , team3 wins : 1
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
    print(ol.unite_teams(1,3)); cout << " == SUCCESS" <<endl;  // unite team3 into team1
    //team1 players: 10,6,8,9,20,22     power:9*6=54
    //team2 players: 11,5,16,10    power 10*4 = 40 + 3
    print(ol.unite_teams(1,3)); cout << " == FAILURE" <<endl;  // team3 doesnt exist anymore
    print(ol.num_wins_for_team(1)); cout << " == SUCCESS , 0 "<<endl;
    print(ol.get_highest_ranked_team()); cout << " == SUCCESS , 54 "<<endl;
    print(ol.num_wins_for_team(3)); cout << " == FAILURE"<<endl; // team doesnt exist

    print(ol.add_team(3)); cout << " == SUCCESS" <<endl;
    print(ol.add_player(3,2));cout << " == SUCCESS" <<endl;
    print(ol.add_player(3,23));cout << " == SUCCESS" <<endl;
    print(ol.add_player(3,15));cout << " == SUCCESS" <<endl;
    print(ol.add_player(3,18));cout << " == SUCCESS" <<endl;
    print(ol.num_wins_for_team(3)); cout << " == SUCCESS ,0"<<endl; // team doesnt exist

    //team1 players: 10,6,8,9,20,22     power:9*6=54
    //team2 players: 11,5,16,10    power 10*4 = 40 + 3
    //team3 players: 2,23,12,18    power: 15*4 = 60
    print(ol.get_highest_ranked_team()); cout << " == SUCCESS , 60 "<<endl;
    print(ol.play_match(1,2)); cout << " == SUCCESS , 1 "<<endl;
    print(ol.play_match(1,2));cout << " == SUCCESS , 1 "<<endl;
    print(ol.play_match(1,2));cout << " == SUCCESS , 1 "<<endl;
    print(ol.play_match(1,2));cout << " == SUCCESS , 1 "<<endl;
    print(ol.play_match(1,2));cout << " == SUCCESS , 1 "<<endl;
    print(ol.play_match(1,2));cout << " == SUCCESS , 1 "<<endl;
    print(ol.play_match(1,2));cout << " == SUCCESS , 1 "<<endl;
    print(ol.num_wins_for_team(1));cout << " == SUCCESS , 7 "<<endl;
    print(ol.get_highest_ranked_team()); cout << " == SUCCESS , 61 "<<endl;
    print(ol.add_team(4)); cout << " == SUCCESS" <<endl;
    print(ol.add_player(4,77));cout << " == SUCCESS" <<endl;
    print(ol.get_highest_ranked_team()); cout << " == SUCCESS , 77 "<<endl;
    print(ol.remove_team(4));cout << " == SUCCESS" <<endl;
    print(ol.get_highest_ranked_team()); cout << " == SUCCESS , 61 "<<endl;
    //print(ol.remove_newest_player(1)); cout << "SUCCESS" << endl;
    //team1 players: 10,6,8,9,20     power:9*5= 45 + 7 = 52
    //team2 players: 11,5,16,10    power 10*4 = 40 + 3  = 43
    //team3 players: 2,23,12,18    power: 15*4 = 60
    //print(ol.get_highest_ranked_team()); cout << " == SUCCESS , 60 "<<endl;

    cout<< endl << "checking play tournament " << endl;
    //team1 players: 10,6,8,9,20,22    power:9*6=54 + 7 = 61
    //team2 players: 11,5,16,10    power 10*4 = 40 + 3  = 43
    //team3 players: 2,23,12,18    power: 15*4 = 60
    print(ol.add_team(4)); cout << " == SUCCESS" <<endl;
    print(ol.add_player(4,22));cout << " == SUCCESS" <<endl;
    print(ol.add_player(4,30));cout << " == SUCCESS" <<endl;
    print(ol.add_team(5)); cout << " == SUCCESS" <<endl;
    print(ol.add_player(5,60));cout << " == SUCCESS" <<endl;
    print(ol.add_team(6)); cout << " == SUCCESS" <<endl;
    print(ol.add_player(6,20));cout << " == SUCCESS" <<endl;
    print(ol.add_team(7)); cout << " == SUCCESS" <<endl;
    print(ol.add_player(7,30));cout << " == SUCCESS" <<endl;
    print(ol.add_team(8)); cout << " == SUCCESS" <<endl;
    print(ol.add_player(8,30));cout << " == SUCCESS" <<endl;
    print(ol.add_team(9)); cout << " == SUCCESS" <<endl;
    print(ol.add_player(9,40));cout << " == SUCCESS" <<endl;
    print(ol.add_team(10)); cout << " == SUCCESS" <<endl;
    print(ol.add_player(10,77));cout << " == SUCCESS" <<endl;
    //team1 players: 10,6,8,9,20,22    power:9*6=54 + 7 = 61
    //team2 players: 11,5,16,10    power 10*4 = 40 + 3  = 43
    //team3 players: 2,23,12,18    power: 15*4 = 60
    //team4 players: 22,30         power:22*2 = 44
    //team5 players: 60            power: 60
    //team6 players: 20            power: 20
    //team7 players: 30            power: 30
    //team8 players: 30            power: 30
    //team9 players: 40            power: 40
    //team10 players: 77           power: 77
    print(ol.play_tournament(-1,-4));cout << "==INVALID INPUT " <<  endl;
    print(ol.play_tournament(40,-4));cout << "==INVALID INPUT " <<  endl;
    print(ol.play_tournament(-1,20));cout << "==INVALID INPUT " <<  endl;
    print(ol.play_tournament(50,20));cout << "==INVALID INPUT " <<  endl;
    print(ol.play_tournament(40,10));cout << "==INVALID INPUT " <<  endl;
    print(ol.play_tournament(20,70)); cout << "==FAILURE " <<  endl; // not power of 2
   print(ol.play_tournament(30,70)); // (6 ,8,7,2,9,4,1,3,5, 10) (20, 30,30,40,40,44,54,60,60, 77)
    //team1 players: 10,6,8,9,20    power:9*6=54 + 7 = 61 + 1
    //team2 players: 11,5,16,10    power 10*4 = 40 + 3  = 43
    //team3 players: 2,23,12,18    power: 15*4 = 60 + 2
    //team4 players: 22,30         power:22*2 = 44 +1
    //team5 players: 60            power: 60 + 3
    //team6 players: 20            power: 20
    //team7 players: 30            power: 30
    //team8 players: 30            power: 30
    //team9 players: 40            power: 40
    //team10 players: 77           power: 77
    cout << " == SUCCESS , 5" <<endl;
    print(ol.num_wins_for_team(5));cout << " == SUCCESS , 3 "<<endl;// todo fail2 to check why the winner get only 2 wins and not 3
    print(ol.num_wins_for_team(3));cout << " == SUCCESS , 2 "<<endl;
    print(ol.num_wins_for_team(1));cout << " == SUCCESS , 8 "<<endl;
    print(ol.num_wins_for_team(4));cout << " == SUCCESS , 1 "<<endl;
    print(ol.num_wins_for_team(6));cout << " == SUCCESS , 0 "<<endl;
    print(ol.num_wins_for_team(8));cout << " == SUCCESS , 0 "<<endl;
    print(ol.num_wins_for_team(10));cout << " == SUCCESS , 0 "<<endl;
    return 0;
}