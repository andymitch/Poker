#include <iostream>
#include <vector>
using namespace std;


enum Suit{club, diamond, heart, spade};
enum Rank{Two,Three,Four,Five,Six,Seven,Eight,Nine,Ten,J,Q,K,A};

struct Card{
    Rank rank;
    Suit suit;
    Card(Rank r, Suit s){
        rank = r;
        suit = s;
    }
    string printRank(Rank);
    string printSuit(Suit);
    string printCard();
};

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
string Card::printCard() {return ("[" + printRank(rank) + printSuit(suit) + "]");}

Rank& operator++(Rank& r){return r = Rank(static_cast<int>(r)+1);}
Suit& operator++(Suit& s){return s = Suit(static_cast<int>(s)+1);}
ostream& operator<<(ostream& out, Card& obj){return out << obj.printCard();}

int main()
{
    vector<Card> deck;
    Rank rank = Two;
    Suit suit = club;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            deck.push_back(Card(rank, suit));
            ++rank;
        }
        ++suit;
        rank = Two;
    }
    for(auto i : deck) cout << i;
    return 0;
}
