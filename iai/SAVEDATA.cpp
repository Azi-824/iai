//SAVEDATA.cpp
//�Z�[�u�f�[�^���Ǘ�����N���X

//################### �w�b�_�t�@�C���ǂݍ��� ##################
#include "SAVEDATA.hpp"

//#################### �N���X��` #######################

//�R���X�g���N�^
SAVEDATA::SAVEDATA()
{


	return;
}

//�f�X�g���N�^
SAVEDATA::~SAVEDATA()
{

	for (int i = 0; i < this->DataCode.size(); ++i)
	{
		delete this->DataCode.at(i);
	}

	//vector�̃�����������s��
	std::vector<DATA*> v;			//���vector���쐬����
	this->DataCode.swap(v);			//��ƒ��g�����ւ���


	return;
}

//�f�[�^�ǉ�
void SAVEDATA::Add(int win_num)
{

	DATEDATA Date;		//���ݎ���

	GetDateTime(&Date);	//���ݎ����擾

	this->DataCode.push_back(new DATA(Date.Year,Date.Mon,Date.Day,win_num));	//�f�[�^���ǉ�

	return;

}
