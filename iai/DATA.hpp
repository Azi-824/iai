//DATA..hpp
//�f�[�^���Ǘ�����N���X

#pragma once

//################### �w�b�_�t�@�C���ǂݍ��� ###################
#include "DxLib.h"

//################### �}�N����` #####################

//################### �N���X��` #####################
class DATA
{

private:

	int Year;		//�N
	int Month;		//��
	int Day;		//��
	int WinNum;		//������

public:

	DATA(int,int,int,int);			//�R���X�g���N�^
	~DATA();						//�f�X�g���N�^

	int GetYear();		//�N�擾
	int GetMonth();		//���擾
	int GetDay();		//���擾
	int GetWinNum();	//�������擾

};
