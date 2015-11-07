
#include <iostream>

#include "ModuleBase.h"
#include "ModuleOne.h"
#include "ModuleTwo.h"

int main()
{
	ModuleBase *pModuleBase;

	pModuleBase = new ModuleBase(new ModuleOne());
	pModuleBase->Operator();
	delete pModuleBase;
	pModuleBase = 0;

	pModuleBase = new ModuleBase(new ModuleTwo());
	pModuleBase->Operator();
	delete pModuleBase;
	pModuleBase = 0;

	return 0;
}