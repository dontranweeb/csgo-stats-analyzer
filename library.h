#include <fstream>
using namespace std;
#include <string>

struct Player {
  string name;
  string team;
  double rating[10];
  double highest = -1;
  double lowest = 10000;
  int highest_recency;
  int lowest_recency;
  double average;
};
struct Stats {
  double highest_rating = -1;
  string highest_rating_name;
  double lowest_rating = 10000;
  string lowest_rating_name;
  double highest_average = -1;
  string highest_average_name;
  double lowest_average = 10000;
  string lowest_average_name;
};


bool collect_data(Player arr[], int& n);
void display_all(const Player arr[], int n);
void sorting(Player arr[], int n);
void remove(Player arr[], int& n, string name);
void filter(Player arr[], int& n, string team_name);
void analysis_player (Player arr[], int n, string player_name);
void analysis_all (Player arr[], int n, Stats s);
void analyze_certain_game (Player arr[], int n, Stats s, int choice);