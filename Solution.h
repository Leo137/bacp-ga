#ifndef SOLUTION_H_
#define SOLUTION_H_
#include <vector>
class Solution{
	public:
		Solution();
		Solution(std::vector<int>*,int*,int,int,float);
		void show_solution();
		std::vector<int>* get_assignation();
		int* get_credits_period();
		int get_max_credits();
		int get_periods();
		float get_time_execution();
	private:
		std::vector<int>* assignation;
		int * credits_period;
		int max_credits;
		int periods;
		float time_execution;
};
#endif
