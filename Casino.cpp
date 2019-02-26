/*******************************************
1 PLAYER TEXAS HOLD 'EM
1 PLAYER BLACKJACK
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TODO:
-create a deck of cards, possibly use enum
-main() menu: resume game
              new game
              return to menu
              number of bots
              quit
-deal() deals cards randomly to player and bots
*******************************************/

#include "Poker.hpp"
#include "Blackjack.hpp"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
///////////////////////////////////////POKER//////////////////////////////////////////////////////////////////////////
  if(argv[1] == "Poker"){
    Poker play;
    while(true){
      cout << "\NTEXAS HOLD 'EM\N\NMAIN MENU\n~~~~~~~~~\n\n\t1. new game\n\t2. resume game\n\t3. quit\n\t0. return to menu (in game)"\n\n;
      int x;
      while(true){
        cin << x;
        switch(x){ //syntax: play.function(play.player);
          case 1:
          case 2:
          case 3:
          default: cout << "Invalid option, try (1-3)" << endl;
        }
      }
    }
///////////////////////////////////////BLACKJACK///////////////////////////////////////////////////////////////////
  }else if(argv[1] == "Blackjack"){
    Blackjack play;
    while(true){
      cout << "\NBLACKJACK\N\NMAIN MENU\n~~~~~~~~~\n\n\t1. new game\n\t2. resume game\n\t3. quit\n\t0. return to menu (in game)"\n\n;
      int x;
      while(true){
        cin << x;
        switch(x){
          case 1:
          case 2:
          case 3:
          default: cout << "Invalid option, try (1-3)" << endl;
        }
      }
    }
///////////////////////////////////////ERROR///////////////////////////////////////////////////////////////////
  }else cerr << "ERR: try './casino poker' or './casino blackjack'" << endl;
  return 0;
}
