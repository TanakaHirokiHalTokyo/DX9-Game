//#include "StayEnemy.h"
//#include  "../XModel/XModel.h"
//#include "../../Vector3/Vector3.h"
//#include "../../main.h"
//#include "../../Camera/Camera.h"
//#include "../GameManager/GameManager.h"
//#include "../../Light/Light.h"
//#include "../Shader/ShaderManager.h"
//#include "../../Texture/Texture.h"
//#include "../Shader/ToonShader.h"
//#include "../Shader/OutlineShader.h"
//#include "../../DirectXRenderer.h"
//#include "../Shader/ShadowMapShader.h"
//#include "../Shader/ShadowVolume.h"
//
//StayEnemy::StayEnemy()
//{
//	model_ = Object::Create<XModel>();
//	model_->SetModelType(XModel::MODEL_HIGE);
//	model_->SetUseShader(true);
//
//	LPDIRECT3DDEVICE9 pDevice = CRendererDirectX::GetDevice();
//	D3DXCreateSprite(pDevice,&shadow_);
//	
//}
//
//StayEnemy::~StayEnemy()
//{
//	if (vector_ != NULL)
//	{
//		delete vector_;
//		vector_ = NULL;
//	}
//
//	SAFE_RELEASE(shadow_);
//	ShadowMapShader::Uninit();
//}
//
//void StayEnemy::Init()
//{
//	model_->SetPosition(3,3,0);
//	model_->SetRotation(0,0,0);
//	model_->SetScale(0.1f, 0.1f, 0.1f);
//
//	model_->SetUseShader(true);
//}
//
//void StayEnemy::Uninit()
//{
//	
//}
//
//void StayEnemy::Update()
//{
//	const auto& rotate = model_->GetRotate();
//	model_->SetRotation(rotate.x,rotate.y + 0.1f,rotate.z);
//}
//
//void StayEnemy::BeginDraw()
//{
//	LPD3DXEFFECT effect;
//
//	const auto& world = model_->GetWorld();
//	ShadowMapShader::SetInfo(world);
//	effect = ShadowMapShader::GetEffect();
//	effect->SetTechnique("Shadow");
//	model_->Draw(effect,0);
//}
//
//void StayEnemy::Draw()
//{
//	if (model_ != NULL)
//	{
//		//World座標
//		const auto& world = model_->GetWorld();
//		LPD3DXEFFECT effect;
//
//		ShadowMapShader::SetInfo(world);		//シャドウマップ　情報セット
//		effect = ShadowMapShader::GetEffect();	//シャドウマップ　エフェクト取得
//		effect->SetTechnique("Scene");			//シャドウマップ　シーン描画
//		model_->Draw(effect,0);
//
//		OutlineShader::SetInfo(world);			//アウトライン　情報セット
//		effect = OutlineShader::GetEffect();	//アウトライン　エフェクト取得
//		effect->SetTechnique("Tech");			//アウトライン描画
//		model_->Draw(effect, 0);
//
//		ToonShader::SetInfo(world);				//トゥーン情報セット
//		effect = ToonShader::GetEffect();		//トゥーン　エフェクト取得
//		effect->SetTechnique("ToonPaint");		//Toon(Outline と　トゥーンシェーダー)
//		model_->Draw(effect,0);
//	}
//}
//
//void StayEnemy::EndDraw()
//{
//	
//}
