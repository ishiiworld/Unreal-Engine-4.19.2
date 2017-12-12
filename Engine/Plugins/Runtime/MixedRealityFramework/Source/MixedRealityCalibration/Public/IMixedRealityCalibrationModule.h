// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "IConsoleManager.h" // for TAutoConsoleVariable<>

class IConsoleVariable;

/**
 * 
 */
class IMixedRealityCalibrationModule : public IModuleInterface
{
public:
	/** Virtual destructor. */
	virtual ~IMixedRealityCalibrationModule() {}
};

