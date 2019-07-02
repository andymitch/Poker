#include "poker.hpp"
#include <iostream>
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm> //shuffle
#include <thread> //this_thread::sleep_for
#include <chrono> //chrono::seconds
#include <cstdlib>
#include <random> //random generator
using namespace std;


//POKER DECLARATION
/******************************************************************************/
Poker::Poker(int i){
  deck = getDeck();
  bigBlind = littleBlind = pot = bet = 0;
  turn = 0;
  players = setPlayers(i);
  user = &players[0];
  setBlind();
  bet = bigBlind;
}

Player* Poker::getWinner(){
  Player* winner;
  int top = 0;
  for(int i = 0; i < players.size(); i++) if(top < players[i].chance) {winner = &players[i]; top = players[i].chance;}
  return winner;
}

stack<Card> Poker::getDeck(){
  cout << "\nShuffling new deck..\n";
  vector<Card> _deck;
  Rank rank = Two; //lowest rank
  Suit suit = club; //lowest suit
  for(int i = 0; i < 4; i++){ //get deck of cards sequentially
      for(int j = 0; j < 13; j++){
          _deck.push_back(Card(rank, suit));
          ++rank;
      }
      ++suit;
      rank = Two;
  }
  shuffle(_deck.begin(), _deck.end(), default_random_engine(chrono::system_clock::now().time_since_epoch().count())); //shuffle deck
  stack<Card> deck;
  while(!_deck.empty()){ //convert vector to stack
    deck.push(_deck.back());
    _deck.pop_back();
  }
  return deck;
}

vector<Player> Poker::setPlayers(int n){
  vector<Player> p;
  for(int i = 0; i <= n; i++) p.push_back(Player(i));
  return p;
}

void Poker::setBlind(){
  littleBlind += 1;
  bigBlind = littleBlind * 2;
}

void Poker::printTable(bool show){
  this_thread::sleep_for(chrono::seconds(1));
  cout << "\033[2J\033[1;1H"; //clear screen
  for(int x = 0; x < 80; x++) cout << '*'; //top border
  cout << "\n\n";
  for(auto& p : players){
    if(p.turn) cout << " *";
    cout << "\t" << p.name << "\t$" << p.money << "\t";
    if(show || &p == user) for(auto c : p.hand) cout << c;
    cout << endl;
  }
  cout << "\n\t\t   Dealer: "; for(auto d : dealer) cout << d;
  cout << "\t\tPot: $" << pot << "\tBet: $" << bet << endl;
  for(int y = players.size(); y < 9; y++) cout << endl; //remaining space
  for(int z = 0; z < 80; z++) cout << '*'; //bottom border
  cout << endl;
}

void Poker::printWinner(Player* winner){
  cout << winner->name << " won with a high ";
  if(winner->chance <= 9000) cout << "royal flush." << endl;
  else if(winner->chance <= 8000) cout << "straight flush." << endl;
  else if(winner->chance <= 7000) cout << "four of a kind." << endl;
  else if(winner->chance <= 6000) cout << "full house." << endl;
  else if(winner->chance <= 5000) cout << "flush." << endl;
  else if(winner->chance <= 4000) cout << "straight." << endl;
  else if(winner->chance <= 3000) cout << "three of a kind." << endl;
  else if(winner->chance <= 2000) cout << "two pair." << endl;
  else if(winner->chance <= 1000) cout << "pair." << endl;
  else cout << "card." << endl;
  char yn; cout << "Again? (y/n): "; cin >> yn; cout << endl;
}

void Poker::lay(){
  dealer.push_back(deck.top());
  deck.pop();
  printTable(false);
}

void Poker::deal(){
  for(auto& p : players){
    p.hand.push_back(deck.top());
    deck.pop();
  }
  printTable(false);
}

