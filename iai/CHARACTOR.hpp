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
	bool IsLoad;				//�ǂݍ��߂���

public:

	CHARACTOR();				//�R���X�g���N�^
	~CHARACTOR();				//�f�X�g���N�^

	void SetIsArive(bool);		//�����Ă��邩��ݒ�
	void SetImage(const char*, const char*);//�摜�ݒ�

	void SetImagePos(int, int);		//�摜�̈ʒu��ݒ肷��

	int  GetWidth();			//�����擾
	int GetHeight();			//�����擾
	bool GetIsArive();			//�����Ă��邩�擾
	bool GetIsLoad();			//�ǂݍ��߂����擾

	void Operation(KEYDOWN *);	//����

	void Draw();				//�`��

	void SetInit();				//�����ݒ�

};

