#include "Poker.hpp"
#include <iostream>
#include <numeric>
using namespace std;
using namespace Poker;

//PLAYER CLASS
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
Player::void setplayers(Player* head, int n){
  for(int i = 0; i < n; i++){
    Player* newPlayer = new Player(i)
    newPlayer->next = player;
    player = newPlayer;
  }
}
Player::void pushCard(Card c){this->card = c;}
Player::string getName(){return this->name;}
Player::vector<Card> getHand(){return this->hand;}
Player::float getMoney(){return this->money;}
Player::int getChance(){return this->chance;}

//POKER CLASS
Poker::Poker(){
  player = nullptr;
}
Poker::~Poker(){
  cout << "Cleaning up table." << endl;
}
Poker::void deal(){
  table.deck = Poker::shuffle();
  Player* turn = player;
  while(turn != nullptr){
    turn->hand.push_back(deck.top());
    deck.pop();
    turn = turn->next;
  }
}
Poker::stack<Card> shuffle(){

}
Poker::void fold(){

}
Poker::void raise(){

}
Poker::void check(){

}
Poker::void bet(){

}
Poker::void call(){

}
