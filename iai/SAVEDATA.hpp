//SAVEDATA.hpp
//�Z�[�u�f�[�^���Ǘ�����N���X

#pragma once

//################## �w�b�_�t�@�C���ǂݍ��� ####################
#include "DATA.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <direct.h>

//################## �}�N����` #######################
#define SAVEDATA_DIR	R"(C:\IAI_DATA)"		//�Z�[�u�f�[�^�̕ۑ��f�B���N�g����

#define SAVEDATA_NAME	R"(\Savedata.csv)"		//�Z�[�u�f�[�^�̖��O

//############## �}�N����`�F�G���[���b�Z�[�W ###################
#define DATA_ERROR_TTILE	"DATA_ERROR"						//�G���[�^�C�g��
#define DATA_ERROR_MSG		"�f�[�^���ǂݍ��߂܂���ł���"		//�G���[���b�Z�[�W

//################## �N���X��` #######################
class SAVEDATA
{

private:

	std::vector<DATA*> DataCode;			//�Z�[�u�f�[�^

public:

	SAVEDATA();		//�R���X�g���N�^
	~SAVEDATA();	//�f�X�g���N�^

	void Add(int);	//�f�[�^�ǉ�

	bool Save();	//�Z�[�u

};
