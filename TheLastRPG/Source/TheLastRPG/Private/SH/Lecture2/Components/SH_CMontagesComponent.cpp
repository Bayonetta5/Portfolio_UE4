#include "SH/Lecture2/Components/SH_CMontagesComponent.h"
#include "SH/SH_Global.h"
#include "GameFramework/Character.h"

USH_CMontagesComponent::USH_CMontagesComponent()
{

}


void USH_CMontagesComponent::BeginPlay()
{
	Super::BeginPlay();
	
	CheckNull(DataTable);

	TArray<FMontageData*> datas;
	DataTable->GetAllRows<FMontageData>("", datas);

	for (const FMontageData* data : datas)
	{
		if (!!data)
		{
			SH_CLog::Print(data->AnimMontage->GetPathName());
			SH_CLog::Log(data->AnimMontage->GetPathName());
		}
	}

	for (int32 i = 0; i < (int32)EStateType::Max; ++i)
	{
		for (FMontageData* data : datas) // 액셀 데이터
		{
			if ((EStateType)i == data->Type) // 타입 같은것만
			{
				Datas[i] = data;

				continue;
			}
		} // for(data)
	}//for(i)
}

void USH_CMontagesComponent::PlayRoll()
{
	PlayAnimMontage(EStateType::Roll);
}

void USH_CMontagesComponent::PlayBackstep()
{
	PlayAnimMontage(EStateType::Backstep);
}

void USH_CMontagesComponent::PlayAnimMontage(EStateType InState)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());

	const FMontageData* data = Datas[(int32)InState];

	if (!!data)
	{
		if (!!data->AnimMontage)
		{
			character->PlayAnimMontage(data->AnimMontage, data->PlayRatio, data->StartSection);
		}
	}
}

