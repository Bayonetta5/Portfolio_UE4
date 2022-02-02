#include "SH/Lecture2/SH_CActionAnimInstance.h"
#include "SH/SH_Global.h"
#include "GameFramework/Character.h"


void USH_CActionAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void USH_CActionAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(character);

	Speed = character->GetVelocity().Size2D();
	Direction = CalculateDirection(character->GetVelocity(), character->GetControlRotation());
}
