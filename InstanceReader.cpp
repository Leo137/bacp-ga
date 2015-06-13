#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <string>
#include <sstream>
#include "InstanceReader.h"

Instance InstanceReader::read_instance(const char* file_path){
	std::ifstream file;
	int courses;
	int periods;
	int min_credits;
	int max_credits;
	int min_courses;
	int max_courses;
	int prerequisites_size;
	
	int * credits;
	std::tuple<int,int> * prerequisites;
	
	char line[1000];
	std::string string_line;
	int i;
	int n;
	int m;
	
	file.open(file_path);
	
	// Primera Linea
	file.getline(line,1000);
	sscanf(line,"%d %d %d %d %d %d %d",&courses,&periods,&min_credits,&max_credits,&min_courses,&max_courses,&prerequisites_size);
	
	// Crea estructuras
	credits = (int*)malloc(sizeof(int)*courses);
	prerequisites = (std::tuple<int,int>*)malloc(sizeof(std::tuple<int,int>)*prerequisites_size);
	
	// Segunda Linea
	std::getline(file,string_line);
	std::istringstream iss(string_line);
	for(i=0;i<courses;i++){
		if(iss >> n){
			credits[i] = n;
		}
	}
	
	// Tercera Linea
	std::getline(file,string_line);
	std::istringstream iss_2(string_line);
	for(i=0;i<prerequisites_size;i++){
		if(iss_2 >> n && iss_2 >> m){
			prerequisites[i] = std::tuple<int,int>(n,m);
		}
	}
	
	return Instance(courses,periods,min_credits,max_credits,min_courses,max_courses,prerequisites_size,credits,prerequisites);
	
}
