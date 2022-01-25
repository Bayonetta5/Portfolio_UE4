#include "SH/SH_CRifle.h"
#include "SH/SH_Global.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

ASH_CRifle* ASH_CRifle::Spawn(class UWorld* InWorld, class ACharacter* InOwner)
{
	FActorSpawnParameters params;
	params.Owner = InOwner;

	return InWorld->SpawnActor<ASH_CRifle>(params);
}

ASH_CRifle::ASH_CRifle()
{
	PrimaryActorTick.bCanEverTick = true;

	SH_CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh");

	USkeletalMesh* mesh;
	SH_CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Lectures/Weapons/Meshes/AR4/SK_AR4.SK_AR4'");
	Mesh->SetSkeletalMesh(mesh);

	/// TODO Montages
	SH_CHelpers::GetAsset<UAnimMontage>(&GrabMontage, "AnimMontage'/Game/SungHoon/Character/Montage/SH_Rifle_Grab_Montage.SH_Rifle_Grab_Montage'");
	SH_CHelpers::GetAsset<UAnimMontage>(&UngrabMontage, "AnimMontage'/Game/SungHoon/Character/Montage/SH_Rifle_Ungrab_Montage.SH_Rifle_Ungrab_Montage'");

}

#pragma region Equip Animation
void ASH_CRifle::Equip()
{
	CheckTrue(bEquipped); // 이미 장비를 장착중이면 pass
	CheckTrue(bEquipping); // 장착 도중이라면 pass

	bEquipping = true;
	// OwnerCharacter로 하는 이유는 다른 캐릭터(적 AI)도 붙을 수 있어서 중립적인 변수로 만듦.
	OwnerCharacter->PlayAnimMontage(GrabMontage);

}

void ASH_CRifle::Begin_Equip()
{
	bEquipped = true;
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HandSocket);
}

void ASH_CRifle::End_Equip()
{
	bEquipping = false;
}
#pragma endregion

#pragma region Unequip Animation
void ASH_CRifle::Unequip()
{
	CheckFalse(bEquipped); // 장착중이지 않을때는 pass
	CheckTrue(bEquipping); // 장착 도중이라면 pass

	bEquipping = true;
	OwnerCharacter->PlayAnimMontage(UngrabMontage);
}

void ASH_CRifle::Begin_Unequip()
{
	bEquipped = false;
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
}

void ASH_CRifle::End_Unequip()
{
	bEquipping = false;
}
#pragma endregion

void ASH_CRifle::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner()); // 본인 자신의 소유권을 가져옴
												  
	// 본인 캐릭터의 메시로가서 소켓에 현재 본인을 부착하는 함수.
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
}

void ASH_CRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

