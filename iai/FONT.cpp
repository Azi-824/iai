//FONT.cpp
//�t�H���g�N���X

//############### �w�b�_�t�@�C���ǂݍ��� ####################
#include "FONT.hpp"

//############### �N���X�̒�` #####################

//�R���X�g���N�^
//���@���Fconst char *�F�t�H���g�̃f�B���N�g��
//���@���Fconst char *�F�t�H���g�̖��O
//���@���Fconst char *�F�t�H���g�̐�������
FONT::FONT(const char *dir,const char *filename,const char *name)
{
	//�����o�[�ϐ�������
	this->LoadFontNow = 0;		//�ǂݍ��񂾃t�H���g�̐�0
								
	//�t�H���g��ǂݍ���
	std::string LoadFilePath;	//�t�H���g�̃p�X���쐬

	LoadFilePath += dir;
	LoadFilePath += filename;
	
	if (AddFontResourceEx(LoadFilePath.c_str(), FR_PRIVATE, NULL) == 0)		//�ǂݍ��ݎ��s
	{
		std::string ErroeMsg(FONT_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
		ErroeMsg += TEXT('\n');					//���s
		ErroeMsg += LoadFilePath;				//�t�H���g�̃p�X

		MessageBox(
			NULL,
			ErroeMsg.c_str(),	//char * ��Ԃ�
			TEXT(FONT_ERROR_TITLE),
			MB_OK);

		this->Isload = false;		//�ǂݍ��ݎ��s

		return;

	}

	this->FilePath.push_back(LoadFilePath.c_str());
	this->FileName.push_back(name);

	ChangeFont(name);							//�w�肳�ꂽ�t�H���g�ɕύX
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	//�t�H���g�̃^�C�v���A���`�G�C���A�X�t�H���g�ɕύX
	this->SetSize(DEFAULT_FONTSIZE);	//�t�H���g�T�C�Y���f�t�H���g�̐����ɐݒ�

	this->Isload = true;		//�ǂݍ��߂�
	++this->LoadFontNow;		//�ǂݍ��񂾃t�H���g�̐���ǉ�

	return;

}

//�f�X�g���N�^	
FONT::~FONT()
{
	for (int i = 0; i < this->LoadFontNow; ++i)
	{
		if (RemoveFontResourceEx(this->FilePath[i].c_str(), FR_PRIVATE, NULL) == 0)	//���s��
		{
			MessageBox(NULL, "remove failure", "", MB_OK);				//�G���[���b�Z�[�W
		}
	}

	//vector�̃�����������s��
	std::vector<std::string> v;			//���vector���쐬����
	this->FilePath.swap(v);					//��ƒ��g�����ւ���

	//vector�̃�����������s��
	std::vector<std::string> v2;			//���vector���쐬����
	this->FileName.swap(v2);				//��ƒ��g�����ւ���

}

//�ǂݍ��߂���
bool FONT::GetIsLoad()
{
	return this->Isload;
}

//�t�H���g�T�C�Y�ݒ�
void FONT::SetSize(int size)
{

	SetFontSize(size);

	return;
}

//�t�H���g�ǉ�
//���@���Fconst char *�F�t�H���g�̃f�B���N�g��
//���@���Fconst char *�F�t�H���g�̖��O
//���@���Fconst char *�F�t�H���g�̐�������
void FONT::AddFont(const char *dir, const char *filename, const char *name)
{

	this->Isload = false;	//�ǂݍ���łȂ�

	//�t�H���g��ǂݍ���
	std::string LoadFilePath;		//�t�H���g�̃p�X���쐬

	LoadFilePath += dir;
	LoadFilePath += filename;

	if (AddFontResourceEx(LoadFilePath.c_str(), FR_PRIVATE, NULL) <= 0)		//�ǂݍ��ݎ��s
	{
		std::string ErroeMsg(FONT_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
		ErroeMsg += TEXT('\n');					//���s
		ErroeMsg += LoadFilePath;				//�t�H���g�̃p�X

		MessageBox(
			NULL,
			ErroeMsg.c_str(),	//char * ��Ԃ�
			TEXT(FONT_ERROR_TITLE),
			MB_OK);

		this->Isload = false;		//�ǂݍ��ݎ��s

		return;

	}

	this->FilePath.push_back(LoadFilePath.c_str());
	this->FileName.push_back(name);

	this->Isload = true;		//�ǂݍ��߂�
	++this->LoadFontNow;		//�ǂݍ��񂾃t�H���g�̐���ǉ�

	return;
}

//�t�H���g�ύX
void FONT::ChengFont(int fontType)
{
	ChangeFont(this->FileName[fontType].c_str());			//�w�肳�ꂽ�t�H���g�ɕύX
	return;
}
