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
	this->Speed = ENEMY_SPD_MAX;	//�͂₳��������

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
