/**************************************************************
struct table
struct player
class player:poker
class player:blackjack
*/

//consolidate Poker.hpp and Blackjack.hpp to this Casino.hpp

/*
Casino.cpp
    ^
Casino.hpp > Poker.cpp
           > PokerRules.cpp
           > Blackjack.cpp
***************************************************************/

#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>//random_shuffle
using namespace std;


struct Card{
  suits suit;
  ranks rank;
  Card(suits s, ranks r){
    suit = s;
    rank = r;
  }
};

struct Table: public Card{
  vector<Card> dealer; //push cards from deck to dealer
  stack<Card> deck;
  float bid;
  float pot;
  stack<Card> shuffle(); //generate new stack of shuffled cards
};

class Player: public Card{
  string name;
  Player* next;
  vector<Card> hand;
  float money;
  int chance;
public:
  Player(string, float, int);
  Player(int);
  void setplayers(Player*);
  void pushCard(Card);
  string getName();
  vector<Card> getHand();
  float getMoney();
  int getChance();
};



namespace poker{
  Table table;
  Player p;
  p.setPlayers(); //reference country .cpp
  void newGame(string name, int opponents){
    Player* player = new Player(name);
    p.setplayers()
  }
  void menu();
  void fold(); //quits hand, doesn't have to bet()
  void raise(); //raise bid and move on, still have to bet()
  void check(); //move on without raising bit, still have to bet()
  void bet(); //put bid amount into pot from player money
  void call(); //calls highHand() for every player: turn->chance = highHand();
  int highHand(hand, deck); //finds best cards in player's hand and returns their chance.

  void play(string); //main function
}

namespace blackjack{
  void menu();
  Table table;
  Player play;

  void play(string); //main function
}

/****************************************************************************/


class Poker: public Player, public Table{
  Table table;
  Player* player;
public:
  Poker();
  ~Poker();
  void deal(); //push ONE card from deck to players' hands, burns one, push one to dealer.
  stack<Card> shuffle(); //generate new stack of shuffled cards
  void fold(); //quits hand, doesn't have to bet()
  void raise(); //raise bid and move on, still have to bet()
  void check(); //move on without raising bit, still have to bet()
  void bet(); //put bid amount into pot from player money
  void call(); //calls highHand() for every player: turn->chance = highHand();
  int highHand(hand, deck); //finds best cards in player's hand and returns their chance.
  void printWinner(Player*);
};

class Blackjack: public Player{

};
