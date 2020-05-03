//GAMEMANEGER.hpp
//�Q�[���̃V�X�e�����Ǘ�����N���X

#pragma once

//############### �w�b�_�t�@�C���ǂݍ��� ##################
#include "DxLib.h"
#include "FPS.hpp"
#include "KEYDOWN.hpp"

//############### �}�N����` ################
#define GAME_FPS_SPEED					   60

//�e�L�X�g�֌W
#define LOAD_TEXT	"NowLoading�c"		//���[�h��ʂ̃e�L�X�g
#define PUSH_TEXT	"PushEnter"			//�G���^�[�L�[�������A�̃e�L�X�g
#define TITLE_TEXT	"NowTitle"			//�^�C�g����ʂ̃e�L�X�g
#define PLAY_TEXT	"NowPlay"			//�v���C��ʂ̃e�L�X�g
#define END_TEXT	"NowEnd"			//�G���h��ʂ̃e�L�X�g

//���W�֌W
#define TEST_TEXT_X	30					//�e�X�g�p�̃e�L�X�g�`��X�ʒu
#define TEST_TEXT_Y	30					//�e�X�g�p�̃e�L�X�g�`��Y�ʒu

//############### �񋓌^ ################
enum GAME_SCENE
{
	SCENE_LOAD,			//���[�h�V�[��
	SCENE_TITLE,		//�^�C�g���V�[��
	SCENE_PLAY,			//�v���C�V�[��
	SCENE_END			//�G���h�V�[��
};

//############### �N���X��` ################
class GAMEMANEGER
{

private:

	FPS *fps;					//fps
	KEYDOWN *keydown;			//�L�[�{�[�h�֌W

	int NowScene;				//���݂̃V�[��
	bool IsLoad;				//�ǂݍ��݂��I�������

public:

	GAMEMANEGER();				//�R���X�g���N�^
	~GAMEMANEGER();				//�f�X�g���N�^

	bool Load();				//�Q�[���Ɏg�p����f�[�^�̓ǂݍ��ݏ���
	bool GameMainLoop();		//�Q�[���̃��C�����[�v

	bool ProcesScene();			//�e�V�[���̏���


	//****************** �V�[���֌W *************************
	bool Scene_Load();			//���[�h��ʂ̏���
	void Draw_Scene_Load();		//���[�h��ʂ̕`�揈��

	void Scene_Title();			//�^�C�g����ʂ̏���
	void Draw_Scene_Title();	//�^�C�g����ʂ̕`�揈��

	void Scene_Play();			//�v���C��ʂ̏���
	void Draw_Scene_Play();		//�v���C��ʂ̕`�揈��

	void Scene_End();			//�G���h��ʂ̏���
	void Draw_Scene_End();		//�G���h��ʂ̕`�揈��



};
