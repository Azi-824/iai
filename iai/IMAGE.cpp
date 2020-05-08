/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* IMAGE.cpp     																				�@ */
/*       																						�@ */

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "IMAGE.hpp"

//########## �N���X�̒�` ##########

//�R���X�g���N�^
//���@���Fconst char *�F�摜�̃f�B���N�g��
//���@���Fconst char *�F�摜�̖��O
IMAGE::IMAGE(const char *dir,const char *name)
{
	//�����o�ϐ���������
	this->FilePath = "";	//�p�X
	this->FileName = "";	//���O
	
	this->ImageKind = 0;	//�ǂݍ��񂾉摜�̎��
	this->Draw_Num = 0;		//�`�悷��摜�̔ԍ�

	this->IsLoad = false;	//�ǂݍ��߂����H

	//�摜��ǂݍ���
	std::string LoadfilePath;	//�摜�̃t�@�C���p�X���쐬
	LoadfilePath += dir;
	LoadfilePath += name;

	this->Handle.push_back(LoadGraph(LoadfilePath.c_str()));//�摜��ǂݍ���
	
	if (this->Handle.back() == -1)	//�摜���ǂݍ��߂Ȃ������Ƃ�
	{
		std::string ErroeMsg(IMAGE_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
		ErroeMsg += TEXT('\n');					//���s
		ErroeMsg += LoadfilePath;				//�摜�̃p�X

		MessageBox(
			NULL, 
			ErroeMsg.c_str(),	//char * ��Ԃ�
			TEXT(IMAGE_ERROR_TITLE),
			MB_OK);

		return;
	}

	this->FilePath = LoadfilePath;		//�摜�̃p�X��ݒ�
	this->FileName = name;				//�摜�̖��O��ݒ�

	this->IsLoad = true;		//�ǂݍ��߂�

	this->IsDraw.push_back(true);	//�`�悵�Ă悢

	this->ImageKind = this->Handle.size();	//�ǂݍ��񂾐����擾

	return;
}

//�f�X�g���N�^
IMAGE::~IMAGE()
{
	for (int handle : this->Handle)
	{
		DeleteGraph(handle);		//�ǂݍ��񂾉摜���폜
	}

	//vector�̃�����������s��
	std::vector<int> v;			//���vector���쐬����
	this->Handle.swap(v);		//��ƒ��g�����ւ���

	std::vector<int>v2;
	this->Width.swap(v2);

	std::vector<int>v3;
	this->Height.swap(v3);

	std::vector<bool>v4;
	this->IsDraw.swap(v4);

	return;
}

//�t�@�C���̖��O���擾
std::string IMAGE::GetFileName(void)
{
	return this->FileName;
}

//�T�C�Y��ݒ肷��
void IMAGE::SetSize(void)
{
	this->Width.resize(this->Handle.size());	//�T�C�Y�ύX
	this->Height.resize(this->Handle.size());	//�T�C�Y�ύX
	//�摜�̐��������[�v����
	for (int i = 0; i < this->Handle.size(); ++i)
	{
		GetGraphSize(this->Handle[i], &this->Width[i], &this->Height[i]);	//�摜�T�C�Y�擾
	}
	return;
}

//�����擾
int IMAGE::GetWidth()
{
	return this->Width[this->Draw_Num];
}

//�������擾
int IMAGE::GetHeight()
{
	return this->Height[this->Draw_Num];
}

//�ǂݍ��߂��H
bool IMAGE::GetIsLoad(void)
{
	return this->IsLoad;
}

//�摜��`��
void IMAGE::Draw(int x, int y)
{
	
	if (this->IsDraw[this->Draw_Num])	//�`�悵�Ă悯���
	{
		DrawGraph(x, y, this->Handle[this->Draw_Num], TRUE);	//�摜��`��
	}

}

//�摜��ǉ�
//���@���Fconst char *�F�摜�̃f�B���N�g��
//���@���Fconst char *�F�摜�̖��O
bool IMAGE::AddImage(const char *dir, const char *name)
{

	this->IsLoad = false;	//�ǂݍ��߂Ă��Ȃ�

	//�摜��ǂݍ���
	std::string LoadfilePath;	//�摜�̃t�@�C���p�X���쐬
	LoadfilePath += dir;
	LoadfilePath += name;

	this->Handle.push_back(LoadGraph(LoadfilePath.c_str()));	//�摜��ǂݍ���


	if (this->Handle.back() == -1)	//�摜���ǂݍ��߂Ȃ������Ƃ�
	{
		std::string ErroeMsg(IMAGE_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
		ErroeMsg += TEXT('\n');					//���s
		ErroeMsg += LoadfilePath;				//�摜�̃p�X

		MessageBox(
			NULL,
			ErroeMsg.c_str(),	//char * ��Ԃ�
			TEXT(IMAGE_ERROR_TITLE),
			MB_OK);

		return false;
	}

	this->IsLoad = true;		//�ǂݍ��߂�

	this->IsDraw.push_back(true);	//�`�悵�Ă悢

	this->ImageKind = this->Handle.size();	//�ǂݍ��񂾐����擾

	return true;

}

//�`�悷��摜��ύX
void IMAGE::ChengeImage(int kind)
{
	this->Draw_Num = kind;
	return;
}
