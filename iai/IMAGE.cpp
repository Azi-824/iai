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

	this->IsFade.push_back(false);	//�t�F�[�h�A�E�g���Ȃ�
	this->FadeEnd.push_back(false);	//�t�F�[�h�G�t�F�N�g���I����Ă��Ȃ�

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

	std::vector<bool>v5;
	this->IsFade.swap(v5);

	std::vector<bool>v6;
	this->FadeEnd.swap(v6);

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

//�`�悵�Ă悢���ݒ�
void IMAGE::SetIsDraw(bool isdraw)
{
	this->IsDraw[this->Draw_Num] = isdraw;
	return;
}

//�摜��`��
void IMAGE::Draw(int x, int y)
{

	static int cnt = FADE_MAX_CNT;				//�J�E���g�p

	if (this->IsFade.at(this->Draw_Num))	//�t�F�[�h�A�E�g����Ƃ���
	{
		if (!this->FadeEnd.at(this->Draw_Num))	//�t�F�[�h�A�E�g�I�����Ă��Ȃ����
		{

			if (this->IsDraw[this->Draw_Num])	//�`�悵�Ă悯���
			{
				
				//60�t���[�����A�҂�
				if (cnt > 0)
				{
					--cnt;	//�J�E���g�A�b�v
				}
				else
				{
					this->FadeEnd.at(this->Draw_Num) = true;	//�t�F�[�h�I��
				}

				//�t�F�[�h�A�E�g�̏���
				double ToukaPercent = cnt / (double)FADE_MAX_CNT;						//����%���v�Z
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, ToukaPercent * TOUKA_MAX_VALUE);	//���߂�����
				DrawGraph(x, y, this->Handle[this->Draw_Num], TRUE);					//�摜��`��
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);								//���߂���߂�


			}


		}
		else 		//�t�F�[�h�A�E�g�I��������
		{
			this->IsDraw.at(this->Draw_Num) = false;	//�`�悵�Ȃ�
			this->FadeEnd.at(this->Draw_Num) = false;	//�t�F�[�h�A�E�g�I���t���O���Z�b�g
			cnt = FADE_MAX_CNT;							//�J�E���g���Z�b�g
			this->IsFade.at(this->Draw_Num) = false;	//�t�F�[�h�A�E�g���Ȃ�
		}

	}
	else		//�t�F�[�h�A�E�g���Ȃ�����
	{

		if (this->IsDraw[this->Draw_Num])	//�`�悵�Ă悯���
		{
			DrawGraph(x, y, this->Handle[this->Draw_Num], TRUE);	//�摜��`��
		}

	}
	

	return;

}

//�摜��`��i�����j
//�����Fint�F��ʂ̉���
//�����Fint�F�`�悷�鍂��
void IMAGE::DrawCenter(int width,int y)
{

	int x = 0;	//�`�悷��X�ʒu
	x = (width / 2) - (this->Width[this->Draw_Num] / 2);	//��ʒ����ɂȂ�悤�Ɍv�Z

	if (this->IsDraw[this->Draw_Num])	//�`�悵�Ă悯���
	{
		DrawGraph(x, y, this->Handle[this->Draw_Num], TRUE);	//�摜��`��
	}

	return;
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
	this->IsFade.push_back(false);	//�t�F�[�h�A�E�g���Ȃ�
	this->FadeEnd.push_back(false);	//�t�F�[�h�G�t�F�N�g���I����Ă��Ȃ�

	this->ImageKind = this->Handle.size();	//�ǂݍ��񂾐����擾

	return true;

}

//�`�悷��摜��ύX
void IMAGE::ChengeImage(int kind)
{
	this->Draw_Num = kind;
	return;
}

//�t�F�[�h�A�E�g���邩�ݒ�
void IMAGE::SetIsFade(bool isfade)
{
	this->IsFade.at(this->Draw_Num) = isfade;
	return;
}
