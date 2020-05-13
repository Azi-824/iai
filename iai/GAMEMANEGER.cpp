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
	this->GameStartFlg = false;				//�Q�[���n�܂��Ă��Ȃ��B
	this->Play_NowStage = (int)PLAY_STAGE_TEXT_DRAW;	//�v���C�V�[���̌��݂̒i�K��������
	this->PushFlg = false;					//�L�[�����Ă��Ȃ�

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
	delete this->enemy;		//enemy�j��
	delete this->se;		//se�j��
	delete this->bgm;		//bgm�j��
	delete this->effect;	//effect�j��
	delete this->font;		//font�j��

	return;

}

//�Q�[�����Ŏg�p����f�[�^�̓ǂݍ��ݏ���
/*
�߂�l�Ftrue�F����
�߂�l�Ffalse�F�G���[�A�����I��
*/
bool GAMEMANEGER::Load()
{

	//�t�H���g�֌W
	this->font = new FONT(FONT_DIR, FONT_FILE_NAME, FONT_NAME);		//�t�H���g���Ǘ�����I�u�W�F�N�g�𐶐�
	if (this->font->GetIsLoad() == false) { return false; }			//�ǂݍ��ݎ��s

	//�摜�֌W
	//�w�i�摜
	this->back = new IMAGE(IMG_DIR_BACK, IMG_NAME_TITLE);	//�w�i�摜���Ǘ�����I�u�W�F�N�g�𐶐�(�^�C�g����ʂ̉摜��ǂݍ���)
	if (this->back->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s
	if (this->back->AddImage(IMG_DIR_BACK, IMG_NAME_PLAY) == false) { return false; }		//�w�i�摜�ǉ�(�v���C���)
	//�}�[�N�摜
	this->mark = new IMAGE(IMG_DIR_MARK, IMG_NAME_MARK);	//�}�[�N�摜�𐶐�
	if (this->mark->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s
	this->mark->SetIsDraw(false);							//�ŏ��͕`�悵�Ă͂����Ȃ�

	//�v���C���[�֌W
	this->player = new PLAYER(IMG_DIR_PLAYER, IMG_NAME_PLAYER);		//�v���C���[����
	if (this->player->GetIsLoad() == false) { return false; }		//�ǂݍ��ݎ��s
	if (this->player->AddImage(IMG_DIR_PLAYER, IMG_NAME_PLAYER_ACT) == false) { return false; }	//�摜�ǉ�
	//�ʒu����
	this->player->SetImagePos(PLAYER_START_X, PLAYER_START_Y);	//�v���C���[�̕`��ʒu��������

	//�G�֌W
	this->enemy = new ENEMY(IMG_DIR_ENEMY, IMG_NAME_ENEMY);		//�G����
	if (this->enemy->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s
	if (this->enemy->AddImage(IMG_DIR_ENEMY, IMG_NAME_ENEMY_ACT) == false) { return false; }	//�摜�ǉ�
	//�ʒu����
	this->enemy->SetImagePos(ENEMY_START_X, ENEMY_START_Y);		//�G�̕`��ʒu��������

	//���֌W
	//SE
	this->se = new MUSIC(MUSIC_DIR_SE, SE_NAME_GAMESTART);		//SE���Ǘ�����I�u�W�F�N�g�𐶐�
	if (this->se->GetIsLoad() == false) { return false; }		//�ǂݍ��ݎ��s
	if (this->se->Add(MUSIC_DIR_SE, SE_NAME_GAMEOVER) == false) { return false; }	//�Q�[���I�[�o�[�̉���ǉ�
	if (this->se->Add(MUSIC_DIR_SE, SE_NAME_TEXT_SE) == false) { return false; }	//�e�L�X�g�\���̉���ǉ�

	//BGM
	this->bgm = new MUSIC(MUSIC_DIR_BGM, BGM_NAME_TITLE_BGM);	//BGM���Ǘ�����I�u�W�F�N�g�𐶐�
	if (this->bgm->GetIsLoad() == false) { return false; }		//�ǂݍ��ݎ��s
	this->bgm->ChengePlayType(DX_PLAYTYPE_LOOP);				//�Đ����@�����[�v�Đ��ɕύX
	this->bgm->ChengeVolume(50.0, (int)BGM_TYPE_TITLE);			//�^�C�g��bgm�̉��ʂ�50%�ɕύX

	//���ʕύX
	this->se->ChengeVolume(50.0, (int)SE_TYPE_GAMESTART);	//�Q�[���X�^�[�g�̉��ʂ�50%�ɕύX
	this->se->ChengeVolume(50.0, (int)SE_TYPE_GAMEOVER);	//�Q�[���I�[�o�[�̉��ʂ�50%�ɕύX

	//�G�t�F�N�g�֌W
	this->effect = new EFFECT(EFFECT_DIR, EFFECT_NAME_SLASH, EFFECT_SLASH_ALL_CNT, EFFECT_SLASH_YOKO_CNT, EFFECT_SLASH_TATE_CNT, EFFECT_SLASH_WIDTH, EFFECT_SLASH_HEIGHT, EFFECT_SLASH_SPEED, false, this->fps->Getvalue());
	if (this->effect->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s


	return true;	//�ǂݍ��ݐ���
}

//�摜�Ȃǂ̃T�C�Y���擾���A�ݒ肷��
void GAMEMANEGER::SetSize()
{
	this->back->SetSize();			//�w�i�摜�A�T�C�Y�ݒ�
	this->mark->SetSize();			//�}�[�N�摜�T�C�Y�ݒ�
	this->effect->SetSize();		//�G�t�F�N�g�̃T�C�Y�ݒ�
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

	//this->fps->Draw(0, 0);		//FPS�`��

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

	this->bgm->Play((int)BGM_TYPE_TITLE);		//bgm���Đ�

	this->player->ResetWinNum();		//�����������Z�b�g

	if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//�G���^�[�L�[�������ꂽ��
	{
		this->bgm->Stop((int)BGM_TYPE_TITLE);	//BGM���~�߂�
		this->NowScene = (int)SCENE_PLAY;	//�v���C��ʂ�
	}

	return;
}

//�^�C�g����ʂ̕`�揈��
void GAMEMANEGER::Draw_Scene_Title()
{

	this->back->Draw(GAME_LEFT,GAME_TOP);	//�w�i�`��

	return;
}

//�v���C��ʂ̏���
void GAMEMANEGER::Scene_Play()
{

	this->back->ChengeImage((int)PLAY_BACK);	//�w�i�摜�ύX

	switch (this->Play_NowStage)		//���݂̒i�K���Ƃɏ����𕪂���
	{

	case (int)PLAY_STAGE_TEXT_DRAW:		//�e�L�X�g�\���i�K�̂Ƃ�

		this->PlayStage_DrawText();		//�e�L�X�g�\���i�K�̏���

		break;			//�e�L�X�g�\���i�K�����܂�

	case (int)PLAY_STAGE_MAIN:		//�Q�[���v���C���̂Ƃ�

		this->PlayStage_Main();		//�Q�[���v���C���̂Ƃ��̏���

		break;		//�Q�[���v���C���̂Ƃ������܂�

	case (int)PLAY_STAGE_RESULT:	//���ʕ\���̂Ƃ�

		this->PlayStage_Result();	//���ʕ\���i�K�̏���

		break;		//���ʕ\�������܂�

	default:
		break;
	}


	if (this->keydown->IsKeyDownOne(KEY_INPUT_SPACE))	//�X�y�[�X�L�[�������ꂽ��
	{
		this->NowScene = (int)SCENE_END;	//�G���h��ʂ�
	}

	return;
}

//�v���C��ʂ̕`�揈��
void GAMEMANEGER::Draw_Scene_Play()
{

	this->back->Draw(GAME_LEFT, GAME_TOP);	//�w�i�摜�`��

	this->player->Draw();		//�v���C���[�`��
	this->enemy->Draw();		//�G�`��

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

//�v���C��ʂŎg�p������̂����Z�b�g
void GAMEMANEGER::PlayReset()
{
	this->player->ChengeImage((int)PLAYER_IMG_NORMAL);		//�`�悷��v���C���[�̉摜��ʏ펞�̉摜�ɕύX
	this->enemy->ChengeImage((int)ENEMY_IMG_NORMAL);		//�`�悷��G�̉摜��ʏ펞�̉摜�ɕύX

	this->player->SetImagePos(PLAYER_START_X, PLAYER_START_Y);	//�v���C���[�̕`��ʒu��������
	this->enemy->SetImagePos(ENEMY_START_X, ENEMY_START_Y);		//�G�̕`��ʒu��������

	this->mark->SetIsDraw(false);			//�}�[�N��`�悵�Ă͂����Ȃ�
	this->GameStartFlg = false;				//�Q�[���X�^�[�g���Ȃ�

	this->Play_NowStage = (int)PLAY_STAGE_TEXT_DRAW;	//�v���C�V�[���̌��݂̒i�K��������

	this->se->PlayReset((int)SE_TYPE_TEXT);		//�e�L�X�g�\���̌��ʉ���炵�Ă��Ȃ���Ԃ�
	this->se->PlayReset((int)SE_TYPE_GAMESTART);//�Q�[���X�^�[�g�̌��ʉ���炵�Ă��Ȃ���Ԃ�

	this->PushFlg = false;	//�L�[�������Ă��Ȃ�

	this->effect->ResetIsAnime((int)EFFECT_SLASH);	//�G�t�F�N�g�̍Đ���Ԃ����Z�b�g

	this->StartTime = GetNowCount();	//�v���J�n���Ԏ擾
	this->WaitTime = GetRand((GAME_START_WAITTIME_MAX / 2)) + GAME_START_WAITTIME_MIN;	//�҂����Ԃ�ݒ�

	return;

}

//�ǂ��炪������������
void GAMEMANEGER::Judg()
{
	//�L�[�������܂łɂ����������Ԃ���ɁA�ǂ��炪�����������肷��
	if (this->player->GetPushTime() < enemy->GetSpeed())		//�����̂ɂ����������Ԃ��A�G�̃X�s�[�h��葬��������
	{
		this->player->IncreaseWinNum();					//�������𑝂₷
		this->player->SetResult((int)RESULT_WIN);		//���ʂ�ݒ�(����)
	}
	else if (this->player->GetPushTime() > enemy->GetSpeed())		//�G���x��������
	{
		this->player->SetResult((int)RESULT_LOSE);		//���ʂ�ݒ�(�s�k)
	}
	else		//����������������
	{
		this->player->SetResult((int)RESULT_DRAW);		//���ʂ�ݒ�(��������)
	}

	return;

}

//�v���C�i�K�A�e�L�X�g�\���̂Ƃ��̏���
void GAMEMANEGER::PlayStage_DrawText()
{

	this->PlayReset();	//�v���C�֌W���Z�b�g

	this->se->Play((int)SE_TYPE_GAMESTART);		//�Q�[���X�^�[�g��SE��炷

	this->effect->SetIsFadeout(true);	//�t�F�[�h�A�E�g���s��

	if (this->effect->FadeOut(GAME_LEFT, GAME_TOP, GAME_WIDTH, GAME_HEIGHT))	//�t�F�[�h�A�E�g�������I�������
	{
		this->Play_NowStage = (int)PLAY_STAGE_MAIN;	//�Q�[���v���C�i�K��
	}


	return;
}

//�v���C�i�K�A�Q�[�����̂Ƃ��̏���
void GAMEMANEGER::PlayStage_Main()
{


	/*
	�C���|�C���g
	*/
	DrawBox(GAME_LEFT, GAME_TOP, GAME_WIDTH, GAME_HEIGHT,COLOR_BLACK,TRUE);	//�^���Âȉ��	

	this->mark->DrawCenter(GAME_WIDTH, MARK_DRAW_Y);	//�}�[�N�`��

	if (this->GameStartFlg)	//�Q�[�����n�܂�����
	{
		if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//�G���^�[�L�[�������ꂽ��
		{
			this->PushFlg = true;	//�L�[��������
		}

	}
	else					//�Q�[�����n�܂��Ă��Ȃ�������
	{

		if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//�G���^�[�L�[�������ꂽ��
		{

			this->player->SetResult((int)RESULT_OTETUKI);	//���ʂ�����t���ɐݒ�

			this->Play_NowStage = (int)PLAY_STAGE_RESULT;	//���ʕ\���i�K��

		}

		//�Q�[�����n�܂�܂ő҂�
		if (this->WaitStartTime())	//�X�^�[�g���ԂɂȂ�����
		{
			this->mark->SetIsDraw(true);		//�}�[�N��`�悵�Ă悢
			this->StartTime = GetNowCount();	//�}�[�N��`�悵�n�߂����Ԃ��X�^�[�g���Ԃɐݒ�
			this->GameStartFlg = true;			//�Q�[���X�^�[�g
		}
	}

	if (this->PushFlg)		//�L�[�������ꂽ��
	{
		this->player->ChengeImage((int)PLAYER_IMG_ACT);				//�`�悷��v���C���[�̉摜���A�N�V������̉摜�ɕύX
		this->player->SetImagePos(PLAYER_AFTER_X, PLAYER_AFTER_Y);	//�`�悷��ʒu���A�N�V������̈ʒu�ɕύX
		this->enemy->ChengeImage((int)ENEMY_IMG_ACT);				//�`�悷��G�̉摜���A�N�V������̉摜�ɕύX
		this->enemy->SetImagePos(ENEMY_AFTER_X, ENEMY_AFTER_Y);		//�`��ʒu���A�N�V������̈ʒu�ɕύX

		this->mark->SetIsDraw(false);	//�}�[�N��\��

		this->player->SetPushTime((GetNowCount() - this->StartTime));	//�����܂łɂ����������Ԃ�ݒ�

		this->effect->Draw(GAME_LEFT, GAME_TOP, (int)EFFECT_SLASH);	//�G�t�F�N�g�`��

		this->effect->SetIsFadein(true);		//�t�F�[�h�C�����s��

		if (this->effect->GetIsDrawEnd())	//�G�t�F�N�g�`�悪�I�������
		{

			this->Judg();	//�ǂ��炪������������

			this->Play_NowStage = (int)PLAY_STAGE_RESULT;	//���ʕ\���i�K��
		}

	}

	return;

}

//�v���C�i�K�A���ʕ\���̂Ƃ��̏���
void GAMEMANEGER::PlayStage_Result()
{

	//�t�F�[�h�C���G�t�F�N�g
	if (this->effect->FadeIn(GAME_LEFT, GAME_TOP, GAME_WIDTH, GAME_HEIGHT))		//�t�F�[�h�G�t�F�N�g���I�������
	{
		this->se->PlayOne((int)SE_TYPE_TEXT);	//�e�L�X�g�\���̉���炷

		//���ʖ��ɏ����𕪊�
		switch (this->player->GetResult())
		{

		case (int)RESULT_WIN:		//�v���C���[����������

			this->DrawTextCenter(RESULT_TEXT_Y,RESULT_WIN_TEXT);		//���������`��

			this->DrawNumTextCenter(DRAW_WIN_NUM_Y, WIN_NUM_DRAW_TEXT, this->player->GetWinNum());	//��������`��

			if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//�G���^�[�L�[�������ꂽ��
			{
				this->Play_NowStage = (int)PLAY_STAGE_TEXT_DRAW;	//�e�L�X�g�\���i�K��
			}


			break;		//�v���C���[���������������܂�

		case (int)RESULT_LOSE:		//�v���C���[���������Ƃ�

			this->DrawTextCenter(RESULT_TEXT_Y,RESULT_LOSE_TEXT);	//�s�k�����`��

			this->se->PlayOne((int)SE_TYPE_GAMEOVER);		//�Q�[���I�[�o�[�̉���炷

			if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//�G���^�[�L�[�������ꂽ��
			{
				this->se->PlayReset((int)SE_TYPE_GAMEOVER);		//�Đ���Ԃ����Z�b�g
				this->Play_NowStage = (int)PLAY_STAGE_TEXT_DRAW;	//�e�L�X�g�\���i�K��
				this->NowScene = (int)SCENE_TITLE;	//�^�C�g����ʂ�
			}

			break;		//�v���C���[���������Ƃ������܂�

		case (int)RESULT_DRAW:		//���������̂Ƃ�

			this->DrawTextCenter(RESULT_TEXT_Y,RESLUT_DRAW_TEXT);	//�������������`��

			if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//�G���^�[�L�[�������ꂽ��
			{
				this->Play_NowStage = (int)PLAY_STAGE_TEXT_DRAW;	//�e�L�X�g�\���i�K��
			}

			break;		//���������̂Ƃ������܂�

		case (int)RESULT_OTETUKI:		//����t���̂Ƃ�

			this->DrawTextCenter(RESULT_TEXT_Y,RESULT_OTETUKI_TEXT);	//����t�������`��

			if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//�G���^�[�L�[�������ꂽ��
			{
				this->Play_NowStage = (int)PLAY_STAGE_TEXT_DRAW;	//�e�L�X�g�\���i�K��
			}

			break;		//����t���̂Ƃ������܂�

		default:
			break;
		}

	}


	return;
}


//�n���ꂽ���������ʒ����ɕ`�悷��(�����͎����Ŏw�肷��)
//�����Fint�F�`��Y�ʒu
//�����Fconst char *�F�`�悷�镶����
void GAMEMANEGER::DrawTextCenter(int y,const char *text)
{
	int Strlen = 0;		//������̒����擾�p
	int Width = 0;		//������̕��擾�p

	Strlen = strlen(text);	//�����񒷂����擾
	Width = GetDrawStringWidth(text, Strlen);	//�����擾

	DrawString((GAME_WIDTH / 2) - (Width / 2), y, text, COLOR_BLACK);		//�������`��

	return;

}

//�����t��(����)������𒆉��ɕ`�悷��(�����͎����Ŏw�肷��)
//�����Fint�F�`��Y�ʒu
//�����Fconst char *�F�`�悷�镶����
//�����Fint�F�����w��q�ŕ`�悷�鐔��
void GAMEMANEGER::DrawNumTextCenter(int y, const char *text, int num)
{
	std::string draw_text = text;										//�`�敶����
	int keypos = draw_text.find(FORMAT_KEY_WORD);						//�u���J�n�ʒu���擾
	draw_text.replace(keypos, FORMAT_REPLACE_NUM, std::to_string(num));	//�u��

	int Strlen = 0;		//������̒����擾�p
	int Width = 0;		//������̕��擾�p

	Strlen = strlen(draw_text.c_str());						//�����񒷂����擾
	Width = GetDrawStringWidth(draw_text.c_str(), Strlen);	//�����擾

	DrawString((GAME_WIDTH / 2) - (Width / 2), y, draw_text.c_str(), COLOR_BLACK);		//�������`��

}