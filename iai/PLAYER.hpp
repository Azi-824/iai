//PLAYER.hpp
//�v���C���[���Ǘ�����N���X

#pragma once

//############## �w�b�_�t�@�C���ǂݍ��� ####################
#include "DxLib.h"
#include "CHARACTOR.hpp"

//############## �}�N����` #######################
#define IMG_DIR_PLAYER		R"(.\MY_IMG\Player)"		//�v���C���[�֌W�̉摜�f�B���N�g��

#define IMG_NAME_PLAYER		R"(\Player.png)"			//�v���C���[�̉摜�̖��O
#define IMG_NAME_PLAYER_ACT	R"(\Player_2.png)"			//�A�N�V������̃v���C���[�̉摜�̖��O

#define PLAYER_START_X		50		//�v���C���[�̕`��J�nX�ʒu
#define PLAYER_START_Y		250		//�v���C���[�̕`��J�nY�ʒu
#define PLAYER_AFTER_X		500		//�v���C���[�̕`��X�ʒu�i�A�N�V������j
#define PLAYER_AFTER_Y		250		//�v���C���[�̕`��Y�ʒu�i�A�N�V������j

//############### �񋓌^ ####################
enum PLAYER_IMAGE
{
	PLAYER_IMG_NORMAL,		//�ʏ펞�̉摜
	PLAYER_IMG_ACT			//�A�N�V������̉摜
};

enum PLAYER_RESULT
{
	RESULT_WIN,			//�v���C���[������
	RESULT_LOSE,		//�v���C���[���s�k
	RESULT_DRAW,		//��������
	RESULT_OTETUKI,		//����t��
	RESULT_NONE = -1	//�����l
};

//############## �N���X��` #######################
class PLAYER : public CHARACTOR		//�L�����N�^�[�N���X���p��
{

private:

	int WinNum;		//������
	double PushTime;//�L�[�{�[�h�������܂łɂ�����������
	int Result;		//����

public:

	PLAYER(const char *,const char *);		//�R���X�g���N�^
	~PLAYER();								//�f�X�g���N�^

	void IncreaseWinNum();		//�������𑝂₷
	int GetWinNum();			//���������擾
	void ResetWinNum();			//�����������Z�b�g

	void SetPushTime(double);	//�����܂łɂ����������Ԃ�ݒ�
	double GetPushTime();		//�����܂łɂ����������Ԃ��擾

	void SetResult(int);		//���ʂ�ݒ�
	int GetResult();			//���ʂ��擾

};
