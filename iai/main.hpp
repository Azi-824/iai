//main.hpp

#pragma once


//#################### �w�b�_�t�@�C���ǂݍ��� #####################
#include "DxLib.h"

//########## �}�N����` ##########
#define GAME_LEFT	  0		//��ʂ̉��̎n�_
#define GAME_TOP	  0		//��ʂ̏c�̎n�_
#define GAME_WIDTH	880		//��ʂ̉��̑傫��
#define GAME_HEIGHT	640		//��ʂ̏c�̑傫��
#define GAME_COLOR	32		//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_NAME	"������"			//�E�B���h�E�̃^�C�g��
#define GAME_WINDOW_MODECHANGE	TRUE			//TRUE�F�E�B���h�E���[�h / FALSE�F�t���X�N���[��

#define SET_WINDOW_ST_MODE_DEFAULT			0	//�f�t�H���g
#define SET_WINDOW_ST_MODE_TITLE_NONE		1	//�^�C�g���o�[�Ȃ�
#define SET_WINDOW_ST_MODE_TITLE_FLAME_NONE	2	//�^�C�g���o�[�ƃt���[���Ȃ�
#define SET_WINDOW_ST_MODE_FLAME_NONE		3	//�t���[���Ȃ�

#define GAME_FPS_SPEED					   60

//�e�L�X�g�֌W
#define LOAD_TEXT	"NowLoading�c"		//���[�h��ʂ̃e�L�X�g
#define TITLE_TEXT	"NowTitle"			//�^�C�g����ʂ̃e�L�X�g
#define PLAY_TEXT	"NowPlay"			//�v���C��ʂ̃e�L�X�g
#define END_TEXT	"NowEnd"			//�G���h��ʂ̃e�L�X�g

//���W�֌W
#define TEST_TEXT_X	30					//�e�X�g�p�̃e�L�X�g�`��X�ʒu
#define TEST_TEXT_Y	30					//�e�X�g�p�̃e�L�X�g�`��Y�ʒu

//########### �񋓌^ ################
enum GAME_SCENE
{
	SCENE_LOAD,			//���[�h�V�[��
	SCENE_TITLE,		//�^�C�g���V�[��
	SCENE_PLAY,			//�v���C�V�[��
	SCENE_END			//�G���h�V�[��
};

//############## �v���g�^�C�v�錾 #############
bool Load();				//�ǂݍ��ݏ���
bool GameMainLoop();		//�������[�v���̃Q�[������
void Delete_Class();		//�N���X���폜���鏈��

bool ProcesScene();			//�e�V�[���̏���

bool Scene_Load();			//���[�h��ʂ̏���
void Draw_Scene_Load();		//���[�h��ʂ̕`�揈��

void Scene_Title();			//�^�C�g����ʂ̏���
void Draw_Scene_Title();	//�^�C�g����ʂ̕`�揈��

void Scene_Play();			//�v���C��ʂ̏���
void Draw_Scene_Play();		//�v���C��ʂ̕`�揈��

void Scene_End();			//�G���h��ʂ̏���
void Draw_Scene_End();		//�G���h��ʂ̕`�揈��

