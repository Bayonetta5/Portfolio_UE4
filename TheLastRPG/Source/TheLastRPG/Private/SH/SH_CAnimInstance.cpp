#include "SH/SH_CAnimInstance.h"
#include "SH/SH_Global.h"
#include "SH/SH_IRifle.h"
#include "SH/SH_CRifle.h"
#include "GameFramework/Character.h"

void USH_CAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void USH_CAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	CheckNull(OwnerCharacter); // NULLÀÌ¸é returnÇÔ

	Speed = OwnerCharacter->GetVelocity().Size2D();

	ISH_IRifle* rifle = Cast<ISH_IRifle>(OwnerCharacter);
	if (!!rifle)
	{
		bEquipped = rifle->GetRifle()->GetEquipped();

	}
}