#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>
#include <thread> //this_thread::sleep_for
#include <chrono> //chrono::seconds
#include <cstdlib>
using namespace std;


//CARD STRUCT
/******************************************************************************/
enum Suit{club, diamond, heart, spade};
enum Rank{Two = 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace};

struct Card{
    Rank rank;
    Suit suit;
    Card();
    Card(Rank r, Suit s){
        rank = r;
        suit = s;
    }
    string printRank(Rank);
    string printSuit(Suit);
    string printCard();
};

Rank& operator++(Rank& r){return r = Rank(static_cast<int>(r)+1);}
Suit& operator++(Suit& s){return s = Suit(static_cast<int>(s)+1);}
Rank& operator--(Rank& r){return r = Rank(static_cast<int>(r)-1);}
Suit& operator--(Suit& s){return s = Suit(static_cast<int>(s)-1);}
ostream& operator<<(ostream& out, Card& obj){return out << obj.printCard();}

string Card::printRank(Rank rank){
    switch (rank){
        case Two: return "2";
        case Three: return "3";
        case Four: return "4";
        case Five: return "5";
        case Six: return "6";
        case Seven: return "7";
        case Eight: return "8";
        case Nine: return "9";
        case Ten: return "10";
        case Jack: return "J";
        case Queen: return "Q";
        case King: return "K";
        case Ace: return "A";
        default: return "VOID";
    }
}
string Card::printSuit(Suit suit){
    switch(suit){
        case club: return "\u2663";
        case diamond: return "\u2666";
        case heart: return "\u2665";
        case spade: return "\u2660";
        default: return "VOID";
    }
}
string Card::printCard(){
  return ("[" + printRank(rank) + printSuit(suit) + "]");
}

//PLAYER STRUCT
/******************************************************************************/
struct Player{
  string name;
  vector<Card> hand;
  float money, bid, allIn;
  int chance;
  bool call, fold, turn;
  Player(){}
  Player(int i){
    if(i == 0) name = "You";
    else if(i == 1) name = "Alex";
    else if(i == 2) name = "Brian";
    else if(i == 3) name = "Carl";
    else if(i == 4) name = "Derrek";
    else if(i == 5) name = "Earl";
    money = 100; chance = 0; bid = 0; allIn = 0;
    call = fold = turn = false;
  }
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//POKER CLASS
/****************************************************************************/
class Poker{
  stack<Card> deck;
  vector<Card> dealer;
  vector<Player> players;
  float bigBlind, littleBlind, pot, bet;
  int turn;
public:
  Poker(int);
  Player* user;
  float min(){return littleBlind;}
  void gameOver();
  bool isBroke(Player);
  bool isUser(Player);
  vector<Player*> getWinners();
  vector<Player> setPlayers(int);
  stack<Card> getDeck();
  void setBlind();
  void printTable(bool);
  void printWinners(vector<Player*>);
  void lay();
  void deal();
  float raise(Player*);
  int getMove(Player*);
  bool iscall();
  void placeBets(int,bool);
  void call();
  bool reset(float);
  vector<vector<Card>> sortHand(Player&);
  void setChance(); //set every player's chance
};
