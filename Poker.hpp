#pragma once
#include <iostream>
#include <vector>
#include <numeric>//iota
#include <algorithm>//random_shuffle
using namespace std;


enum suits{club, diamond, heart, spade};
enum ranks{2,3,4,5,6,7,8,9,10,J,Q,K,A};

class Card{
  suits suit;
  ranks rank;
public:
  Card(suits s, ranks r){
    suit = s;
    rank = r;
  }
  ~Card();
};

struct Player{
  string name;
  Player* next;
  vector <Card> hand;
  float money;
};

class Poker{
  Player* dealer;
  Player* player;
  vector<Card> deck;
  float pot;
public:
  Poker(int i){
    if(i == 2) player->name = "Alex";
    else if(i == 3) player->name = "Brian";
    else if(i == 4) player->name = "Carl";
    else if(i == 5) player->name = "Derrek";
    else player->name = "Mike";
    player->next = nullptr;
  }
  Poker(string n){
    player->name = n;
    player->next = nullptr;
  }
  ~Poker(){
    while(player != NULL){
      Player* temp = player;
      player = temp->next;
      delete temp;
    }
  }
  void table(int);
  void deal();
  vector<card> shuffle();
  int rules(Player);
};

//order of linked list: dealer, player, bots...
