//CHARACTOR.hpp
//キャラクタークラス

#pragma once

//###################### ヘッダファイル読み込み ###################
#include "DxLib.h"
#include "IMAGE.hpp"
#include "KEYDOWN.hpp"
#include "SIKAKU.hpp"


//###################### マクロ定義 #######################

//###################### クラス定義 #######################
class CHARACTOR
{
private:
	IMAGE *image;				//画像
	SIKAKU *sikaku_draw;		//キャラの描画する領域

	bool IsArive;				//生きているか
	bool IsLoad;				//読み込めたか

public:

	CHARACTOR();				//コンストラクタ
	~CHARACTOR();				//デストラクタ

	void SetIsArive(bool);		//生きているかを設定
	void SetImage(const char*, const char*);//画像設定

	void SetImagePos(int, int);		//画像の位置を設定する

	int  GetWidth();			//横幅取得
	int GetHeight();			//高さ取得
	bool GetIsArive();			//生きているか取得
	bool GetIsLoad();			//読み込めたか取得

	void Operation(KEYDOWN *);	//操作

	void Draw();				//描画

	void SetInit();				//初期設定

};

