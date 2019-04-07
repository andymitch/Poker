#include "Casino.hpp"
#include <iostream>
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>
#include <thread> //this_thread::sleep_for
#include <chrono> //chrono::seconds
#include <cstdlib>
using namespace std;


//PLAY
/******************************************************************************/
void playPoker(){
  Poker p(5);
  while(!p.isBroke(p.getUser())){ //user isn't broke
    p.deal();
    p.deal();
    p.makeBet();
    p.lay();
    p.lay();
    p.lay();
    p.makeBet();
    p.lay();
    p.makeBet();
    p.lay();
    p.makeBet();
    p.call();
    p.reset(); //reset table, keep players
  }
}

//PokerPlayer DECLARATION
/******************************************************************************/
PokerPlayer::PokerPlayer(){}
PokerPlayer::PokerPlayer(int i){
  if(i == 0) name = "You";
  else if(i == 1) name = "Alex";
  else if(i == 2) name = "Brian";
  else if(i == 3) name = "Carl";
  else if(i == 4) name = "Derrek";
  else if(i == 5) name = "Mike";
  money = 100;
  call = fold = turn = false;
}

//POKER DECLARATION
/******************************************************************************/
Poker::Poker(int i){
  deck = getDeck();
  bigBlind = littleBlind = pot = bet = 0;
  players = setplayers(i);
  USER = &players[0];
  setBlind();
  bet = bigBlind;
}
PokerPlayer Poker::getUser(){
  return *USER;
}
bool Poker::isBroke(PokerPlayer p){
  return (p.money < 1);
}
bool Poker::isUser(PokerPlayer p){
  return(USER == &p);
}
PokerPlayer Poker::getWinner(){
  vector<PokerPlayer> temp = players;
  vector<PokerPlayer>::iterator it, t;
  for(it = temp.begin(); it != temp.end()-1; it++){
    if(it->chance > (it+1)->chance){
      t = it;
      it = (it+1);
      (it+1) = t;
    }
  }
  return temp.back();
}
stack<Card> Poker::getDeck(){
  vector<Card> _deck;
  Rank rank = Two;
  Suit suit = club;
  for(int i = 0; i < 4; i++){
      for(int j = 0; j < 13; j++){
          _deck.push_back(Card(rank, suit));
          ++rank;
      }
      ++suit;
      rank = Two;
  }
  random_shuffle(_deck.begin(), _deck.end());
  stack<Card> deck;
  while(!_deck.empty()){
    deck.push(_deck.back());
    _deck.pop_back();
  }
  return deck;
}
vector<PokerPlayer> Poker::setplayers(int n){
  vector<PokerPlayer> p;
  for(int i = 0; i <= n; i++) p.push_back(PokerPlayer(i));
  return p;
}
void Poker::setBlind(){
  if(littleBlind == 0) littleBlind = .50;
  else littleBlind *= 2;
  bigBlind = littleBlind * 2;
}
void Poker::printTable(){
  //dimensions: 80X24
  this_thread::sleep_for(chrono::seconds(1));
  cout << "\033[2J\033[1;1H"; //clear screen sorta
  for(int x = 0; x < 80; x++) cout << '*'; //top border
  cout << "\n\n";
  PokerPlayer you;
  for(auto p : players){
    if(p.turn) cout << " *";
    cout << "\t" << p.name << "\t$" << p.money << "\t";
    for(auto c : p.hand) cout << c;
    cout << endl;
    if(p.name == "You") you = p;
  }
  int space = 5 - players.size(); //buffer space
  cout << "\n\n\n\t\tYour hand: ";
  for(auto card : you.hand) cout << card;
  cout << endl;
  cout << "\t\t   Dealer: ";
  for(auto d : dealer) cout << d;
  cout << "\n\n\t\tYour chance of winning: " << you.chance << "%\n\n\n";
  cout << "\t\tPot: $" << pot << endl;
  cout << "\t\tLittle Blind: $" << littleBlind << endl;
  cout << "\t\tBig Blind: $" << bigBlind << endl;
  for(int y = 0; y < space+2; y++) cout << endl; //remaining space
  for(int z = 0; z < 80; z++) cout << '*'; //bottom border
  cout << endl;
}
void Poker::printWinner(PokerPlayer PokerPlayer){
  cout << PokerPlayer.name << " won with a high ";
  if(PokerPlayer.chance <= 9000) cout << "royal flush." << endl;
  else if(PokerPlayer.chance <= 8000) cout << "straight flush." << endl;
  else if(PokerPlayer.chance <= 7000) cout << "four of a kind." << endl;
  else if(PokerPlayer.chance <= 6000) cout << "full house." << endl;
  else if(PokerPlayer.chance <= 5000) cout << "flush." << endl;
  else if(PokerPlayer.chance <= 4000) cout << "straight." << endl;
  else if(PokerPlayer.chance <= 3000) cout << "three of a kind." << endl;
  else if(PokerPlayer.chance <= 2000) cout << "two pair." << endl;
  else if(PokerPlayer.chance <= 1000) cout << "pair." << endl;
  else cout << "card." << endl;
}
void Poker::lay(){
  dealer.push_back(deck.top());
  deck.pop();
  printTable();
}
void Poker::deal(){
  for(auto p : players){
    p.hand.push_back(deck.top());
    deck.pop();
    printTable();
  }
}
float Poker::raise(PokerPlayer p){
  if(isUser(p)){
    cout << "Current bet: $" << bet << endl;
    cout << "How much do you want to raise the bet to?: $";
    float raise;
    cin >> raise;
    cout << endl;
    while(true){
      if(raise <= bet){
        cout << "It has to be more than the current bet: $";
        cin >> raise;
        cout << endl;
      }else if(raise > p.money){
        cout << "You don't have enough money to cover that bet: $";
        cin >> raise;
        cout << endl;
      }else{
        bet = p.makeBet(raise);
        return raise;
      }
    }
  }else{
    float raise;
    float r = rand()%15-10;
    raise = (p.money*p.chance/100)+r;
    if(raise > p.money) raise = p.money;
    bet = p.makeBet(raise);
    return raise;
  }
}
int Poker::getMove(PokerPlayer p){
  if(p.money < bet){
    if(isUser(p)) cout << "You don't have enough money to cover the bet; you must fold." << endl;
    return 3;
  }
  setChance();
  if(isUser(p)){ //user choice
    cout << "What's your move?:" << endl;
    cout << "\t1. raise" << endl;
    cout << "\t2. check" << endl;
    cout << "\t3. fold" << endl;
    int x = 0;
    while(x < 1 && x > 3) cin >> x;
    return x;
  }else{ //bot choice
    int r = rand() % 3 + 1;
    int c;
    if(p.chance >= 50) c = 1;
    else if(p.chance >= 20) c = 2;
    else c = 3;
    return ((r+c)/2);
  }
}
bool Poker::iscall(){
  for(auto p : players) if(!p.call) return false;
  return true;
}
void Poker::makeBet(){
  while(!iscall()){
    for(auto& p : players){
      if(!p.fold){
        p.turn = true;
        printTable();
        int x = getMove(p);
        switch(x){
          case 1: pot += p.makeBet(raise(p)); //raise
          case 2: pot += p.makeBet(bet); //check
            p.call = true;
          case 3: p.fold = true; //fold
            p.call = true;
        }
        p.turn = false;
      }
    }
  }
}
void Poker::call(){
  PokerPlayer winner = getWinner();
  winner.money += pot;
  pot = 0;
  printTable();
  printWinner(winner);
}
void Poker::reset(){
  for(int i = 0; i < players.size(); i++){
    if(players[i].money < 1) players.erase(players.begin()+i);
    else{
      players[i].call = players[i].fold = false;
      players[i].hand.clear();
    }
  }
  while(!deck.empty()) deck.pop();
  dealer.clear();
  bigBlind = littleBlind = bet = 0;
}

