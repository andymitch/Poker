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


enum Suit{club, diamond, heart, spade};
enum Rank{2,3,4,5,6,7,8,9,10,J,Q,K,A}; //0-12 (13)
enum Risk{low, mid, high};

struct Card{
  Suit suit;
  Rank rank;
  Card(suits s, ranks r){
    suit = s;
    rank = r;
  }
  void printCard(Card);
};

class Table{
  vector<Card> dealer; //push cards from deck to dealer
  stack<Card> deck;
  float bigBlind, littleBlind, pot;
public:
  void shuffle(); //generate new stack of shuffled cards
  void deal(); // deal ONE card to dealer and each player
  void raisePot(float); //add money to pot
  void peekPot(); //peek at pot
  void setBlind();
};

struct Player{
  string name;
  Player* next;
  vector<Card> hand;
  float money;
  int chance;
  Risk risk;
  Player(string);
  Player(int);
  void pushCard(Card);
};

//POKER NAMESPACE
/*****************************************************************************/

namespace poker{

  class Poker: public Player, public Table{
    Table table;
    Player* player;
  public:
    Poker();
    ~Poker();
    void setplayers(int);
    void menu();
    void fold(); //quits hand, doesn't have to bet()
    void raise(); //raise bid and move on, still have to bet()
    void check(); //move on without raising bit, still have to bet()
    void bet(); //put bid amount into pot from player money
    void call(); //calls highHand() for every player: turn->chance = highHand();
    int highHand(hand, deck); //finds best cards in player's hand and returns their chance.
  }

}

//BLACKJACK NAMESPACE
/*****************************************************************************/

namespace blackjack{
  void menu();
  Table table;
  Player blackjack;

  void play(string); //main function
}

//MESS...
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
