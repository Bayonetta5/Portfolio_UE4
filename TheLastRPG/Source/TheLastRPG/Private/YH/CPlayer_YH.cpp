#include "YH/CPlayer_YH.h"
#include "YH/Weapon/YH_CRifle.h"
#include "YH/YH_CAnimInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "YH/Global_YH.h"

// Sets default values
ACPlayer_YH::ACPlayer_YH()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	PrimaryActorTick.bCanEverTick = true;

	//SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	//SpringArm->SetupAttachment(GetCapsuleComponent());

	//Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	//Camera->SetupAttachment(SpringArm);


	CHelpers_YH::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetCapsuleComponent());
	CHelpers_YH::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);


	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	//SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'
	USkeletalMesh* mesh;
	CHelpers_YH::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/YongHwan/Meshes/Character/YH_SK_Mannequin.YH_SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	TSubclassOf<UAnimInstance> animInstance;
	//블루프린트 클래스가 아니라 애니메이션 블루프린트를 가져와야돼! 와 이거 에러도 안뜨네
	//AnimBlueprint'/Game/YongHwan/BP/YH_ABP_CPlayer.YH_ABP_CPlayer_C'
	//Blueprint'/Game/YongHwan/BP/YH_BP_CAnimInstance.YH_BP_CAnimInstance_C' 이게 아니라
	//AnimBlueprint'/Game/YongHwan/BP/YH_ABP_CPlayer2.YH_ABP_CPlayer2'
	CHelpers_YH::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/YongHwan/BP/Character/YH_BP_AnimBlueprint2.YH_BP_AnimBlueprint2_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);

	SpringArm->SetRelativeLocation(FVector(0, 0, 60));
	SpringArm->TargetArmLength = 200.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SocketOffset = FVector(0, 60, 0);
}

// Called when the game starts or when spawned
void ACPlayer_YH::BeginPlay()
{
	Super::BeginPlay();
	UMaterialInstanceConstant* bodyMaterial;
	//MaterialInstanceConstant'/Game/YongHwan/Materials/YH_M_UE4Man_Body_Inst.YH_M_UE4Man_Body_Inst'
	//MaterialInstanceConstant'/Game/YongHwan/Materials/YH_M_UE4Man_ChestLogo_Inst.YH_M_UE4Man_ChestLogo_Inst'
	CHelpers_YH::GetAssetDynamic<UMaterialInstanceConstant>(&bodyMaterial, "MaterialInstanceConstant'/Game/YongHwan/Materials/YH_M_UE4Man_Body_Inst.YH_M_UE4Man_Body_Inst'");

	UMaterialInstanceConstant* logoMaterial;
	CHelpers_YH::GetAssetDynamic<UMaterialInstanceConstant>(&logoMaterial, "MaterialInstanceConstant'/Game/YongHwan/Materials/YH_M_UE4Man_ChestLogo_Inst.YH_M_UE4Man_ChestLogo_Inst'");

	BodyMaterial = UMaterialInstanceDynamic::Create(bodyMaterial, this);
	LogoMaterial = UMaterialInstanceDynamic::Create(logoMaterial, this);

	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);
	//등장은되는데 부착이 아직 없어
	Rifle = AYH_CRifle::Spawn(GetWorld(), this);
}

// Called every frame
void ACPlayer_YH::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPlayer_YH::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer_YH::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer_YH::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ACPlayer_YH::OnHorizontalLook);
	PlayerInputComponent->BindAxis("Lookup", this, &ACPlayer_YH::OnVerticalLook);

	PlayerInputComponent->BindAction("Running", EInputEvent::IE_Pressed, this, &ACPlayer_YH::OnRunning);
	PlayerInputComponent->BindAction("Running", EInputEvent::IE_Released, this, &ACPlayer_YH::OffRunning);

	PlayerInputComponent->BindAction("Rifle", EInputEvent::IE_Pressed, this, &ACPlayer_YH::OnRifle);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &ACPlayer_YH::OnAim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &ACPlayer_YH::OffAim);
}

void ACPlayer_YH::OnMoveForward(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void ACPlayer_YH::OnMoveRight(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void ACPlayer_YH::OnHorizontalLook(float Axis)
{
	AddControllerYawInput(Axis);
}

void ACPlayer_YH::OnVerticalLook(float Axis)
{
	AddControllerPitchInput(Axis);
}

void ACPlayer_YH::OnRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 900;
	
	YH_CLog::Log(GetCharacterMovement()->MaxWalkSpeed);
}

void ACPlayer_YH::OffRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 400;
	YH_CLog::Log(GetCharacterMovement()->MaxWalkSpeed);
}

void ACPlayer_YH::OnRifle()
{
	if (Rifle->GetEquipped())
	{
		Rifle->Unequip();

		return;
	}

	Rifle->Equip();
}

void ACPlayer_YH::OnAim()
{
	CheckFalse(Rifle->GetEquipped());
	CheckTrue(Rifle->GetEquipping());

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	SpringArm->TargetArmLength = 100;
	SpringArm->SocketOffset = FVector(0, 30, 10);
	//Camera->FieldOfView = 40; 커브적용한다.
	OnZoomIn();
	Rifle->Begin_Aiming();
}

void ACPlayer_YH::OffAim()
{
	CheckFalse(Rifle->GetEquipped());
	CheckTrue(Rifle->GetEquipping());

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	SpringArm->TargetArmLength = 200;
	SpringArm->SocketOffset = FVector(0, 60, 0);
	//Camera->FieldOfView = 90;
	OnZoomOut();
	Rifle->End_Aiming();
}

void ACPlayer_YH::ChangeColor(FLinearColor InColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InColor);
}

