
#include "Billboard.h"
#include "../../main.h"
#include "../../DirectXRenderer.h"
#include "../../Imgui/ImguiManager.h"
#include "../../Camera/Camera.h"

Billboard::Billboard()
{

}
Billboard::~Billboard()
{
}
void Billboard::Init()
{
	
}
void Billboard::Uninit()
{
	
}
void Billboard::Update()
{
	CAMERA_INFO camInfo = Camera::GetCameraInfo();

	this->SetView(camInfo.view);
}
void Billboard::BeginDraw()
{
}
void Billboard::Draw()
{
	
}

void Billboard::EndDraw()
{
}

void Billboard::SetView(D3DXMATRIX view)
{
	if (stand_)
	{
		D3DXMatrixIdentity(&this->mtxView_);
		this->mtxView_ = view;
		D3DXMatrixTranspose(&mtxView_, &mtxView_);

		mtxView_._14 = 0.0f;				//41�̕��s�ړ������������Ă���̂�0��
		mtxView_._24 = 0.0f;				//42�̕��s�ړ������������Ă���̂�0��
		mtxView_._34 = 0.0f;				//43�̕��s�ړ������������Ă���̂�0��

		mtxView_._12 = 0.0f;
		mtxView_._21 = 0.0f;

		mtxView_._23 = 0.0f;
		mtxView_._32 = 0.0f;
	}
	else
	{
		D3DXMatrixIdentity(&this->mtxView_);
		this->mtxView_ = view;
		D3DXMatrixTranspose(&mtxView_, &mtxView_);

		mtxView_._14 = 0.0f;				//41�̕��s�ړ������������Ă���̂�0��
		mtxView_._24 = 0.0f;				//42�̕��s�ړ������������Ă���̂�0��
		mtxView_._34 = 0.0f;				//43�̕��s�ړ������������Ă���̂�0��
	}
}

void BillboardManager::SetTexture(TextureManager::TextureList texture)
{
	TextureManager::TexInfo textureInfo = TextureManager::GetTexture(texture);
	pTexture_ = textureInfo.pTex;
	texSize_ = D3DXVECTOR2(textureInfo.width,textureInfo.height);
	texcoordSize_ = D3DXVECTOR2(textureInfo.texcoordX,textureInfo.texcoordY);
}

void Billboard::SetStand(bool stand)
{
	stand_ = stand;
}

void BillboardManager::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CRendererDirectX::GetDevice();


	VERTEX3D* Vertex;
	WORD* pIndex;

	//FVF�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX3D);


	//VertexBuffer�쐬
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX3D) * 4,				//���_�����̃T�C�Y
		D3DUSAGE_WRITEONLY,					//�������݂������Ȃ�
		FVF_VERTEX3D,						//FVF
		D3DPOOL_MANAGED,					//�f�o�C�X������ꂽ�Ƃ�����ɕ�������
		&this->pVertexBuffer_,					//���_�΂��ӂ����Ǘ����邽�߂̃A�h���X	�g��Ȃ��Ȃ�����Release
		NULL
	);

	//Vertex���o�^
	this->pVertexBuffer_->Lock(
		0,
		0,
		(void**)&Vertex,
		D3DLOCK_DISCARD						//Lock���Ă���͈͂��������ݐ�p�ŏ㏑��������
	);

	//���_�o�^
	Vertex[0].pos = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	Vertex[1].pos = D3DXVECTOR3(0.5f, 0.5f, 0.0f);
	Vertex[2].pos = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	Vertex[3].pos = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);

	//�@���o�^
	Vertex[0].vec =
		Vertex[1].vec =
		Vertex[2].vec =
		Vertex[3].vec = D3DXVECTOR3(0, 0, 1.0f);

	//���_�J���[�o�^
	Vertex[0].color =
		Vertex[1].color =
		Vertex[2].color =
		Vertex[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);

	this->pVertexBuffer_->Unlock();

	//Index�o�b�t�@�쐬
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * 6,					//�C���f�b�N�X�̃T�C�Y
		D3DUSAGE_WRITEONLY,					//�������݂������Ȃ�
		D3DFMT_INDEX16,						//(index�̌^ ��WORD(unsigned short)�̂���
		D3DPOOL_MANAGED,					//�f�o�C�X������ꂽ�Ƃ�����ɕ�������
		&this->pIndexBuffer_,					//�C���f�b�N�X�΂��ӂ����Ǘ����邽�߂̃A�h���X	�g��Ȃ��Ȃ�����Release
		NULL
	);

	//Index���o�^
	this->pIndexBuffer_->Lock(
		0,
		0,
		(void**)&pIndex,
		D3DLOCK_DISCARD
	);

	pIndex[0] = 0;
	pIndex[1] = 1;
	pIndex[2] = 2;
	pIndex[3] = 0;
	pIndex[4] = 2;
	pIndex[5] = 3;

	this->pIndexBuffer_->Unlock();
}

