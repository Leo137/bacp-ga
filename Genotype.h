#ifndef GENOTYPE_H_
#define GENOTYPE_H_
#include <vector>
#include "Solution.h"
#include "Instance.h"
class Genotype{
	public:
		Genotype(int,int);
		Genotype(int*,int,int);
		int* get_gene();
		float get_fitness();
		float get_cfitness();
		float get_rfitness();
		void set_fitness(float);
		void set_cfitness(float);
		void set_rfitness(float);
		void calculate_fitness(Instance);
		void course_swap(int,int);
		int get_courses();
		int get_periods();
	private:
		int* gene;
		float fitness;
		float rfitness;
		float cfitness;
		int courses;
		int periods;
}
#endif
