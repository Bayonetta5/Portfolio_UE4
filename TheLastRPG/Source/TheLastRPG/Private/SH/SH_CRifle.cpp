#include "SH/SH_CRifle.h"
#include "SH/SH_Global.h"
#include "SH/SH_IRifle.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"
#include "Engine/StaticMeshActor.h"
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

void ASH_CRifle::Begin_Aiming()
{
	bAiming = true;
}
void ASH_CRifle::End_Aiming()
{
	bAiming = false;
}

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
	CheckFalse(bAiming); // Aiming 상태가 아니면 return

	ISH_IRifle* rifle = Cast<ISH_IRifle>(OwnerCharacter);
	CheckNull(rifle); // Rifle이 ISH_IRifle 상속하고 있지 않으면 return

	FVector start, end, direction;
	rifle->GetLocationAndDirection(start, end, direction);

	//DrawDebugLine(GetWorld(), start, end, FColor::Green, false, 3.0f);

	FCollisionQueryParams params;
	params.AddIgnoredActor(this); // rifle
	params.AddIgnoredActor(OwnerCharacter); // character

	FHitResult hitResult;
	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_WorldDynamic, params))
	{
		AStaticMeshActor* staticMeshActor = Cast<AStaticMeshActor>(hitResult.GetActor()); // 부딪힌 액터를 캐스팅해봄
		if (!!staticMeshActor) // 성공적으로 캐스팅된다면
		{
			UStaticMeshComponent* meshComponent = Cast<UStaticMeshComponent>(staticMeshActor->GetRootComponent());
			if (!!meshComponent)
			{
				if (meshComponent->BodyInstance.bSimulatePhysics) // 충돌처리가 켜져있다면
				{
					rifle->OnFocus();
					return;
				}
			}
		}
	}

	rifle->OffFocus();
}

void ASH_CRifle::Begin_Fire()
{
	CheckFalse(bEquipped); // 장착중이지 않으면 return
	CheckTrue(bEquipping); // 장착중이면 return
	CheckFalse(bAiming); // 에임중이지 않으면 return
	CheckTrue(bFiring); // 발사중이면 return

	Firing();
}

void ASH_CRifle::Firing()
{
	// 부모* 변수 = 자식 
	ISH_IRifle* rifle = Cast<ISH_IRifle>(OwnerCharacter); // 처음보는 문법.
	CheckNull(rifle); // 라이플이 있다면

	FVector start, end, direction;
	rifle->GetLocationAndDirection(start, end, direction);

	FCollisionQueryParams params;
	params.AddIgnoredActor(this); // rifle
	params.AddIgnoredActor(OwnerCharacter); // character

	FHitResult hitResult;
	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_WorldDynamic, params))
	{
		AStaticMeshActor* staticMeshActor = Cast<AStaticMeshActor>(hitResult.GetActor()); // 부딪힌 액터를 캐스팅해봄
		if (!!staticMeshActor) // 성공적으로 캐스팅된다면
		{
			UStaticMeshComponent* meshComponent = Cast<UStaticMeshComponent>(staticMeshActor->GetRootComponent());
			if (!!meshComponent)
			{
				if (meshComponent->BodyInstance.bSimulatePhysics) // 충돌처리가 켜져있다면
				{
					direction = staticMeshActor->GetActorLocation() - OwnerCharacter->GetActorLocation(); // 방향벡터
					direction.Normalize();
					
					meshComponent->AddImpulseAtLocation(direction* meshComponent->GetMass() * 100, OwnerCharacter->GetActorLocation());
					SH_CLog::Log("hit!");
					return;
				}
			}
		}
	}
}

void ASH_CRifle::End_Fire()
{

}
