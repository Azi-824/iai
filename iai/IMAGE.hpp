/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* IMAGE.cpp     																				�@ */
/* �摜�N���X 																					�@ */

/*
�ǉ����@
�E�t�H���_���ƃt�@�C�������}�N����`����
�EAdd�������g�p���āA�摜��ǂݍ���
*/

#pragma once

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"
#include <string>
#include <vector>

//########## �}�N����`�F�摜�̃t�@�C���p�X�Ɩ��O ##########
#define IMG_DIR_BACK		R"(.\MY_IMG\Back)"				//�w�i�摜�̃t�@�C���̏ꏊ
#define IMG_DIR_MARK		R"(.\MY_IMG\Mark)"				//�}�[�N�摜�̃t�@�C���̏ꏊ

#define IMG_NAME_TITLE		R"(\Title.jpg)"					//�^�C�g����ʂ̔w�i�摜�̖��O
#define IMG_NAME_PLAY		R"(\Play.jpg)"					//�v���C��ʂ̔w�i�摜�̖��O

#define IMG_NAME_MARK		R"(\Mark.png)"					//�}�[�N�摜�̖��O

#define MARK_DRAW_X			350		//�}�[�N�摜�̕`��X�ʒu
#define MARK_DRAW_Y			100		//�}�[�N�摜�̕`��Y�ʒu

//########## �}�N����`�F�G���[���b�Z�[�W##########
#define IMAGE_ERROR_TITLE "IMAGE_ERROR"					//�G���[�^�C�g��
#define IMAGE_ERROR_MSG	"�摜���ǂݍ��߂܂���ł���"	//�G���[���b�Z�[�W

//########## �񋓌^ ################
enum BACK_IMAGE
{
	TITLE_BACK,		//�^�C�g����ʂ̔w�i�摜
	PLAY_BACK,		//�v���C��ʂ̔w�i�摜
	END_BACK		//�G���h��ʂ̔w�i�摜
};

//########## �N���X�̒�` ##########

class IMAGE
{
private:
	std::string FilePath;	//�p�X
	std::string FileName;	//���O

	std::vector<int> Handle;				//�n���h��

	std::vector<int> Width;					//��
	std::vector<int> Height;				//����

	int ImageKind;				//�ǂݍ��񂾉摜�̎��
	int Draw_Num;				//�`�悷��摜�̔ԍ�

	bool IsLoad;				//�ǂݍ��߂����H
	std::vector<bool> IsDraw;	//�`�悵�Ă悢��

public:
	IMAGE(const char *,const char *);	//�R���X�g���N�^
	virtual ~IMAGE();					//�f�X�g���N�^

	std::string GetFileName(void);	//���O���擾

	void SetSize(void);				//�T�C�Y���Z�b�g

	int GetWidth();		//�����擾
	int GetHeight();	//�������擾

	bool GetIsLoad(void);			//�ǂݍ��߂��H

	void Draw(int, int);		//�摜��`��

	bool AddImage(const char *, const char *);	//�摜��ǉ�
	void ChengeImage(int);						//�`�悷��摜��ύX

};