void BillboardManager::Uninit()
{
	if (this->pIndexBuffer_ != nullptr)
	{
		this->pIndexBuffer_->Release();
		this->pIndexBuffer_ = nullptr;
	}
	if (this->pVertexBuffer_ != nullptr)
	{
		this->pVertexBuffer_->Release();
		this->pVertexBuffer_ = nullptr;
	}
}

void BillboardManager::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CRendererDirectX::GetDevice();
	VERTEX3D* Vertex;

	//World�s��Ɋe�s����Z�b�g
	D3DXMATRIX mtxTrans, mtxScale, mtxWorld;

	D3DXMatrixTranslation(&mtxTrans, transform_.pos.x, transform_.pos.y, transform_.pos.z);
	D3DXMatrixScaling(&mtxScale, transform_.scale.x, transform_.scale.y, transform_.scale.z);


	mtxWorld = this->mtxView_;
	mtxWorld *= mtxScale;
	mtxWorld *= mtxTrans;


	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	//�A���t�@�e�X�g��TRUE�ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 40);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	//FVF�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX3D);

	//���C�g�I�t�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�e�N�X�`���Z�b�g
	pDevice->SetTexture(0, this->pTexture_);
	//�e��s��̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//Vertex���o�^
	this->pVertexBuffer_->Lock(
		0,
		0,
		(void**)&Vertex,
		D3DLOCK_DISCARD						//Lock���Ă���͈͂��������ݐ�p�ŏ㏑��������
	);

	float u0 = (float)this->texcoord_.x / this->texSize_.x;
	float v0 = (float)this->texcoord_.y / this->texSize_.y;
	float u1 = (float)(this->texcoord_.x + this->texcoordSize_.x) / this->texSize_.x;
	float v1 = (float)(this->texcoord_.y + this->texcoordSize_.y) / this->texSize_.y;

	Vertex[0].color =
		Vertex[1].color =
		Vertex[2].color =
		Vertex[3].color = this->color_;

	Vertex[0].texcoord = D3DXVECTOR2(u0, v0);
	Vertex[1].texcoord = D3DXVECTOR2(u1, v0);
	Vertex[2].texcoord = D3DXVECTOR2(u1, v1);
	Vertex[3].texcoord = D3DXVECTOR2(u0, v1);

	this->pVertexBuffer_->Unlock();



	// GPU��VertexBuffer���p�C�v���C���łȂ� - +
	pDevice->SetStreamSource(
		0,						//�p�C�v���C���̃Z�b�g�ԍ�
		this->pVertexBuffer_,		//�o�b�t�@
		0,						//�ǂ����珑�����ނ�
		sizeof(VERTEX3D)		//�ׂ̒��_�܂łǂꂭ�炢�̒���
	);

	// �f�o�C�X�ɃC���f�b�N�X�Z�b�g
	pDevice->SetIndices(
		this->pIndexBuffer_				//�o�b�t�@
	);

	//������o�b�t�@�g�������Ȃ��Ƃ��������Ƃ��o�b�t�@��NULL�ɂ���Ύg��Ȃ��Ȃ�B

	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,
		0,
		0,
		4,			//���_��
		0,
		2			//�v���~�e�B�u��
	);


	//�A���t�@�e�X�g��FALSE�ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//���C�g�I���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

void BillboardManager::SetPosition(float x, float y, float z)
{
	transform_.pos = D3DXVECTOR3(x,y,z);
}

void BillboardManager::SetPosition(D3DXVECTOR3 pos)
{
	transform_.pos = pos;
}

D3DXVECTOR3 BillboardManager::GetPosition()
{
	return transform_.pos;
}

void BillboardManager::SetRotation(float x, float y, float z)
{
	transform_.rotate = D3DXVECTOR3(x,y,z);
}

void BillboardManager::SetRotation(D3DXVECTOR3 rot)
{
	transform_.rotate = rot;
}

D3DXVECTOR3 BillboardManager::GetRotation()
{
	return transform_.rotate;
}

void BillboardManager::SetView(const D3DXMATRIX & view)
{
	mtxView_ = view;
}

D3DXMATRIX BillboardManager::GetView()
{
	return mtxView_;
}

void BillboardManager::SetScale(float x, float y, float z)
{
	transform_.scale = D3DXVECTOR3(x,y,z);
}

void BillboardManager::SetScale(D3DXVECTOR3 scale)
{
	transform_.scale = scale;
}

D3DXVECTOR3 BillboardManager::GetScale()
{
	return transform_.scale;
}
