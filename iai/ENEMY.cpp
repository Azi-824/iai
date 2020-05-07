//ENEMY.cpp
//敵を管理するクラス

//############### ヘッダファイル読み込み #################
#include "ENEMY.hpp"

//############### クラス定義 ###################

//コントラクタ
ENEMY::ENEMY()
{
	return;
}

//デストラクタ
ENEMY::~ENEMY()
{
	return;
}

//速度を取得
double ENEMY::GetSpeed()
{
	return this->Speed;
}
