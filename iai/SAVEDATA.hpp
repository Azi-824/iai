//SAVEDATA.hpp
//セーブデータを管理するクラス

#pragma once

//################## ヘッダファイル読み込み ####################
#include "DATA.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <direct.h>

//################## マクロ定義 #######################
#define SAVEDATA_DIR	R"(C:\IAI_DATA)"		//セーブデータの保存ディレクトリ名

#define SAVEDATA_NAME	R"(\Savedata.csv)"		//セーブデータの名前

//############## マクロ定義：エラーメッセージ ###################
#define DATA_ERROR_TTILE	"DATA_ERROR"						//エラータイトル
#define DATA_ERROR_MSG		"データが読み込めませんでした"		//エラーメッセージ

//################## クラス定義 #######################
class SAVEDATA
{

private:

	std::vector<DATA*> DataCode;			//セーブデータ

public:

	SAVEDATA();		//コンストラクタ
	~SAVEDATA();	//デストラクタ

	void Add(int);	//データ追加

	bool Save();	//セーブ

};
