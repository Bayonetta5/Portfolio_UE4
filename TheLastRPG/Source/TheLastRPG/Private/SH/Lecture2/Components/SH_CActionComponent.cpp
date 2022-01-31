#include "SH/Lecture2/Components/SH_CActionComponent.h"
#include "SH/Lecture2/Actions/SH_CActionData.h"
#include "SH/Lecture2/Actions/SH_CEquipment.h"
#include "SH/SH_Global.h"
#include "GameFramework/Character.h"

USH_CActionComponent::USH_CActionComponent()
{

}

void USH_CActionComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* character = Cast<ACharacter>(GetOwner());

	for (int32 i = 0; i < (int32)EActionType::Max; ++i)
	{
		if (!!Datas[i])
			Datas[i]->BeginPlay(character);
	}
}

void USH_CActionComponent::SetUnarmedMode()
{
	if (!!Datas[(int32)Type])
	{
		ASH_CEquipment* equipment = Datas[(int32)Type]->GetEquipment();
		if (!!equipment)
			equipment->Unequip();
	}

	ChangeType(EActionType::Unarmed);
}

void USH_CActionComponent::SetOneHandMode()
{
	SetMode(EActionType::OneHand);
}

void USH_CActionComponent::SetTwoHandMode()
{
	SetMode(EActionType::TwoHand);
}

void USH_CActionComponent::SetMode(EActionType InType)
{
	if (Type == InType) // 같은 무기 장착
	{
		SetUnarmedMode(); // 무기 해제

		return;
	}
	else if (IsUnarmedMode() == false) // 다른 무기 장착
	{
		ASH_CEquipment* equipment = Datas[(int32)Type]->GetEquipment();
		CheckNull(equipment);

		equipment->Unequip();
	}

	ASH_CEquipment* equipment = Datas[(int32)InType]->GetEquipment();
	CheckNull(equipment);

	equipment->Equip();

	ChangeType(InType);
}

void USH_CActionComponent::ChangeType(EActionType InNewType)
{
	/// Q. 아래 InNewType으로 하던데, Type으로 미리 저장해두는게 맞지 않나?
	EActionType prevType = InNewType; // 강의는 InNewType이었음.
	Type = InNewType; // 새롭게 수정

	if (OnActionTypeChanged.IsBound())
		OnActionTypeChanged.Broadcast(prevType, InNewType);
}