
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

		mtxView_._14 = 0.0f;				//41の平行移動成分が入っているので0に
		mtxView_._24 = 0.0f;				//42の平行移動成分が入っているので0に
		mtxView_._34 = 0.0f;				//43の平行移動成分が入っているので0に

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

		mtxView_._14 = 0.0f;				//41の平行移動成分が入っているので0に
		mtxView_._24 = 0.0f;				//42の平行移動成分が入っているので0に
		mtxView_._34 = 0.0f;				//43の平行移動成分が入っているので0に
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

	//FVFの設定
	pDevice->SetFVF(FVF_VERTEX3D);


	//VertexBuffer作成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX3D) * 4,				//頂点数分のサイズ
		D3DUSAGE_WRITEONLY,					//書き込みしかしない
		FVF_VERTEX3D,						//FVF
		D3DPOOL_MANAGED,					//デバイスが失われたとき勝手に復旧する
		&this->pVertexBuffer_,					//頂点ばっふぁを管理するためのアドレス	使わなくなったらRelease
		NULL
	);

	//Vertex情報登録
	this->pVertexBuffer_->Lock(
		0,
		0,
		(void**)&Vertex,
		D3DLOCK_DISCARD						//Lockしている範囲を書き込み専用で上書きをする
	);

	//頂点登録
	Vertex[0].pos = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	Vertex[1].pos = D3DXVECTOR3(0.5f, 0.5f, 0.0f);
	Vertex[2].pos = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	Vertex[3].pos = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);

	//法線登録
	Vertex[0].vec =
		Vertex[1].vec =
		Vertex[2].vec =
		Vertex[3].vec = D3DXVECTOR3(0, 0, 1.0f);

	//頂点カラー登録
	Vertex[0].color =
		Vertex[1].color =
		Vertex[2].color =
		Vertex[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);

	this->pVertexBuffer_->Unlock();

	//Indexバッファ作成
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * 6,					//インデックスのサイズ
		D3DUSAGE_WRITEONLY,					//書き込みしかしない
		D3DFMT_INDEX16,						//(indexの型 今WORD(unsigned short)のため
		D3DPOOL_MANAGED,					//デバイスが失われたとき勝手に復旧する
		&this->pIndexBuffer_,					//インデックスばっふぁを管理するためのアドレス	使わなくなったらRelease
		NULL
	);

	//Index情報登録
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

	//World行列に各行列をセット
	D3DXMATRIX mtxTrans, mtxScale, mtxWorld;

	D3DXMatrixTranslation(&mtxTrans, transform_.pos.x, transform_.pos.y, transform_.pos.z);
	D3DXMatrixScaling(&mtxScale, transform_.scale.x, transform_.scale.y, transform_.scale.z);


	mtxWorld = this->mtxView_;
	mtxWorld *= mtxScale;
	mtxWorld *= mtxTrans;


	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	//アルファテストをTRUEにする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 40);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	//FVFの設定
	pDevice->SetFVF(FVF_VERTEX3D);

	//ライトオフにする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//テクスチャセット
	pDevice->SetTexture(0, this->pTexture_);
	//各種行列の設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//Vertex情報登録
	this->pVertexBuffer_->Lock(
		0,
		0,
		(void**)&Vertex,
		D3DLOCK_DISCARD						//Lockしている範囲を書き込み専用で上書きをする
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



	// GPUとVertexBufferをパイプラインでつなぐ - +
	pDevice->SetStreamSource(
		0,						//パイプラインのセット番号
		this->pVertexBuffer_,		//バッファ
		0,						//どこから書き込むか
		sizeof(VERTEX3D)		//隣の頂点までどれくらいの長さ
	);

	// デバイスにインデックスセット
	pDevice->SetIndices(
		this->pIndexBuffer_				//バッファ
	);

	//次からバッファ使いたくないときが来たときバッファをNULLにすれば使わなくなる。

	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,
		0,
		0,
		4,			//頂点数
		0,
		2			//プリミティブ数
	);


	//アルファテストをFALSEにする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//ライトオンにする
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
