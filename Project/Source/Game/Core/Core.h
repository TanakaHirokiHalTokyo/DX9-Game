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
	StateCore* stateCore_ = nullptr;		//Core�̏�Ԃ��Ǘ�
	XModel* model_ = nullptr;				//Model���
};