float Poker::raise(Player* p){
  float raise;
  if(p == user){ //user choice
    cout << "Current bet: $" << bet << endl;
    cout << "How much do you want to raise the bet to?: $";
    cin >> raise;
    cout << endl;
    while(true){
      if(raise <= bet){
        cout << "It has to be more than the current bet: $";
        cin >> raise;
        cout << endl;
      }else if(raise > p->money){
        cout << "You don't have enough money to cover that bet: $";
        cin >> raise;
        cout << endl;
      }else{
        if(raise == p->money) cout << p->name << " go all in!";
        return raise;
      }
    }
  }else{ //bot choice
    float r = rand()%15 - 10;
    raise = (p->money * p->chance / 200) + r;
    if(raise <= 0) raise *= -1;
    raise += bet;
    if(raise > p->money){
      raise = p->money;
      cout << p->name << " goes all in!";
    }
    return raise;
  }
}

int Poker::getMove(Player* p){
  if(p->money < bet){
    if(p == user) cout << "You don't have enough money to cover the bet, you must fold." << endl;
    return 3;
  }
  setChance();
  if(p == user){ //user choice
    cout << "What's your move?:" << endl;
    cout << "\t1. raise" << endl;
    cout << "\t2. check" << endl;
    cout << "\t3. fold" << endl;
    int x = 0;
    while(x < 1 || x > 3){
      cin >> x;
      if(x == 3 && p->money == bet){
        if(p == user) cout << "You don't have enough money to raise, you must check." << endl;
        return 2;
      }
    }
    return x;
  }else{ //bot choice
    int c, r = rand()%3 + 1;
    if(p->chance >= 50) c = 2;
    else if(p->chance >= 20) c = 4;
    else c = 6;
    return ((r+c)/3); //2:1 chance:random
  }
}

bool Poker::iscall(){
  for(auto& p : players) if(!p.call) return false;
  return true;
}

void Poker::placeBets(){
  while(!iscall()){
    for(auto& p : players){
      if(!p.fold){
        p.turn = true;
        printTable(false);
        switch(getMove(&p)){
          case 1: bet = raise(&p); p.money -= (bet-p.bid); pot += (bet-p.bid); p.bid = bet; break; //raise
          case 2: p.money -= (bet-p.bid); pot += (bet-p.bid); p.bid = bet; p.call = true; break; //check
          case 3: p.fold = true; p.call = true; break; //fold
        }
        p.turn = false;
      }
    }
  }
}

void Poker::call(){
  Player* winner = getWinner();
  winner->money += pot;
  pot = 0;
  printTable(true);
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
  deck = getDeck();
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
    if(!suit.empty()){
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
  }
  return false;
}

bool royalFlush(vector<vector<Card>>& a){
  //royal flush: 5 royal cards in sequence (10-A) of the same suit
  for(auto suit : a){
    if(suit.empty());
    else if(suit[0].rank == 10 && suit.size() == 5){
      vector<vector<Card>> temp;
      temp.push_back(suit);
      a = temp;
      return true;
    }
  }
  return false;
}

vector<vector<Card>> Poker::sortHand(Player& p){
  vector<vector<Card>> sh(4);
  vector<Card> hand = join_vector(p.hand, dealer);
  int x = 0;
  for(Suit suit = club; suit <= spade; ++suit){
    //sort hand by suit
    for(auto card : hand) if(card.suit == suit) sh[x].push_back(card);
    x++;
  }
  int i, j, k;
  for(i = 0; i < 4; i++){
    //sort suits by rank
    if(sh[i].size() > 1){
      for(j = 0; j < sh[i].size(); j++){
        for(k = sh[i].size()-1; k > j; k--){
          if(sh[i][k].rank > sh[i][k-1].rank){
            swap(sh[i][k-1], sh[i][j]);
          }
        }
      }
      reverse(sh[i].begin(), sh[i].end());
    }
  }
  reverse(sh.begin(), sh.end());
  return sh;
}

void Poker::setChance(){
  int chance;
  for(auto& p : players){
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
    cout << p.name << " " << p.chance << endl;
  }
}

//MAIN
/*****************************************************************************/

int main(){
  Poker p(5);
  while(p.user->money >= p.min()){ //user isn't broke
    p.deal();
    p.deal();
    p.printTable(true);
    p.placeBets();
    p.lay();
    p.lay();
    p.lay();
    p.placeBets();
    p.lay();
    p.placeBets();
    p.lay();
    p.placeBets();
    p.call();
    p.reset(); //reset table, keep players
  }
  return 0;
}
