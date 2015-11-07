
#include "ModuleBase.h"

ModuleBase::ModuleBase(IModuleInterface* pModuleInterface) : pModuleInterface_(pModuleInterface)
{

}

ModuleBase::~ModuleBase()
{
	if (pModuleInterface_)
	{
		delete pModuleInterface_;
	}
}

void ModuleBase::Operator()
{
	pModuleInterface_->Operator();
}