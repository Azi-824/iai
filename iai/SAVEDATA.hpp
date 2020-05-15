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
	bool Load();	//読み込み

	//*************** ソート関係 ********************
	void Sort();				//セーブデータを降順に並べ替える
	void QuiqSort(int, int);	//クイックソート
	int Partition(int,int);		//pivotを決め、pivotを境目に振り分けをする
	void Swap(DATA*, DATA*);	//値を交換する
	int GetMaxWinNum();			//勝ち数の最大値を取得
	int GetMinWinNum();			//勝ち数の最小値を取得


};
