//ENEMY.hpp
//�G���Ǘ�����N���X

#pragma once

//################ �w�b�_�t�@�C���ǂݍ��� #################
#include "CHARACTOR.hpp"

//################ �}�N����` ##################
#define IMG_DIR_ENEMY		R"(.\MY_IMG\Enemy)"		//�G�֌W�̉摜�f�B���N�g��

#define IMG_NAME_ENEMY		R"(\Enemy.png)"			//�G�̉摜�̖��O
#define IMG_NAME_ENEMY_ACT	R"(\Enemy_2.png)"		//�A�N�V������̓G�̉摜�̖��O

#define ENEMY_START_X		600		//�G�̕`��J�nX�ʒu
#define ENEMY_START_Y		250		//�G�̕`��J�nY�ʒu
#define ENEMY_AFTER_X		50		//�G�̕`��X�ʒu�i�A�N�V������j
#define ENEMY_AFTER_Y		250		//�G�̕`��Y�ʒu�i�A�N�V������j

#define ENEMY_SPD_MIN		0.5		//�G�̂͂₳�̍ŏ��l
#define ENEMY_SPD_INIT		1.5		//�G�̂͂₳�̏����l
#define ENEMY_SPD_UP_VALUE	0.1		//���ɑ����Ȃ�l

//################ �񋓌^ ################
enum ENEMY_IMAGE
{
	ENEMY_IMG_NORMAL,		//�ʏ펞�̉摜
	ENEMY_IMG_ACT			//�A�N�V������̉摜
};

//################ �N���X��` ##################
class ENEMY :public CHARACTOR	//�L�����N�^�[�N���X���p��
{

private:

	double Speed;									//���x

public:

	ENEMY(const char *,const char *);		//�R���X�g���N�^
	~ENEMY();								//�f�X�g���N�^

	double GetSpeed();	//���x���擾
	void SpeedUp();		//���x�𑁂�����
	void SpeedReset();	//���x�����Z�b�g����

};
