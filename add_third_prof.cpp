#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <random>
#include <chrono>
using namespace std;

int const meetings = 5;
int const teachers = 5;
array<int,teachers> third_prof = {};

int matched_pairs[meetings][3] = { };
vector<vector<int>> matches;

void setup(){ // sets up the vectors
	for(int i = 0; i < 5; i++){
		vector<int> setup{};
    setup.push_back(i);
		matches.push_back(setup);
	}
}

void third_proff_setup(){
	for(int i = 0; i < teachers; i++){
		third_prof[i] = i;
	}
	unsigned num = chrono::system_clock::now().time_since_epoch().count();
	shuffle (third_prof.begin(), third_prof.end(), default_random_engine(num));
}


void print_(){
  for (int i = 0; i< meetings; i++){
    for (int j = 0; j < 3; j++){
      cout<<matched_pairs[i][j];
    }
  }
}


int vec_to_matrix(){ // this function is the part that will go into the big doc
  int counter = 0;
  int teacher;
  for (int i = 0; i<teachers; i++){

    teacher = i;
	   vector< vector<int> >::iterator row;
	    vector<int>::iterator col;
		    for( col = matches[teacher].begin(); col != matches[teacher].end(); col++) {
			       matched_pairs[counter][0] = teacher;
             matched_pairs[counter][1] = *col;
						 matched_pairs[counter][2] = third_prof[teacher];
             counter += 1;
		         }
    }
  print_();
  return 0;
}



int main(int argc, char** argv){

  setup();
	third_proff_setup();
	vec_to_matrix();
	return 0;
}
