#ifndef SOLVERGA_H_
#define SOLVERGA_H_
#include "Instance.h"
#include "Solution.h"
#include "Gen.h"

class SolverGA{
	public:
		static Solution solve_instance(Instance);
	private:
		// Helpers
		std::vector<Gen> generate_initial_population();
		void fill_population(std::vector<Gen>);
		Gen get_random_gen(std::vector<Gen>);
		// AG
		Gen binary_tournament(std::vector<Gen>);
		void crossover(std::vector<Gen>);
		void mutate(std::vector<Gen>);
		std::vector<Gen> elitism(std::vector<Gen>);
};
#endif
