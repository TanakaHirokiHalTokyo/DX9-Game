#pragma once

#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
#include <d3d9.h>
#include <d3dx9.h>

struct EffectFile
{
	const wchar_t fileName[256];
};


class CEffekseer
{
public:
	struct Transform
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 scale;
		D3DXVECTOR3 rotate;
	};

	const enum Effect
	{
		Effect_SpawnAvatar,
		Effect_DestroyEffect,
		Effect_SpeedUp,
		Effect_Dash,
		Effect_Horming,
		Effect_CircleShot,
		Effect_MonsterRoar,
		Effect_BurstShot,
		Effect_Teleportation,
		Effect_PlayerHeal,
		Effect_PlayerLightning,
		Effect_Explosion,
		Effect_Max
	};
	const EffectFile fileName_[Effect_Max]{
		L"resource/Effect/SpawnAvatar.efk",
		L"resource/Effect/DestroyEffect.efk",
		L"resource/Effect/SpeedUp.efk",
		L"resource/Effect/dash.efk",
		L"resource/Effect/horming.efk",
		L"resource/Effect/CircleShot.efk",
		L"resource/Effect/MonsterRoar.efk",
		L"resource/Effect/BurstShot.efk",
		L"resource/Effect/Teleportation.efk",
		L"resource/Effect/PlayerHeal.efk",
		L"resource/Effect/PlayerLightning.efk",
		L"resource/Effect/Explosion.efk",
	};


public:
	CEffekseer(Effect EffectType,D3DXVECTOR3 pos);
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetLocation(D3DXVECTOR3 pos);
	void SetProj(float Fov, float ScreenWidth, float ScreenHeight, float Near, float Far);
	void SetView(D3DXVECTOR3 Pos, D3DXVECTOR3 At, D3DXVECTOR3 Up);
	void SetSpeed(float speed);
	void RepeatEffect(bool repeat);
	void Play();
	void Paused(bool paused);
	void Stop();
	void SetMatrix(D3DXMATRIX mat);
	bool GetPlaying();

	void SetVisible(bool flag);
	bool GetVisible();

	void SetPosition(float x,float y,float z);
	void SetPosition(D3DXVECTOR3 trans);
	D3DXVECTOR3 GetPosition();
	void SetRotate(float x,float y,float z);
	void SetRotate(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetRotate();
	void SetScale(float x, float y,float z);
	void SetScale(D3DXVECTOR3 scale);
	D3DXVECTOR3 GetScale();

private:
	void LoadEffect();

	Effekseer::Manager*					effekseerManager_;
	EffekseerRendererDX9::Renderer*		effekseerRenderer_;
	Effekseer::Effect*					effekseerEffect_;
	Effekseer::Handle					effekseerHandle_;
	CEffekseer::Effect					effectType_;
	bool repeat_ = false;				//繰りかえし再生するか。
	bool paused_ = false;				//ポーズ中か。
	bool playing_ = false;				//再生中か
	bool visible_ = false;				//表示するか
	Transform transform_;
	int priority_;

};