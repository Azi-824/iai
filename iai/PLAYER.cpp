//PLAYER.cpp
//プレイヤーを管理するクラス

//############## ヘッダファイル読み込み ##################
#include "PLAYER.hpp"

//############## クラス定義 #####################

//コンストラクタ
PLAYER::PLAYER()
{
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
int PLAYER::GetWinNum()
{
	return this->WinNum;
}

//押されてからの時間を設定
void PLAYER::SetPushTime(double time)
{
	this->PushTime = time;
	return;
}

//押されてからの時間を取得
double PLAYER::GetPushTime()
{
	return this->PushTime;
}
