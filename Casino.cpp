#include "Casino.hpp"
#include <iostream>
#include <vector>
using namespace std;


//CARD STRUCT
/****************************************************************************/
void Card:: printCard(Card card){
  cout << card.rank;
  Suit s = card.suit;
  switch(s){
    case club: cout << "\u2663";
    break;
    case diamond: cout << "\u2666";
    break;
    case heart: cout << "\u2665";
    break;
    case spade: cout << "\u2660";
    break;
    default: break;
  }
}

//TABLE STRUCT
/****************************************************************************/
Table::Table(){
  deck = shuffle();
  littleBlind = bigBlind = 0;
  pot = 0;
}
void Table::shuffle(){
  while(!deck.empty()) deck.pop(); //clear deck
  vector<Card> _deck;
  for(Suit i = 0; i < 4; i++){
    for(Rank j = 0; j < 13; j++){
      Card temp = new Card(i,j);
      _deck.push_back(temp);
    }
    suit
  }
  random_shuffle(_deck.begin(), _deck.end());
  while(!_deck.empty()){
    deck.push(_deck.back());
    _deck.pop();
  }
}
void Table::deal(){
  deck = shuffle();
  Player* turn = player;
  while(turn != nullptr){
    turn->hand.push_back(deck.top());
    deck.pop();
    turn = turn->next;
  }
}
void Table::raisePot(float raise){
  pot += raise;
}
void Table::peekPot(){
  return pot;
}
void Table::setBlind(){
  if(littleBlind == 0) littleBlind = .50;
  else littleBlind *= 2;
  bigBlind = littleBlind * 2;
}

//PLAYER STRUCT
/****************************************************************************/
Player::Player(string n){
  name = n;
  money = 100;
  chance = 0;
  next = nullptr;
}
Player::Player(int i){
  if(i == 0) name = "Alex";
  else if(i == 1) name = "Brian";
  else if(i == 2) name = "Carl";
  else if(i == 3) name = "Derrek";
  else if(i == 4)name = "Mike";
  money = 100;
  chance = 0;
  next = nullptr;
}
void Player::pushCard(Card c){
  card = c;
}
string Player::getName(){
  return this->name;
}
vector<Card> Player::getHand(){
  return this->hand;
}
float Player::getMoney(){
  return this->money;
}
int Player::getChance(){
  return this->chance;
}
