//ENEMY.cpp
//�G���Ǘ�����N���X

//############### �w�b�_�t�@�C���ǂݍ��� #################
#include "ENEMY.hpp"

//############### �N���X��` ###################

//�R���g���N�^
//���@���Fconst char *�F�摜�̃f�B���N�g��
//���@���Fconst char *�F�摜�̖��O
ENEMY::ENEMY(const char *dir,const char *name)
{

	this->SetImage(dir, name);	//�摜�𐶐�

	//�����o�[�ϐ�������
	this->Speed = ENEMY_SPD_INIT;		//�͂₳��������

	return;
}

//�f�X�g���N�^
ENEMY::~ENEMY()
{
	return;
}

//���x���擾
double ENEMY::GetSpeed()
{
	return this->Speed;
}

//���x�𑁂�����
void ENEMY::SpeedUp()
{
	if (this->Speed > ENEMY_SPD_MIN)		//�ō����x���x�����
	{
		this->Speed -= ENEMY_SPD_UP_VALUE;	//����
	}
	return;
}

//���x�����Z�b�g����
void ENEMY::SpeedReset()
{
	this->Speed = ENEMY_SPD_INIT;	//������������
	return;
}
