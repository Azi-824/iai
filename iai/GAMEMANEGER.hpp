//GAMEMANEGER.hpp
//�Q�[���̃V�X�e�����Ǘ�����N���X

#pragma once

//############### �w�b�_�t�@�C���ǂݍ��� ##################
#include "DxLib.h"
#include "FPS.hpp"
#include "KEYDOWN.hpp"
#include "IMAGE.hpp"
#include "PLAYER.hpp"
#include "ENEMY.hpp"

//############### �}�N����` ################
#define GAME_LEFT	  0		//��ʂ̉��̎n�_
#define GAME_TOP	  0		//��ʂ̏c�̎n�_
#define GAME_WIDTH	880		//��ʂ̉��̑傫��
#define GAME_HEIGHT	640		//��ʂ̏c�̑傫��

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

//�F�֌W
#define COLOR_RED	GetColor(255,0,0)		//�ԐF
#define COLOR_GREEN	GetColor(0,255,0)		//�ΐF
#define COLOR_BLUE	GetColor(0,0,255)		//�F
#define COLOR_WHITE GetColor(255,255,255)	//���F
#define COLOR_BLACK GetColor(0,0,0)			//���F

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
	IMAGE *back;				//�w�i�摜
	PLAYER *player;				//�v���C���[
	ENEMY *enemy;				//�G

	int NowScene;				//���݂̃V�[��
	bool IsLoad;				//�ǂݍ��݂��I�������

public:

	GAMEMANEGER();				//�R���X�g���N�^
	~GAMEMANEGER();				//�f�X�g���N�^

	bool Load();				//�Q�[���Ɏg�p����f�[�^�̓ǂݍ��ݏ���
	void SetSize();				//�摜�Ȃǂ̃T�C�Y���擾���A�ݒ肷��
	bool GameMainLoop();		//�Q�[���̃��C�����[�v

	void ProcesScene();			//�e�V�[���̏���


	//****************** �V�[���֌W *************************
	void Scene_Load();			//���[�h��ʂ̏���
	void Draw_Scene_Load();		//���[�h��ʂ̕`�揈��

	void Scene_Title();			//�^�C�g����ʂ̏���
	void Draw_Scene_Title();	//�^�C�g����ʂ̕`�揈��

	void Scene_Play();			//�v���C��ʂ̏���
	void Draw_Scene_Play();		//�v���C��ʂ̕`�揈��

	void Scene_End();			//�G���h��ʂ̏���
	void Draw_Scene_End();		//�G���h��ʂ̕`�揈��



};
