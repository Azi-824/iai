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
