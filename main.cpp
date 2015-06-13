#include <iostream>

#include "Instance.h"
#include "InstanceReader.h"
#include "Solution.h"
#include "SolverGA.h"

int main (int argc, char const *argv[]){
	if (argc != 2)
	{
		//cout << "BACP" << endl;
		return 1;
	}
	
	Instance i = InstanceReader::read_instance(argv[1]);
	i.print_params();
	Solution s = SolverGA::solve_instance(i);
	return 0;
}
