//main.cpp

//#################### ヘッダファイル読み込み #######################
#include "main.hpp"
#include "FPS.hpp"
#include "KEYDOWN.hpp"

//########## グローバルオブジェクト ##########
FPS *fps = new FPS(GAME_FPS_SPEED);			//FPSクラスのオブジェクトを生成
KEYDOWN *keydown = new KEYDOWN();			//KEYDOWNクラスのオブジェクトを生成

//######### グローバル変数 ############
int NowScene = (int)SCENE_LOAD;	//現在のシーン(最初はロード画面から)
bool IsLoad = false;			//読み込みが終わったか（最初は読み込めていない）

//########## プログラムで最初に実行される関数 ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(GAME_WINDOW_MODECHANGE);					//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);			//指定の数値で画面を表示する

	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);				//タイトルバーあり

	SetMainWindowText(TEXT(GAME_WINDOW_NAME));					//タイトルの文字

	SetAlwaysRunFlag(TRUE);										//非アクティブに設定

	if (DxLib_Init() == -1) { return -1; }						//ＤＸライブラリ初期化処理

	SetDrawScreen(DX_SCREEN_BACK);								//Draw系関数は裏画面に描画

	//ゲームのメインループ
	while (GameMainLoop())
	{
		/*
		ループ内で異常が発生するまで無限ループ
		ゲーム終了やエラー等が発生したらループ終了
		*/
	}

	Delete_Class();			//使用したクラスを破棄

	DxLib_End();			//ＤＸライブラリ使用の終了処理

	return 0;
}

//読み込み処理
/*
戻り値：true：正常
戻り値：false：エラー、強制終了
*/
bool Load()
{
	return true;	//読み込み成功
}

//無限ループ内のゲーム処理
/*
戻り値：true：正常
戻り値：false：エラー、強制終了
*/
bool GameMainLoop()
{
	if (ProcessMessage() != 0) { return false; }	//メッセージ処理の結果がエラーのとき、強制終了

	if (ClearDrawScreen() != 0) { return false; }	//画面を消去できなかったとき、強制終了

	keydown->KeyDownUpdate();	//キーの入力状態を更新する

	fps->Update();				//FPSの処理[更新]

	//▼▼▼▼▼ゲームのシーンここから▼▼▼▼▼

	ProcesScene();				//各シーンの処理

	//▲▲▲▲▲ゲームのシーンここまで▲▲▲▲▲

	fps->Draw(0,0);				//FPS描画

	ScreenFlip();				//モニタのリフレッシュレートの速さで裏画面を再描画

	fps->Wait();				//FPSの処理[待つ]

	return true;				//正常

}

//ゲーム内で使用したクラスを削除する処理
void Delete_Class()
{

	delete fps;			//fps破棄
	delete keydown;		//keydown破棄

	return;
}

//各シーンの処理
bool ProcesScene()
{
	switch (NowScene)		//現在のシーンの描画処理を実行
	{

	case (int)SCENE_LOAD:	//ロード画面のとき

		Draw_Scene_Load();	//ロード画面の描画処理

		return Scene_Load();//ロード画面の処理

		break;				//ロード画面のときここまで

	case (int)SCENE_TITLE:	//タイトル画面のとき

		Draw_Scene_Title();	//描画

		Scene_Title();		//処理

		break;				//タイトル画面のときここまで

	case (int)SCENE_PLAY:	//プレイ画面のとき

		Draw_Scene_Play();	//描画

		Scene_Play();		//処理

		break;				//プレイ画面のときここまで

	case (int)SCENE_END:	//エンド画面のとき

		Draw_Scene_End();	//描画

		Scene_End();		//処理

		break;				//エンド画面のときここまで

	default:
		break;
	}

	return true;	//通常

}


//ロード画面の処理
/*
戻り値：true：正常
戻り値：false：エラー、強制終了
*/
bool Scene_Load()
{
	if (IsLoad)	//読み込みが完了していたら
	{
		if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーを押されたら
		{
			NowScene = (int)SCENE_TITLE;	//タイトル画面へ
		}
	}

	if (GetASyncLoadNum() == 0)	//非同期で読み込んでいる処理が終わったら
	{

		SetUseASyncLoadFlag(FALSE);		//同期読み込みに設定

		IsLoad = true;	//読み込み完了
	}

	return Load();		//読み込み処理
}

//ロード画面の描画処理
void Draw_Scene_Load()
{

	if (IsLoad)	//読み込みが完了したら
	{
		DrawString(TEST_TEXT_X, TEST_TEXT_Y, PUSH_TEXT, GetColor(255, 255, 255));	//プッシュ、のテキストを描画
	}
	else		//完了していなければ
	{
		DrawString(TEST_TEXT_X, TEST_TEXT_Y, LOAD_TEXT, GetColor(255, 255, 255));	//読み込み中のテキストを描画
	}

	return;
}

//タイトル画面の処理
void Scene_Title()
{

	if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーを押されたら
	{
		NowScene = (int)SCENE_PLAY;	//プレイ画面へ
	}

	return;
}

//タイトル画面の描画処理
void Draw_Scene_Title()
{

	DrawString(TEST_TEXT_X, TEST_TEXT_Y, TITLE_TEXT, GetColor(255, 255, 255));	//テスト用のテキストを描画

	return;
}

//プレイ画面の処理
void Scene_Play()
{

	if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーを押されたら
	{
		NowScene = (int)SCENE_END;	//エンド画面へ
	}

	return;
}

//プレイ画面の描画処理
void Draw_Scene_Play()
{

	DrawString(TEST_TEXT_X, TEST_TEXT_Y, PLAY_TEXT, GetColor(255, 255, 255));	//テスト用のテキストを描画

	return;
}

//エンド画面の処理
void Scene_End()
{

	if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーを押されたら
	{
		NowScene = (int)SCENE_TITLE;	//タイトル画面へ
	}

	return;
}

//エンド画面の描画処理
void Draw_Scene_End()
{

	DrawString(TEST_TEXT_X, TEST_TEXT_Y, END_TEXT, GetColor(255, 255, 255));	//テスト用のテキストを描画

	return;
}
