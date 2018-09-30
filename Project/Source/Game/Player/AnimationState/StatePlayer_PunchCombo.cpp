#include "StatePlayer_PunchCombo.h"
#include "StatePlayer_Idle.h"
#include "../DefaultPlayer.h"
#include "../../SkinMesh/sceneSkinMesh.h"
#include "../../../DInput/DirectInput.h"
#include "../../../main.h"

constexpr float ANIMATION_SPEED = 2.0f;
constexpr float ANIMATION_TIME = 1.5f;
constexpr int ANIMATION_COUNT = (int)ANIMATION_TIME * GameFPS / ANIMATION_SPEED;

void StatePlayer_PunchCombo::UpdateKeyboard(DefaultPlayer * player)
{
	//Get SkinMeshModel
	auto player_model = player->GetAnimModel();

	player_model->SetAnimPlaySpeed(ANIMATION_SPEED);

	//UpdateCount
	count_++;

	if (count_ > ANIMATION_COUNT)
	{
		player_model->ChangeAnim(DefaultPlayer::IDLE,ANIMATION_SHIFTTIME);
		player->ChangeState(new StatePlayer_Idle());
		return;
	}
}
