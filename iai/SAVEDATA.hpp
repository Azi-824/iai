//SAVEDATA.hpp
//セーブデータを管理するクラス

#pragma once

//################## ヘッダファイル読み込み ####################
#include "DATA.hpp"
#include <vector>

//################## マクロ定義 #######################

//################## クラス定義 #######################
class SAVEDATA
{

private:

	std::vector<DATA*> DataCode;			//セーブデータ

public:

	SAVEDATA();		//コンストラクタ
	~SAVEDATA();	//デストラクタ

	void Add(int);	//データ追加

};
