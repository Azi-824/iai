//DATA.cpp
//�f�[�^���Ǘ�����N���X

//################# �w�b�_�t�@�C���ǂݍ��� ##################
#include "DATA.hpp"

//################# �N���X��` ###################

//�R���X�g���N�^
DATA::DATA(int year,int month,int day,int win_num)
{

	this->Year = year;		//�N
	this->Month = month;	//��
	this->Day = day;		//��
	this->WinNum = win_num;	//������

	return;
}

//�f�X�g���N�^
DATA::~DATA()
{
	return;
}

//�N�擾
int DATA::GetYear()
{
	return this->Year;
}

//���擾
int DATA::GetMonth()
{
	return this->Month;
}

//���擾
int DATA::GetDay()
{
	return this->Day;
}

//�������擾
int DATA::GetWinNum()
{
	return this->WinNum;
}