//EFFECT.cpp
//�G�t�F�N�g�N���X

//################## �w�b�_�t�@�C���ǂݍ��� ##################
#include "EFFECT.hpp"

//################## �N���X��` #######################

//�R���X�g���N�^
/*
���@���Fconst char *�F�摜�̃f�B���N�g��
���@���Fconst char *�F�摜�̖��O
���@���Fint�F�摜�̑�������
���@���Fint�F�摜�̉������̕�����
���@���Fint�F�摜�̏c�����̕�����
���@���Fint�F�摜�̕������ꂽ���̑傫��
���@���Fint�F�摜�̕������ꂽ�c�̑傫��
���@���Fdouble�F���̉摜�ɕύX���鑬��
���@���Fbool�F�A�j���[�V���������[�v���邩�ǂ���
���@���Fint�FFPS�̑��x
*/
EFFECT::EFFECT(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop,int fps_spd)
{

	this->IsLoad = false;			//�ǂݍ��߂����H
	this->IsDrawEnd = false;		//�`��I��������?

	//�摜��ǂݍ���
	std::string LoadfilePath;		//�摜�̃t�@�C���p�X���쐬
	LoadfilePath += dir;
	LoadfilePath += name;

	std::vector<int> work(SplitNumALL);	//�����ǂݍ��݂œ����n���h�����i�[����z��𑍕������ŏ�����

	//�摜�𕪊����ēǂݍ���
	LoadDivGraph(LoadfilePath.c_str(), SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, &work.front());
	this->Handle.push_back(work);
	
	if (this->Handle.front().front() == -1)	//�摜���ǂݍ��߂Ȃ������Ƃ�
	{
		std::string ErrorMsg(EFFECT_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
		ErrorMsg += TEXT('\n');						//���s
		ErrorMsg += LoadfilePath;					//�摜�̃p�X

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * ��Ԃ�
			TEXT(EFFECT_ERROR_TTILE),
			MB_OK);

		return;
	}

	this->ChangeMaxCnt.push_back(fps_spd * changeSpeed);
	this->ChangeCnt = 0;	//�A�j���[�V��������t���[���̃J�E���g

	this->NextChangeSpeed.push_back(changeSpeed);	//�摜��ς��鑬��

	this->IsAnimeLoop.push_back(IsLoop);	//�A�j���[�V���������[�v���邩
	this->IsAnimeStop.push_back(false);		//�A�j���[�V�����𓮂���

	this->Handle_itr = this->Handle.front().begin();	//�擪�v�f���C�e���[�^�ɐݒ�

	this->IsLoad = true;		//�ǂݍ��߂�

	//vector�̃�����������s��
	std::vector<int> v;			//���vector���쐬����
	work.swap(v);				//��ƒ��g�����ւ���

	return;

}

//�f�X�g���N�^
EFFECT::~EFFECT()
{
	for (int i = 0; i < this->Handle.size(); ++i)
	{
		DeleteGraph(this->Handle[i][0]);
	}

	//vector�̃�����������s��
	std::vector<std::vector<int>> v;			//���vector���쐬����
	this->Handle.swap(v);						//��ƒ��g�����ւ���

	std::vector<int> v2;
	this->Width.swap(v2);

	std::vector<int> v3;
	this->Height.swap(v3);

	std::vector<bool> v4;
	this->IsAnimeLoop.swap(v4);

	std::vector<bool> v5;
	this->IsAnimeStop.swap(v5);

	std::vector<double> v6;
	this->NextChangeSpeed.swap(v6);

	std::vector<int> v7;
	this->ChangeMaxCnt.swap(v7);

	return;

}

//�����擾
int EFFECT::GetWidth(int type)
{
	return this->Width[type];
}

//�������擾
int EFFECT::GetHeight(int type)
{
	return this->Height[type];
}

//�ǂݍ��߂��H
bool EFFECT::GetIsLoad(void)
{
	return this->IsLoad;
}

//�A�j���[�V�����̓X�g�b�v���������擾
bool  EFFECT::GetIsAnimeStop(int type)
{
	return this->IsAnimeStop[type];
}

//�`��I���������ǂ����擾
bool EFFECT::GetIsDrawEnd()
{
	return this->IsDrawEnd;
}

//�`��I���������ݒ�
void EFFECT::SetIsDrawEnd(bool isend)
{
	this->IsDrawEnd = isend;
	return;
}

//�A�j���[�V�������X�g�b�v�����������Z�b�g
void EFFECT::ResetIsAnime(int type)
{
	this->IsAnimeStop[type] = false;
	this->IsDrawEnd = false;		
	return;
}

