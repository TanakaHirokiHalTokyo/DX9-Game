#pragma once

#include "../Object.h"
#include "../../Texture/Texture.h"

class Billboard : public Object
{
public:
	
	enum Billboard_Tex
	{
		BilTex_Turret,
		BilTex_Difficulity,
		BilTex_Max
	};


public:
	Billboard();
	virtual ~Billboard();

	void Init()override;
	void Uninit()override;
	void Update()override;
	void BeginDraw()override;
	void Draw()override;
	void EndDraw()override;
	void SetView(D3DXMATRIX view);
	void SetStand(bool stand);

private:
	D3DXMATRIX mtxView_ = {};
	bool stand_ = false;

};

class BillboardManager
{
public :
	struct VERTEX3D
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 vec;
		D3DCOLOR color;
		D3DXVECTOR2 texcoord;
	};
	struct Transform
	{
		D3DXVECTOR3 pos = D3DXVECTOR3(0, 0, 0);
		D3DXVECTOR3 rotate = D3DXVECTOR3(0, 0, 0);
		D3DXVECTOR3 scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	};
	void Init();
	void Uninit();
	void Draw();
	void SetPosition(float x,float y,float z);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition();
	void SetRotation(float x,float y,float z);
	void SetRotation(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetRotation();
	void SetView(const D3DXMATRIX& view);
	D3DXMATRIX GetView();
	void SetScale(float x,float y,float z);
	void SetScale(D3DXVECTOR3 scale);
	D3DXVECTOR3 GetScale();
	void SetTexture(TextureManager::TextureList texture);
	void SetColor(D3DCOLOR color) { this->color_ = color; }
	void SetTexcoord(int tcx, int tcy) { this->texcoord_.x = (float)tcx; this->texcoord_.y = (float)tcy; }
	void SetTexcoordSize(float tcw, float tch) { this->texcoordSize_.x = tcw; this->texcoordSize_.y = tch; }
private:

	LPDIRECT3DTEXTURE9 pTexture_ = NULL;
	D3DXMATRIX mtxView_ = {};
	Transform transform_ = {};
	D3DCOLOR color_ = D3DCOLOR_RGBA(255,255,255,255);
	D3DXVECTOR2 texcoord_ = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 texSize_ = D3DXVECTOR2(1, 1);
	D3DXVECTOR2 texcoordSize_ = D3DXVECTOR2(1, 1);

	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer_ = NULL;
	LPDIRECT3DINDEXBUFFER9 pIndexBuffer_ = NULL;
};