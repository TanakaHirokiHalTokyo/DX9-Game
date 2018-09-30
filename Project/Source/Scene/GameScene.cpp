#include "GameScene.h"
#include "../Game/Object.h"
#include "../Game/Player/PlayerCamera.h"
#include "../Light/Light.h"
#include "../Game/Enemy/StayEnemy.h"
#include "../Game/XModel/XModel.h"
#include "../Game/Player/Player.h"
#include "../Game/SkinMesh/sceneSkinMesh.h"
#include "../Game/GameManager/GameManager.h"
#include "../Game/MeshField/MeshField.h"	
#include "../Game/Shader/ShadowMapShader.h"
#include "../DirectXRenderer.h"
#include "../Game/Player/DefaultPlayer.h"
#include "../Game/Player/AnimPlayer.h"
#include "../Game/Core/Core.h"
#include "../Game/Portal/Portal.h"
#include "../UI/UI.h"
#include "Fade.h"

GameScene::GameScene()
{
	DirectionalLight* light = Object::Create<DirectionalLight>();
	light->SetPause(true);
	light->SetVector(D3DXVECTOR3(0.0f, -1.0f, 1.0f));
	GameManager::SetDirectionalLight(light);
	XModel* dome = Object::Create<XModel>();
	dome->SetPause(true);
	dome->SetModelType(XModel::MODEL_DOME303);
	dome->SetScale(10.0f, 10.0f, 10.0f);
	field_ = Object::Create<MeshField>();
	player_ = Object::Create<DefaultPlayer>();
	core_ = Object::Create<Core>();
	Portal* portal =  Object::Create<Portal>();
	portal->SetPosition(10.0f,0.0f,0.0f);

	UI* ui = Object::Create<UI>(TextureManager::Tex_Fade);
	ui->SetScale(100.0f,100.0f,100.0f);
	ui->SetPosition((float)ScreenWidth / 2.0f, (float)ScreenHeight / 2.0f,0.0f);
	ui->MoveTexture(1.0f,30.0f,0,0);
	ui->ScalingTexture(1.0f,30.0f,300.0f,300.0f);
}

GameScene::~GameScene()
{
	ShadowMapShader::Uninit();
	Object::ReleaseAll();
}

void GameScene::Init()
{
	
}

void GameScene::Uninit()
{
	
}

void GameScene::Update()
{
	Object::UpdateAll();
}

void GameScene::BeginDraw()
{
	ShadowMapShader::CreateShadowMapTexture();
	ShadowMapShader::CreateShadowMap();
	CRendererDirectX::Clear();
	Object::BeginDrawAll();
}

void GameScene::Draw()
{
	Object::DrawAll();
}

void GameScene::EndDraw()
{
	CRendererDirectX::ClearZ();
	Object::EndDrawAll();
}
