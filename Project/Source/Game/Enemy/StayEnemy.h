#pragma once

#include "Enemy.h"
class Texture;

class StayEnemy :public Enemy
{
public:
	StayEnemy();
	~StayEnemy();
	void Init()override;
	void Uninit()override;
	void Update()override;
	void BeginDraw()override;
	void Draw()override;
	void EndDraw()override;
private:
	LPD3DXSPRITE shadow_ = NULL;
};