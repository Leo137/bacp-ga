#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "SolverGA.h"
#include "Solution.h"
#include "Instance.h"
#include "Config.h"

SolverGA::SolverGA(){
}
Solution SolverGA::solve_instance(Instance instance){
	std::vector<Genotype> population = generate_initial_population(instance);
	Genotype best = Genotype(instance.get_courses(),instance.get_periods());
	int iters;
	iters = 0;
	clock_t start_time,end_time;
	double diff_time;
	start_time = clock();
	evaluate(&population,instance);
	elitism(&population,&best,iters);
		
	for(iters=0;iters<MAX_ITERS;iters++){

		//std::cout << "Seleccion" << std::endl;
		population = select_new_population(population,&best);

		//std::cout << "Mutacion y Crossover" << std::endl;
		fill_population(&population);
		
		//std::cout << "Evaluacion" << std::endl;
		evaluate(&population,instance);
		
		//std::cout << "Elitismo" << std::endl;
		elitism(&population,&best,iters);
	}
	
	end_time = clock();
	diff_time = (end_time-start_time)/(CLOCKS_PER_SEC/1000);
	
	Solution s = get_solution(best,instance,diff_time);
	return s;
}

std::vector<Genotype> SolverGA::generate_initial_population(Instance instance){
	std::vector<Genotype> population = std::vector<Genotype>();
	while(population.size() < POPULATION_SIZE){
		Genotype g = get_random_gen(instance);
		population.push_back(g);
	}
	return population;
}

std::vector<Genotype> SolverGA::select_new_population(std::vector<Genotype> population,Genotype* best){
	std::vector<Genotype> new_population = std::vector<Genotype>();
	
	// Insert tha best
	new_population.push_back(*best);
	
	while(new_population.size() < SELECTION_SIZE){
		
		Genotype g = roulette_selection(population);
		new_population.push_back(g);
	}
	return new_population;
}

void SolverGA::fill_population(std::vector<Genotype>* population){
	while((*population).size() < POPULATION_SIZE){
		crossover(population);
		mutate(population);
	}
	(*population).resize(POPULATION_SIZE);
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

Solution SolverGA::get_solution(Genotype genotype,Instance instance,double diff_time){
	std::vector<int>* assignation = new std::vector<int>[instance.get_periods()];
	int* gene = genotype.get_gene();
	int* credits_period = new int[instance.get_periods()];
	int* credits = instance.get_credits();
	int max_credits = 0;
	int periods = instance.get_periods();
	int courses = instance.get_courses();
	
	// iterators
	int i,j;
	
	// Get the assignations for each period in vectors
	for(i=0;i<periods;i++){
		assignation[i] = std::vector<int>();
	}
	for(i=0;i<courses;i++){
		assignation[gene[i]].push_back(i);
	}
	
	// Get the credits for each period + max credits in a period
	for(i=0;i<periods;i++){
		credits_period[i] = 0;
		for(j=0;j<(int)assignation[i].size();j++){
			credits_period[i] += credits[assignation[i][j]];
		}
		if(credits_period[i]>max_credits){
			max_credits = credits_period[i];
		}
	}
	Solution s = Solution(assignation,credits_period,max_credits,periods,genotype.get_fitness(),(float)diff_time);
	return s;
}

void SolverGA::calculate_relative_fitness(std::vector<Genotype>* population){
	int i;
	float sum = 0;
	float max_fit = 0;
	float min_fit = 999999999999;
	float adjust = 0;
	for(i=0;i<POPULATION_SIZE;i++){
		if((*population)[i].get_fitness() > max_fit){
			max_fit = (*population)[i].get_fitness();
		}
		if((*population)[i].get_fitness() < min_fit){
			min_fit = (*population)[i].get_fitness();
		}
	}
	adjust = max_fit + min_fit;
	for(i=0;i<POPULATION_SIZE;i++){
		sum += (adjust-(*population)[i].get_fitness());
	}
	
	for(i=0;i<POPULATION_SIZE;i++){
		(*population)[i].set_rfitness((adjust-(*population)[i].get_fitness())/sum);
	}
}

void SolverGA::calculate_cumulative_fitness(std::vector<Genotype>* population){
	int i;
	(*population)[0].set_cfitness(0.0);
	for(i=1;i<POPULATION_SIZE;i++){
		(*population)[i].set_cfitness((*population)[i-1].get_cfitness()+(*population)[i].get_rfitness());
	}
	(*population)[0].set_cfitness((*population)[0].get_rfitness());
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
			if((p >= population[i].get_cfitness())&&(p < population[i+1].get_cfitness())){
				return population[i+1];
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

void SolverGA::crossover(std::vector<Genotype>* population){
	srand (time(NULL)*(*population).size()+rand());
	Genotype one = Genotype();
	int i,r;
	int first = 0;
	for(i=0;i<(int)(*population).size();i++){
		srand (time(NULL)*(*population).size()+rand());
		r = rand()%100;
		if(r > CHANCE_CROSS){
			first++;
			if(first%2 == 0){
				std::vector<Genotype> childs = x_over(one,(*population)[i]);
				(*population).push_back(childs[0]);
				(*population).push_back(childs[1]);
			}
			else{
				one = (*population)[i];
			}
		}
	}
}

void SolverGA::mutate(std::vector<Genotype>* population){
	int i,r;
	for(i=0;i<(int)(*population).size();i++){
		srand (time(NULL)*(*population).size()+rand());
		r = rand()%100;
		if(r > CHANCE_MUT){
			Genotype a = m_tate((*population)[i]);
			(*population).push_back(a);
		}
	}
}

void SolverGA::evaluate(std::vector<Genotype>* population,Instance instance){
	int i;
	for(i=0;i<(int)(*population).size();i++){
		(*population)[i].calculate_fitness(instance);
	}
	
	calculate_relative_fitness(population);
	calculate_cumulative_fitness(population);
}

void SolverGA::elitism(std::vector<Genotype>* population,Genotype* best,int iter){
	int i;
	for(i=0;i<(int)(*population).size();i++){
		if((*population)[i].get_fitness()<(*best).get_fitness()){
			//std::cout << "Nuevo best: " << (*population)[i].get_fitness() << " en iteracion " << iter+1 << "." << std::endl;
			(*best) = (*population)[i];
		}
	}
}

std::vector<Genotype> SolverGA::x_over(Genotype a,Genotype b){
	std::vector<Genotype> childs = std::vector<Genotype>();
	int* gene_a = a.get_gene();
	int* gene_b = b.get_gene();
	int* gene_c = (int*)malloc(sizeof(int)*a.get_courses());
	int* gene_d = (int*)malloc(sizeof(int)*a.get_courses());
	int i;
	int r = 1 + rand()%(a.get_courses()-2);
	for(i=0;i<a.get_courses();i++){
		if(i < r){
			gene_c[i] = gene_a[i];
			gene_d[i] = gene_b[i];
		}
		else{
			gene_c[i] = gene_b[i];
			gene_d[i] = gene_a[i];
		}
	}
	Genotype c = Genotype(gene_c,a.get_courses(),a.get_periods());
	Genotype d = Genotype(gene_d,a.get_courses(),a.get_periods());
	childs.push_back(c);
	childs.push_back(d);
	return childs;
}

Genotype SolverGA::m_tate(Genotype a){
	int* gene = a.get_gene();
	int* gene_cpy = new int[a.get_courses()];
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
