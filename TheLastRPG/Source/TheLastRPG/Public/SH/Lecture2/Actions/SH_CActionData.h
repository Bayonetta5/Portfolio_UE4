#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SH_CActionData.generated.h"

USTRUCT(BlueprintType)
struct FEquipmentData // 무기 장착관련 몽타주 데이터
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float PlayRatio = 1.0f;

	UPROPERTY(EditAnywhere)
		FName StartSection;

	UPROPERTY(EditAnywhere)
		bool bCanMove = true;
};

UCLASS()
class THELASTRPG_API USH_CActionData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	FORCEINLINE class ASH_CEquipment* GetEquipment() { return Equipment; }

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ASH_CEquipment> EquipmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FEquipmentData EquipmentData;

public:
	void BeginPlay(class ACharacter* InOwnerCharacter);

private:
	class ASH_CEquipment* Equipment;
};
