#pragma once
#include "../Object.h"

class StateCore;
class XModel;

class Core :public Object
{
public:
	Core();
	~Core()override;
	void Init()override;
	void Uninit()override;
	void Update()override;
	void BeginDraw()override;
	void Draw()override;
	void EndDraw()override;

private:
	StateCore* stateCore_ = nullptr;		//Core‚Ìó‘Ô‚ğŠÇ—
	XModel* model_ = nullptr;				//Modelî•ñ
};