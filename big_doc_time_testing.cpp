#include <iostream>
#include <stdio.h>
#include <list>
#include <vector>
#include<typeinfo>
#include <algorithm>
#include <array>
#include <random>
#include <chrono>
using namespace std;
using namespace std::chrono;


const int students = 30;
const int teachers = 6; //note: all numbers in rankings represent identities and positions rep ranks
//teacher's rankings of students
int teachers_rankings[teachers][students]=
{13,23,27,14,21,20,11,3,26,5,0,16,15,2,6,7,17,4,9,22,19,25,1,28,18,24,8,12,10,29,
8,17,9,7,3,29,10,22,25,18,23,14,5,13,12,26,27,1,4,20,2,15,16,6,28,11,0,21,19,24,
22,21,10,11,23,3,25,18,5,0,20,13,9,27,1,29,14,26,4,12,6,28,2,8,16,24,19,17,7,15,
5,22,6,1,7,25,14,26,17,21,12,0,15,11,13,28,18,24,23,20,16,10,29,9,27,2,3,4,8,19,
4,0,2,26,21,17,9,19,28,27,5,16,24,25,3,20,10,14,15,1,7,8,12,23,22,29,13,6,18,11,
19,12,14,25,6,27,26,20,24,21,13,10,23,18,0,3,7,11,29,1,5,4,9,2,8,15,16,28,17,22};

//student's rankings of teachers
int students_rankings[students][teachers]= {1,4,0,3,5,2,
4,1,3,5,2,0,
0,4,1,3,5,2,
0,1,5,2,4,3,
4,1,0,2,3,5,
3,4,5,2,0,1,
0,1,2,3,5,4,
0,2,4,1,5,3,
0,5,1,3,2,4,
3,5,0,1,2,4,
2,0,3,4,5,1,
0,5,1,3,4,2,
3,4,5,1,2,0,
1,4,0,5,2,3,
0,3,4,1,5,2,
1,3,0,2,5,4,
0,5,3,4,1,2,
0,1,4,3,5,2,
4,0,3,1,2,5,
0,1,5,2,3,4,
3,4,1,5,0,2,
5,2,1,4,0,3,
1,5,4,0,3,2,
3,1,5,2,0,4,
1,0,2,4,5,3,
0,4,2,3,1,5,
5,1,3,0,2,4,
2,5,4,0,1,3,
5,0,3,4,1,2,
3,0,2,5,4,1};


int max_s_per_prof[teachers]= {5,5,5,5,5,5};

int match_counter[teachers] = { };
const int meetings = students;
bool is_student_matched[students] = { };
vector<vector<int>> matches {};//[profesor][matches]
array<int,teachers> third_prof = {};
int matched_pairs[meetings][3] = { };
int adjacency_matrix[meetings][meetings];
int degrees[meetings] = { };
int order[meetings] = { };
vector<vector<int>> vec{};
int max_index = meetings - 1;
int coloring[meetings] = { };
bool complete = false;

void setup(){ // sets up the vectors
	for(int i = 0; i < teachers; i++){
		vector<int> setup{};
		matches.push_back(setup);
	}
	for(int i = 0; i < meetings; i++){
		vector<int> setup{};
		vec.push_back(setup);
	}
}


void third_proff_setup(){
	for(int i = 0; i < teachers; i++){
		third_prof[i] = i;
	}
	unsigned num = chrono::system_clock::now().time_since_epoch().count();
	shuffle (third_prof.begin(), third_prof.end(), default_random_engine(num));
}

int find(int arr[], int len, int seek){ //return the index of what we are looking for in an array or -1 if not found
	for(int i = 0; i < len; i++){

	//	std::cout<<"i = "<< i<<" \n";
	//	std::cout<<"arr[i] = "<< arr[i] << " \n";
	//	std::cout<<"seek = "<< seek << " \n";

		if(arr[i] == seek){
			return i;
		}
	}
	std::cout<<"Error: find function didn't find that value in the array \n";
	return -1;
}

int check_space(int teacher, int match_counter[], int max_s_per_prof[]){ // returns 1 or 0 for if teacher has more space/spots available
	if(match_counter[teacher] < max_s_per_prof[teacher]){
		return 1;
	} else{
		return 0;
	}
}

void add(int student, int teacher){
		matches[teacher].push_back(student); // add student to matches list
		match_counter[teacher] += 1;
		is_student_matched[student] = true; // update students matched status
}


int remove(int teacher, int lowest_ranked){ 	//this is meant to remove the student from this teachers matches

    std::vector<int>::iterator position = std::find(matches[teacher].begin(), matches[teacher].end(), lowest_ranked);
    if (position != matches[teacher].end()) {// == myVector.end() means the element was not found
        matches[teacher].erase(position);
				match_counter[teacher] -= 1;
				is_student_matched[lowest_ranked] = false;
        return 1;
    }
    return -1;

}

