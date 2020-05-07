//CHARACTOR.cpp
//�L�����N�^�[�N���X

//################# �w�b�_�t�@�C���ǂݍ��� #####################
#include "CHARACTOR.hpp"

//################ �N���X��` ########################
//�R���X�g���N�^
CHARACTOR::CHARACTOR()
{
	//�����o�[�ϐ�������
	this->IsArive = false;	//����ł���
	this->IsLoad = false;	//�ǂݍ��߂Ă��Ȃ�

	return;
}

//�f�X�g���N�^
CHARACTOR::~CHARACTOR()
{
	delete this->image;		//image�폜
	delete this->sikaku_draw;	//sikaku_draw�폜

	return;
}

//�����Ă��邩�ݒ�
void CHARACTOR::SetIsArive(bool Isarive)
{
	this->IsArive = Isarive;
	return;
}

//�摜��ݒ�
void CHARACTOR::SetImage(const char *dir, const char *name)
{
	this->image = new IMAGE(dir, name);
	this->IsLoad = this->image->GetIsLoad();	//�ǂݍ��߂����ݒ�

	return;

}

//�������擾
int CHARACTOR::GetWidth()
{
	return this->image->GetWidth(0);
}

//�������擾
int CHARACTOR::GetHeight()
{
	return this->image->GetHeight(0);
}

//�摜�̈ʒu��ݒ肷��
void CHARACTOR::SetImagePos(int x, int y)
{

	this->sikaku_draw->Left = x;
	this->sikaku_draw->Top = y;

	//�`��̈�
	this->sikaku_draw->SetValue(
		this->sikaku_draw->Left,
		this->sikaku_draw->Top,
		this->sikaku_draw->Width,
		this->sikaku_draw->Height
	);

}

//�����Ă��邩�擾
bool CHARACTOR::GetIsArive()
{
	return this->IsArive;
}

//�ǂݍ��߂����擾
bool CHARACTOR::GetIsLoad()
{
	return this->IsLoad;
}

//����
void CHARACTOR::Operation(KEYDOWN *keydown)
{

	//if (keydown->IsKeyDown(KEY_INPUT_W))		//W�L�[�������Ă���Ƃ�
	//{
	//	this->MoveUp();							//��ֈړ�
	//}
	//else if (keydown->IsKeyDown(KEY_INPUT_S))	//S�L�[�������Ă���Ƃ�
	//{
	//	this->MoveDown();						//���ֈړ�
	//}
	//else if (keydown->IsKeyDown(KEY_INPUT_A))	//A�L�[�������Ă���Ƃ�
	//{
	//	this->MoveLeft();						//���ֈړ�
	//}
	//else if (keydown->IsKeyDown(KEY_INPUT_D))	//D�L�[�������Ă���Ƃ�
	//{
	//	this->MoveRight();						//�E�ֈړ�
	//}

	//�`��̈�Đݒ�
	this->sikaku_draw->SetValue(
		this->sikaku_draw->Left,
		this->sikaku_draw->Top,
		this->sikaku_draw->Width,
		this->sikaku_draw->Height);

	return;
	
}

//�������ݒ�
void CHARACTOR::SetInit()
{

	this->image->SetSize();		//�摜�T�C�Y�ݒ�


	this->sikaku_draw = new SIKAKU();		//�`��̈���쐬
	this->sikaku_draw->SetValue(0, 0, this->image->GetWidth(), this->image->GetHeight());	//�����蔻��̗̈��ݒ�

	this->IsArive = true;	//�����Ă���

	return;

}

//�`��
void CHARACTOR::Draw()
{
	if (this->IsArive)	//�����Ă����
	{
			this->image->Draw(this->sikaku_draw->Left, this->sikaku_draw->Top);	//�摜�`��
	}
}
