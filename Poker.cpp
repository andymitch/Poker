#include <iostream>
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>
#include <thread> //this_thread::sleep_for
#include <chrono> //chrono::seconds
#include <cstdlib>
using namespace std;


//CARD STRUCT
/*****************************************************************************/
enum Suit{club, diamond, heart, spade};
enum Rank{Two,Three,Four,Five,Six,Seven,Eight,Nine,Ten,J,Q,K,A};

struct Card{
    Rank rank;
    Suit suit;
    Card();
    Card(Rank r, Suit s){
        rank = r;
        suit = s;
    }
    string printRank(Rank);
    string printSuit(Suit);
    string printCard();
};

Rank& operator++(Rank& r){return r = Rank(static_cast<int>(r)+1);}
Suit& operator++(Suit& s){return s = Suit(static_cast<int>(s)+1);}
Rank& operator--(Rank& r){return r = Rank(static_cast<int>(r)-1);}
Suit& operator--(Suit& s){return s = Suit(static_cast<int>(s)-1);}
ostream& operator<<(ostream& out, Card& obj){return out << obj.printCard();}


string Card::printRank(Rank rank){
    switch (rank){
        case Two: return "2";
        case Three: return "3";
        case Four: return "4";
        case Five: return "5";
        case Six: return "6";
        case Seven: return "7";
        case Eight: return "8";
        case Nine: return "9";
        case Ten: return "T";
        case J: return "J";
        case Q: return "Q";
        case K: return "K";
        case A: return "A";
        default: return "VOID";
    }
}
string Card::printSuit(Suit suit){
    switch(suit){
        case club: return "\u2663";
        case diamond: return "\u2666";
        case heart: return "\u2665";
        case spade: return "\u2660";
        default: return "VOID";
    }
}
string Card::printCard(){
  return ("[" + printRank(rank) + printSuit(suit) + "]");
}

//PLAYER STRUCT
/*****************************************************************************/
struct Player{
  string name;
  vector<Card> hand;
  float money;
  int chance;
  bool call, fold, turn;
  Player(){}
  Player(int i){
    if(i == 0) name = "You";
    else if(i == 1) name = "Alex";
    else if(i == 2) name = "Brian";
    else if(i == 3) name = "Carl";
    else if(i == 4) name = "Derrek";
    else if(i == 5) name = "Mike";
    money = 100;
    call = fold = turn = false;
  }
  float makeBet(float bet){
    money -= bet;
    return bet;
  }
};

//POKER CLASS
/*****************************************************************************/
class Poker{
  stack<Card> deck;
  vector<Card> dealer;
  vector<Player> players;
  float bigBlind, littleBlind, pot, bet;
public:
  vector<Player>::iterator USER;
  Poker(int i){
    deck = getDeck();
    bigBlind = littleBlind = pot = bet = 0;
    players = setPlayers(i);
    USER = players.begin();
    setBlind();
    bet = bigBlind;
  }
  vector<Player> setPlayers(int);
  stack<Card> getDeck();
  void setBlind();
  void printTable();
  void printWinner(Player);
  void lay();
  void deal();
  float raise(Player);
  int getMove(Player);
  bool iscall();
  void makeBet();
  void call();
  void reset();
  bool byRank(const Card&, const Card&);
  vector<vector<Card>> sortHand(Player);
  int setChance(); //set every player's chance
};

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
vector<Player> Poker::setPlayers(int n){
  vector<Player> p;
  for(int i = 0; i <= n; i++) p.push_back(Player(i));
  return p;
}
void Poker::setBlind(){
  if(littleBlind == 0) littleBlind = .50;
  else littleBlind *= 2;
  bigBlind = littleBlind * 2;
}
void Poker::printTable(){
  //dimensions: 80X24
  this_thread::sleep_for (chrono::seconds(1));
  cout << "\033[2J\033[1;1H"; //clear screen sorta
  for(int x = 0; x < 80; x++) cout << '*'; //top border
  cout << "\n\n";
  Player you;
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
void Poker::printWinner(Player player){
  cout << player.name << " won with a high ";
  if(player.chance <= 9000) cout << "royal flush." << endl;
  else if(player.chance <= 8000) cout << "straight flush." << endl;
  else if(player.chance <= 7000) cout << "four of a kind." << endl;
  else if(player.chance <= 6000) cout << "full house." << endl;
  else if(player.chance <= 5000) cout << "flush." << endl;
  else if(player.chance <= 4000) cout << "straight." << endl;
  else if(player.chance <= 3000) cout << "three of a kind." << endl;
  else if(player.chance <= 2000) cout << "two pair." << endl;
  else if(player.chance <= 1000) cout << "pair." << endl;
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
float Poker::raise(Player p){
  if(*p == USER){
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
int Poker::getMove(Player p){
  if(p.money < bet){
    if(*p == USER) cout << "You don't have enough money to cover the bet; you must fold." << endl;
    return 3;
  }
  setChance();
  if(*p == USER){ //user choice
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
  Player& winner = max_element(players.begin(), players.end(), [](const Player& a, const Player& b) {return a.chance < b.chance;});
  winner.money += pot;
  pot = 0;
  printTable();
  printWinner(winner);
}
void Poker::reset(){
  for(auto& p : players){
    if(p.money > 1) players.erase(p);
    else{
      p.call = p.fold = false;
      p.hand.clear();
    }
  }
  while(!deck.empty()) deck.pop();
  dealer.clear();
  bigBlind = littleBlind = bet = 0;
}

//POKER::GETCHANCE()
/*****************************************************************************/
bool threeKind(vector<vector<Card>>&); //declaration
bool aPair(vector<vector<Card>>&); //declaration
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
bool fullHouse(vector<vector<Card>>& a){
  //full house: 3 cards of the same rank with 2 cards of the same rank
  vector<vector<Card>> b = a;
  vector<vector<Card>> c,d;
  if(threeKind(a)){
    c = a;
    if(aPair(b)){
      d = b;
      if(c.front() != d.front()){
        merge(c.begin(), c.end(), d.begin(), d.begin(), a.begin());
        return true;
      }
    }
    else a = b;
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
bool twoPair(vector<vector<Card>>& a){
  //two pair: 2 pairs of 2 cards in the same rank
  vector<vector<Card>> c = a;
  vector<vector<Card>> b;
  if(aPair(a)){
    b = a;
    for(auto& suit : c){ // std::erase cards that we already visited
      for(auto& card : suit){
        if(card.rank >= a[0][0]) a.erase(card);
      }
    }
    if(aPair(c)){
      merge(b.begin(), b.end(), c.begin(), c.end(), a.begin());
      return true;
    }
  }
  return false;
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
bool Poker::byRank(const Card& a, const Card& b){return (a.rank < b.rank);}
vector<vector<Card>> Poker::sortHand(Player p){
  vector<Card> hand;
  vector<vector<Card>> sh(4);
  merge(p.hand.begin(), p.hand.end(), dealer.begin(), dealer.end(), hand.begin());
  Suit suit = club;
  for(auto s : sh){
    vector<Card> temp;
    for(auto c : hand){
      if(c.suit == suit) temp.push_back(c);
      sort(sh.begin(), sh.end(), byRank);
      sh.push_back(temp);
      ++suit;
    }
    reverse(sh.begin(), sh.end());
  }
  return sh;
}
int Poker::setChance(){
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

//MAIN
/*****************************************************************************/
namespace poker{
  void play(){
    Poker p(5);
    while(p.USER->money > 0){ //user isn't broke
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
}

int main(){
  poker::play();
  return 0;
}
