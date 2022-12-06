
#include <iostream>
using namespace std;
const int meetings = 5;
int degrees[5] = {0,0,0,0,0};

//this takes the list of matched pairs and makes an adjacency_matrix

//teacher1, student, teacher2

int matched_pairs[meetings][3] = {0,1,4,
																	1,0,2,
																	2,2,1,
																	3,3,2,
																	0,4,1};

int adjacency_matrix[meetings][meetings];

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
		for (int i = 0; i < 5; i++){
			for (int j = 0; j < 2; j++){
				cout<< matched_pairs[i][j] << "\n";
			//	cout<< argv[count] << "\n";

			}
		}

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

void print_adjacency_matrix(){
	for (int i = 0; i < meetings; i++){
		for (int j = 0; j < meetings; j++){
			cout<<adjacency_matrix[i][j];
		}
		cout<<"\n";
	}
}

int main(){


	matches_to_adj_matrix();
	print_adjacency_matrix();
	return 0;
}
