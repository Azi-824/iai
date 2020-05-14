//SAVEDATA.cpp
//セーブデータを管理するクラス

//################### ヘッダファイル読み込み ##################
#include "SAVEDATA.hpp"

//#################### クラス定義 #######################

//コンストラクタ
SAVEDATA::SAVEDATA()
{


	return;
}

//デストラクタ
SAVEDATA::~SAVEDATA()
{

	for (int i = 0; i < this->DataCode.size(); ++i)
	{
		delete this->DataCode.at(i);
	}

	//vectorのメモリ解放を行う
	std::vector<DATA*> v;			//空のvectorを作成する
	this->DataCode.swap(v);			//空と中身を入れ替える


	return;
}

//データ追加
void SAVEDATA::Add(int win_num)
{

	DATEDATA Date;		//現在時刻

	GetDateTime(&Date);	//現在時刻取得

	this->DataCode.push_back(new DATA(Date.Year,Date.Mon,Date.Day,win_num));	//データ情報追加

	return;

}

//セーブ
bool SAVEDATA::Save()
{

	struct stat statbuf;	//ディレクトリの存在確認に使用

	if (stat(SAVEDATA_DIR, &statbuf) != 0)//セーブデータ用のフォルダが作成されていない場合（初めてのセーブの場合）
	{
		_mkdir(SAVEDATA_DIR);	//セーブデータを格納するフォルダを作成
	}

	std::string LoadFile;
	LoadFile += SAVEDATA_DIR;
	LoadFile += SAVEDATA_NAME;

	std::ofstream ofs(LoadFile.c_str(), std::ios_base::ate);	//ファイルオープン

	if (!ofs)		//ファイルオープン失敗時
	{
		std::string ErrorMsg(DATA_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadFile;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(DATA_ERROR_TTILE),
			MB_OK);

		return false;		//セーブ失敗

	}

	//セーブデータを書き込む
	for (int i = 0; i < this->DataCode.size(); ++i)	//データの数だけループ
	{
		ofs << this->DataCode.at(i)->GetYear() << ',';				//年、書き出し
		ofs << this->DataCode.at(i)->GetMonth() << ',';				//月、書き出し
		ofs << this->DataCode.at(i)->GetDay() << ',';				//日、書き出し
		ofs << this->DataCode.at(i)->GetWinNum() << std::endl;		//勝ち数、書き出し

	}

	return true;		//セーブ成功
}
