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
	

}

GameScene::~GameScene()
{
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
