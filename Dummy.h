#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleDummy : public Module
{
	bool Init()
	{
		ENGINELOG("Dummy Init!");
		return true;
	}

	bool CleanUp()
	{
		ENGINELOG("Dummy CleanUp!");
		return true;
	}
};