int min_ranked(int teacher, int teacher_rankings[teachers][students], int student){  //return student who is min ranked

  vector<int> find_results;
  vector< vector<int> >::iterator row;
  vector<int>::iterator col;
    for( col = matches[teacher].begin(); col != matches[teacher].end(); col++) {
      int x = *col;
      int y = find(teacher_rankings[teacher], students, x);
      find_results.push_back(y);

    }
		int y = find(teacher_rankings[teacher], students, student);
		find_results.push_back(y);

    if (find_results.empty()){
      std::cout << "Error: min_ranked function \n";
      return -1;

    }
    int index = *max_element(find_results.begin(), find_results.end());
    return teacher_rankings[teacher][index];
//iterate through matches, get find for each one and put in a vector, then get the lowest thing in the vector and use that as an index to return student who is min

}






int matching(){
	for(int s = 0; s < students; s++){
		for(int p = 0; p < teachers; p++){
			int t = students_rankings[s][p];// this makes it so we are testing the teachers in order of how students ranked them rather than in the same order every time
			int space_bool = check_space(t, match_counter, max_s_per_prof);

			if(is_student_matched[s]==1){ // if student is already matched, move along
					t = 0;
					break;
					//we want to break back to the s level loop (test this)
			} else if (space_bool == 1){ // if teacher has an empty space
					add(s,t);//add student to teachers list
					break;
			} else {
					int lowest_ranked = min_ranked(t, teachers_rankings, s);
					if(s == lowest_ranked){
						continue; //i think this moves on to next t
					} else{
						remove(t, lowest_ranked);
						add(s,t);
						s = lowest_ranked;
						p = find(students_rankings[s], teachers, t);

					}

				}


		}
	}
	return 0;
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
  return 0;
}

bool no_conflict(int i, int j){ // here we check if the meetings i and j have the same professors, we dont need to check matched_pairs[1] because that is a student
	if(matched_pairs[i][0] == matched_pairs[j][0] || matched_pairs[i][0] == matched_pairs[j][2]){
		return false;
	}
	if(matched_pairs[i][2] == matched_pairs[j][0] || matched_pairs[i][2] == matched_pairs[j][2]){
		return false;
	}
	return true;
}

int matches_to_adj_matrix(){
	//	for(int i = 1; i < argc; i++){
	//		cout<< argv[i] << "\n";
	//	}
		int count = 1;

		for (int i = 0; i < meetings; i++){
			for (int j = i; j < meetings; j++){
				if (i==j){
					adjacency_matrix[i][j] = 1;
				}
				else{
					if (no_conflict(i,j)){
						adjacency_matrix[i][j] = 0;
						adjacency_matrix[j][i] = 0;
					}
					else{
						degrees[i] += 1;
						degrees[j] += 1;
						adjacency_matrix[i][j] = 1;
						adjacency_matrix[j][i] = 1;
					}
				}
			}
		}

		return 0;
}




int degrees_to_order(int teacher, int count){

  int how_many_loops = 0;
	vector< vector<int> >::iterator row;
	vector<int>::iterator col;
		for( col = vec[teacher].begin(); col != vec[teacher].end(); col++) {
      order[(meetings - 1)-(count + how_many_loops)] = *col;
      how_many_loops += 1;
		}
    return how_many_loops;

}


 void get_order(){
   int count = 0;
	 for (int i = 0; i<meetings; i++){
		 int x = degrees_to_order(i, count);
     count += x;
	 }
 }

 void counting_sort(){
	 for (int i = 0; i <meetings; i++){
     vec[degrees[i]].push_back(i);
   }
 }



 bool check(int index, int color){
 	for(int i = 0; i < meetings; i++){
 		if(adjacency_matrix[index][i] == 1 && color == coloring[i]){
 			return false;
 		}
 	}
 	return true;

 }

 int graphColor(int i){
 	int index = order[i];
 	if(complete){
 		return 0;
 	}
 	for(int color = 1; color <= max_index; color++){
 		if(check(index,color)){
 			coloring[index] = color;
 			if (i < max_index){
 				graphColor(i+1);
 			}
 			else{

 				complete = true;
 				return 0;
 			}
 		}
 	}
 	return 0;
 }

int main (int argc, char** argv){
  const auto start1 = steady_clock::now();
	setup();
	third_proff_setup();
	matching();
	vec_to_matrix();
	matches_to_adj_matrix();
	counting_sort();
	get_order();


	graphColor(0);
  const auto end1 = steady_clock::now();
  cout << "\nRuntime: " << duration_cast<duration<double>>(end1 - start1).count() << "\n";
	
	return(0);
}
