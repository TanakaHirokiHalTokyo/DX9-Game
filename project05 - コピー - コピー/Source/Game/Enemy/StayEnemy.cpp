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
//		//World���W
//		const auto& world = model_->GetWorld();
//		LPD3DXEFFECT effect;
//
//		ShadowMapShader::SetInfo(world);		//�V���h�E�}�b�v�@���Z�b�g
//		effect = ShadowMapShader::GetEffect();	//�V���h�E�}�b�v�@�G�t�F�N�g�擾
//		effect->SetTechnique("Scene");			//�V���h�E�}�b�v�@�V�[���`��
//		model_->Draw(effect,0);
//
//		OutlineShader::SetInfo(world);			//�A�E�g���C���@���Z�b�g
//		effect = OutlineShader::GetEffect();	//�A�E�g���C���@�G�t�F�N�g�擾
//		effect->SetTechnique("Tech");			//�A�E�g���C���`��
//		model_->Draw(effect, 0);
//
//		ToonShader::SetInfo(world);				//�g�D�[�����Z�b�g
//		effect = ToonShader::GetEffect();		//�g�D�[���@�G�t�F�N�g�擾
//		effect->SetTechnique("ToonPaint");		//Toon(Outline �Ɓ@�g�D�[���V�F�[�_�[)
//		model_->Draw(effect,0);
//	}
//}
//
//void StayEnemy::EndDraw()
//{
//	
//}
