#include "Gen.h"
#include "Solution.h"

Gen::Gen(int* _chromosome){
	chromosome = _chromosome;
	fitness = 9999999999999; // big value
}

Solution Gen::get_chromosome(){
	return choromosome;
}
float Gen::get_fitness(){
	return fitness;
}
void Gen::calculate_fitness(Instance){
	fitness = 0;
}
void Gen::course_swap(int a,int b){
	int temp = chrosomome[a];
	chrosomome[a] = chrosomome[b];
	chrosomome[b] = temp;
}
