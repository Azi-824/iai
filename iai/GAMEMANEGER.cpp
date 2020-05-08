//GAMEMANEGER.cpp
//�Q�[���̃V�X�e�����Ǘ�����N���X

//############### �w�b�_�t�@�C���ǂݍ��� ################
#include "GAMEMANEGER.hpp"

//############### �N���X��` ################

//�R���X�g���N�^
GAMEMANEGER::GAMEMANEGER()
{
	//�I�u�W�F�N�g�̐���
	this->fps = new FPS(GAME_FPS_SPEED);	//FPS�N���X�̃I�u�W�F�N�g�𐶐�
	this->keydown = new KEYDOWN();			//KEYDOWN�N���X�̃I�u�W�F�N�g�𐶐�

	//�����o�[�ϐ�������
	this->NowScene = (int)SCENE_LOAD;		//�ŏ��̃V�[���́A���[�h���
	this->IsLoad = false;					//�ǂݍ��݁A������
	this->StartTime = 0;					//�v���J�n���ԏ�����
	this->WaitTime = 0;						//�҂����ԏ�����

	return;

}

//�f�X�g���N�^
GAMEMANEGER::~GAMEMANEGER()
{
	//�I�u�W�F�N�g�̔j��
	delete this->fps;		//fps�j��
	delete this->keydown;	//keydown�j��
	delete this->back;		//back�j��
	delete this->mark;		//mark�j��
	delete this->player;	//player�j��

	return;

}

