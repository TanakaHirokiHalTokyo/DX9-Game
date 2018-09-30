#include "GameCamera.h"
#include "../Imgui/ImguiManager.h"
#include "../Game/XModel/XModel.h"
#include "../Vector3/Vector3.h"

void GameCamera::Init()
{
	vector_->SetFront(0.0f, 0.0f, 1.0f);
	vector_->SetUp(0.0f, 1.0f, 0.0f);
	vector_->SetRight(-1.0f, 0.0f, 0.0f);
	at_ = D3DXVECTOR3(0.0f,0.0f,0.0f);

	SetPosition(0, 4, -5.0f);

	this->SetProjection();
}

void GameCamera::Uninit()
{
	
}
	

void GameCamera::Update()
{
	this->SetView();
	this->SetMainCameraInfo(this->transform_.pos, this->at_, vector_->GetUp(), this->mtxView_, this->mtxProj_);

	ImGui::Begin("Debug Camera");
	ImGui::DragFloat("Pos X", &transform_.pos.x, 0.01f);
	ImGui::DragFloat("Pos Y", &transform_.pos.y, 0.01f);
	ImGui::DragFloat("Pos Z", &transform_.pos.z, 0.01f);
	ImGui::DragFloat("At X", &at_.x, -300.0f, 300.0f, 0.01f);
	ImGui::DragFloat("At Y", &at_.y, -300.0f, 300.0f, 0.01f);
	ImGui::DragFloat("At Z", &at_.z, -300.0f, 300.0f, 0.01f);
	ImGui::End();
}

void GameCamera::BeginDraw()
{
}

void GameCamera::Draw()
{
}

void GameCamera::EndDraw()
{
}

void GameCamera::SetModel1(XModel * model)
{
	model1_ = model;
}

void GameCamera::SetModel2(XModel * model)
{
	model2_ = model;
}
