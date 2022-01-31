#include "SH/Lecture2/Actions/SH_CActionData.h"
#include "SH/Lecture2/Actions/SH_CEquipment.h"
#include "SH/SH_Global.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

void USH_CActionData::BeginPlay(class ACharacter* InOwnerCharacter)
{
	FTransform transform;

	// Equipment
	{
		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ASH_CEquipment>(EquipmentClass, transform, InOwnerCharacter); // 생성
		Equipment->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true)); // 캐릭터에 장착
		Equipment->SetData(EquipmentData); // 데이터 업로드

		UGameplayStatics::FinishSpawningActor(Equipment, transform); // 최종적으로 확정
	}
}