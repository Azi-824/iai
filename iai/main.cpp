//main.cpp

//#################### �w�b�_�t�@�C���ǂݍ��� #######################
#include "main.hpp"
#include "FPS.hpp"
#include "KEYDOWN.hpp"

//########## �O���[�o���I�u�W�F�N�g ##########
FPS *fps = new FPS(GAME_FPS_SPEED);			//FPS�N���X�̃I�u�W�F�N�g�𐶐�
KEYDOWN *keydown = new KEYDOWN();			//KEYDOWN�N���X�̃I�u�W�F�N�g�𐶐�

//######### �O���[�o���ϐ� ############
int NowScene = (int)SCENE_LOAD;	//���݂̃V�[��(�ŏ��̓��[�h��ʂ���)
bool IsLoad = false;			//�ǂݍ��݂��I��������i�ŏ��͓ǂݍ��߂Ă��Ȃ��j

//########## �v���O�����ōŏ��Ɏ��s�����֐� ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(GAME_WINDOW_MODECHANGE);					//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);			//�w��̐��l�ŉ�ʂ�\������

	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);				//�^�C�g���o�[����

	SetMainWindowText(TEXT(GAME_WINDOW_NAME));					//�^�C�g���̕���

	SetAlwaysRunFlag(TRUE);										//��A�N�e�B�u�ɐݒ�

	if (DxLib_Init() == -1) { return -1; }						//�c�w���C�u��������������

	SetDrawScreen(DX_SCREEN_BACK);								//Draw�n�֐��͗���ʂɕ`��

	//�Q�[���̃��C�����[�v
	while (GameMainLoop())
	{
		/*
		���[�v���ňُ킪��������܂Ŗ������[�v
		�Q�[���I����G���[�������������烋�[�v�I��
		*/
	}

	Delete_Class();			//�g�p�����N���X��j��

	DxLib_End();			//�c�w���C�u�����g�p�̏I������

	return 0;
}

//�ǂݍ��ݏ���
/*
�߂�l�Ftrue�F����
�߂�l�Ffalse�F�G���[�A�����I��
*/
bool Load()
{
	return true;	//�ǂݍ��ݐ���
}

//�������[�v���̃Q�[������
/*
�߂�l�Ftrue�F����
�߂�l�Ffalse�F�G���[�A�����I��
*/
bool GameMainLoop()
{
	if (ProcessMessage() != 0) { return false; }	//���b�Z�[�W�����̌��ʂ��G���[�̂Ƃ��A�����I��

	if (ClearDrawScreen() != 0) { return false; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

	keydown->KeyDownUpdate();	//�L�[�̓��͏�Ԃ��X�V����

	fps->Update();				//FPS�̏���[�X�V]

	//�����������Q�[���̃V�[���������灥��������

	ProcesScene();				//�e�V�[���̏���

	//�����������Q�[���̃V�[�������܂Ł���������

	fps->Draw(0,0);				//FPS�`��

	ScreenFlip();				//���j�^�̃��t���b�V�����[�g�̑����ŗ���ʂ��ĕ`��

	fps->Wait();				//FPS�̏���[�҂�]

	return true;				//����

}

//�Q�[�����Ŏg�p�����N���X���폜���鏈��
void Delete_Class()
{

	delete fps;			//fps�j��
	delete keydown;		//keydown�j��

	return;
}

//�e�V�[���̏���
bool ProcesScene()
{
	switch (NowScene)		//���݂̃V�[���̕`�揈�������s
	{

	case (int)SCENE_LOAD:	//���[�h��ʂ̂Ƃ�

		Draw_Scene_Load();	//���[�h��ʂ̕`�揈��

		return Scene_Load();//���[�h��ʂ̏���

		break;				//���[�h��ʂ̂Ƃ������܂�

	case (int)SCENE_TITLE:	//�^�C�g����ʂ̂Ƃ�

		Draw_Scene_Title();	//�`��

		Scene_Title();		//����

		break;				//�^�C�g����ʂ̂Ƃ������܂�

	case (int)SCENE_PLAY:	//�v���C��ʂ̂Ƃ�

		Draw_Scene_Play();	//�`��

		Scene_Play();		//����

		break;				//�v���C��ʂ̂Ƃ������܂�

	case (int)SCENE_END:	//�G���h��ʂ̂Ƃ�

		Draw_Scene_End();	//�`��

		Scene_End();		//����

		break;				//�G���h��ʂ̂Ƃ������܂�

	default:
		break;
	}

	return true;	//�ʏ�

}


//���[�h��ʂ̏���
/*
�߂�l�Ftrue�F����
�߂�l�Ffalse�F�G���[�A�����I��
*/
bool Scene_Load()
{
	if (IsLoad)	//�ǂݍ��݂��������Ă�����
	{
		if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//�G���^�[�L�[�������ꂽ��
		{
			NowScene = (int)SCENE_TITLE;	//�^�C�g����ʂ�
		}
	}

	if (GetASyncLoadNum() == 0)	//�񓯊��œǂݍ���ł��鏈�����I�������
	{

		SetUseASyncLoadFlag(FALSE);		//�����ǂݍ��݂ɐݒ�

		IsLoad = true;	//�ǂݍ��݊���
	}

	return Load();		//�ǂݍ��ݏ���
}

//���[�h��ʂ̕`�揈��
void Draw_Scene_Load()
{

	if (IsLoad)	//�ǂݍ��݂�����������
	{
		DrawString(TEST_TEXT_X, TEST_TEXT_Y, PUSH_TEXT, GetColor(255, 255, 255));	//�v�b�V���A�̃e�L�X�g��`��
	}
	else		//�������Ă��Ȃ����
	{
		DrawString(TEST_TEXT_X, TEST_TEXT_Y, LOAD_TEXT, GetColor(255, 255, 255));	//�ǂݍ��ݒ��̃e�L�X�g��`��
	}

	return;
}

//�^�C�g����ʂ̏���
void Scene_Title()
{

	if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//�G���^�[�L�[�������ꂽ��
	{
		NowScene = (int)SCENE_PLAY;	//�v���C��ʂ�
	}

	return;
}

//�^�C�g����ʂ̕`�揈��
void Draw_Scene_Title()
{

	DrawString(TEST_TEXT_X, TEST_TEXT_Y, TITLE_TEXT, GetColor(255, 255, 255));	//�e�X�g�p�̃e�L�X�g��`��

	return;
}

//�v���C��ʂ̏���
void Scene_Play()
{

	if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//�G���^�[�L�[�������ꂽ��
	{
		NowScene = (int)SCENE_END;	//�G���h��ʂ�
	}

	return;
}

//�v���C��ʂ̕`�揈��
void Draw_Scene_Play()
{

	DrawString(TEST_TEXT_X, TEST_TEXT_Y, PLAY_TEXT, GetColor(255, 255, 255));	//�e�X�g�p�̃e�L�X�g��`��

	return;
}

//�G���h��ʂ̏���
void Scene_End()
{

	if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//�G���^�[�L�[�������ꂽ��
	{
		NowScene = (int)SCENE_TITLE;	//�^�C�g����ʂ�
	}

	return;
}

//�G���h��ʂ̕`�揈��
void Draw_Scene_End()
{

	DrawString(TEST_TEXT_X, TEST_TEXT_Y, END_TEXT, GetColor(255, 255, 255));	//�e�X�g�p�̃e�L�X�g��`��

	return;
}
