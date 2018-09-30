#include "StatePlayer_KickCombo.h"
#include "StatePlayer_Idle.h"
#include "../DefaultPlayer.h"
#include "../../../DInput/DirectInput.h"
#include "../../SkinMesh/sceneSkinMesh.h"
#include "../../../main.h"

constexpr float ANIMATION_TIME = 1.8f;
constexpr int	ANIMATION_COUNT = (int)GameFPS * ANIMATION_TIME / ANIMATION_SPEED_KICK;

void StatePlayer_KickCombo::UpdateKeyboard(DefaultPlayer * player)
{
	//Get SkinMeshModel
	auto player_model = player->GetAnimModel();

	//Update Count 
	count_++;

	player_model->SetAnimPlaySpeed(ANIMATION_SPEED_KICK);

	if (count_ > ANIMATION_COUNT)
	{
		player_model->ChangeAnim(DefaultPlayer::IDLE,ANIMATION_SHIFTTIME);
		player->ChangeState(new StatePlayer_Idle());
		return;
	}
}