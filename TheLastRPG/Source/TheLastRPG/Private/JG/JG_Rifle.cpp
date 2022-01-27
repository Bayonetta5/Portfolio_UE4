// Fill out your copyright notice in the Description page of Project Settings.


#include "JG/JG_Rifle.h"
#include "JG/JG_Global.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AJG_Rifle::AJG_Rifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	JG_Helpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh");

	//USkeletalMesh* mesh;
	//JG_Helpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Lectures/Weapons/Meshes/AR4/SK_AR4.SK_AR4'");
	//Mesh->SetSkeletalMesh(mesh);
}

// Called when the game starts or when spawned
void AJG_Rifle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJG_Rifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

