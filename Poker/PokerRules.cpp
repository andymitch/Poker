#include "Casino.hpp"
#include <iostream>
#include <algorythm>
using namespace std;
using namespace Poker;


/*bool Poker::highest(Card a, Card b){
  if(a.rank > b.rank) return true;
  else if(a.rank < b.rank) return false;
  else{
    if(a.suit > b.suit) return true;
    else return false;
  }
}*/

int highRank(vector<Card> a){
  Rank rank = 0;
  for (auto i : a)
    if(i->rank > rank) rank = i->rank;
  return rank*10;
}

int highSuit(vector<Card> a){
  Suit suit = 0;
  for (vector<int>::iterator it = a.begin() ; it != a.end(); ++it)
    if(i->suit > suit) suit = i->suit;
  return suit;
}

//royal flush: A,K,Q,J,10 of the same suit
bool royalFlush(vector<Card> &a){
  //if royal flush, reduce hand to the royal flush. same with other functions.
  for(auto i : a){
    if(i->rank == A){
      vector<Card> temp;
      Suit suit = i->suit;
      temp.push_back(i);
      for(auto j : a){
        if((j->suit == suit)&&(j->rank > 9)){
          temp.push_back(j);
        }
      }
      if(temp.size() == 5){
        a = temp;
        return true;
      }
    }
  }
  return false;
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

void Poker::printWinner(Player* player){
  cout << player->name << " won with a high ";
  if(player->chance <= 9000) return "royal flush." << endl;
  else if(player->chance <= 8000) cout << "straight flush." << endl;
  else if(player->chance <= 7000) cout << "four of a kind." << endl;
  else if(player->chance <= 6000) cout << "full house." << endl;
  else if(player->chance <= 5000) cout << "flush." << endl;
  else if(player->chance <= 4000) cout << "straight." << endl;
  else if(player->chance <= 3000) cout << "three of a kind." << endl;
  else if(player->chance <= 2000) cout << "two pair." << endl;
  else if(player->chance <= 1000) cout << "pair." << endl;
  else cout << "card." << endl;
}
