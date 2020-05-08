//ENEMY.hpp
//敵を管理するクラス

#pragma once

//################ ヘッダファイル読み込み #################
#include "CHARACTOR.hpp"

//################ マクロ定義 ##################
#define IMG_DIR_ENEMY		R"(.\MY_IMG\Enemy)"		//敵関係の画像ディレクトリ

#define IMG_NAME_ENEMY		R"(\Enemy.png)"			//敵の画像の名前
#define IMG_NAME_ENEMY_ACT	R"(\Enemy_2.png)"		//アクション後の敵の画像の名前

#define ENEMY_START_X		600		//敵の描画開始X位置
#define ENEMY_START_Y		250		//敵の描画開始Y位置

//################ 列挙型 ################
enum ENEMY_IMAGE
{
	ENEMY_IMG_NORMAL,		//通常時の画像
	ENEMY_IMG_ACT			//アクション後の画像
};

//################ クラス定義 ##################
class ENEMY :public CHARACTOR	//キャラクタークラスを継承
{

private:

	double Speed;		//速度

public:

	ENEMY(const char *,const char *);		//コンストラクタ
	~ENEMY();								//デストラクタ

	double GetSpeed();	//速度を取得

};
