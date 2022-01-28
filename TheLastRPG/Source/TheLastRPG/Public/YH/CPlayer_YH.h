// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YH/Weapon/YH_IRifle.h"
#include "GameFramework/Character.h"
#include "CPlayer_YH.generated.h"

UCLASS()
class THELASTRPG_API ACPlayer_YH : public ACharacter, public IYH_IRifle
{
	GENERATED_BODY()

public:
	
	ACPlayer_YH();
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

protected: //줌인하기위해서 블프에서 가져오려고 private -> protected
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class UCameraComponent* Camera;

protected:
	UFUNCTION(BlueprintImplementableEvent)
		void OnZoomIn();

	UFUNCTION(BlueprintImplementableEvent)
		void OnZoomOut();
protected:
	
	virtual void BeginPlay() override;

public: // 순수 가상함수 재정의
	FORCEINLINE class AYH_CRifle* GetRifle() override { return Rifle; }


public:	
	
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	void OnHorizontalLook(float Axis);
	void OnVerticalLook(float Axis);


private:
	void OnRunning();
	void OffRunning();
	void OnRifle();

	void OnAim();
	void OffAim();
public:
	UFUNCTION(BlueprintCallable)
		void ChangeColor(FLinearColor InColor);

private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

private:
	class AYH_CRifle* Rifle;
};
