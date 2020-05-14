//SAVEDATA.cpp
//�Z�[�u�f�[�^���Ǘ�����N���X

//################### �w�b�_�t�@�C���ǂݍ��� ##################
#include "SAVEDATA.hpp"

//#################### �N���X��` #######################

//�R���X�g���N�^
SAVEDATA::SAVEDATA()
{


	return;
}

//�f�X�g���N�^
SAVEDATA::~SAVEDATA()
{

	for (int i = 0; i < this->DataCode.size(); ++i)
	{
		delete this->DataCode.at(i);
	}

	//vector�̃�����������s��
	std::vector<DATA*> v;			//���vector���쐬����
	this->DataCode.swap(v);			//��ƒ��g�����ւ���


	return;
}

//�f�[�^�ǉ�
void SAVEDATA::Add(int win_num)
{

	DATEDATA Date;		//���ݎ���

	GetDateTime(&Date);	//���ݎ����擾

	this->DataCode.push_back(new DATA(Date.Year,Date.Mon,Date.Day,win_num));	//�f�[�^���ǉ�

	return;

}

//�Z�[�u
bool SAVEDATA::Save()
{

	struct stat statbuf;	//�f�B���N�g���̑��݊m�F�Ɏg�p

	if (stat(SAVEDATA_DIR, &statbuf) != 0)//�Z�[�u�f�[�^�p�̃t�H���_���쐬����Ă��Ȃ��ꍇ�i���߂ẴZ�[�u�̏ꍇ�j
	{
		_mkdir(SAVEDATA_DIR);	//�Z�[�u�f�[�^���i�[����t�H���_���쐬
	}

	std::string LoadFile;
	LoadFile += SAVEDATA_DIR;
	LoadFile += SAVEDATA_NAME;

	std::ofstream ofs(LoadFile.c_str(), std::ios_base::ate);	//�t�@�C���I�[�v��

	if (!ofs)		//�t�@�C���I�[�v�����s��
	{
		std::string ErrorMsg(DATA_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
		ErrorMsg += TEXT('\n');						//���s
		ErrorMsg += LoadFile;					//�摜�̃p�X

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * ��Ԃ�
			TEXT(DATA_ERROR_TTILE),
			MB_OK);

		return false;		//�Z�[�u���s

	}

	//�Z�[�u�f�[�^����������
	for (int i = 0; i < this->DataCode.size(); ++i)	//�f�[�^�̐��������[�v
	{
		ofs << this->DataCode.at(i)->GetYear() << ',';				//�N�A�����o��
		ofs << this->DataCode.at(i)->GetMonth() << ',';				//���A�����o��
		ofs << this->DataCode.at(i)->GetDay() << ',';				//���A�����o��
		ofs << this->DataCode.at(i)->GetWinNum() << std::endl;		//�������A�����o��

	}

	return true;		//�Z�[�u����
}
