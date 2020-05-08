//GAMEMANEGER.cpp
//ゲームのシステムを管理するクラス

//############### ヘッダファイル読み込み ################
#include "GAMEMANEGER.hpp"

//############### クラス定義 ################

//コンストラクタ
GAMEMANEGER::GAMEMANEGER()
{
	//オブジェクトの生成
	this->fps = new FPS(GAME_FPS_SPEED);	//FPSクラスのオブジェクトを生成
	this->keydown = new KEYDOWN();			//KEYDOWNクラスのオブジェクトを生成

	//メンバー変数初期化
	this->NowScene = (int)SCENE_LOAD;		//最初のシーンは、ロード画面
	this->IsLoad = false;					//読み込み、未完了
	this->StartTime = 0;					//計測開始時間初期化
	this->WaitTime = 0;						//待ち時間初期化

	return;

}

//デストラクタ
GAMEMANEGER::~GAMEMANEGER()
{
	//オブジェクトの破棄
	delete this->fps;		//fps破棄
	delete this->keydown;	//keydown破棄
	delete this->back;		//back破棄
	delete this->mark;		//mark破棄
	delete this->player;	//player破棄

	return;

}

//ゲーム内で使用するデータの読み込み処理
/*
戻り値：true：正常
戻り値：false：エラー、強制終了
*/
bool GAMEMANEGER::Load()
{
	//画像関係
	//背景画像
	this->back = new IMAGE(IMG_DIR_BACK, IMG_NAME_TITLE);	//背景画像を管理するオブジェクトを生成(タイトル画面の画像を読み込む)
	if (this->back->GetIsLoad() == false) { return false; }	//読み込み失敗
	if (this->back->AddImage(IMG_DIR_BACK, IMG_NAME_PLAY) == false) { return false; }		//背景画像追加(プレイ画面)
	//マーク画像
	this->mark = new IMAGE(IMG_DIR_MARK, IMG_NAME_MARK);	//マーク画像を生成
	if (this->mark->GetIsLoad() == false) { return false; }	//読み込み失敗

	//プレイヤー関係
	this->player = new PLAYER(IMG_DIR_PLAYER, IMG_NAME_PLAYER);		//プレイヤー生成
	if (this->player->GetIsLoad() == false) { return false; }		//読み込み失敗
	if (this->player->AddImage(IMG_DIR_PLAYER, IMG_NAME_PLAYER_ACT) == false) { return false; }	//画像追加

	//敵関係
	this->enemy = new ENEMY(IMG_DIR_ENEMY, IMG_NAME_ENEMY);		//敵生成
	if (this->enemy->GetIsLoad() == false) { return false; }	//読み込み失敗
	if (this->enemy->AddImage(IMG_DIR_ENEMY, IMG_NAME_ENEMY_ACT) == false) { return false; }	//画像追加

	return true;	//読み込み成功
}

//画像などのサイズを取得し、設定する
void GAMEMANEGER::SetSize()
{
	this->back->SetSize();	//背景画像、サイズ設定
	this->mark->SetSize();	//マーク画像サイズ設定

	return;
}

//初期設定をする
void GAMEMANEGER::SetInit()
{

	this->SetSize();			//サイズ設定

	this->player->SetInit();	//プレイヤーの初期設定
	this->enemy->SetInit();		//敵の初期設定

}

//ゲームのメインループ
/*
戻り値：true：正常
戻り値：false：エラー、強制終了
*/
bool GAMEMANEGER::GameMainLoop()
{
	if (ProcessMessage() != 0) { return false; }	//メッセージ処理の結果がエラーのとき、強制終了

	if (ClearDrawScreen() != 0) { return false; }	//画面を消去できなかったとき、強制終了

	this->keydown->KeyDownUpdate();	//キーの入力状態を更新する

	this->fps->Update();		//FPSの処理[更新]

	//▼▼▼▼▼ゲームのシーンここから▼▼▼▼▼

	this->ProcesScene();		//各シーンの処理

	//▲▲▲▲▲ゲームのシーンここまで▲▲▲▲▲

	this->fps->Draw(0, 0);		//FPS描画

	ScreenFlip();				//モニタのリフレッシュレートの速さで裏画面を再描画

	this->fps->Wait();			//FPSの処理[待つ]

	return true;				//正常

}

//各シーンの処理
void GAMEMANEGER::ProcesScene()
{
	switch (this->NowScene)		//現在のシーンの描画処理を実行
	{

	case (int)SCENE_LOAD:	//ロード画面のとき

		this->Draw_Scene_Load();	//ロード画面の描画処理

		this->Scene_Load();			//ロード画面の処理

		break;				//ロード画面のときここまで

	case (int)SCENE_TITLE:	//タイトル画面のとき

		this->Draw_Scene_Title();	//描画

		this->Scene_Title();		//処理

		break;				//タイトル画面のときここまで

	case (int)SCENE_PLAY:	//プレイ画面のとき

		this->Draw_Scene_Play();	//描画

		this->Scene_Play();		//処理

		break;				//プレイ画面のときここまで

	case (int)SCENE_END:	//エンド画面のとき

		this->Draw_Scene_End();	//描画

		this->Scene_End();		//処理

		break;				//エンド画面のときここまで

	default:
		break;
	}

	return;	

}

