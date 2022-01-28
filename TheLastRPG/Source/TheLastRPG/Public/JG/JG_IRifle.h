// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "JG_IRifle.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UJG_IRifle : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THELASTRPG_API IJG_IRifle
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual class AJG_Rifle* GetRifle() = 0;
};