//POKER::GETCHANCE FUNCTION
/*****************************************************************************/
vector<Card> join_vector(vector<Card> a, vector<Card> b){
  vector<Card> c;
  for(auto i : a) c.push_back(i);
  for(auto j : b) c.push_back(j);
  return c;
}
vector<vector<Card>> join_vectors(vector<vector<Card>> a, vector<vector<Card>> b){
  vector<vector<Card>> c;
  for(auto i : a) c.push_back(i);
  for(auto j : a) c.push_back(j);
  return c;
}
void sortByRank(vector<Card>& suit){
  for(int i = 0; i < suit.size()-1; i++){
    for(int j = suit.size()-1; j > i; j--){
      if(suit[j].rank > suit[j-1].rank){
        swap(suit[j-1], suit[j]);
      }
    }
  }
  reverse(suit.begin(), suit.end());
}
int highCard(vector<vector<Card>> a){
  Rank rank = Two;
  Suit suit = club;
  if(a.size() == 1){ //straight
    for (auto i : a[0]) if(i.rank > rank) rank = i.rank;
    return ((rank*10) + a[0][0].suit);
  }else{ //pair+
    return ((a[0][0].rank*10) + a[0][0].suit);
  }
}

bool aPair(vector<vector<Card>>& a){
  //pair: 2 cards in the same rank
  for(auto s : a) reverse(s.begin(), s.end());
  for(auto suit : a){
    for(auto card : suit){
      for(auto compSuit : a){
        for(auto compCard : compSuit){
          if(card.rank == compCard.rank){
            vector<Card> temp;
            temp.push_back(card);
            temp.push_back(compCard);
            a.clear();
            a.push_back(temp);
            return true;
          }
        }
      }
    }
  }
  return false;
}
bool twoPair(vector<vector<Card>>& a){
  //two pair: 2 pairs of 2 cards in the same rank
  vector<vector<Card>> b = a;
  if(aPair(a)){
    for(auto& suit : b){ // erase cards that we already visited
      for(int i = 0; i < suit.size(); i++){
        if(suit[i].rank >= a[0][0].rank) suit.erase(suit.begin()+i);
      }
    }
    if(aPair(b)){
      a = join_vectors(a, b);
      return true;
    }
  }
  return false;
}
bool threeKind(vector<vector<Card>>& a){
  //three of a kind: 3 cards of the same rank
  vector<Card> sameRank;
  for(int i = (a[0].size()-1); i >= 0; i--){
    sameRank.push_back(a[0][i]);
    for(int j = 1; j < 4; j++){
      for(auto c : a[j]){
        if(c.rank == sameRank[0].rank) sameRank.push_back(c);
        if(sameRank.size() == 3){
          vector<vector<Card>> temp;
          temp.push_back(sameRank);
          a = temp;
          return true;
        }
      }
    }
    sameRank.clear();
  }
  return false;
}
bool straight(vector<vector<Card>>& a){
  //straight: 5 cards in sequence
  for(auto& c : a) reverse(c.begin(), c.end()); //reverse ranks to decreasing
  Rank rank;
  vector<Card> seqRank;
  for(auto i : a){
    for(auto j : i){
      rank = j.rank;
      seqRank.push_back(j);
      for(auto k : a){
        for(auto l : k){
          if(l.rank == rank-1){
            seqRank.push_back(l);
            --rank;
          }
          if(seqRank.size() == 5){
            vector<vector<Card>> temp;
            reverse(seqRank.begin(), seqRank.end()); //reverse back to increasing
            temp.push_back(seqRank);
            a = temp;
            return true;
          }
        }
      }
      seqRank.clear();
    }
  }
  return false;
}
bool flush(vector<vector<Card>>& a){
  //flush: 5 cards in the same suit
  for(auto s : a) if(s.size() == 5){
    vector<vector<Card>> temp;
    temp.push_back(s);
    a = temp;
    return true;
  }
  return false;
}
bool fullHouse(vector<vector<Card>>& a){
  //full house: 3 cards of the same rank with 2 cards of the same rank
  vector<vector<Card>> b = a, c = a; // c is safety vector
  if(threeKind(a)){ //modify a
    if(aPair(b)){ //modify copy of a
      if(a.begin() != b.begin()){ // if pair != three (ie. same cards within)
        a = join_vectors(a,b);
        return true;
      }
    }
    else a = c; //restore a
  }
  return false;
}
bool fourKind(vector<vector<Card>>& a){
  //four of a kind: 4 cards of the same rank
  vector<Card> sameRank;
  for(int i = (a[0].size()-1); i >= 0; i--){
    sameRank.push_back(a[0][i]);
    for(int j = 1; j < 4; j++){
      for(auto c : a[j]){
        if(c.rank == sameRank[0].rank) sameRank.push_back(c);
        if(sameRank.size() == 4){
          vector<vector<Card>> temp;
          temp.push_back(sameRank);
          a = temp;
          return true;
        }
      }
    }
    sameRank.clear();
  }
  return false;
}
bool straightFlush(vector<vector<Card>>& a){
  //straight flush: 5 cards in sequence of the same suit
  for(auto suit : a){
    reverse(suit.begin(), suit.end());
    Rank rank = suit[0].rank;
    vector<Card> winSuit;
    winSuit.push_back(suit[0]);
    for(auto card : suit){
      if(card.rank != --rank){
        rank = card.rank;
        winSuit.clear();
      }
      winSuit.push_back(card);
      if(winSuit.size() == 5){
        vector<vector<Card>> temp;
        temp.push_back(suit);
        a = temp;
        return true;
      }
    }
  }
  return false;
}
bool royalFlush(vector<vector<Card>>& a){
  //royal flush: 5 royal cards in sequence (10-A) of the same suit
  for(auto suit : a){
    if(suit[0].rank == 10 && suit.size() == 5){
      vector<vector<Card>> temp;
      temp.push_back(suit);
      a = temp;
      return true;
    }
  }
  return false;
}

