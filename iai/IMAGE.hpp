/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* IMAGE.cpp     																				　 */
/* 画像クラス 																					　 */

/*
追加方法
・フォルダ名とファイル名をマクロ定義する
・Add処理を使用して、画像を読み込む
*/

#pragma once

//########## ヘッダーファイル読み込み ##########
#include "DxLib.h"
#include <string>
#include <vector>

//########## マクロ定義：画像のファイルパスと名前 ##########
#define IMG_DIR_BACK		R"(.\MY_IMG\Back)"				//背景画像のファイルの場所

#define IMG_NAME_TITLE		R"(\Title.jpg)"					//タイトル画面の背景画像の名前
#define IMG_NAME_PLAY		R"(\Play.jpg)"					//プレイ画面の背景画像の名前

//########## マクロ定義：エラーメッセージ##########
#define IMAGE_ERROR_TITLE "IMAGE_ERROR"					//エラータイトル
#define IMAGE_ERROR_MSG	"画像が読み込めませんでした"	//エラーメッセージ

//########## 列挙型 ################
enum BACK_IMAGE
{
	TITLE_BACK,		//タイトル画面の背景画像
	PLAY_BACK,		//プレイ画面の背景画像
	END_BACK		//エンド画面の背景画像
};

//########## クラスの定義 ##########

class IMAGE
{
private:
	std::string FilePath;	//パス
	std::string FileName;	//名前

	std::vector<int> Handle;				//ハンドル

	std::vector<int> Width;					//幅
	std::vector<int> Height;				//高さ

	int ImageKind;			//読み込んだ画像の種類

	bool IsLoad;			//読み込めたか？

public:
	IMAGE(const char *,const char *);	//コンストラクタ
	virtual ~IMAGE();					//デストラクタ

	std::string GetFileName(void);	//名前を取得

	void SetSize(void);				//サイズをセット

	int GetWidth(int);				//幅を取得
	int GetHeight(int);				//高さを取得

	bool GetIsLoad(void);			//読み込めた？

	void Draw(int, int, int type=0);	//指定された画像を描画(指定しない場合、先頭の画像)

	bool AddImage(const char *, const char *);	//画像を追加

};

