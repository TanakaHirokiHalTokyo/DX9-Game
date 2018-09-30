#include "StatePlayer_KickLeft.h"
#include "../DefaultPlayer.h"
#include "StatePlayer_Idle.h"
#include "../../SkinMesh/sceneSkinMesh.h"
#include "../../../DInput/DirectInput.h"
#include "StatePlayer_KickCombo.h"
#include "../../../main.h"

constexpr float ANIMATION_TIME = 1.8f;
constexpr int	ANIMATION_COUNT = (int)GameFPS * ANIMATION_TIME / ANIMATION_SPEED_KICK;

void StatePlayer_KickLeft::UpdateKeyboard(DefaultPlayer * player)
{
	//Get SkinMeshModel 
	auto player_model = player->GetAnimModel();
	
	//UpdateCount
	count_++;

	player_model->SetAnimPlaySpeed(ANIMATION_SPEED_KICK);

	if (count_ > ANIMATION_COUNT)
	{
		if (combo_)
		{
			player_model->ChangeAnim(DefaultPlayer::KICK_COMBO,ANIMATION_SHIFTTIME);
			player->ChangeState(new StatePlayer_KickCombo());
			return;
		}
		else
		{
			player_model->ChangeAnim(DefaultPlayer::IDLE,ANIMATION_SHIFTTIME);
			player->ChangeState(new StatePlayer_Idle());
			return;
		}
	}
	else
	{
		if (GetKeyboardTrigger(KICK_KEY))
		{
			combo_ = true;
		}
	}
	return;
}
