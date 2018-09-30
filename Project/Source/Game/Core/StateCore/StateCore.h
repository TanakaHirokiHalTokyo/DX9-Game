#pragma once
class Core;

//		Coreの状態を管理する
class StateCore
{
public:
	virtual ~StateCore(){}
	virtual void UpdateCore(Core* core) = 0;
};