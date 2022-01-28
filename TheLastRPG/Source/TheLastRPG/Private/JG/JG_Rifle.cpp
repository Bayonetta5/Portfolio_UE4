// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/JG_Rifle.h"
#include "JG/JG_Global.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

AJG_Rifle* AJG_Rifle::Spawn(class UWorld* InWorld, class ACharacter* InOwner)
{
	FActorSpawnParameters params;
	params.Owner = InOwner;

	return InWorld->SpawnActor<AJG_Rifle>(params);
}

// Sets default values
AJG_Rifle::AJG_Rifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	JG_Helpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh");

	USkeletalMesh* mesh;
	JG_Helpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Lectures/Weapons/Meshes/AR4/SK_AR4.SK_AR4'");
	Mesh->SetSkeletalMesh(mesh);

	JG_Helpers::GetAsset<UAnimMontage>(&GrabMontage, "AnimMontage'/Game/JongGyun/Character/Animation/Montage/Rifle_Grab_Montage.Rifle_Grab_Montage'");
	JG_Helpers::GetAsset<UAnimMontage>(&UngrabMontage, "AnimMontage'/Game/JongGyun/Character/Animation/Montage/Rifle_Ungrab_Montage.Rifle_Ungrab_Montage'");

}

void AJG_Rifle::Equip()
{
	CheckTrue(bEquipped);
	CheckTrue(bEquipping);

	bEquipping = true;
	OwnerCharacter->PlayAnimMontage(GrabMontage);
}

void AJG_Rifle::Begin_Equip()
{
	bEquipped = true;
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HandSocket);
}

void AJG_Rifle::End_Equip()
{

	bEquipping =false;
}

void AJG_Rifle::Unequip()
{
	CheckFalse(bEquipped);
	CheckTrue(bEquipping);

	bEquipping = true;
	OwnerCharacter->PlayAnimMontage(UngrabMontage);
}

void AJG_Rifle::Begin_Unequip()
{
	bEquipped = false;
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
}

void AJG_Rifle::End_Unequip()
{
	bEquipping = false;
}

// Called when the game starts or when spawned
void AJG_Rifle::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner()); 

	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
}

// Called every frame
void AJG_Rifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

