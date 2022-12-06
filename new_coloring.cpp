#include <iostream>
#include <algorithm>
#include <array>
#include <random>
#include <chrono>
using namespace std;


const int meetings = 5;
int adjacency_matrix[meetings][meetings] = {1,1,1,0,1,
											1,1,0,0,0,
											1,0,1,1,0,
											0,0,1,1,0,
											1,0,0,0,1};
int coloring[meetings] = { };

int max_index = 4;
bool complete = false;
array<int,5> nodes {0,1,2,3,4};
int order[meetings] = {4,2,1,3,0};
int degrees[5] = {0,0,0,0,0};
//we wanna then go from the degrees to listing indices from greatest to smallest





bool check(int index, int color){
	for(int i = 0; i < meetings; i++){
		if(adjacency_matrix[index][i] == 1 && color == coloring[i]){
			return false;
		}
	}
	return true;

}
//for each node check if the first color works, if it does assign it, if not try the next color





int graphColor(){
  for (int i = 0; i < meetings; i++){
    	int index = order[i];
      for( int color = 1; color <= max_index; color++){
        if (check(index,color)){
          coloring[index] = color;
          color = max_index + 1;
        }
      }
  }
  return 0;
}



int main(){

  graphColor();
  for( int i = 0; i < meetings; i++){
    std::cout<<coloring[i];

  }

return 0;
}
