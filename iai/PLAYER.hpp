//PLAYER.hpp
//�v���C���[���Ǘ�����N���X

#pragma once

//############## �w�b�_�t�@�C���ǂݍ��� ####################
#include "DxLib.h"
#include "CHARACTOR.hpp"

//############## �}�N����` #######################

//############## �N���X��` #######################
class PLAYER : public CHARACTOR		//�L�����N�^�[�N���X���p��
{

private:

	int WinNum;		//������
	double PushTime;//�L�[�{�[�h�������܂łɂ�����������

public:

	PLAYER();		//�R���X�g���N�^
	~PLAYER();		//�f�X�g���N�^

	void IncreaseWinNum();		//�������𑝂₷
	int GetWinNum();			//���������擾

	void SetPushTime(double);	//�����܂łɂ����������Ԃ�ݒ�
	double GetPushTime();		//�����܂łɂ����������Ԃ��擾

};
