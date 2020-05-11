//EFFECT.hpp
//�G�t�F�N�g�N���X

/*
�G�t�F�N�g�ǉ����@
�E��{�́AANIMATION�N���X�Ɠ���
�E�I�u�W�F�N�g������́AAdd�������g�p���邱�ƂŁA�G�t�F�N�g�̒ǉ������邱�Ƃ��ł���
*/

#pragma once

//###################### �w�b�_�t�@�C���ǂݍ��� #########################
#include "DxLib.h"
#include <vector>
#include <string>
#include "FPS.hpp"

//###################### �}�N����`�F�t�@�C���p�X�A���O ######################
#define EFFECT_DIR				R"(.\MY_EFFECT)"				//�G�t�F�N�g�̉摜�t�@�C���̏ꏊ

#define EFFECT_NAME_START		R"(\start.png)"					//�J�n�G�t�F�N�g�̉摜�̖��O
#define EFFECT_NAME_SLASH		R"(\slash.png)"					//�X���b�V���G�t�F�N�g�̉摜�̖��O

//###################### �}�N����`�F�G���[���b�Z�[�W ########################
#define EFFECT_ERROR_TTILE	"EFFECT_ERROR"						//�G���[�^�C�g��
#define EFFECT_ERROR_MSG	"�G�t�F�N�g���ǂݍ��߂܂���ł���"	//�G���[���b�Z�[�W

//###################### �}�N����` #################################

//********************** �T�C�Y ************************
#define	EFFECT_START_WIDTH		880	//������
#define EFFECT_START_HEIGHT		640	//��������
#define EFFECT_SLASH_WIDTH		880	//������
#define EFFECT_SLASH_HEIGHT		640	//��������


//********************** ������ **************************
#define EFFECT_START_YOKO_CNT		1	//��������
#define EFFECT_START_TATE_CNT		5	//�c������

#define EFFECT_SLASH_YOKO_CNT		3	//��������
#define EFFECT_SLASH_TATE_CNT		3	//�c������

//************************ �������� **************************
#define EFFECT_START_ALL_CNT	EFFECT_START_YOKO_CNT * EFFECT_START_TATE_CNT	//��������

#define EFFECT_SLASH_ALL_CNT	EFFECT_SLASH_YOKO_CNT * EFFECT_SLASH_TATE_CNT	//��������

//************************ �`�摬�x ***************************
#define EFFECT_START_SPEED		0.05

#define EFFECT_SLASH_SPEED		0.02

#define INIT_VALUE	0	//�����l

//###################### �񋓌^ ##########################
enum EFFECT_KIND
{
	EFFECT_START,		//�X�^�[�g�G�t�F�N�g
	EFFECT_SLASH		//�X���b�V���G�t�F�N�g
};

//###################### �N���X��` ################################
class EFFECT
{
private:

	std::vector<std::vector<int>> Handle;				//�n���h��
	std::vector<int>::iterator Handle_itr;				//�n���h���̃C�e���[�^
	
	std::vector<int> Width;				//��
	std::vector<int> Height;			//����

	std::vector<double> NextChangeSpeed;		//�A�j���[�V������ύX���鑬��(�b)
	int ChangeCnt;								//�A�j���[�V��������t���[���̃J�E���g
	std::vector<int> ChangeMaxCnt;				//�A�j���[�V��������t���[���̍ő�l

	std::vector<bool> IsAnimeLoop;			//�A�j���[�V�����̓��[�v����H
	std::vector<bool> IsAnimeStop;			//�A�j���[�V�����̓X�g�b�v�������H

	bool IsDrawEnd;				//�`��I��������

	bool IsLoad;				//�ǂݍ��߂����H

public:

	EFFECT(const char *, const char *, int, int, int, int, int, double, bool,int);	//�R���X�g���N�^	

	~EFFECT();					//�f�X�g���N�^

	int GetWidth(int);				//�����擾
	int GetHeight(int);			//�������擾

	bool GetIsLoad(void);			//�ǂݍ��߂��H

	bool GetIsAnimeStop(int);		//�A�j���[�V�����̓X�g�b�v���������擾

	bool GetIsDrawEnd();		//�`��I���������擾

	void SetIsDrawEnd(bool);	//�`��I���������ݒ�

	void ResetIsAnime(int);		//�A�j���[�V�������X�g�b�v�����������Z�b�g

	void Draw(int, int, int);		//�`��

	bool Add(const char *, const char *, int, int, int, int, int, double, bool, int);	//�G�t�F�N�g�ǉ�

	void SetSize();				//�T�C�Y�ݒ�

};
