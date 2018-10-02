#pragma once
#include "Enemy.h"

class Zombie :public Enemy
{
public:
	Zombie();
	~Zombie()override;
	void Init()override;
	void Uninit()override;
	void Update()override;
	void BeginDraw()override;
	void Draw()override;
	void EndDraw()override;
};