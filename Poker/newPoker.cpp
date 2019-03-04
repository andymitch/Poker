#include "Poker.hpp"
#include <iostream>
#include <numeric>
using namespace std;
using namespace Poker;



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
