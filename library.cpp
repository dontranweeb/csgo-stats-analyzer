#include <iostream>
#include <string>
#include "library.h"
#include <iomanip>
#include <fstream>
using namespace std;

bool collect_data(Player arr[], int& n){
  ifstream fin("input.dat");
  string url;
  if (fin.is_open() == false){
    return false;
  } 
  else{
    getline (fin, url);
    cout << "This program takes data from HLTV which is a professional stats for counter-strike. CREDIT: " << url << endl;
    do {
      double total = 0;
      getline(fin, arr[n].name, ',');
      //cout << "name collected: " << arr[n].name << endl;
      getline (fin, arr[n].team);
      //cout << "team collected: " << arr[n].team << endl;
      for (int i = 0; i < 10; i++){
        fin >> arr[n].rating[i];
        //cout << "when i is " << i << " rating is ";
        //cout << arr[n].rating[i] << endl;
        total = total + arr[n].rating[i];
    }
      arr[n].average = total / 10;
      n++;
      fin.ignore();
    } while(!fin.eof());
    fin.close();
    return true;
  }
}

void sorting(Player arr[], int n){
  cout << "Sort player based on average rating past 10 games from highest to lowest.\n";
  for (int j = 0; j < n; j++){
    for (int i = j; i > 0 && arr[i-1].average < arr[i].average; i--){
      swap(arr[i-1], arr[i]);
    }
  }
}
void display_all(const Player arr[], int n){
  cout << "Here's the data for Counter-Strike Professional Players in the list\n";
  cout << "Name: " << setw(3) << " " << "Team: " << setw(19) <<  "Rating:" << setw(10) << right << setw(55) << "Average:"  << endl;
  cout << left;
  cout << setfill('=') << setw(80) << "=" << endl;
  cout << setfill(' ');
  for (int i = 0; i < n; i++){
    cout << left << setw(10) << arr[i].name << setw(15) << arr[i].team << setw(2);
    for (int j = 0; j < 10; j++){
      cout << ' ' << setw(4);
      cout <<  arr[i].rating[j];
    }
    cout << right << ' ' << setw(10) << arr[i].average << setw(10)<< endl;
  }
}
void remove(Player arr[], int& n, string name){
  int index = 0;
  while (index < n && arr[index].name != name){
    index ++;
  }  
  if (index != n) {
    for (int i = index; i < n; i ++){
      arr[i] = arr[i+1];
    }
    n--;
  }
  else{
    cout << "Not found.\n";
  }
}


void filter(Player arr[], int& n, string team_name){
  cout << "\nHere's the data for Counter-Strike Professional Players in the list\n";
  cout << "Name: " << setw(3) << " " << "Team: " << setw(19) <<  "Rating:" << setw(10) << right << setw(55) << "Average:"  << endl;
  cout << left;
  cout << setfill('=') << setw(80) << "=" << endl;
  cout << setfill(' ');
  for (int i = 0; i < n; i++){
    if (arr[i].team == team_name){
      i++;
    }
    cout << left << setw(10) << arr[i].name << setw(15) << arr[i].team << setw(2);
    for (int j = 0; j < 10; j++){
      cout << ' ' << setw(4);
      cout <<  arr[i].rating[j];
    }
    cout << right << ' ' << setw(10) << arr[i].average << setw(10)<< endl;
  }
}


void analysis_player (Player arr[], int n, string player_name){
  int index = 0;
  while (index < n && arr[index].name != player_name){
    index ++;
  }  
  if (index != n) {
    for (int j = 0; j < 10; j++){
      if (arr[index].rating[j] > arr[index].highest){
        arr[index].highest = arr[index].rating[j];
        arr[index].highest_recency = j + 1;
      }
      if (arr[index].rating[j] < arr[index].lowest){
        arr[index].lowest = arr[index].rating[j];
        arr[index].lowest_recency = j + 1 ;
      }
    }
    double range = 0;
    range = arr[index].highest - arr[index].lowest;
    cout << arr[index].name << " has the highest rating at " << arr[index].highest << " at game " << arr[index].highest_recency <<  " and the lowest rating at "<< arr[index].lowest << " at game " << arr[index].lowest_recency << ". The player has an average rating of " << arr[index].average << ". The player's rating range from " << arr[index].lowest  << " to " << arr[index].highest  << " is " << range << ". The player currently plays for " << arr[index].team << ".\n";
  }
  else{
    cout << "Not found.\n";
  }
}

void analysis_all (Player arr[], int n, Stats s){
  unsigned above_1_tally = 0;
  unsigned below_1_tally = 0;
  for (int i = 0; i < n; i++){
    for (int j = 0; j < 10; j++){
      if (arr[i].rating[j] > s.highest_rating){
        s.highest_rating = arr[i].rating[j];
        s.highest_rating_name = arr[i].name;
      }
      if (arr[i].rating[j] < s.lowest_rating){
        s.lowest_rating = arr[i].rating[j];
        s.lowest_rating_name = arr[i].name;
      }
      }
      if (arr[i].average > s.highest_average){
        s.highest_average = arr[i].average;
        s.highest_average_name = arr[i].name;
      }
      if (arr[i].average < s.lowest_average){
        s.lowest_average = arr[i].average;
        s.lowest_average_name = arr[i].name;
      }
      if (arr[i].average > 1){
        above_1_tally ++;
      }
      if (arr[i].average <= 1){
        below_1_tally++;
      }
    }
  cout << "The highest rating in the list is " << s.highest_rating_name << " with a rating of " << s.highest_rating << ". The one with the lowest rating in the list is " << s.lowest_rating_name << " with a rating of " << s.lowest_rating << ". The player with the highest average rating is " << s.highest_average_name << " with a rating of " << s.highest_average << ". The player with the lowest average rating is " << s.lowest_average_name << " with a rating of " << s.lowest_average << ". There is " << above_1_tally << " player(s) with an average rating of 1 or more. There is " << below_1_tally <<" with an equal to or less than 1 rating.\n";
}
void analyze_certain_game (Player arr[], int n, Stats s, int game){
  game--;
  for (int i = 0; i < n; i++){
    if (arr[i].rating[game] > s.highest_rating){
      s.highest_rating = arr[i].rating[game];
      s.highest_rating_name = arr[i].name;
      }
    if (arr[i].rating[game] < s.lowest_rating){
      s.lowest_rating = arr[i].rating[game];
      s.lowest_rating_name = arr[i].name;
    }
}
  game++;
  cout << "At game " << game << ", " << s.highest_rating_name << " has the highest rating of " << s.highest_rating << " while " << s.lowest_rating_name << " has the lowest rating of " << s.lowest_rating << ".\n";
}