#pragma once
#include "../Game/Object.h"
#include "../Texture/Texture.h"

class UIState;

class UI :public Object
{
public:
	UI(TextureManager::TextureList type);
	~UI()override;
	void Init()override;
	void Uninit()override;
	void Update()override;
	void BeginDraw()override;
	void Draw()override;
	void EndDraw()override;

	void MoveTexture(float afterSpawnCount,float moveTime,float update_x,float update_y);								//���̊֐����ĂԂ�Update�Ńe�N�X�`����
	void MoveTexture(float afterSpawnCount, float moveTime, D3DXVECTOR3 update_pos);									//���̊֐����ĂԂ�Update�Ńe�N�X�`��������
	void MoveTexture(float afterSpawnCount, float moveTime, D3DXVECTOR2 update_pos);									//���̊֐����ĂԂ�Update�Ńe�N�X�`��������

	void ScalingTexture(float afterSpawnCount, float moveTime, float update_x, float update_y);							//���̊֐����ĂԂ�Update�Ńe�N�X�`����
	void ScalingTexture(float afterSpawnCount, float moveTime, D3DXVECTOR3 update_scale);								//���̊֐����ĂԂ�Update�Ńe�N�X�`��������
	void ScalingTexture(float afterSpawnCount, float moveTime, D3DXVECTOR2 update_scale);								//���̊֐����ĂԂ�Update�Ńe�N�X�`��������

	Texture* GetTexture();
	//	Move	------------------------------------------------------------------------------------
	float GetCountMove();							//�����J�n���牽�b�œ������̂����擾
	float GetMoveTime();							//�ړ��J�n���牽�b�ԓ������̂����擾
	D3DXVECTOR2 GetAfterPos();						//�X�V��̍��W���擾
	void SetUpdateMove(bool flag);
	bool GetUpdateMove();

	//	Scale	------------------------------------------------------------------------------------
	float GetCountScale();							//�����J�n���牽�b�œ������̂����擾
	float GetScaleTime();							//�ړ��J�n���牽�b�ԓ������̂����擾
	D3DXVECTOR2 GetAfterScale();					//�X�V���Scale���擾
	void SetUpdateScale(bool flag);
	bool GetUpdateScale();



private:
	Texture* texture_ = nullptr;
	UIState* stateMove_ = nullptr;					//�����𐧌�
	UIState* stateScale_ = nullptr;					//�T�C�Y�𐧌�
	//		Move Info	----------------------------------------------------------------------------
	bool move_ = false;								//�������Ă��瓮�����̂�
	bool updateMove_ = true;						//�ړ��X�V���܂��s���̂�
	float countMove_ = 0;							//�������Ă��牽�b��Ɉړ������邩
	float moveTime_ = 0;							//�ړ��J�n���牽�b�Ԃňړ����I���̂�
	D3DXVECTOR2 updatePos_ = D3DXVECTOR2(0, 0);		//�ړ���̍��W

	//		Scale Info  -----------------------------------------------------------------------------
	bool scale_ = false;							//�������Ă���T�C�Y��ς��邩
	bool updateScale_ = true;						//�T�C�Y�ύX���܂��s���̂�
	float countScale_ = 0;							//�������Ă��牽�b��ɃT�C�Y��ς���̂�
	float scaleTime_ = 0;							//�T�C�Y�ύX�J�n���牽�b�ԂŕύX���I���̂�
	D3DXVECTOR2 updateSize_ = D3DXVECTOR2(1, 1);	//�ύX��̃T�C�Y
};