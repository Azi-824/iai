//DATA.cpp
//データを管理するクラス

//################# ヘッダファイル読み込み ##################
#include "DATA.hpp"

//################# クラス定義 ###################

//コンストラクタ
DATA::DATA(int year,int month,int day,int win_num)
{

	this->Year = year;		//年
	this->Month = month;	//月
	this->Day = day;		//日
	this->WinNum = win_num;	//勝ち数

	return;
}

//デストラクタ
DATA::~DATA()
{
	return;
}
