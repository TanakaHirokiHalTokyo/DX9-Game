#pragma once

#include "Camera.h"

class XModel;

class GameCamera :public Camera
{
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void BeginDraw()override;
	void Draw()override;
	void EndDraw()override;
	void MUpdate();
	void SetModel1(XModel* model);
	void SetModel2(XModel* model);
private:
	XModel* model1_ = nullptr;
	XModel* model2_ = nullptr;
};