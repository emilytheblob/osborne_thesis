



int find(int arr[], int len, int seek){ //return the index of what we are looking for in an array or -1 if not found
	for(int i = 0; i < len; i++){

		if(arr[i] == seek){
			return i;
		}
	}
	std::cout<<"Error: find function didn't find that value in the array \n";
	return -1;
}

int check_space(int teacher, int match_counter[], int max_s_per_prof[]){ // returns 1 or 0 for if teacher has more space/spots available
	std::cout<< "Teacher " << teacher << " has " << match_counter[teacher] << " tentative matches rn. \n";
	if(match_counter[teacher] < max_s_per_prof[teacher]){
		return 1;
	} else{
		return 0;
	}
}
