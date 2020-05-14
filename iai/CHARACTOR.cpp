//CHARACTOR.cpp
//�L�����N�^�[�N���X

//################# �w�b�_�t�@�C���ǂݍ��� #####################
#include "CHARACTOR.hpp"

//################ �N���X��` ########################
//�R���X�g���N�^
CHARACTOR::CHARACTOR()
{
	
	//�����o�[�ϐ�������
	this->IsArive = false;	//����ł���
	this->IsLoad = false;	//�ǂݍ��߂Ă��Ȃ�

	return;
}

//�f�X�g���N�^
CHARACTOR::~CHARACTOR()
{
	delete this->image;		//image�폜

	return;
}

//�����Ă��邩�ݒ�
void CHARACTOR::SetIsArive(bool Isarive)
{
	this->IsArive = Isarive;
	return;
}

//�摜��ݒ�
//���@���Fconst char *�F�摜�̃f�B���N�g��
//���@���Fconst char *�F�摜�̖��O
void CHARACTOR::SetImage(const char *dir, const char *name)
{
	this->image = new IMAGE(dir, name);
	this->IsLoad = this->image->GetIsLoad();	//�ǂݍ��߂����ݒ�

	return;

}

//�摜��ǉ�
//���@���Fconst char *�F�摜�̃f�B���N�g��
//���@���Fconst char *�F�摜�̖��O
bool CHARACTOR::AddImage(const char *dir, const char *name)
{
	return this->image->AddImage(dir, name);	
}

//�摜��ύX����
//�����Fint�F�ύX����摜�̔ԍ�
void CHARACTOR::ChengeImage(int kind)
{
	this->image->ChengeImage(kind);
	return;
}

//�������擾
int CHARACTOR::GetWidth()
{
	return this->image->GetWidth();
}

//�������擾
int CHARACTOR::GetHeight()
{
	return this->image->GetHeight();
}

//�摜�̈ʒu��ݒ肷��
void CHARACTOR::SetImagePos(int x, int y)
{

	this->Draw_X = x;
	this->Draw_Y = y;

}

//�����Ă��邩�擾
bool CHARACTOR::GetIsArive()
{
	return this->IsArive;
}

//�ǂݍ��߂����擾
bool CHARACTOR::GetIsLoad()
{
	return this->IsLoad;
}

//����
void CHARACTOR::Operation(KEYDOWN *keydown)
{
	return;
}

//�������ݒ�
void CHARACTOR::SetInit()
{

	this->image->SetSize();		//�摜�T�C�Y�ݒ�

	this->IsArive = true;		//�����Ă���

	return;

}

//�`��
void CHARACTOR::Draw()
{
	if (this->IsArive)	//�����Ă����
	{
		this->image->Draw(this->Draw_X, this->Draw_Y);	//�摜�`��
	}
}

//�t�F�[�h�A�E�g���邩�ݒ�
void CHARACTOR::SetFade(bool isfade)
{
	this->image ->SetIsFade(isfade);
	return;
}

//�`�悷�邩�ݒ�
void CHARACTOR::SetIsDraw(bool isdraw)
{
	this->image->SetIsDraw(isdraw);
	return;
}

//�t�F�[�h�G�t�F�N�g���I���������擾
bool CHARACTOR::GetFadeEnd()
{
	return this->image->GetFadeEnd();
}