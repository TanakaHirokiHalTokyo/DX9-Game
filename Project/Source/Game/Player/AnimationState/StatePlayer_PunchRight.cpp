#include "StatePlayer_PunchRight.h"
#include "StatePlayer_Idle.h"
#include "../DefaultPlayer.h"
#include "../../SkinMesh/sceneSkinMesh.h"
#include "../../../DInput/DirectInput.h"
#include "../../../main.h"

constexpr float ANIMATION_TIME = 0.5f;
constexpr int ANIMATION_COUNT = (int)ANIMATION_TIME * GameFPS;

void StatePlayer_PunchRight::UpdateKeyboard(DefaultPlayer * player)
{
	//Get SkinMeshModel
	auto player_model = player->GetAnimModel();

	//UpdateCount
	count_++;

	if (GetKeyboardTrigger(PUNCH_KEY))
	{
		combo_ = true;
	}

	if (count_ > ANIMATION_COUNT)
	{
		if (combo_)
		{
			player_model->ChangeAnim(DefaultPlayer::PUNCH_COMBO,ANIMATION_SHIFTTIME);
			player->ChangeState();
			return;
		}
		player_model->ChangeAnim(DefaultPlayer::IDLE, ANIMATION_SHIFTTIME);
		player->ChangeState(new StatePlayer_Idle());
		return;
	}
}
