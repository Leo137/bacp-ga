#ifndef SOLVERGA_H_
#define SOLVERGA_H_
#include "Instance.h"
#include "Solution.h"
#include "Genotype.h"
#include "Config.h"

class SolverGA{
	public:
		SolverGA();
		Solution solve_instance(Instance);
	private:
		// Helpers
		std::vector<Genotype> generate_initial_population(Instance);
		std::vector<Genotype> select_new_population(std::vector<Genotype>,Genotype*);
		void fill_population(std::vector<Genotype>*);
		Genotype get_random_gen(Instance);
		Solution get_solution(Genotype,Instance,double);
		void calculate_relative_fitness(std::vector<Genotype>*);
		void calculate_cumulative_fitness(std::vector<Genotype>*);
		// AG
		Genotype binary_tournament(std::vector<Genotype>);
		Genotype roulette_selection(std::vector<Genotype>);
		void crossover(std::vector<Genotype>*);
		void mutate(std::vector<Genotype>*);
		void evaluate(std::vector<Genotype>*,Instance);
		void elitism(std::vector<Genotype>*,Genotype*,int);
		std::vector<Genotype> x_over(Genotype,Genotype);
		Genotype m_tate(Genotype);
};
#endif
