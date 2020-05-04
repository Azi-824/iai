//PLAYER.hpp
//プレイヤーを管理するクラス

#pragma once

//############## ヘッダファイル読み込み ####################
#include "DxLib.h"
#include "CHARACTOR.hpp"

//############## マクロ定義 #######################

//############## クラス定義 #######################
class PLAYER : public CHARACTOR		//キャラクタークラスを継承
{

private:

	int WinNum;		//勝ち数
	double PushTime;//キーボードを押すまでにかかった時間

public:

	PLAYER();		//コンストラクタ
	~PLAYER();		//デストラクタ

	void IncreaseWinNum();		//勝ち数を増やす
	int GetWinNum();			//勝ち数を取得

	void SetPushTime(double);	//押すまでにかかった時間を設定
	double GetPushTime();		//押すまでにかかった時間を取得

};
