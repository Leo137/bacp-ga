#include <vector>
#include <stdlib.h>
#include <time.h>

#include "SolverGA.h"
#include "Solution.h"
#include "Instance.h"
#include "Config.h"

Solution SolverGA::solve_instance(Instance instance){
	int iters;
	std::vector<Gen> population = generate_initial_population();
	
	for(iters=0;iters<MAX_ITERS;iters++){
		if(iters!=0){
			fill_population(population);
		}
		population = elitism(population);
	}
	return Solution();
}

std::vector<Gen> SolverGA::generate_initial_population(){
	std::vector<Gen> population = std::vector<Gen>();
}

void SolverGA::fill_population(std::vector<Gen> population){
	while(population.size() < POPULATION_SIZE){
		crossover(population);
		mutate(population);
	}
}

Gen SolverGA::get_random_gen(std::vector<Gen> population){
	srand (time(NULL)*population.size()+rand());
	return population[rand()%population.size()];
}

Gen SolverGA::binary_tournament(std::vector<Gen> population){
	srand (time(NULL)*population.size()+rand());
	return population[0];
}

void SolverGA::crossover(std::vector<Gen> population){
	srand (time(NULL)*population.size()+rand());
	int r = rand()%100;
	if(r < CHANCE_CROSS){
		Gen a = binary_tournament(population);
		Gen b = binary_tournament(population);
	}	
}

void SolverGA::mutate(std::vector<Gen> population){
	srand (time(NULL)*population.size()+rand());
	int r = rand()%100;
	if(r < CHANCE_MUT){
		Gen a = binary_tournament(population);
	}
}

std::vector<Gen> SolverGA::elitism(std::vector<Gen> population){
}
