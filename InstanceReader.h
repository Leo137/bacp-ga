#ifndef INSTANCEREADER_H_
#define INSTANCEREADER_H_
#include "Instance.h"

class InstanceReader{
	public:
		InstanceReader(){};
		static Instance read_instance(const char*);
};
#endif
