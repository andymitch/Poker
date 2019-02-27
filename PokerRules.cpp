#include "Poker.hpp"
#include <iostream>
#include <algorythm>
using namespace std;


bool Poker::highest(Card a, Card b){
  if(a.rank > b.rank) return true;
  else if(a.rank < b.rank) return false;
  else{
    if(a.suit > b.suit) return true;
    else return false;
  }
}

bool Poker::royalFlush(vector<Card> a){

}

bool Poker::straightFlush(vector<Card> a){

}

bool fourKind(vector<Card> a){

}

bool fullHouse(vector<Card> a){

}

bool flush(vector<Card> a){

}

bool straight(vector<Card> a){

}

bool threeKind(vector<Card> a){

}

bool twoPair(vector<Card> a){

}

bool pair(vector<Card> a){

}

bool highCard(vector<Card> a){

}

bool Poker::rules(vector<Card> a){
  int highest = 0, temp, pos;
  suit highsuit = club; //lowest suit
  rank highrank = 2;
  for(i = 0; i < a.size(); i++){
    temp = count(a.begin(), a.end(), a[i]);
    if(temp > highest){
      highest = temp;
      pos = i;
    }else if(temp == highest){
      if(a[i].rank > highrank){
        highrank = a[i].rank;
        //?
      }else if(a[i].rank == highrank){
        if(a[i].suit > highsuit){
          highsuit = a[i].suit;
          //?
        }
      }
    }
  }


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
}
