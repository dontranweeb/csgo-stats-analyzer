#include <iostream>
#include "library.h"
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

int main() {
  cout << fixed <<  showpoint << setprecision(2);
  const int CAPACITY = 11;
  char choice;
  Player statistics[CAPACITY];
  Stats analysis;
  int num_players = 0;
  if (collect_data(statistics, num_players) == false){
    cout << "Input file can't open.";
    return 0;
  } 
  else {
    cout << "File has been opened successfully and data has been collected.\n";
  }
  do {
    cout << "\nPick a choice. (1 for display data, 2 for sort data, 3 for remove data, 4 for filter, 5 for one player's analysis, 6 for all player's analysis, 7 for specific game analysis, 8 to end program." << endl;
    cin >> choice;
    if (choice == '1'){
      display_all(statistics, num_players);
    }
    if (choice == '2'){
      sorting(statistics, num_players);
      display_all(statistics, num_players);
    }
    if (choice == '3'){
      string remove_name;
      cout << "Whose name do you want to remove?\n";
      cin.ignore();
      getline(cin,remove_name);
      remove(statistics, num_players, remove_name);
  }
    if (choice == '4'){
      string filter_team;
      cout << "Which team do you want to filter out?\t";
      cin.ignore();
      getline(cin,filter_team);
      filter(statistics, num_players, filter_team);
    }
    if (choice == '5'){
      cout << "What player's rating do you want to analyzed?\t";
      string player_name;
      cin.ignore();
      getline(cin,player_name);
      analysis_player(statistics, num_players, player_name);
    }
    if (choice == '6'){
      analysis_all(statistics, num_players, analysis);
    }
    if (choice == '7'){
      int game_choice;
      cout << "What game do you want to analyze? (1-10)\n";
      cin >> game_choice;
      if (game_choice > 0 && game_choice <=10){
        analyze_certain_game(statistics, num_players, analysis, game_choice);
      } 
      else{
        cout << "Invalid. Please try again.\n";
      }
    }
  }
  while (choice != '8');
} 