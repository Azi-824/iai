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
		if (i == this->DataCode.size() - 1)	//�Ō�̏������݂�������
		{
			//�I�[������t����
			ofs << this->DataCode.at(i)->GetWinNum() << '\0';			//�������A�����o��
		}
		else	//�Ō�̏������݂���Ȃ����
		{
			//���s����
			ofs << this->DataCode.at(i)->GetWinNum() << '\n';			//�������A�����o��
		}


	}

	return true;		//�Z�[�u����
}

//�ǂݍ���
bool SAVEDATA::Load()
{
	std::string LoadFile;
	LoadFile += SAVEDATA_DIR;
	LoadFile += SAVEDATA_NAME;

	std::ifstream ifs(LoadFile.c_str());	//�t�@�C���ǂݎ��

	if (!ifs)		//�t�@�C���I�[�v�����s��
	{
		std::string ErrorMsg(DATA_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
		ErrorMsg += TEXT('\n');						//���s
		ErrorMsg += LoadFile;					//�摜�̃p�X

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * ��Ԃ�
			TEXT(DATA_ERROR_TTILE),
			MB_OK);

		return false;	//�ǂݍ��ݎ��s

	}


	std::string buf;
	int yy = 0, mm = 0, dd = 0, wn = 0;		//�N�A���A���A������

	while (!ifs.eof())				//�Ō�̍s�܂œǂݍ���
	{
		std::getline(ifs, buf,',');		//�J���}�܂œǂݍ���
		yy = atoi(buf.c_str());			//�N�ǂݍ���
		
		std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
		mm = atoi(buf.c_str());			//���ǂݍ���

		std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
		dd = atoi(buf.c_str());			//���ǂݍ���

		std::getline(ifs, buf, '\n');	//���s�܂œǂݍ���
		wn = atoi(buf.c_str());			//�������ǂݍ���

		this->DataCode.push_back(new DATA(yy, mm, dd, wn));		//�f�[�^�ǉ�

	}

	return true;	//�ǂݍ��ݐ���
}

//**************** �\�[�g�֌W ******************
//�Z�[�u�f�[�^���~���ɕ��בւ���
void SAVEDATA::Sort()
{

	for (int i = 0; i < this->DataCode.size(); ++i)
	{
		for (int j = this->DataCode.size() - 1; j > i; --j)
		{
			if (this->DataCode.at(j)->GetWinNum() > this->DataCode.at(j - 1)->GetWinNum())
			{
				auto temp = this->DataCode.at(j);
				this->DataCode.at(j) = this->DataCode.at(j - 1);
				this->DataCode.at(j - 1) = temp;
			}
		}
	}

	return;
}

//�f�[�^�`��
void SAVEDATA::Draw()
{

	int Height = GetFontSize();		//�����擾

	DrawString(DRAW_DATA_X, DRAW_DATA_Y, DRAW_DATA_TEXT_INDEX, GetColor(255, 255, 255));		//�����L���O�^�C�g���`��

	for (int i = 0; i < this->DataCode.size();++i)
	{

		if (i >= DRAW_DATA_MAX)		//�����L���O�`�悷��ő吔�ɂȂ�����
		{
			break;					//���[�v�𔲂���
		}

		DrawFormatString(DRAW_DATA_X, DRAW_DATA_Y + (i + 1) * Height, GetColor(255, 255, 255), DRAW_DATA_TEXT,
			i + 1,								//���ʂ�
			this->DataCode.at(i)->GetWinNum(),	//������
			this->DataCode.at(i)->GetYear(),	//�N
			this->DataCode.at(i)->GetMonth(),	//��
			this->DataCode.at(i)->GetDay());	//��
	}

	return;
}
