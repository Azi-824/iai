//main.hpp

#pragma once


//#################### ヘッダファイル読み込み #####################
#include "DxLib.h"

//########## マクロ定義 ##########
#define GAME_LEFT	  0		//画面の横の始点
#define GAME_TOP	  0		//画面の縦の始点
#define GAME_WIDTH	880		//画面の横の大きさ
#define GAME_HEIGHT	640		//画面の縦の大きさ
#define GAME_COLOR	32		//画面のカラービット

#define GAME_WINDOW_NAME	"居合道"			//ウィンドウのタイトル
#define GAME_WINDOW_MODECHANGE	TRUE			//TRUE：ウィンドウモード / FALSE：フルスクリーン

#define SET_WINDOW_ST_MODE_DEFAULT			0	//デフォルト
#define SET_WINDOW_ST_MODE_TITLE_NONE		1	//タイトルバーなし
#define SET_WINDOW_ST_MODE_TITLE_FLAME_NONE	2	//タイトルバーとフレームなし
#define SET_WINDOW_ST_MODE_FLAME_NONE		3	//フレームなし

#define GAME_FPS_SPEED					   60

//テキスト関係
#define LOAD_TEXT	"NowLoading…"		//ロード画面のテキスト
#define TITLE_TEXT	"NowTitle"			//タイトル画面のテキスト
#define PLAY_TEXT	"NowPlay"			//プレイ画面のテキスト
#define END_TEXT	"NowEnd"			//エンド画面のテキスト

//座標関係
#define TEST_TEXT_X	30					//テスト用のテキスト描画X位置
#define TEST_TEXT_Y	30					//テスト用のテキスト描画Y位置

//########### 列挙型 ################
enum GAME_SCENE
{
	SCENE_LOAD,			//ロードシーン
	SCENE_TITLE,		//タイトルシーン
	SCENE_PLAY,			//プレイシーン
	SCENE_END			//エンドシーン
};

//############## プロトタイプ宣言 #############
bool Load();				//読み込み処理
bool GameMainLoop();		//無限ループ内のゲーム処理
void Delete_Class();		//クラスを削除する処理

bool ProcesScene();			//各シーンの処理

bool Scene_Load();			//ロード画面の処理
void Draw_Scene_Load();		//ロード画面の描画処理

void Scene_Title();			//タイトル画面の処理
void Draw_Scene_Title();	//タイトル画面の描画処理

void Scene_Play();			//プレイ画面の処理
void Draw_Scene_Play();		//プレイ画面の描画処理

void Scene_End();			//エンド画面の処理
void Draw_Scene_End();		//エンド画面の描画処理

