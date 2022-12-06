#include <iostream>
#include <stdio.h>
#include <list>
#include <vector>
#include<typeinfo>
#include <algorithm>
#include "util_functions.cpp"
using namespace std;

const int students = 6;
const int teachers = 4; //note: all numbers in rankings represent identities and positions rep ranks

//teacher's rankings of students
int teachers_rankings[teachers][students]={3,1,2,0,5,4,
														 4,5,3,0,2,1,
														 1,2,0,5,4,3,
														 3,4,5,0,1,2};

//student's rankings of teachers
int students_rankings[students][teachers]= {0,1,2,3,
														  3,1,2,0,
															0,1,3,2,
															3,0,1,2,
															0,3,1,2,
															3,2,1,0};

int max_s_per_prof[teachers]= {2,1,2,2};

int match_counter[teachers] = { };
bool is_student_matched[students] = { };
vector<vector<int>> matches {};//[profesor][matches]

void setup(){ // sets up the vectors
	for(int i = 0; i < teachers; i++){
		vector<int> setup{};
		matches.push_back(setup);
	}
}

//the lines bellow are functions included in util_functions. They are listed here so you can see their inputs.
//int find(int arr[], int len, int seek){ //return the index of what we are looking for in an array or -1 if not found

//int check_space(int teacher, int match_counter[], int max_s_per_prof[]){ // returns 1 or 0 for if teacher has more space/spots available

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




void print_teachers_list(int teacher){
	std::cout<< "teacher #" << teacher << " ";
	vector< vector<int> >::iterator row;
	vector<int>::iterator col;
		for( col = matches[teacher].begin(); col != matches[teacher].end(); col++) {
			std::cout << *col << ",";
		}
		std::cout<<"\n";
}


 void print_results(){
	 for (int i = 0; i<teachers; i++){
		 print_teachers_list(i);
	 }
 }

int matching(){
	for(int s = 0; s < students; s++){
		for(int p = 0; p < teachers; p++){
			int t = students_rankings[s][p];// this makes it so we are testing the teachers in order of how students ranked them rather than in the same order every time
			std::cout<< "We are trying to match student " << s << " and teacher "<<t<<". \n";
			int space_bool = check_space(t, match_counter, max_s_per_prof);

			if(is_student_matched[s]==1){ // if student is already matched, move along
					std::cout<< "student " << s << " is already matched. \n";
					t = 0;
					break;
					//we want to break back to the s level loop (test this)
			} else if (space_bool == 1){ // if teacher has an empty space
					std::cout << "teacher "<< t << " has an empty space so we will add student " << s << ".\n";
					add(s,t);//add student to teachers list
					std::cout << "teacher " << t << " list is currently: ";
					print_teachers_list(t);
					std::cout<< "\n";
					break;
			} else {
					int lowest_ranked = min_ranked(t, teachers_rankings, s);
					if(s == lowest_ranked){
						std::cout<<"s == lowest_ranked \n";
						continue; //i think this moves on to next t
					} else{
						std::cout << "swap because we found a better ranked match \n";
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

int main (int argc, char** argv){
	setup();
	matching();
	print_results();


	return(0);
}
