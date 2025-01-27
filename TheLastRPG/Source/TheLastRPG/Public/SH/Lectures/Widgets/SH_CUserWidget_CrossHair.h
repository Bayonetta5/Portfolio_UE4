// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SH_CUserWidget_CrossHair.generated.h"

/**
 * 
 */
UCLASS()
class THELASTRPG_API USH_CUserWidget_CrossHair : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnFocus();

	UFUNCTION(BlueprintImplementableEvent)
		void OffFocus();
};
