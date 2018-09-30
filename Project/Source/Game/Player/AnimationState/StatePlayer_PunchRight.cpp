#include "StatePlayer_PunchRight.h"
#include "StatePlayer_Idle.h"
#include "../DefaultPlayer.h"
#include "../../SkinMesh/sceneSkinMesh.h"
#include "../../../DInput/DirectInput.h"
#include "../../../main.h"
#include "StatePlayer_PunchCombo.h"

constexpr float ANIMATION_SPEED = 2.0f;
constexpr float ANIMATION_TIME = 1.5f;
constexpr int ANIMATION_COUNT = (int)ANIMATION_TIME * GameFPS / ANIMATION_SPEED;

void StatePlayer_PunchRight::UpdateKeyboard(DefaultPlayer * player)
{
	//Get SkinMeshModel
	auto player_model = player->GetAnimModel();

	//UpdateCount
	count_++;

	player_model->SetAnimPlaySpeed(ANIMATION_SPEED);

	if (GetKeyboardTrigger(PUNCH_KEY))
	{
		combo_ = true;
	}

	if (count_ > ANIMATION_COUNT)
	{
		if (combo_)
		{
			player_model->ChangeAnim(DefaultPlayer::PUNCH_COMBO,ANIMATION_SHIFTTIME);
			player->ChangeState(new StatePlayer_PunchCombo());
			return;
		}
		player_model->ChangeAnim(DefaultPlayer::IDLE, ANIMATION_SHIFTTIME);
		player->ChangeState(new StatePlayer_Idle());
		return;
	}
}