//***************************** シーン毎の処理 ********************************
//ロード画面の処理
void GAMEMANEGER::Scene_Load()
{
	if (this->IsLoad)	//読み込みが完了していたら
	{
		if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーを押されたら
		{
			this->NowScene = (int)SCENE_TITLE;	//タイトル画面へ
		}
	}

	if (GetASyncLoadNum() == 0)	//非同期で読み込んでいる処理が終わったら
	{

		SetUseASyncLoadFlag(FALSE);	//同期読み込みに設定

		this->SetInit();			//初期設定

		this->IsLoad = true;		//読み込み完了
	}

	return;		
}

//ロード画面の描画処理
void GAMEMANEGER::Draw_Scene_Load()
{

	if (IsLoad)	//読み込みが完了したら
	{
		DrawString(TEST_TEXT_X, TEST_TEXT_Y, PUSH_TEXT, COLOR_WHITE);	//プッシュ、のテキストを描画
	}
	else		//完了していなければ
	{
		DrawString(TEST_TEXT_X, TEST_TEXT_Y, LOAD_TEXT, COLOR_WHITE);	//読み込み中のテキストを描画
	}

	return;
}

//タイトル画面の処理
void GAMEMANEGER::Scene_Title()
{

	this->back->ChengeImage((int)TITLE_BACK);	//背景画像変更

	//リセット処理
	this->player->ChengeImage((int)PLAYER_IMG_NORMAL);		//描画するプレイヤーの画像を通常時の画像に変更
	this->enemy->ChengeImage((int)ENEMY_IMG_NORMAL);		//描画する敵の画像を通常時の画像に変更

	this->player->SetImagePos(PLAYER_START_X, PLAYER_START_Y);	//プレイヤーの描画位置を初期化
	this->enemy->SetImagePos(ENEMY_START_X, ENEMY_START_Y);		//敵の描画位置を初期化

	if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーを押されたら
	{
		this->NowScene = (int)SCENE_PLAY;	//プレイ画面へ
		this->StartTime = GetNowCount();	//計測開始時間取得
		this->WaitTime = GetRand((GAME_START_WAITTIME_MAX / 2)) + GAME_START_WAITTIME_MIN;	//待ち時間を設定
	}

	return;
}

//タイトル画面の描画処理
void GAMEMANEGER::Draw_Scene_Title()
{

	this->back->Draw(GAME_LEFT,GAME_TOP);	//背景描画

	DrawString(TEST_TEXT_X, TEST_TEXT_Y, TITLE_TEXT, COLOR_WHITE);	//テスト用のテキストを描画

	return;
}

//プレイ画面の処理
void GAMEMANEGER::Scene_Play()
{


	this->back->ChengeImage((int)PLAY_BACK);	//背景画像変更

	if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーを押されたら
	{
		this->NowScene = (int)SCENE_END;	//エンド画面へ
	}
	else if (this->keydown->IsKeyDownOne(KEY_INPUT_SPACE))	//スペースキーを押されたら
	{
		this->player->ChengeImage((int)PLAYER_IMG_ACT);		//描画するプレイヤーの画像をアクション後の画像に変更
		this->enemy->ChengeImage((int)ENEMY_IMG_ACT);		//描画する敵の画像をアクション後の画像に変更
	}

	return;
}

//プレイ画面の描画処理
void GAMEMANEGER::Draw_Scene_Play()
{

	this->back->Draw(GAME_LEFT, GAME_TOP);	//背景画像描画

	this->player->Draw();		//プレイヤー描画
	this->enemy->Draw();		//敵描画

	if (this->WaitStartTime())	//スタート時間まで待つ
	{
		this->mark->Draw(MARK_DRAW_X, MARK_DRAW_Y);	//マーク描画
	}

	DrawString(TEST_TEXT_X, TEST_TEXT_Y, PLAY_TEXT, COLOR_WHITE);	//テスト用のテキストを描画

	return;
}

//エンド画面の処理
void GAMEMANEGER::Scene_End()
{

	if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーを押されたら
	{
		this->NowScene = (int)SCENE_TITLE;	//タイトル画面へ
	}

	return;
}

//エンド画面の描画処理
void GAMEMANEGER::Draw_Scene_End()
{

	DrawString(TEST_TEXT_X, TEST_TEXT_Y, END_TEXT, COLOR_WHITE);	//テスト用のテキストを描画

	return;
}


//******************** プレイ画面で使用する処理関係 ***********************
//スタート時間まで待つ
bool GAMEMANEGER::WaitStartTime()
{

	if ((GetNowCount() - this->StartTime) / 1000 < this->WaitTime)	//待ち時間が過ぎていなければ
	{
		return false;
	}
	else 			//待ち時間が過ぎたら
	{
		return true;
	}
}
