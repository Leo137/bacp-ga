#include <iostream>

#include "Instance.h"
#include "InstanceReader.h"
#include "Solution.h"
#include "SolverGA.h"

int main (int argc, char const *argv[]){
	if (argc != 2)
	{
		std::cout << "Numero incorrecto de parametros" << std::endl;
		std::cout << "Usage: ./bacp instancia.txt" << std::endl;
		//Instance i = InstanceReader::read_instance("/home/leo137/Dev/bacp/informatica/bacp8.txt");
		//i.print_params();
		//SolverGA solverGA = SolverGA();
		//Solution s = solverGA.solve_instance(i);
		//s.show_solution();
		/*i = InstanceReader::read_instance("/home/leo137/Dev/bacp/informatica/bacp10.txt");
		s = solverGA.solve_instance(i);
		s.show_solution();*/
		/*i = InstanceReader::read_instance("/home/leo137/Dev/bacp/informatica/bacp12.txt");
		s = solverGA.solve_instance(i);
		s.show_solution();*/
		//i = InstanceReader::read_instance("/home/leo137/Dev/bacp/informatica/bacp10.txt");
		//s = solverGA.solve_instance(i);
		//s.show_solution();
	}
	else{
		Instance i = InstanceReader::read_instance(argv[1]);
		i.print_params();
		SolverGA solverGA = SolverGA();
		Solution s = solverGA.solve_instance(i);
		s.show_solution();
	}
	return 0;
}
