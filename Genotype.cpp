#include "Genotype.h"
#include "Solution.h"

Genotype::Genotype(int _courses,int _periods){
	// gene = _gene;
	courses = _courses;
	periods = _periods;
	fitness = 9999999999999; // big value
}
Genotype::Genotype(int* _gene,int _courses,int _periods){
	gene = _gene;
	courses = _courses;
	periods = _periods;
	fitness = 9999999999999; // big value
}
Solution Genotype::get_gene(){
	return gene;
}
float Genotype::get_fitness(){
	return fitness;
}
float Genotype::get_cfitness(){
	return cfitness;
}
float Genotype::get_rfitness(){
	return rfitness;
}
void Genotype::set_fitness(float _fitness){
	fitness = _fitness;
}
void Genotype::set_cfitness(float _cfitness){
	cfitness = _cfitness;
}
void Genotype::set_rfitness(float _rfitness){
	rfitness = _rfitness;
}
void Genotype::calculate_fitness(Instance instance){
	fitness = 0; // lol
}
void Genotype::course_swap(int a,int b){
	int temp = gene[a];
	gene[a] = gene[b];
	gene[b] = temp;
}
int Genotype::get_courses(){
	return courses;
}
int Genotype::get_periods(){
	return periods;
}
