#ifndef GEN_H_
#define GEN_H_
#include <vector>
#include "Solution.h"
#include "Instance.h"
class Gen{
	public:
		Gen(int*);
		int* get_chromosomes();
		float get_fitness();
		void calculate_fitness(Instance);
		void course_swap(int,int);
	private:
		int* chromosome;
		float fitness;
}
#endif
