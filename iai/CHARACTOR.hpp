//CHARACTOR.hpp
//�L�����N�^�[�N���X

#pragma once

//###################### �w�b�_�t�@�C���ǂݍ��� ###################
#include "DxLib.h"
#include "IMAGE.hpp"
#include "KEYDOWN.hpp"
#include "SIKAKU.hpp"


//###################### �}�N����` #######################

//###################### �N���X��` #######################
class CHARACTOR
{
private:
	IMAGE *image;				//�摜
	SIKAKU *sikaku_draw;		//�L�����̕`�悷��̈�

	bool IsArive;				//�����Ă��邩
	bool IsDraw;				//�`��ł��邩

public:

	CHARACTOR();				//�R���X�g���N�^
	~CHARACTOR();				//�f�X�g���N�^

	void SetIsArive(bool);		//�����Ă��邩��ݒ�
	void SetIsDraw(bool);		//�`�悵�Ă悢����ݒ�
	bool SetImage(const char*, const char*);//�摜�ݒ�

	void SetImagePos(int, int);		//�摜�̈ʒu��ݒ肷��

	int  GetWidth();			//�����擾
	int GetHeight();			//�����擾
	bool GetIsArive();			//�����Ă��邩�擾
	bool GetIsDraw();			//�`��ł��邩�擾

	void Operation(KEYDOWN *);	//����

	void Draw();				//�`��

	bool SetInit();				//�����ݒ�

};

