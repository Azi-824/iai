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

	this->QuiqSort(this->GetMinWinNum(), this->GetMaxWinNum());	//�N�C�b�N�\�[�g

	return;
}

//�N�C�b�N�\�[�g
void SAVEDATA::QuiqSort(int left, int right)
{
	int pivot = 0;

	if (left < right)
	{
		pivot = this->Partition(left, right);
		this->QuiqSort(left, pivot - 1);		//pivot�����ɍċA�I�ɃN�C�b�N�\�[�g
		this->QuiqSort(pivot + 1, right);		//pivot�����ɍċA�I�ɃN�C�b�N�\�[�g
	}
	return;
}

//pivot�����߁Apivot�����ڂɐU�蕪��������
int SAVEDATA::Partition(int left,int right)
{

	int i = 0, j = 0, pivot = 0;	//������
	i = left;
	j = right + 1;
	pivot = left;		//�擪�v�f��pivot�Ƃ���

	do
	{

		do { ++i; } while (this->DataCode.at(i)->GetWinNum() > this->DataCode.at(pivot)->GetWinNum());
		do { --j; } while (this->DataCode.at(pivot)->GetWinNum() > this->DataCode.at(j)->GetWinNum());

		//pivot��菬�������̂����ցA�傫�����̂��E��
		if (i < j)
		{
			this->Swap(this->DataCode.at(pivot), this->DataCode.at(j));	//pivot���X�V
		}

	} while (i<j);

	return;
}

//�l����������
void SAVEDATA::Swap(DATA *i, DATA *j)
{
	auto temp = *i;	//�l���ꎞ�ۊǂ���
	*i = *j;
	*j = temp;

	return;
}

//�������̍ő�l���擾
int SAVEDATA::GetMaxWinNum()
{
	int max_value = 0;	//�ő�l�i�[�p

	for (int i = 0; i < this->DataCode.size(); ++i)	//�f�[�^�̐������[�v
	{
		if (this->DataCode.at(i)->GetWinNum() > max_value)	//���݂̍ő�l���傫��������
		{
			max_value = this->DataCode.at(i)->GetWinNum();	//�ő�l�X�V
		}
	}

	return max_value;
}

//�������̍ŏ��l���擾
int SAVEDATA::GetMinWinNum()
{
	int min_value = 99;		//�ŏ��l�i�[�p

	for (int i = 0; i < this->DataCode.size(); ++i)
	{
		if (this->DataCode.at(i)->GetWinNum() < min_value)	//���݂̍ŏ��l���傫��������
		{
			min_value = this->DataCode.at(i)->GetWinNum();	//�ŏ��l�X�V
		}
	}

	return min_value;

}
