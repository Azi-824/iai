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
#define IMG_DIR_MARK		R"(.\MY_IMG\Mark)"				//マーク画像のファイルの場所
#define IMG_DIR_TEXT		R"(.\MY_IMG\Text)"				//テキスト画像のファイルの場所

#define IMG_NAME_TITLE		R"(\Title.jpg)"					//タイトル画面の背景画像の名前
#define IMG_NAME_PLAY		R"(\Play.jpg)"					//プレイ画面の背景画像の名前

#define IMG_NAME_MARK		R"(\Mark.png)"					//マーク画像の名前

#define IMG_NAME_TEXT_WIN	R"(\Win_text.png)"				//勝利テキストの画像の名前
#define IMG_NAME_TEXT_LOSE	R"(\Lose_text.png)"				//敗北テキストの画像の名前
#define IMG_NAME_TEXT_DRAW	R"(\Draw_text.png)"				//引き分けテキストの画像の名前
#define IMG_NAME_TEXT_OTETUKI	R"(\Otetuki.png)"			//お手付きのテキストの画像の名前

#define MARK_DRAW_Y			100		//マーク画像の描画Y位置

#define TEXT_DRAW_Y			50		//テキスト画像の描画Y位置

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

enum TEXT_IMAGE
{
	TEXT_IMG_WIN,	//勝利テキスト
	TEXT_IMG_LOSE,	//敗北テキスト
	TEXT_IMG_DRAW,	//引き分けテキスト
	TEXT_IMG_OTETUKI//お手付きテキスト
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

	int ImageKind;				//読み込んだ画像の種類
	int Draw_Num;				//描画する画像の番号

	bool IsLoad;				//読み込めたか？
	std::vector<bool> IsDraw;	//描画してよいか

public:
	IMAGE(const char *,const char *);	//コンストラクタ
	virtual ~IMAGE();					//デストラクタ

	std::string GetFileName(void);	//名前を取得

	void SetSize(void);				//サイズをセット

	int GetWidth();		//幅を取得
	int GetHeight();	//高さを取得

	bool GetIsLoad(void);			//読み込めた？
	void SetIsDraw(bool);			//描画してよいか設定

	void Draw(int, int);		//画像を描画
	void DrawCenter(int ,int);	//画像を描画（中央）

	bool AddImage(const char *, const char *);	//画像を追加
	void ChengeImage(int);						//描画する画像を変更

};

