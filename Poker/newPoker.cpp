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

void Poker::setPlayers(int n){
  for(int i = 0; i < n; i++){
    Player* newPlayer = new Player(i)
    newPlayer->next = player;
    player = newPlayer;
  }
  string name;
  cout << "What is your name?: ";
  cin >> name;
  cout << endl;
  Player* newPlayer = new Player(name);
  cin.ignore(); //MAY CAUSE AN INPUT FAULT
  newPlayer->next = player;
  player = newPlayer;
}


void Poker::deal(){
  table.deck = Poker::shuffle();
  Player* turn = player;
  while(turn != nullptr){
    turn->hand.push_back(deck.top());
    deck.pop();
    turn = turn->next;
  }
}
stack<Card> Poker::shuffle(){

}
void Poker::fold(){

}
void Poker::raise(){

}
void Poker::check(){

}
void Poker::bet(){

}
void Poker::call(){

}
