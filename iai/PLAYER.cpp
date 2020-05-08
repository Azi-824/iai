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

	//�����o�[�ϐ��̏�����
	this->WinNum = 0;					//������������
	this->PushTime = 0.0;				//�����̂ɂ����������ԏ�����
	this->Result = (int)RESULT_NONE;	//�������ʏ�����

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
//�߂�l�Fint�F���݂̏�����
int PLAYER::GetWinNum()
{
	return this->WinNum;
}

//�����܂ł̎��Ԃ�ݒ�
void PLAYER::SetPushTime(double time)
{
	//���Ԃ́A�~���b�Ŏw�肳��邽�߁A�b���ɕϊ����Đݒ肷��
	this->PushTime = time/1000;
	return;
}

//�����܂ł̎��Ԃ��擾
//�߂�l�Fdouble�F�����܂ł̎���
double PLAYER::GetPushTime()
{
	return this->PushTime;
}

//�������ʐݒ�
void PLAYER::SetResult(int result)
{
	this->Result = result;
	return;
}

//�������ʎ擾
int PLAYER::GetResult()
{
	return this->Result;
}
