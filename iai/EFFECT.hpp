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

#define EFFECT_NAME_SLASH		R"(\slash.png)"					//�X���b�V���G�t�F�N�g�̉摜�̖��O

//###################### �}�N����`�F�G���[���b�Z�[�W ########################
#define EFFECT_ERROR_TTILE	"EFFECT_ERROR"						//�G���[�^�C�g��
#define EFFECT_ERROR_MSG	"�G�t�F�N�g���ǂݍ��߂܂���ł���"	//�G���[���b�Z�[�W

//###################### �}�N����` #################################

//********************** �T�C�Y ************************
#define EFFECT_SLASH_WIDTH		880	//������
#define EFFECT_SLASH_HEIGHT		640	//��������


//********************** ������ **************************
#define EFFECT_SLASH_YOKO_CNT		3	//��������
#define EFFECT_SLASH_TATE_CNT		3	//�c������

//************************ �������� **************************
#define EFFECT_SLASH_ALL_CNT	EFFECT_SLASH_YOKO_CNT * EFFECT_SLASH_TATE_CNT	//��������

//************************ �`�摬�x ***************************

#define EFFECT_SLASH_SPEED		0.02

//****************** ���̑� ***********************
#define INIT_VALUE		0	//�����l
#define FADE_MAX_CNT	60	//�t�F�[�h�����̃J�E���g�ő�l
#define TOUKA_MAX_VALUE	255	//���߂̍ő�l

//###################### �񋓌^ ##########################
enum EFFECT_KIND
{
	EFFECT_SLASH		//�X���b�V���G�t�F�N�g
};

//###################### �N���X��` ################################
class EFFECT
{
private:

	std::vector<std::vector<int>> Handle;				//�n���h��
	std::vector<std::vector<int>::iterator> Handle_itr;	//�n���h���̃C�e���[�^
	
	std::vector<int> Width;				//��
	std::vector<int> Height;			//����

	std::vector<double> NextChangeSpeed;		//�A�j���[�V������ύX���鑬��(�b)
	int ChangeCnt;								//�A�j���[�V��������t���[���̃J�E���g
	std::vector<int> ChangeMaxCnt;				//�A�j���[�V��������t���[���̍ő�l

	std::vector<bool> IsAnimeLoop;			//�A�j���[�V�����̓��[�v����H
	std::vector<bool> IsAnimeStop;			//�A�j���[�V�����̓X�g�b�v�������H

	bool IsDrawEnd;				//�`��I��������

	bool IsLoad;				//�ǂݍ��߂����H

	bool IsFadeout;				//�t�F�[�h�A�E�g�������s����
	bool IsFadein;				//�t�F�[�h�C���������s����

public:

	EFFECT(const char *, const char *, int, int, int, int, int, double, bool,int);	//�R���X�g���N�^	

	~EFFECT();					//�f�X�g���N�^

	int GetWidth(int);			//�����擾
	int GetHeight(int);			//�������擾

	bool GetIsLoad(void);		//�ǂݍ��߂��H

	bool GetIsAnimeStop(int);	//�A�j���[�V�����̓X�g�b�v���������擾

	bool GetIsDrawEnd();		//�`��I���������擾

	void SetIsDrawEnd(bool);	//�`��I���������ݒ�

	void ResetIsAnime(int);		//�A�j���[�V�������X�g�b�v�����������Z�b�g

	void Draw(int, int, int);	//�`��

	bool Add(const char *, const char *, int, int, int, int, int, double, bool, int);	//�G�t�F�N�g�ǉ�

	void SetSize();						//�T�C�Y�ݒ�

	void SetIsFadeout(bool);			//�t�F�[�h�A�E�g�����邩�ݒ�
	void SetIsFadein(bool);				//�t�F�[�h�C�������邩�ݒ�

	bool FadeOut(int,int,int,int);		//�t�F�[�h�A�E�g�G�t�F�N�g
	bool FadeIn(int, int, int, int);	//�t�F�[�h�C���G�t�F�N�g

};
