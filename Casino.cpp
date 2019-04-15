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


int main(){
  int x;
  cout << "CASINO!\n\n";
  cout << "1. Poker\n2. Blackjack\n\n";
  cin >> x;
  switch(x){
    case 1: playPoker();
    case 2: //playBlackjack();
    default: cout << "Invalid option." << endl;
  }
  return 0;
}
