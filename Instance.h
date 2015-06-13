#ifndef INSTANCE_H_
#define INSTANCE_H_
#include <tuple>
class Instance {
	public:
		Instance(int,int,int,int,int,int,int,int*,std::tuple<int,int>*);
		void print_params();
		int get_courses();
		int get_periods();
		int get_min_credits();
		int get_max_credits();
		int get_min_courses();
		int get_max_courses();
		int get_prerequisites_size();
		int * get_credits();
		std::tuple<int,int>* get_prerequisites();
		
	private:
		int courses;
		int periods;
		int min_credits;
		int max_credits;
		int min_courses;
		int max_courses;
		int prerequisites_size;
		int * credits;
		std::tuple<int,int> * prerequisites;
};
#endif
