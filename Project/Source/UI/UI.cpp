#include "UI.h"
#include "../main.h"
#include "../Imgui/ImguiManager.h"
#include "UIState\UIState_Move.h"
#include "UIState\UIState_Scale.h"

UI::UI(TextureManager::TextureList type)
{
	//Textureê∂ê¨
	texture_ = Object::Create<Texture>(type);
}

UI::~UI()
{
	if (stateMove_ != nullptr)
	{
		delete stateMove_;
		stateMove_ = nullptr;
	}
	if (stateScale_ != nullptr)
	{
		delete stateScale_;
		stateScale_ = nullptr;
	}
}

void UI::Init()
{
	SetPosition(0,0,0);
	SetScale(1.0f,1.0f,1.0f);
	texture_->SetPosition(GetPosition());
	texture_->SetDrawSize(GetScale().x,GetScale().y);
}

void UI::Uninit()
{
}

void UI::Update()
{
	if (move_)
	{
		if (updateMove_)
		{
			if (stateMove_ != nullptr) { stateMove_->Update(this); }
		}
	}
	if (scale_)
	{
		if (updateScale_)
		{
			if (stateScale_ != nullptr) { stateScale_->Update(this); }
		}
	}
	texture_->SetPosition(GetPosition());
	texture_->SetDrawSize(GetScale().x, GetScale().y);
}

void UI::BeginDraw()
{
}

void UI::Draw()
{
	ImGui::Begin("UI Position");
	ImGui::Text("UI Pos: %f %f %f",GetPosition().x, GetPosition().y, GetPosition().z);
	ImGui::End();
}

void UI::EndDraw()
{
}

void UI::MoveTexture(float afterSpawnCount, float moveTime, float update_x, float update_y)
{
	if (stateMove_ == nullptr)
	{
		stateMove_ = new UIState_Move();
	}
	this->move_ = true;
	this->countMove_ = afterSpawnCount;
	this->moveTime_ = moveTime;
	this->updatePos_.x = update_x;
	this->updatePos_.y = update_y;
}

void UI::MoveTexture(float afterSpawnCount, float moveTime, D3DXVECTOR3 update_pos)
{
	if (stateMove_ == nullptr)
	{
		stateMove_ = new UIState_Move();
	}
	this->move_ = true;
	this->countMove_ = afterSpawnCount;
	this->moveTime_ = moveTime;
	this->updatePos_.x = update_pos.x;
	this->updatePos_.y = update_pos.y;
}

void UI::MoveTexture(float afterSpawnCount, float moveTime, D3DXVECTOR2 update_pos)
{
	if (stateMove_ == nullptr)
	{
		stateMove_ = new UIState_Move();
	}
	this->move_ = true;
	this->countMove_ = afterSpawnCount;
	this->moveTime_ = moveTime;
	this->updatePos_.x = update_pos.x;
	this->updatePos_.y = update_pos.y;
}

void UI::ScalingTexture(float afterSpawnCount, float moveTime, float update_x, float update_y)
{
	if (stateScale_ == nullptr)
	{
		stateScale_ = new UIState_Scale();
	}
	this->scale_ = true;
	this->countScale_ = afterSpawnCount;
	this->scaleTime_ = moveTime;
	this->updateSize_.x = update_x;
	this->updateSize_.y = update_y;
}

void UI::ScalingTexture(float afterSpawnCount, float moveTime, D3DXVECTOR3 update_scale)
{
	if (stateScale_ == nullptr)
	{
		stateScale_ = new UIState_Scale();
	}
	this->scale_ = true;
	this->countScale_ = afterSpawnCount;
	this->scaleTime_ = moveTime;
	this->updateSize_.x = update_scale.x;
	this->updateSize_.y = update_scale.y;
}

void UI::ScalingTexture(float afterSpawnCount, float moveTime, D3DXVECTOR2 update_scale)
{
	if (stateScale_ == nullptr)
	{
		stateScale_ = new UIState_Scale();
	}
	this->scale_ = true;
	this->countScale_ = afterSpawnCount;
	this->scaleTime_ = moveTime;
	this->updateSize_.x = update_scale.x;
	this->updateSize_.y = update_scale.y;
}

Texture * UI::GetTexture()
{
	return texture_;
}

float UI::GetCountMove()
{
	return countMove_;
}

float UI::GetMoveTime()
{
	return moveTime_;
}

D3DXVECTOR2 UI::GetAfterPos()
{
	return updatePos_;
}

void UI::SetUpdateMove(bool flag)
{
	updateMove_ = flag;
}

bool UI::GetUpdateMove()
{
	return updateMove_;
}

float UI::GetCountScale()
{
	return countScale_;
}

float UI::GetScaleTime()
{
	return scaleTime_;
}

D3DXVECTOR2 UI::GetAfterScale()
{
	return updateSize_;
}

void UI::SetUpdateScale(bool flag)
{
	updateScale_ = flag;
}

bool UI::GetUpdateScale()
{
	return updateScale_;
}

