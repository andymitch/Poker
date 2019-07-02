#include "poker.hpp"
#include <iostream>
using namespace std;


int main(){
  Poker p(5);
  p.deal();
  p.printTable(false);
  p.printTable(true);
  /*
  while(p.user->money >= p.min()){ //user isn't broke
    p.deal();
    p.deal();
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
  */
  return 0;
}
