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
	//�����o�[�ϐ�������
	this->IsLoad = false;			//�ǂݍ��߂����H
	this->IsDrawEnd = false;		//�`��I��������?
	this->IsFadein = false;			//�t�F�[�h�C���������s��Ȃ�
	this->IsFadeout = false;		//�t�F�[�h�A�E�g�������s��Ȃ�
	this->Width.push_back(0);		//������������
	this->Height.push_back(0);		//������������

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

	this->Handle_itr.push_back(this->Handle.front().begin());	//�擪�v�f���C�e���[�^�ɐݒ�

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

	std::vector<std::vector<int>::iterator> v8;
	this->Handle_itr.swap(v8);

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

		if (this->IsAnimeStop[type] == false)	//�A�j���[�V�������X�g�b�v�����Ȃ��Ȃ�
		{
			DrawGraph(x, y, *this->Handle_itr.at(type), TRUE);	//�C�e���[�^(�|�C���^)���g�p���ĕ`��
		}
		else
		{
			this->IsDrawEnd = true;		//�`��I��
		}

		if (this->ChangeCnt == this->ChangeMaxCnt.at(type))	//���̉摜��\�����鎞��������
		{
			//this->Handle.end()�́A�Ō�̗v�f�̂P���̃C�e���[�^��Ԃ��̂ŁA-1���Ă���B
			if (this->Handle_itr.at(type) == this->Handle[type].end() - 1)	//�C�e���[�^(�|�C���^)���Ō�̗v�f�̂Ƃ���
			{
				//�A�j���[�V���������[�v���Ȃ��Ȃ�
				if (this->IsAnimeLoop[type] == false)
				{
					this->IsAnimeStop[type] = true;	//�A�j���[�V�������~�߂�
				}

				//����̕`��ɔ����āA�擪�̉摜�ɖ߂��Ă���
				this->Handle_itr.at(type) = this->Handle[type].begin();	//�C�e���[�^(�|�C���^)��v�f�̍ŏ��ɖ߂�
			}
			else
			{
				++this->Handle_itr.at(type);	//���̃C�e���[�^(�|�C���^)(���̉摜)�Ɉړ�����
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
	this->Width.push_back(0);					//������������
	this->Height.push_back(0);					//������������

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

	this->Handle_itr.push_back(this->Handle.back().begin());		//�擪�v�f���C�e���[�^�ɐݒ�

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

//�t�F�[�h�A�E�g�����邩�ݒ�
void EFFECT::SetIsFadeout(bool isfadeout)
{
	this->IsFadeout = isfadeout;
	return;
}

//�t�F�[�h�C�������邩�ݒ�
void EFFECT::SetIsFadein(bool isfadein)
{
	this->IsFadein = isfadein;
	return;
}

//�t�F�[�h�A�E�g�G�t�F�N�g
//�����Fint�F���߂��������͈͂�X�ʒu
//�����Fint�F���߂��������͈͂�Y�ʒu
//�����Fint�F���߂��������͈͂̉���
//�����Fint�F���߂��������͈͂̍���
//�߂�l�Fbool�F�t�F�[�h�A�E�g���I��������
//true�F�I���Ffalse�F�I�����Ă��Ȃ�
bool EFFECT::FadeOut(int x,int y,int width,int height)
{

	static int cnt = 0;				//�J�E���g�p
	static bool end_flg = false;	//�t�F�[�h�I���t���O

	if (this->IsFadeout)		//�t�F�[�h�A�E�g����Ƃ�
	{

		if (!end_flg)	//�t�F�[�h�A�E�g�I�����Ă��Ȃ����
		{
			//60�t���[�����A�҂�
			if (cnt < FADE_MAX_CNT)
			{
				++cnt;	//�J�E���g�A�b�v
			}
			else
			{
				end_flg = true;	//�t�F�[�h�I��
			}

			//�t�F�[�h�A�E�g�̏���
			double ToukaPercent = cnt / (double)FADE_MAX_CNT;						//����%���v�Z
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, ToukaPercent * TOUKA_MAX_VALUE);	//���߂�����
			DrawBox(x, y, width, height, GetColor(0, 0, 0), TRUE);					//�^���Âȉ�ʂɂ���
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);								//���߂���߂�

		}
		else if (end_flg)	//�t�F�[�h�A�E�g�I��������
		{
			this->IsFadeout = false;	//�t�F�[�h�A�E�g���Ȃ�
			cnt = 0;			//�J�E���g���Z�b�g
			end_flg = false;	//�I���t���O���Z�b�g
		}

	}
	else		//�t�F�[�h�A�E�g�����Ȃ���
	{
		cnt = 0;			//�J�E���g���Z�b�g
		end_flg = false;	//�I���t���O���Z�b�g
		return true;		//�t�F�[�h�A�E�g�͏I����Ă���
	}

	return end_flg;

}

//�t�F�[�h�C���G�t�F�N�g
//�����Fint�F���߂��������͈͂�X�ʒu
//�����Fint�F���߂��������͈͂�Y�ʒu
//�����Fint�F���߂��������͈͂̉���
//�����Fint�F���߂��������͈͂̍���
//�߂�l�Fbool�F�t�F�[�h�C�����I��������
//true�F�I���Ffalse�F�I�����Ă��Ȃ�
bool EFFECT::FadeIn(int x, int y, int width, int height)
{
	static int cnt = FADE_MAX_CNT;	//�J�E���g�p
	static bool end_flg = false;	//�t�F�[�h�I���t���O

	if (this->IsFadein)		//�t�F�[�h�C������Ƃ�
	{

		if (!end_flg)	//�t�F�[�h�C���I�����Ă��Ȃ����
		{
			//60�t���[�����A�҂�
			if (cnt > 0)
			{
				--cnt;	//�J�E���g�_�E��
			}
			else
			{
				end_flg = true;	//�t�F�[�h�I��
			}

			//�t�F�[�h�C���̏���
			double ToukaPercent = cnt / (double)FADE_MAX_CNT;						//����%���v�Z
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, ToukaPercent * TOUKA_MAX_VALUE);	//���߂�����
			DrawBox(x, y, width, height, GetColor(0, 0, 0), TRUE);					//�^���Âȉ�ʂɂ���
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);								//���߂���߂�

		}
		else if (end_flg)	//�t�F�[�h�C���I��������
		{
			cnt = FADE_MAX_CNT;		//�J�E���g���Z�b�g
			end_flg = false;		//�G���h�t���O���Z�b�g
			this->IsFadein = false;	//�t�F�[�h�C�����Ȃ�
		}

	}
	else		//�t�F�[�h�C�������Ȃ���
	{
		cnt = FADE_MAX_CNT;	//�J�E���g���Z�b�g
		end_flg = false;	//�I���t���O���Z�b�g
		return true;		//�t�F�[�h�C���͏I����Ă���
	}

	return end_flg;

}

