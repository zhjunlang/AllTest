
#ifndef MODULE_BASE_H_
#define MODULE_BASE_H_

#include "IModuleInterface.h"

class ModuleBase
{
public:
	ModuleBase(IModuleInterface* pModuleInterface);
	~ModuleBase();

	void Operator();

private:
	IModuleInterface* pModuleInterface_;
};

#endif