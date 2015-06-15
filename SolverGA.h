#ifndef SOLVERGA_H_
#define SOLVERGA_H_
#include "Instance.h"
#include "Solution.h"
#include "Genotype.h"

class SolverGA{
	public:
		static Solution solve_instance(Instance);
	private:
		// Helpers
		std::vector<Genotype> generate_initial_population(Instance);
		std::vector<Genotype> select_new_population(std::vector<Genotype>,Genotype);
		void fill_population(std::vector<Genotype>);
		Genotype get_random_gen(Instance);
		Solution get_solution(Genotype,Instance);
		void calculate_relative_fitness(std::vector<Genotype>);
		void calculate_cumulative_fitness(std::vector<Genotype>);
		// AG
		Gen binary_tournament(std::vector<Genotype>);
		Gen roulette_selection(std::vector<Genotype>);
		void crossover(std::vector<Genotype>);
		void mutate(std::vector<Genotype>);
		void evaluate(std::vector<Genotype>,Instance);
		Genotype elitism(std::vector<Genotype>,Genotype);
		std::vector<Genotype> x_over(Genotype,Genotype);
		Genotype m_tate(Genotype);
};
#endif
