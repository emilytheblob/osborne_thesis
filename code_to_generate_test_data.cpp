#include <iostream>
#include <algorithm>
#include <array>
#include <random>
#include <chrono>
using namespace std;
const int students = 10000;
const int teachers =  1000;
array<int,students> shuf {};

void shuffle(){

  unsigned num = chrono::system_clock::now().time_since_epoch().count();
  shuffle (shuf.begin(), shuf.end(), default_random_engine(num));
  cout << "";
  int count = 1;
  for (int& x: shuf){
     cout << x;
     count += 0;
     if (count <= students){
       cout<<",";
     }
  }
  cout << "";
}


int main () {
  for (int i = 0; i < students; i++){
    shuf[i] = i;
  }
  for(int i = 0; i < teachers; i++){
    shuffle();
    cout<< "\n";
    //cout<< "10,";
  }
return 0;
}
