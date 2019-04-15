#ifndef CASINO_HPP
#define CASINO_HPP
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
enum Rank{Two,Three,Four,Five,Six,Seven,Eight,Nine,Ten,Jack,Queen,King,Ace};

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
        case Ten: return "T";
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
  float money;
  float makeBet(float bet){
    money -= bet;
    return bet;
  }
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//PLAY
/****************************************************************************/
void playPoker();

//PLAYER STRUCT
/****************************************************************************/
struct PokerPlayer : public Player{
  int chance;
  bool call, fold, turn;
  PokerPlayer();
  PokerPlayer(int);
};

//POKER CLASS
/****************************************************************************/
class Poker{
  stack<Card> deck;
  vector<Card> dealer;
  vector<PokerPlayer> players;
  float bigBlind, littleBlind, pot, bet;
  PokerPlayer* USER;
public:
  Poker(int);
  PokerPlayer getUser();
  bool isBroke(PokerPlayer);
  bool isUser(PokerPlayer);
  PokerPlayer getWinner();
  vector<PokerPlayer> setPlayers(int);
  stack<Card> getDeck();
  void setBlind();
  void printTable();
  void printWinner(PokerPlayer);
  void lay();
  void deal();
  float raise(PokerPlayer);
  int getMove(PokerPlayer);
  bool iscall();
  void makeBet();
  void call();
  void reset();
  vector<vector<Card>> sortHand(PokerPlayer&);
  void setChance(); //set every player's chance
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//PLAY
/****************************************************************************/
//void playBlackjack();

//PLAYER STRUCT
/****************************************************************************/
/*struct BlackjackPlayer : public Player{
  bool hit, stay;
  BlackjackPlayer(){}
};*/

//BLACKJACK CLASS
/****************************************************************************/

#endif
