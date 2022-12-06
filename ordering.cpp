#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//maybe go from degrees to
const int meetings = 5;
int degrees[] = { 4, 4, 3, 2, 0 };
int order[] = { 0,0,0,0,0};
vector<vector<int>> vec{};

void setup(){ // sets up the vectors
	for(int i = 0; i < meetings; i++){
		vector<int> setup{};
		vec.push_back(setup);
	}
}



int degrees_to_order(int teacher, int count){
  std::cout<< "list #:" << teacher << ":";
  int how_many_loops = 0;
	vector< vector<int> >::iterator row;
	vector<int>::iterator col;
		for( col = vec[teacher].begin(); col != vec[teacher].end(); col++) {
			std::cout << *col << ",";
      order[(meetings - 1)-(count + how_many_loops)] = *col;
      how_many_loops += 1;
		}
    std::cout<<"\n";
    return how_many_loops;

}


 void get_order(){ // iterate through the vectors and the meetings to order[] from most degrees to fewest
   int count = 0;
	 for (int i = 0; i<meetings; i++){
		 int x = degrees_to_order(i, count);
     count += x;
	 }
 }

 void counting_sort(){ // puts the index of an element into a bucket # that matches its content
	 for (int i = 0; i <meetings; i++){
     vec[degrees[i]].push_back(i);
   }
 }

int main()
{
  setup();
  counting_sort();

  get_order();
  for (int i = 0; i <meetings; i++){
    std::cout<<order[i];
  }
  return 0;

}
