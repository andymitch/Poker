#include "Poker.hpp"
#include <iostream>
#include <numeric>
using namespace std;


//PLAYER STRUCT FUNCTIONS:
/****************************************************************************/
Player::Player(string n){
  this->name = n;
  this->next = nullptr;
}

Player::Player(int i){
  if(i == 2) this->name = "Alex";
  else if(i == 3) this->name = "Brian";
  else if(i == 4) this->name = "Carl";
  else if(i == 5) this->name = "Derrek";
  else this->name = "Mike";
  this->next = nullptr;
}

Player::table(int i){
  for(int i = 2; i <= n; i++){
    Player* newPlayer = new Player(i)
    newPlayer->next = player;
    player = newPlayer;
  }
}

//POKER CLASS (DE/CON)STRUCTORS & FUNCTIONS:
/****************************************************************************/
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



int rules(Player* p){
  vector<Card> hand = p->hand;
  /*
  10 royal flush: A,K,Q,J,10 of the same suit
  9 straight flush: 5 cards in sequence of the same suit
  8 four of a kind: 4 cards of the same rank
  7 full house: 3 cards of the same rank with 2 cards of the same rank
  6 flush: 5 cards in the same suit
  5 straight: 5 cards in sequence
  4 three of a kind: 3 cards of the same rank
  3 two pair: 2 pairs of 2 cards in the same rank
  4 pair: 2 cards in the same rank
  1 high card: highest card in hand (cascading if statements so that high card is last resort)
  */
  //precedence: hand->rank->suit
  if(){

  }
}

vector<cards> Poker::shuffle(){ //maybe change container to stack
  vector<Card> deck;
  for(suits i = 0; i < 4; i++){
    for(ranks j = 0; j < 13; j++){
      Card temp = new Card(i,j);
      deck.push_back(temp);
    }
  }
  random_shuffle(deck.begin(), deck.end());
}

void RPNCalculator::push(float num){
  Operand* newOp = new Operand;
  newOp->next = stackHead;
  stackHead = newOp;
  stackHead->number = num;
  return;
}
