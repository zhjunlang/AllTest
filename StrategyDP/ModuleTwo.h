
#ifndef MODULE_TWO_H_
#define MODULE_TWO_H_

#include "IModuleInterface.h"

class ModuleTwo : public IModuleInterface
{
public:
	ModuleTwo();
	~ModuleTwo();
	
	void Operator();
};

#endif