vector<vector<Card>> Poker::sortHand(PokerPlayer p){
  vector<vector<Card>> sh(4);
  vector<Card> hand = join_vector(p.hand, dealer);
  int i = 0;
  for(Suit suit = club; suit <= spade; ++suit){
    for(auto card : hand) if(card.suit == suit) sh[i].push_back(card);
    i++;
  }
  for(auto s : sh) sortByRank(s);
  reverse(sh.begin(), sh.end());
  return sh;
}
void Poker::setChance(){
  int chance;
  for(auto& p : players){
    p.chance = 0; //reset chance
    vector<vector<Card>> hand = sortHand(p); //get a sorted 2D vector hand
    if(royalFlush(hand)) chance = 9000 + highCard(hand);
    else if(straightFlush(hand)) chance = 8000 + highCard(hand);
    else if(fourKind(hand)) chance = 7000 + highCard(hand);
    else if(fullHouse(hand)) chance = 6000 + highCard(hand);
    else if(flush(hand)) chance = 5000 + highCard(hand);
    else if(straight(hand)) chance = 4000 + highCard(hand);
    else if(threeKind(hand)) chance = 3000 + highCard(hand);
    else if(twoPair(hand)) chance = 2000 + highCard(hand);
    else if(aPair(hand)) chance = 1000 + highCard(hand);
    else chance = highCard(hand);
    p.chance = chance*100/9134;
  }
}
