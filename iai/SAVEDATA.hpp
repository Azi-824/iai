//SAVEDATA.hpp
//�Z�[�u�f�[�^���Ǘ�����N���X

#pragma once

//################## �w�b�_�t�@�C���ǂݍ��� ####################
#include "DATA.hpp"
#include <vector>

//################## �}�N����` #######################

//################## �N���X��` #######################
class SAVEDATA
{

private:

	std::vector<DATA*> DataCode;			//�Z�[�u�f�[�^

public:

	SAVEDATA();		//�R���X�g���N�^
	~SAVEDATA();	//�f�X�g���N�^

	void Add(int);	//�f�[�^�ǉ�

};
