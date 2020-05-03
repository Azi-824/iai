//main.cpp

//#################### �w�b�_�t�@�C���ǂݍ��� #######################
#include "main.hpp"
#include "GAMEMANEGER.hpp"

//########## �O���[�o���I�u�W�F�N�g ##########
GAMEMANEGER *gamemaneger = new GAMEMANEGER();	//gamemaneger����

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

	//�Q�[���f�[�^�̓ǂݍ��݊J�n
	if (gamemaneger->Load() == false) { return -1; }			//�Q�[���f�[�^�ǂݍ��ݎ��s

	//�Q�[���̃��C�����[�v
	while (gamemaneger->GameMainLoop())
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

//�Q�[�����Ŏg�p�����N���X���폜���鏈��
void Delete_Class()
{

	delete gamemaneger;		//gamemaneger�j��

	return;
}
