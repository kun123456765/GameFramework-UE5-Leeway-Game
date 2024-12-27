//--------------------
// kun 2024.12.27
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FLeewayModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
