//ENEMY.hpp
//�G���Ǘ�����N���X

#pragma once

//################ �w�b�_�t�@�C���ǂݍ��� #################
#include "CHARACTOR.hpp"

//################ �}�N����` ##################

//################ �N���X��` ##################
class ENEMY :public CHARACTOR	//�L�����N�^�[�N���X���p��
{

private:

	double Speed;		//���x

public:

	ENEMY();			//�R���X�g���N�^
	~ENEMY();			//�f�X�g���N�^

	double GetSpeed();	//���x���擾

};
