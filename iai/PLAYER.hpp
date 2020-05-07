//PLAYER.hpp
//プレイヤーを管理するクラス

#pragma once

//############## ヘッダファイル読み込み ####################
#include "DxLib.h"
#include "CHARACTOR.hpp"

//############## マクロ定義 #######################
#define IMG_DIR_PLAYER		R"(.\MY_IMG\Player)"		//プレイヤー関係の画像ディレクトリ

#define IMG_NAME_PLAYER		R"(\Player.png)"			//プレイヤーの画像の名前

//############## クラス定義 #######################
class PLAYER : public CHARACTOR		//キャラクタークラスを継承
{

private:

	int WinNum;		//勝ち数
	double PushTime;//キーボードを押すまでにかかった時間

public:

	PLAYER(const char *,const char *);		//コンストラクタ
	~PLAYER();								//デストラクタ

	void IncreaseWinNum();		//勝ち数を増やす
	int GetWinNum();			//勝ち数を取得

	void SetPushTime(double);	//押すまでにかかった時間を設定
	double GetPushTime();		//押すまでにかかった時間を取得

};
