#include "SH/Lecture2/Components/SH_CMontagesComponent.h"
#include "SH/SH_Global.h"
//#include "Animation/AnimMontage.h"

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
}

