#include <iostream>
#include <vector>
#include <iomanip>
#include "Instance.h"
#include "Solution.h"
Solution::Solution(){
}
Solution::Solution(std::vector<int>* _assignation, int* _credits_period, int _max_credits, int _periods){
	assignation = _assignation;
	credits_period = _credits_period;
	max_credits = _max_credits;
	periods = _periods;
}
void Solution::show_solution(){
	int i,j;
	for(i=0;i<periods;i++){
		std::cout << "Periodo " << i+1 << std::endl;
		for(j=0;j<(int)assignation[i].size();j++){
			if(j+1<(int)assignation[i].size()){
				std::cout << assignation[i][j] << " - ";
			}
			else{
				std::cout << assignation[i][j] << " : " << credits_period[i] << std::endl;
			}
		}
	}
	std::cout << std::endl;
	std::cout << "Maxima carga academica " << max_credits << std::endl;
	std::cout << "Tiempo ejecucion " << std::fixed << std::setprecision(2) << time_execution << " s" << std::endl;
}
std::vector<int>* Solution::get_assignation(){
	return assignation;
}
int * Solution::get_credits_period(){
	return credits_period;
}
int Solution::get_max_credits(){
	return max_credits;
}
int Solution::get_periods(){
	return periods;
}

float Solution::get_time_execution(){
	return time_execution;
}
