#include "Genotype.h"
#include "Solution.h"
#include <cmath>

Genotype::Genotype(){
}
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
int* Genotype::get_gene(){
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
	int* credits = instance.get_credits();
	std::tuple<int,int>* prerequisites = instance.get_prerequisites();
	int prerequisites_size = instance.get_prerequisites_size();
	int* period_load = new int[periods];
	int* period_courses = new int[periods];
	int max_load = 0;
	int sum_load = 0;
	float avg_load;
	float desv_load = 0;
	int i,c_1,c_2;
	int r = 0;
	// Asignacion de cargas en periodos
	for(i=0;i<periods;i++){
		period_load[i] = 0;
		period_courses[i] = 0;
	}
	for(i=0;i<courses;i++){
		period_load[gene[i]] += credits[i];
		period_courses[gene[i]] += 1;
	}
	// Determinacion del max load
	for(i=0;i<periods;i++){
		if(period_load[i] > max_load){
			max_load = period_load[i];
		}
		sum_load += period_load[i];
	}
	avg_load = ((float)sum_load)/((float)periods);
	for(i=0;i<periods;i++){
		desv_load += std::abs(avg_load - period_load[i]);
	}
	// Calculo de incumplimiento de restricciones
	// Min-Max creditos y cursos por periodo
	for(i=0;i<periods;i++){
		if(period_load[i] < instance.get_min_credits()){
			r+=7;
		}
		if(period_load[i] > instance.get_max_credits()){
			r+=7;
		}
		if(period_courses[i] < instance.get_min_courses()){
			r+=7;
		}
		if(period_courses[i] > instance.get_max_courses()){
			r+=7;
		}
	}
	// Prerequisitos
	for(i=0;i<prerequisites_size;i++){
		c_1 = std::get<0>(prerequisites[i]);
		c_2 = std::get<1>(prerequisites[i]);
		if(gene[c_2] <= gene[c_1]){
			r++;
		}
	}
	// Asignar fitness del individuo
	fitness = max_load + desv_load + r*PENALIZE;
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
Genotype& Genotype::operator=(Genotype a){
	std::swap((*this).gene,a.gene);
	(*this).fitness = a.fitness;
	(*this).cfitness = a.cfitness;
	(*this).rfitness = a.rfitness;
	(*this).courses = a.courses;
	(*this).periods = a.periods;
	
	return *this;
}
Genotype::~Genotype(){
	//free(gene);
}
void Genotype::free_gene(){
	delete gene;
}
