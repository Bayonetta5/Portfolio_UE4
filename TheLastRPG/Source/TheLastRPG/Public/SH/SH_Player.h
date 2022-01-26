// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SH/SH_IRifle.h"
#include "GameFramework/Character.h"
#include "SH_Player.generated.h"

UCLASS()
class THELASTRPG_API ASH_Player : public ACharacter, public ISH_IRifle
{
	GENERATED_BODY()


private:
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<class USH_CUserWidget_CrossHair> CrossHairClass;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UCameraComponent* Camera;

protected:
	UFUNCTION(BlueprintImplementableEvent)
		void OnZoomIn();
	UFUNCTION(BlueprintImplementableEvent)
		void OnZoomOut();

public:
	FORCEINLINE class ASH_CRifle* GetRifle() override { return Rifle; }

public:
	// Sets default values for this character's properties
	ASH_Player();

	void GetLocationAndDirection(FVector& OutStart, FVector& OutEnd, FVector& OutDirection) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnFocus() override;
	void OffFocus() override;

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

	void OnFire();
	void OffFire();

public:
	UFUNCTION(BlueprintCallable) // BP에서 콜할 수 있는 함수
		void ChangeColor(FLinearColor InColor);

private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

private:
	class ASH_CRifle* Rifle;
	class USH_CUserWidget_CrossHair* CrossHair; // 조준점 위젯
};
