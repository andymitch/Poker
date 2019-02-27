#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>//random_shuffle
using namespace std;


enum suits{club, diamond, heart, spade}; //0-3 (4)
enum ranks{2,3,4,5,6,7,8,9,10,J,Q,K,A}; //0-12 (13)

struct Card{
  suits suit;
  ranks rank;
  Card(suits s, ranks r){
    suit = s;
    rank = r;
  }
};

struct Player{
  string name;
  Player* next;
  vector <Card> hand; //push cards from deck to hand (vector in order to reference cards)
  float money;
  Player(string n); //human constructor
  Player(int); //bot constructor
  ~Player();
  void table(int);
};

class Poker{
  vector<Card> dealer; //push cards from deck to dealer (vector in order to reference cards)
  stack<Card> deck;
  float pot;
  Player* player; //reference to player list
public:
  Poker();
  ~Poker();
  void deal(); //push ONE card from deck to players' hands
  stack<Card> shuffle(); //generate new stack of shuffled cards
  int rules(Player);
};