//�Q�[�����Ŏg�p����f�[�^�̓ǂݍ��ݏ���
/*
�߂�l�Ftrue�F����
�߂�l�Ffalse�F�G���[�A�����I��
*/
bool GAMEMANEGER::Load()
{
	//�摜�֌W
	//�w�i�摜
	this->back = new IMAGE(IMG_DIR_BACK, IMG_NAME_TITLE);	//�w�i�摜���Ǘ�����I�u�W�F�N�g�𐶐�(�^�C�g����ʂ̉摜��ǂݍ���)
	if (this->back->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s
	if (this->back->AddImage(IMG_DIR_BACK, IMG_NAME_PLAY) == false) { return false; }		//�w�i�摜�ǉ�(�v���C���)
	//�}�[�N�摜
	this->mark = new IMAGE(IMG_DIR_MARK, IMG_NAME_MARK);	//�}�[�N�摜�𐶐�
	if (this->mark->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	//�v���C���[�֌W
	this->player = new PLAYER(IMG_DIR_PLAYER, IMG_NAME_PLAYER);		//�v���C���[����
	if (this->player->GetIsLoad() == false) { return false; }		//�ǂݍ��ݎ��s
	if (this->player->AddImage(IMG_DIR_PLAYER, IMG_NAME_PLAYER_ACT) == false) { return false; }	//�摜�ǉ�

	//�G�֌W
	this->enemy = new ENEMY(IMG_DIR_ENEMY, IMG_NAME_ENEMY);		//�G����
	if (this->enemy->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s
	if (this->enemy->AddImage(IMG_DIR_ENEMY, IMG_NAME_ENEMY_ACT) == false) { return false; }	//�摜�ǉ�

	return true;	//�ǂݍ��ݐ���
}

//�摜�Ȃǂ̃T�C�Y���擾���A�ݒ肷��
void GAMEMANEGER::SetSize()
{
	this->back->SetSize();	//�w�i�摜�A�T�C�Y�ݒ�
	this->mark->SetSize();	//�}�[�N�摜�T�C�Y�ݒ�

	return;
}

//�����ݒ������
void GAMEMANEGER::SetInit()
{

	this->SetSize();			//�T�C�Y�ݒ�

	this->player->SetInit();	//�v���C���[�̏����ݒ�
	this->enemy->SetInit();		//�G�̏����ݒ�

}

//�Q�[���̃��C�����[�v
/*
�߂�l�Ftrue�F����
�߂�l�Ffalse�F�G���[�A�����I��
*/
bool GAMEMANEGER::GameMainLoop()
{
	if (ProcessMessage() != 0) { return false; }	//���b�Z�[�W�����̌��ʂ��G���[�̂Ƃ��A�����I��

	if (ClearDrawScreen() != 0) { return false; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

	this->keydown->KeyDownUpdate();	//�L�[�̓��͏�Ԃ��X�V����

	this->fps->Update();		//FPS�̏���[�X�V]

	//�����������Q�[���̃V�[���������灥��������

	this->ProcesScene();		//�e�V�[���̏���

	//�����������Q�[���̃V�[�������܂Ł���������

	this->fps->Draw(0, 0);		//FPS�`��

	ScreenFlip();				//���j�^�̃��t���b�V�����[�g�̑����ŗ���ʂ��ĕ`��

	this->fps->Wait();			//FPS�̏���[�҂�]

	return true;				//����

}

//�e�V�[���̏���
void GAMEMANEGER::ProcesScene()
{
	switch (this->NowScene)		//���݂̃V�[���̕`�揈�������s
	{

	case (int)SCENE_LOAD:	//���[�h��ʂ̂Ƃ�

		this->Draw_Scene_Load();	//���[�h��ʂ̕`�揈��

		this->Scene_Load();			//���[�h��ʂ̏���

		break;				//���[�h��ʂ̂Ƃ������܂�

	case (int)SCENE_TITLE:	//�^�C�g����ʂ̂Ƃ�

		this->Draw_Scene_Title();	//�`��

		this->Scene_Title();		//����

		break;				//�^�C�g����ʂ̂Ƃ������܂�

	case (int)SCENE_PLAY:	//�v���C��ʂ̂Ƃ�

		this->Draw_Scene_Play();	//�`��

		this->Scene_Play();		//����

		break;				//�v���C��ʂ̂Ƃ������܂�

	case (int)SCENE_END:	//�G���h��ʂ̂Ƃ�

		this->Draw_Scene_End();	//�`��

		this->Scene_End();		//����

		break;				//�G���h��ʂ̂Ƃ������܂�

	default:
		break;
	}

	return;	

}

//***************************** �V�[�����̏��� ********************************
//���[�h��ʂ̏���
void GAMEMANEGER::Scene_Load()
{
	if (this->IsLoad)	//�ǂݍ��݂��������Ă�����
	{
		if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//�G���^�[�L�[�������ꂽ��
		{
			this->NowScene = (int)SCENE_TITLE;	//�^�C�g����ʂ�
		}
	}

	if (GetASyncLoadNum() == 0)	//�񓯊��œǂݍ���ł��鏈�����I�������
	{

		SetUseASyncLoadFlag(FALSE);	//�����ǂݍ��݂ɐݒ�

		this->SetInit();			//�����ݒ�

		this->IsLoad = true;		//�ǂݍ��݊���
	}

	return;		
}

//���[�h��ʂ̕`�揈��
void GAMEMANEGER::Draw_Scene_Load()
{

	if (IsLoad)	//�ǂݍ��݂�����������
	{
		DrawString(TEST_TEXT_X, TEST_TEXT_Y, PUSH_TEXT, COLOR_WHITE);	//�v�b�V���A�̃e�L�X�g��`��
	}
	else		//�������Ă��Ȃ����
	{
		DrawString(TEST_TEXT_X, TEST_TEXT_Y, LOAD_TEXT, COLOR_WHITE);	//�ǂݍ��ݒ��̃e�L�X�g��`��
	}

	return;
}

//�^�C�g����ʂ̏���
void GAMEMANEGER::Scene_Title()
{

	this->back->ChengeImage((int)TITLE_BACK);	//�w�i�摜�ύX

	//���Z�b�g����
	this->player->ChengeImage((int)PLAYER_IMG_NORMAL);		//�`�悷��v���C���[�̉摜��ʏ펞�̉摜�ɕύX
	this->enemy->ChengeImage((int)ENEMY_IMG_NORMAL);		//�`�悷��G�̉摜��ʏ펞�̉摜�ɕύX

	this->player->SetImagePos(PLAYER_START_X, PLAYER_START_Y);	//�v���C���[�̕`��ʒu��������
	this->enemy->SetImagePos(ENEMY_START_X, ENEMY_START_Y);		//�G�̕`��ʒu��������

	if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//�G���^�[�L�[�������ꂽ��
	{
		this->NowScene = (int)SCENE_PLAY;	//�v���C��ʂ�
		this->StartTime = GetNowCount();	//�v���J�n���Ԏ擾
		this->WaitTime = GetRand((GAME_START_WAITTIME_MAX / 2)) + GAME_START_WAITTIME_MIN;	//�҂����Ԃ�ݒ�
	}

	return;
}

//�^�C�g����ʂ̕`�揈��
void GAMEMANEGER::Draw_Scene_Title()
{

	this->back->Draw(GAME_LEFT,GAME_TOP);	//�w�i�`��

	DrawString(TEST_TEXT_X, TEST_TEXT_Y, TITLE_TEXT, COLOR_WHITE);	//�e�X�g�p�̃e�L�X�g��`��

	return;
}

//�v���C��ʂ̏���
void GAMEMANEGER::Scene_Play()
{


	this->back->ChengeImage((int)PLAY_BACK);	//�w�i�摜�ύX

	if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//�G���^�[�L�[�������ꂽ��
	{
		this->NowScene = (int)SCENE_END;	//�G���h��ʂ�
	}
	else if (this->keydown->IsKeyDownOne(KEY_INPUT_SPACE))	//�X�y�[�X�L�[�������ꂽ��
	{
		this->player->ChengeImage((int)PLAYER_IMG_ACT);		//�`�悷��v���C���[�̉摜���A�N�V������̉摜�ɕύX
		this->enemy->ChengeImage((int)ENEMY_IMG_ACT);		//�`�悷��G�̉摜���A�N�V������̉摜�ɕύX
	}

	return;
}

//�v���C��ʂ̕`�揈��
void GAMEMANEGER::Draw_Scene_Play()
{

	this->back->Draw(GAME_LEFT, GAME_TOP);	//�w�i�摜�`��

	this->player->Draw();		//�v���C���[�`��
	this->enemy->Draw();		//�G�`��

	if (this->WaitStartTime())	//�X�^�[�g���Ԃ܂ő҂�
	{
		this->mark->Draw(MARK_DRAW_X, MARK_DRAW_Y);	//�}�[�N�`��
	}

	DrawString(TEST_TEXT_X, TEST_TEXT_Y, PLAY_TEXT, COLOR_WHITE);	//�e�X�g�p�̃e�L�X�g��`��

	return;
}

//�G���h��ʂ̏���
void GAMEMANEGER::Scene_End()
{

	if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//�G���^�[�L�[�������ꂽ��
	{
		this->NowScene = (int)SCENE_TITLE;	//�^�C�g����ʂ�
	}

	return;
}

//�G���h��ʂ̕`�揈��
void GAMEMANEGER::Draw_Scene_End()
{

	DrawString(TEST_TEXT_X, TEST_TEXT_Y, END_TEXT, COLOR_WHITE);	//�e�X�g�p�̃e�L�X�g��`��

	return;
}


//******************** �v���C��ʂŎg�p���鏈���֌W ***********************
//�X�^�[�g���Ԃ܂ő҂�
bool GAMEMANEGER::WaitStartTime()
{

	if ((GetNowCount() - this->StartTime) / 1000 < this->WaitTime)	//�҂����Ԃ��߂��Ă��Ȃ����
	{
		return false;
	}
	else 			//�҂����Ԃ��߂�����
	{
		return true;
	}
}
