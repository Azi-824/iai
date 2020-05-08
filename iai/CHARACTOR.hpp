//CHARACTOR.hpp
//�L�����N�^�[�N���X

#pragma once

//###################### �w�b�_�t�@�C���ǂݍ��� ###################
#include "DxLib.h"
#include "IMAGE.hpp"
#include "KEYDOWN.hpp"


//###################### �}�N����` #######################

//###################### �N���X��` #######################
class CHARACTOR
{
private:
	IMAGE *image;				//�摜

	int Draw_X;					//�`��X�ʒu
	int Draw_Y;					//�`��Y�ʒu

	bool IsArive;				//�����Ă��邩
	bool IsLoad;				//�ǂݍ��߂���

public:

	CHARACTOR();				//�R���X�g���N�^
	~CHARACTOR();				//�f�X�g���N�^

	void SetIsArive(bool);		//�����Ă��邩��ݒ�
	void SetImage(const char*, const char*);	//�摜�ݒ�
	bool AddImage(const char *, const char *);	//�摜�ǉ�
	void ChengeImage(int);						//�摜��ύX����

	void SetImagePos(int, int);		//�摜�̈ʒu��ݒ肷��

	int  GetWidth();			//�����擾
	int GetHeight();			//�����擾
	bool GetIsArive();			//�����Ă��邩�擾
	bool GetIsLoad();			//�ǂݍ��߂����擾

	void Operation(KEYDOWN *);	//����

	void Draw();				//�`��

	void SetInit();				//�����ݒ�

};

