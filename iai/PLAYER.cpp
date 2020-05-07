//PLAYER.cpp
//プレイヤーを管理するクラス

//############## ヘッダファイル読み込み ##################
#include "PLAYER.hpp"

//############## クラス定義 #####################

//コンストラクタ
//引　数：const char *：画像のディレクトリ
//引　数：const char *：画像の名前
PLAYER::PLAYER(const char *dir,const char *name)
{

	this->SetImage(dir, name);	//画像を生成

	return;
}

//デストラクタ
PLAYER::~PLAYER()
{
	return;
}

//勝ち数を増やす
void PLAYER::IncreaseWinNum()
{
	++this->WinNum;
	return;
}

//勝ち数を取得
//戻り値：int：現在の勝ち数
int PLAYER::GetWinNum()
{
	return this->WinNum;
}

//押すまでの時間を設定
void PLAYER::SetPushTime(double time)
{
	this->PushTime = time;
	return;
}

//押すまでの時間を取得
//戻り値：double：押すまでの時間
double PLAYER::GetPushTime()
{
	return this->PushTime;
}