//�`��
/*
�����Fint�FX�̕`��ʒu
�����Fint�FY�̕`��ʒu
�����Fint�F�`�悷��G�t�F�N�g�̎��
*/
void EFFECT::Draw(int x, int y, int type)
{
	static bool setflg = false;	//�n���h���ݒ�t���O
	if (setflg == false)
	{
		this->Handle_itr = this->Handle[type].begin();		//�w�肳�ꂽ�G�t�F�N�g�^�C�v�̃n���h������
		setflg = true;	//�n���h���ݒ�ς�
	}

		if (this->IsAnimeStop[type] == false)	//�A�j���[�V�������X�g�b�v�����Ȃ��Ȃ�
		{
			DrawGraph(x, y, *this->Handle_itr, TRUE);	//�C�e���[�^(�|�C���^)���g�p���ĕ`��
		}
		else
		{
			this->IsDrawEnd = true;		//�`��I��
			setflg = false;				//�n���h�����ݒ�
		}

		if (this->ChangeCnt == this->ChangeMaxCnt.at(type))	//���̉摜��\�����鎞��������
		{
			//this->Handle.end()�́A�Ō�̗v�f�̂P���̃C�e���[�^��Ԃ��̂ŁA-1���Ă���B
			if (this->Handle_itr == this->Handle[type].end() - 1)	//�C�e���[�^(�|�C���^)���Ō�̗v�f�̂Ƃ���
			{
				//�A�j���[�V���������[�v���Ȃ��Ȃ�
				if (this->IsAnimeLoop[type] == false)
				{
					this->IsAnimeStop[type] = true;	//�A�j���[�V�������~�߂�
				}

				//����̕`��ɔ����āA�擪�̉摜�ɖ߂��Ă���
				this->Handle_itr = this->Handle[type].begin();	//�C�e���[�^(�|�C���^)��v�f�̍ŏ��ɖ߂�
			}
			else
			{
				this->Handle_itr++;	//���̃C�e���[�^(�|�C���^)(���̉摜)�Ɉړ�����
			}

			this->ChangeCnt = 0;	//�J�E���g������
		}
		else
		{
			this->ChangeCnt++;	//�J�E���g�A�b�v
		}

	return;

}


//�ǉ�
/*
���@���Fconst char *�F�摜�̃f�B���N�g��
���@���Fconst char *�F�摜�̖��O
���@���Fint�F�摜�̑�������
���@���Fint�F�摜�̉������̕�����
���@���Fint�F�摜�̏c�����̕�����
���@���Fint�F�摜�̕������ꂽ���̑傫��
���@���Fint�F�摜�̕������ꂽ�c�̑傫��
���@���Fdouble�F���̉摜�ɕύX���鑬��
���@���Fbool�F�A�j���[�V���������[�v���邩�ǂ���
���@���Fint�FFPS�̑��x
*/
bool EFFECT::Add(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop,int fps_spd)
{
	this->IsAnimeLoop.push_back(IsLoop);		//�A�j���[�V�����̓��[�v����H
	this->IsAnimeStop.push_back(false);			//�A�j���[�V�����𓮂���

	//�摜��ǂݍ���
	std::string LoadfilePath;		//�摜�̃t�@�C���p�X���쐬
	LoadfilePath += dir;
	LoadfilePath += name;

	std::vector<int> work(SplitNumALL);	//�����ǂݍ��݂œ����n���h�����A�i�[����z��𑍕������ŏ�����

	//�摜�𕪊����ēǂݍ���
	LoadDivGraph(LoadfilePath.c_str(), SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, &work.front());
	this->Handle.push_back(work);	//�n���h�����i�[

	if (this->Handle.back().front() == -1)	//�摜���ǂݍ��߂Ȃ������Ƃ�
	{
		std::string ErrorMsg(EFFECT_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
		ErrorMsg += TEXT('\n');						//���s
		ErrorMsg += LoadfilePath;					//�摜�̃p�X

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * ��Ԃ�
			TEXT(EFFECT_ERROR_TTILE),
			MB_OK);

		return false;		//�ǂݍ��ݎ��s
	}

	this->Handle_itr = this->Handle.back().begin();		//�擪�v�f���C�e���[�^�ɐݒ�

	this->ChangeMaxCnt.push_back(fps_spd * changeSpeed);
	this->NextChangeSpeed.push_back(changeSpeed);		//���̉摜�ɕύX���鑬��

	//vector�̃�����������s��
	std::vector<int> v;			//���vector���쐬����
	work.swap(v);				//��ƒ��g�����ւ���

	return true;		//�ǂݍ��߂�

}

//�T�C�Y�ݒ�
void EFFECT::SetSize(void)
{
	//�G�t�F�N�g�̐��������[�v������
	for (int i = 0; i < this->Handle.size(); ++i)
	{
		GetGraphSize(this->Handle[i][0], &this->Width[i], &this->Height[i]);	//�T�C�Y�擾
	}
}
