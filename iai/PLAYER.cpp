//PLAYER.cpp
//�v���C���[���Ǘ�����N���X

//############## �w�b�_�t�@�C���ǂݍ��� ##################
#include "PLAYER.hpp"

//############## �N���X��` #####################

//�R���X�g���N�^
//���@���Fconst char *�F�摜�̃f�B���N�g��
//���@���Fconst char *�F�摜�̖��O
PLAYER::PLAYER(const char *dir,const char *name)
{

	this->SetImage(dir, name);	//�摜�𐶐�

	return;
}

//�f�X�g���N�^
PLAYER::~PLAYER()
{
	return;
}

//�������𑝂₷
void PLAYER::IncreaseWinNum()
{
	++this->WinNum;
	return;
}

//���������擾
int PLAYER::GetWinNum()
{
	return this->WinNum;
}

//������Ă���̎��Ԃ�ݒ�
void PLAYER::SetPushTime(double time)
{
	this->PushTime = time;
	return;
}

//������Ă���̎��Ԃ��擾
double PLAYER::GetPushTime()
{
	return this->PushTime;
}
