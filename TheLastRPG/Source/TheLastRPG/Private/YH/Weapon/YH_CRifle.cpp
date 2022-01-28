#include "YH/Weapon/YH_CRifle.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "YH/Global_YH.h"
// Sets default values
AYH_CRifle::AYH_CRifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;

	CHelpers_YH::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh");

	
	USkeletalMesh* mesh;
	CHelpers_YH::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Lectures/Weapons/Meshes/AR4/SK_AR4.SK_AR4'");
	Mesh->SetSkeletalMesh(mesh);

	CHelpers_YH::GetAsset<UAnimMontage>(&GrabMontage, "AnimMontage'/Game/YongHwan/Montages/YH_Rifle_Grab_Montage.YH_Rifle_Grab_Montage'");
	CHelpers_YH::GetAsset<UAnimMontage>(&UngrabMontage, "AnimMontage'/Game/YongHwan/Montages/YH_Rifle_Ungrab_Montage.YH_Rifle_Ungrab_Montage'");
}

void AYH_CRifle::Equip()
{
	CheckTrue(bEquipped);
	CheckTrue(bEquipping);

	bEquipping = true;
	//플레이어만이 꼭 아니다. 적도된다.
	OwnerCharacter->PlayAnimMontage(GrabMontage);
}

void AYH_CRifle::Begin_Equip()
{
	bEquipped = true;

	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HandSocket);
}

void AYH_CRifle::End_Equip()
{
	bEquipping = false;
}

void AYH_CRifle::Unequip()
{
	CheckFalse(bEquipped);
	CheckTrue(bEquipping);

	bEquipping = true;
	OwnerCharacter->PlayAnimMontage(UngrabMontage);
}

void AYH_CRifle::Begin_Unequip()
{
	bEquipped = false;

	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
}

void AYH_CRifle::End_Unequip()
{
	bEquipping = false;
}

void AYH_CRifle::Begin_Aiming()
{
	bAiming = true;
}

void AYH_CRifle::End_Aiming()
{
	bAiming = false;
}

AYH_CRifle * AYH_CRifle::Spawn(UWorld * InWorld, ACharacter * InOwner)
{
	FActorSpawnParameters params;
	params.Owner = InOwner;
	//AYH_RIfle 형태로 리턴해준다.
	return InWorld->SpawnActor<AYH_CRifle>(params);
}

// Called when the game starts or when spawned
void AYH_CRifle::BeginPlay()
{
	Super::BeginPlay();
	//등에 붙인다
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
	
}

// Called every frame
void AYH_CRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

