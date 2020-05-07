//ENEMY.hpp
//敵を管理するクラス

#pragma once

//################ ヘッダファイル読み込み #################
#include "CHARACTOR.hpp"

//################ マクロ定義 ##################

//################ クラス定義 ##################
class ENEMY :public CHARACTOR	//キャラクタークラスを継承
{

private:

	double Speed;		//速度

public:

	ENEMY();			//コンストラクタ
	~ENEMY();			//デストラクタ

	double GetSpeed();	//速度を取得

};
