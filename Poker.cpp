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

stack<Card> Poker::shuffle(){
  vector<Card> _deck;
  for(suits i = 0; i < 4; i++){
    for(ranks j = 0; j < 13; j++){
      Card temp = new Card(i,j);
      _deck.push(temp);
    }
  }
  random_shuffle(deck.begin(), deck.end());
  stack<Card> deck;
  while(!deck.empty()){
    deck.push(_deck.end());
    _deck.pop();
  }
  return deck;
}

void Poker::deal(){
  deck = shuffle();
  Player* turn = player;
  while(turn != nullptr){
    turn->hand.push_back(deck.top());
    deck.pop();
    turn = turn->next;
  }
}



void RPNCalculator::push(float num){
  Operand* newOp = new Operand;
  newOp->next = stackHead;
  stackHead = newOp;
  stackHead->number = num;
  return;
}
