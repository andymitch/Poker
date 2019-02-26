#include "Poker.hpp"
#include <iostream>
#include <numeric>
using namespace std;


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

Poker::table(int n){
  for(int i = 2; i <= n; i++){
    Player* newBot = new Player(i) // thats not right; it needs to be Poker(i) but remain Player*
  }
}

void RPNCalculator::push(float num){
  Operand* newOp = new Operand;
  newOp->next = stackHead;
  stackHead = newOp;
  stackHead->number = num;
  return;
}
