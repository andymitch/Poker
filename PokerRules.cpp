#include "Casino.hpp"
#include <iostream>
#include <algorythm>
using namespace std;
using namespace Poker;


bool Poker::highest(Card a, Card b){
  if(a.rank > b.rank) return true;
  else if(a.rank < b.rank) return false;
  else{
    if(a.suit > b.suit) return true;
    else return false;
  }
}

int highRank(vector<Card> a){
  Ranks rank = 0;
  for (vector<int>::iterator it = a.begin() ; it != a.end(); ++it)
    if(*it > rank) rank = *it;
  return rank*10;
}

int highSuit(vector<Card> a){
  Suits suit = 0;
  for (vector<int>::iterator it = a.begin() ; it != a.end(); ++it)
    if(*it > suit) suit = *it;
  return suit;
}

//royal flush: A,K,Q,J,10 of the same suit
bool royalFlush(vector<Card> &a){
  //if royal flush, reduce hand to the royal flush. same with other functions.
}

//straight flush: 5 cards in sequence of the same suit
bool straightFlush(vector<Card> &a){

}

//four of a kind: 4 cards of the same rank
bool fourKind(vector<Card> &a){

}

//full house: 3 cards of the same rank with 2 cards of the same rank
bool fullHouse(vector<Card> &a){

}

//flush: 5 cards in the same suit
bool flush(vector<Card> &a){

}

//straight: 5 cards in sequence
bool straight(vector<Card> &a){

}

//three of a kind: 3 cards of the same rank
bool threeKind(vector<Card> &a){

}

//two pair: 2 pairs of 2 cards in the same rank
bool twoPair(vector<Card> &a){

}

//pair: 2 cards in the same rank
bool pair(vector<Card> &a){

}

//high card: highest card in hand
int highCard(vector<Card> a){
  return highRank(a)+highSuit(a);
}

int Poker::highHand(vector<Card> player, vector<Card> dealer){
  //joint hand
  vector<Card> a;
  //accumulate points for player's chance
  chance = 0;
  //merge p and d into a
  merge(player.begin(),player.end(),dealer.begin(),dealer.end(),a.begin());
  //call hands starting from highest, returns chance points based on highest hand acceived.
  if(royalFlush(a)) chance = 9000 + highRank(a) + highSuit(a);
  else if(straightFlush(a))chance = 8000 + highRank(a) + highSuit(a);
  else if(fourKind(a))chance = 7000 + highRank(a) + highSuit(a);
  else if(fullHouse(a))chance = 6000 + highRank(a) + highSuit(a);
  else if(flush(a))chance = 5000 + highRank(a) + highSuit(a);
  else if(straight(a))chance = 4000 + highRank(a) + highSuit(a);
  else if(threeKind(a))chance = 3000 + highRank(a) + highSuit(a);
  else if(twoPair(a))chance = 2000 + highRank(a) + highSuit(a);
  else if(pair(a))chance = 1000 + highRank(a) + highSuit(a);
  else chance = highRank(a) + highSuit(a);
  return chance;
}

string Poker::decoder(int n){
  if(n<9000)
}
