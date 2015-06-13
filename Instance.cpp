#include <iostream>
#include "Instance.h"

Instance::Instance(int _courses,int _periods,int _min_credits,int _max_credits,int _min_courses,int _max_courses,int _prerequisites_size,int* _credits,std::tuple<int,int>* _prerequisites){
	courses = _courses;
	periods = _periods;
	min_credits = _min_credits;
	max_credits = _max_credits;
	min_courses = _min_courses;
	max_courses = _max_courses;
	prerequisites_size = _prerequisites_size;
	credits = _credits;
	prerequisites = _prerequisites;
}
void Instance::print_params(){
	std::cout << "Datos de la instancia" << std::endl;
	std::cout << "Cursos:" << courses << std::endl;
	std::cout << "Periodos:" << periods << std::endl;
	std::cout << "Minima carga:" << min_credits << std::endl;
	std::cout << "Maxima carga:" << max_credits << std::endl;
	std::cout << "Minimos cursos:" << min_courses << std::endl;
	std::cout << "Maximos cursos:" << max_courses << std::endl;
	std::cout << "Cantidad de prerequisitos:" << prerequisites_size << std::endl;
	int i;
	for(i=0;i<courses;i++){
		std::cout << "Creditos Curso " << i+1 << ": "<< credits[i] << std::endl;
	}
	for(i=0;i<prerequisites_size;i++){
		std::cout << "Prerequisito " << i+1 << ": "<< std::get<0>(prerequisites[i]) << ","<< std::get<1>(prerequisites[i]) << std::endl;
	}
}
int Instance::get_courses(){
	return courses;
}
int Instance::get_periods(){
	return periods;
}
int Instance::get_min_credits(){
	return min_credits;
}
int Instance::get_max_credits(){
	return max_credits;
}
int Instance::get_min_courses(){
	return min_courses;
}
int Instance::get_max_courses(){
	return max_courses;
}
int Instance::get_prerequisites_size(){
	return prerequisites_size;
}
int * Instance::get_credits(){
	return credits;
}
std::tuple<int,int>* Instance::get_prerequisites(){
	return prerequisites;
}
