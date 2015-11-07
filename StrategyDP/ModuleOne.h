
#ifndef MODULE_ONE_H_
#define MODULE_ONE_H_

#include "IModuleInterface.h"

class ModuleOne : public IModuleInterface
{
public:
	ModuleOne();
	~ModuleOne();

	void Operator();
};

#endif