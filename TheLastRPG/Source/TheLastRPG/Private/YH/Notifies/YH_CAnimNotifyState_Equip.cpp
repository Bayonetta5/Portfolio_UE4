// Fill out your copyright notice in the Description page of Project Settings.


#include "YH/Notifies/YH_CAnimNotifyState_Equip.h"
#include "YH/Global_YH.h"
#include "YH/Weapon/YH_IRifle.h"
#include "YH/Weapon/YH_CRifle.h"

FString UYH_CAnimNotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void UYH_CAnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);

	IYH_IRifle* rifle = Cast<IYH_IRifle>(MeshComp->GetOwner());
	CheckNull(rifle);

	rifle->GetRifle()->Begin_Equip();
}

void UYH_CAnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);

	IYH_IRifle* rifle = Cast<IYH_IRifle>(MeshComp->GetOwner());
	CheckNull(rifle);

	rifle->GetRifle()->End_Equip();
}
