//PLAYER.hpp
//�v���C���[���Ǘ�����N���X

#pragma once

//############## �w�b�_�t�@�C���ǂݍ��� ####################
#include "DxLib.h"
#include "CHARACTOR.hpp"

//############## �}�N����` #######################
#define IMG_DIR_PLAYER		R"(.\MY_IMG\Player)"		//�v���C���[�֌W�̉摜�f�B���N�g��

#define IMG_NAME_PLAYER		R"(\Player.png)"			//�v���C���[�̉摜�̖��O

//############## �N���X��` #######################
class PLAYER : public CHARACTOR		//�L�����N�^�[�N���X���p��
{

private:

	int WinNum;		//������
	double PushTime;//�L�[�{�[�h�������܂łɂ�����������

public:

	PLAYER(const char *,const char *);		//�R���X�g���N�^
	~PLAYER();								//�f�X�g���N�^

	void IncreaseWinNum();		//�������𑝂₷
	int GetWinNum();			//���������擾

	void SetPushTime(double);	//�����܂łɂ����������Ԃ�ݒ�
	double GetPushTime();		//�����܂łɂ����������Ԃ��擾

};
