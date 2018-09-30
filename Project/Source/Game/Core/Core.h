#pragma once
#include "../Object.h"

class StateCore;
class XModel;
class Billboard;

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
	Billboard* test_ = nullptr;
	StateCore* stateCore_ = nullptr;		//Coreの状態を管理
	XModel* model_ = nullptr;				//Model情報
};