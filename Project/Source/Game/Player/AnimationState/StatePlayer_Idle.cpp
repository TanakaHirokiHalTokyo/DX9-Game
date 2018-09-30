#include "StatePlayer_Idle.h"
#include "../../../DInput/DirectInput.h"
#include "../DefaultPlayer.h"
#include "../../SkinMesh/sceneSkinMesh.h"
#include "StatePlayer_Walk_Forward.h"
#include "StatePlayer_Walk_Back.h"
#include "StatePlayer_KickRight.h"
#include "StatePlayer_PunchLeft.h"
#include "StatePlayer_Run.h"

void StatePlayer_Idle::UpdateKeyboard(DefaultPlayer* player)
{
	//Get SkinMesh
	auto player_model = player->GetAnimModel();

	//Get PlayerPosition
	const auto& player_position = player->GetPosition();

	player_model->SetAnimPlaySpeed(ANIMATION_SPEED_IDLE);

	//キック
	if (GetKeyboardTrigger(KICK_KEY))
	{
		player_model->ChangeAnim(DefaultPlayer::KICK_RIGHT,ANIMATION_SHIFTTIME);
		player->ChangeState(new StatePlayer_KickRight());
		return;
	}
	//パンチ
	if (GetKeyboardTrigger(PUNCH_KEY))
	{
		player_model->ChangeAnim(DefaultPlayer::PUNCH_LEFT,ANIMATION_SHIFTTIME);
		player->ChangeState(new StatePlayer_PunchLeft());
		return;
	}

	//		前歩き
	if (GetKeyboardTrigger(WALK_FRONT_KEY))
	{
		//　　走り
		if (GetKeyboardPress(SPRINT_KEY))
		{
			player_model->ChangeAnim(DefaultPlayer::RUN, ANIMATION_SHIFTTIME);
			player->ChangeState(new StatePlayer_Run());
			return;
		}

		player_model->ChangeAnim(DefaultPlayer::WALK_FORWARD,ANIMATION_SHIFTTIME);
		player->ChangeState(new StatePlayer_Walk_Forward());
		return;
	}
	//		後ろ歩き
	if (GetKeyboardTrigger(WALK_BACK_KEY))
	{
		player_model->ChangeAnim(DefaultPlayer::WALK_BACK,ANIMATION_SHIFTTIME);
		player->ChangeState(new StatePlayer_Walk_Back());
		return;
	}


	return;
}
