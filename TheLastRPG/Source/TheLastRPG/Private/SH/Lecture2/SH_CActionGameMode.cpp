#include "SH/Lecture2/SH_CActionGameMode.h"
#include "SH/SH_Global.h"


ASH_CActionGameMode::ASH_CActionGameMode()
{
	SH_CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/SungHoon/Lectures/ActionRPG/Character/SH_BP_CActionPlayer.SH_BP_CActionPlayer_C'");
}