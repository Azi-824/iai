//MUSIC.hpp
//���y�p�N���X

/*
�ǉ����@
�E�t�H���_���A�t�@�C�������}�N����`����
�E�ǉ��������̎�ނ��ƂɁA�񋓌^�ɒǉ�����
�@��F�퓬�Ŏg�p����SE��ǉ������ꍇ
    �@BT_SE_TYPE�ɒǉ�����
�EAdd�������g�p���āASE��BGM��ǉ����邱�Ƃ��ł���
*/

#pragma once

//##################### �w�b�_�t�@�C���ǂݍ��� #######################
#include "DxLib.h"
#include <string>
#include <vector>

//##################### �}�N����`�F�t�@�C���p�X�A���O ###################
#define MUSIC_DIR_SE		R"(.\MY_MUSIC\SE)"			//SE�̃t�@�C����

#define SE_NAME_GAMESTART	R"(\gamestart.mp3)"		//�Q�[���X�[�^�g��SE�̖��O
#define SE_NAME_GAMEOVER	R"(\gameover.mp3)"		//�Q�[���I�[�o�[��SE�̖��O
#define SE_NAME_TEXT_SE		R"(\text_se.mp3)"		//�e�L�X�g�\����SE�̖��O

//##################### �}�N����`�F�G���[���b�Z�[�W ######################
#define MUSIC_ERROR_TITLE "MUSIC_ERROR"					//�G���[�^�C�g��
#define MUSIC_ERROR_MSG	"�����ǂݍ��߂܂���ł���"		//�G���[���b�Z�[�W

//##################### �}�N����` ##########################
#define VOLUME_MAX		255	//���ʂ̍ő�l

//##################### �񋓌^ #########################
enum SE_TYPE
{
	SE_TYPE_GAMESTART,		//�Q�[���X�^�[�g
	SE_TYPE_GAMEOVER,		//�Q�[���I�[�o�[
	SE_TYPE_TEXT			//�e�L�X�g�\��
};

//##################### �N���X��` ############################
class MUSIC
{
private:

	std::string FilePath;		//�t�@�C���p�X
	std::string FileName;		//���O

	std::vector<int> Handle;	//�n���h��
	int PlayType;				//���̍Đ����@

	bool IsLoad;				//�ǂݍ��߂���
	std::vector<bool> IsPlayed;	//�Đ��ς݂�


public:

	MUSIC(const char *, const char *);		//�R���X�g���N�^

	~MUSIC();								//�f�X�g���N�^

	bool GetIsLoad();						//�ǂݍ��߂������擾����
	bool GetIsPlay(int);					//�����Đ�����Ă��邩�擾����

	void ChengePlayType(int);				//���̍Đ����@��ύX����
	void ChengeVolume(double,int);			//���ʂ�ύX����

	void Play(int);							//�����Đ�����
	void PlayOne(int);						//�����Đ�����(1�񂾂�)

	void PlayReset(int);					//�Đ��ς݂��ǂ��������Z�b�g����

	void Stop();							//�����~�߂�(�S��)
	void Stop(int);							//�����~�߂�(�w�肳�ꂽ���̂���)

	bool Add(const char*, const char*);		//����ǉ�����

};
