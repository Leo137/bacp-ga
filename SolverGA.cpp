#include <vector>
#include <stdlib.h>
#include <time.h>

#include "SolverGA.h"
#include "Solution.h"
#include "Instance.h"
#include "Config.h"

Solution SolverGA::solve_instance(Instance instance){
	std::vector<Genotype> population = generate_initial_population(instance);
	Genotype best = Genotype(instance.get_courses(),instance.get_periods());
	int iters;
	
	evaluate(population,instance);
	best = elitism(population,best);
	
	for(iters=0;iters<MAX_ITERS;iters++){
		
		population = select_new_population(population,best);
		
		fill_population(population);
		
		evaluate(population,instance);
		
		best = elitism(population,best);
		
	}
	
	return get_solution(best,instance);
}

std::vector<Genotype> SolverGA::generate_initial_population(Instance instance){
	std::vector<Genotype> population = std::vector<Genotype>();
	while(population.size() < POPULATION_SIZE){
		Genotype g = get_random_gen(instance);
		new_population.push_back(g);
	}
	return population;
}

std::vector<Genotype> SolverGA::select_new_population(std::vector<Genotype> population,Genotype best){
	std::vector<Genotype> new_population = std::vector<Genotype>();
	
	// Insert tha best
	new_population.push_back(best);
	
	while(new_population.size() < SELECTION_SIZE){
		Genotype g = roulette_selection(population);
		new_population.push_back(g);
	}
	return new_population;
}

void SolverGA::fill_population(std::vector<Genotype> population){
	while(population.size() < POPULATION_SIZE){
		crossover(population);
		mutate(population);
	}
}

Genotype SolverGA::get_random_gen(Instance instance){
	srand (time(NULL)+rand());
	int periods = instance.get_periods();
	int courses = instance.get_courses();
	int i;
	int* gene = (int*)malloc(sizeof(int)*courses);
	for(i=0;i<courses;i++){
		srand (time(NULL)*periods+rand()*i);
		gene[i] = rand()%periods;
	}
	return Genotype(gene,courses,periods);
}

Solution get_solution(Genotype genotype,Instance instance){
	std::vector<int> * assignation = (std::vector<int>*)malloc(sizeof(std::vector<int>*instance.get_periods());
	int* gene = genotype.get_gene();
	int* credits_period = (int*)malloc(sizeof(instance.get_periods());
	int* credits = instance.get_credits();
	int maxcredits = 0;
	int periods = instance.get_periods();
	int courses = instance.get_courses();
	
	// iterators
	int i,j;
	
	// Get the assignations for each period in vectors
	for(i=0;i<courses;i++){
		assignation[gene[i]].push_back(i);
	}
	
	// Get the credits for each period + max credits in a period
	for(i=0;i<periods;i++){
		credits_period[i] = 0;
		for(j=0;j<assignation[i].size();j++){
			credits_period[i] += credits[assignation[i][j]];
		}
		if(credits_period[i]>max_credits){
			max_credits = credits_period[i];
		}
	}
	
	return Solution(assignation,credits_period,max_credits,periods,0.0);
}

void calculate_relative_fitness(std::vector<Genotype> population){
	int i;
	float sum;
	for(i=0;i<POPULATION_SIZE;i++){
		sum += population[i].get_fitness();
	}
	for(i=0;i<POPULATION_SIZE;i++){
		population[i].set_rfitness(population[i].get_fitness()/sum);
	}
}

void calculate_cumulative_fitness(std::vector<Genotype> population){
	int i;
	population[0].set_cfitness(0.0);
	for(i=1;i<POPULATION_SIZE;i++){
		population[i].set_cfitness(population[i-1].get_cfitness()+population[i].get_rfitness());
	}
	population[0].set_cfitness(population[0].get_rfitness());
}
		
Genotype SolverGA::roulette_selection(std::vector<Genotype> population){
	srand (time(NULL)*population.size()+rand());
	int i;
	float p = (rand()%1000)/1000;
	if(p < population[0].get_cfitness()){
		return population[0];
	}
	else{
		for(i=0;i<POPULATION_SIZE-1;i++){
			if((p >= poplation[i].get_cfitness())&&(p < population[i+1].get_cfitness())){
				return poplation[i+1];
			}
		}
	}
	return population[POPULATION_SIZE-1];
}

Genotype SolverGA::binary_tournament(std::vector<Genotype> population){
	srand (time(NULL)*population.size()+rand());
	
	// unimplemented..
	return population[0];
}

void SolverGA::crossover(std::vector<Genotype> population){
	srand (time(NULL)*population.size()+rand());
	Genotype one;
	int i,r;
	int first = 0;
	for(i=0;i<population.size();i++){
		srand (time(NULL)*population.size()+rand());
		r = rand()%100;
		if(r < CHANCE_CROSS){
			first++;
			if(first%2 == 0){
				std::vector<Genotype> childs = x_over(one,population[i]);
				population.push_back(childs[0]);
				population.push_back(childs[1]);
			}
			else{
				one = population[i];
			}
		}
	}
}

void SolverGA::mutate(std::vector<Genotype> population){
	int i,r;
	int first = 0;
	for(i=0;i<population.size();i++){
		srand (time(NULL)*population.size()+rand());
		r = rand()%100;
		if(r < CHANCE_MUT){
			Genotype a = m_tate(population[i]);
			population.push_back(a);
		}
	}
}

void evaluate(std::vector<Genotype> population,Instance instance){
	int i;
	for(i=0;i<population.size();i++){
		population[i].calculate_fitness(instance);
	}
	calculate_relative_fitness(population);
	calculate_cumulative_fitness(population);
}

std::vector<Genotype> SolverGA::elitism(std::vector<Genotype> population,Genotype best){
	int i;
	for(i=0;i<POPULATION_SIZE;i++){
		if(population[i].get_fitness()<best.get_fitness()){
			best = population[i];
		}
	}
	return best;
}

std::vector<Genotype> SolverGA::x_over(Genotype a,Genotype b){
	Genotype c;
	Genotype d;
	std::vector<Genotype> childs = std::vector<Genotype>();
	
	return childs;
	
}

Genotype SolverGA::m_tate(Genotype a){
	int* gene = a.get_gene();
	int* gene_cpy = (int*)malloc(sizeof(int)*a.get_courses());
	int i;
	int r,r_2;
	for(i=0;i<a.get_courses();i++){
		gene_cpy[i] = gene[i];
	}
	Genotype b = Genotype(gene_cpy,a.get_courses(),a.get_periods());
	r = rand()%a.get_courses();
	r_2 = r;
	while(r_2 == r){
		r_2 = rand()%a.get_courses();
	}
	b.course_swap(r,r_2);
	return b;
}
