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
	this->GameStartFlg = false;				//ゲーム始まっていない。
	this->Play_NowStage = (int)PLAY_STAGE_TEXT_DRAW;	//プレイシーンの現在の段階を初期化

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
	delete this->text_image;//text_image破棄
	delete this->player;	//player破棄
	delete this->enemy;		//enemy破棄
	delete this->se;		//se破棄

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
	this->mark->SetIsDraw(false);							//最初は描画してはいけない
	//テキスト画像
	this->text_image = new IMAGE(IMG_DIR_TEXT, IMG_NAME_TEXT_WIN);	//テキスト画像を生成
	if (this->text_image->GetIsLoad() == false) { return false; }	//読み込み失敗
	if (this->text_image->AddImage(IMG_DIR_TEXT, IMG_NAME_TEXT_LOSE) == false) { return -1; }	//敗北テキスト追加
	if (this->text_image->AddImage(IMG_DIR_TEXT, IMG_NAME_TEXT_DRAW) == false) { return -1; }	//引き分けテキスト追加
	if (this->text_image->AddImage(IMG_DIR_TEXT, IMG_NAME_TEXT_OTETUKI) == false) { return -1; }//お手付きテキスト追加

	//プレイヤー関係
	this->player = new PLAYER(IMG_DIR_PLAYER, IMG_NAME_PLAYER);		//プレイヤー生成
	if (this->player->GetIsLoad() == false) { return false; }		//読み込み失敗
	if (this->player->AddImage(IMG_DIR_PLAYER, IMG_NAME_PLAYER_ACT) == false) { return false; }	//画像追加

	//敵関係
	this->enemy = new ENEMY(IMG_DIR_ENEMY, IMG_NAME_ENEMY);		//敵生成
	if (this->enemy->GetIsLoad() == false) { return false; }	//読み込み失敗
	if (this->enemy->AddImage(IMG_DIR_ENEMY, IMG_NAME_ENEMY_ACT) == false) { return false; }	//画像追加

	//音関係
	//SE
	this->se = new MUSIC(MUSIC_DIR_SE, SE_NAME_GAMESTART);		//SEを管理するオブジェクトを生成
	if (this->se->GetIsLoad() == false) { return false; }		//読み込み失敗
	if (this->se->Add(MUSIC_DIR_SE, SE_NAME_GAMEOVER) == false) { return false; }	//ゲームオーバーの音を追加

	//音量変更
	this->se->ChengeVolume(50.0, (int)SE_TYPE_GAMESTART);	//ゲームスタートの音量を50%に変更
	this->se->ChengeVolume(50.0, (int)SE_TYPE_GAMEOVER);	//ゲームオーバーの音量を50%に変更

	return true;	//読み込み成功
}

//画像などのサイズを取得し、設定する
void GAMEMANEGER::SetSize()
{
	this->back->SetSize();			//背景画像、サイズ設定
	this->mark->SetSize();			//マーク画像サイズ設定
	this->text_image->SetSize();	//テキスト画像サイズ設定

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

	if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーを押されたら
	{
		this->NowScene = (int)SCENE_PLAY;	//プレイ画面へ
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

	switch (this->Play_NowStage)		//現在の段階ごとに処理を分ける
	{

	case (int)PLAY_STAGE_TEXT_DRAW:		//テキスト表示段階のとき

		this->PlayStage_DrawText();		//テキスト表示段階の処理

		break;			//テキスト表示段階ここまで

	case (int)PLAY_STAGE_MAIN:		//ゲームプレイ中のとき

		this->PlayStage_Main();		//ゲームプレイ中のときの処理

		break;		//ゲームプレイ中のときここまで

	case (int)PLAY_STAGE_RESULT:	//結果表示のとき

		this->PlayStage_Result();	//結果表示段階の処理

		break;		//結果表示ここまで

	default:
		break;
	}


	if (this->keydown->IsKeyDownOne(KEY_INPUT_SPACE))	//スペースキーを押されたら
	{
		this->NowScene = (int)SCENE_END;	//エンド画面へ
	}

	return;
}

//プレイ画面の描画処理
void GAMEMANEGER::Draw_Scene_Play()
{

	this->back->Draw(GAME_LEFT, GAME_TOP);	//背景画像描画

	this->player->Draw();		//プレイヤー描画
	this->enemy->Draw();		//敵描画

	this->mark->DrawCenter(GAME_WIDTH, MARK_DRAW_Y);	//マーク描画

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

//プレイ画面で使用するものをリセット
void GAMEMANEGER::PlayReset()
{
	this->player->ChengeImage((int)PLAYER_IMG_NORMAL);		//描画するプレイヤーの画像を通常時の画像に変更
	this->enemy->ChengeImage((int)ENEMY_IMG_NORMAL);		//描画する敵の画像を通常時の画像に変更

	this->player->SetImagePos(PLAYER_START_X, PLAYER_START_Y);	//プレイヤーの描画位置を初期化
	this->enemy->SetImagePos(ENEMY_START_X, ENEMY_START_Y);		//敵の描画位置を初期化

	this->mark->SetIsDraw(false);			//マークを描画してはいけない
	this->GameStartFlg = false;				//ゲームスタートしない

	this->Play_NowStage = (int)PLAY_STAGE_TEXT_DRAW;	//プレイシーンの現在の段階を初期化

	this->StartTime = GetNowCount();	//計測開始時間取得
	this->WaitTime = GetRand((GAME_START_WAITTIME_MAX / 2)) + GAME_START_WAITTIME_MIN;	//待ち時間を設定

	return;

}

//どちらが勝ったか判定
void GAMEMANEGER::Judg()
{
	//キーを押すまでにかかった時間を基に、どちらが勝ったか判定する
	if (this->player->GetPushTime() < enemy->GetSpeed())		//押すのにかかった時間が、敵のスピードより速かったら
	{
		this->player->IncreaseWinNum();					//勝ち数を増やす
		this->player->SetResult((int)RESULT_WIN);		//結果を設定(勝利)
	}
	else if (this->player->GetPushTime() > enemy->GetSpeed())		//敵より遅かったら
	{
		this->player->SetResult((int)RESULT_LOSE);		//結果を設定(敗北)
	}
	else		//引き分けだったら
	{
		this->player->SetResult((int)RESULT_DRAW);		//結果を設定(引き分け)
	}

	return;

}

//プレイ段階、テキスト表示のときの処理
void GAMEMANEGER::PlayStage_DrawText()
{

	this->se->Play((int)SE_TYPE_GAMESTART);		//ゲームスタートのSEを鳴らす

	this->PlayReset();	//プレイ関係リセット

	this->Play_NowStage = (int)PLAY_STAGE_MAIN;	//ゲームプレイ段階へ

	return;
}

//プレイ段階、ゲーム中のときの処理
void GAMEMANEGER::PlayStage_Main()
{
	if (this->GameStartFlg)	//ゲームが始まったら
	{
		if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーを押されたら
		{
			this->player->ChengeImage((int)PLAYER_IMG_ACT);				//描画するプレイヤーの画像をアクション後の画像に変更
			this->player->SetImagePos(PLAYER_AFTER_X, PLAYER_AFTER_Y);	//描画する位置をアクション後の位置に変更
			this->enemy->ChengeImage((int)ENEMY_IMG_ACT);				//描画する敵の画像をアクション後の画像に変更
			this->enemy->SetImagePos(ENEMY_AFTER_X, ENEMY_AFTER_Y);		//描画位置をアクション後の位置に変更

			this->mark->SetIsDraw(false);	//マーク非表示

			this->player->SetPushTime((GetNowCount() - this->StartTime));	//押すまでにかかった時間を設定

			this->Judg();		//どちらが勝ったか判定

			this->Play_NowStage = (int)PLAY_STAGE_RESULT;	//結果表示段階へ

		}

	}
	else					//ゲームが始まっていなかったら
	{

		if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//エンターキーを押されたら
		{

			this->player->SetResult((int)RESULT_OTETUKI);	//結果をお手付きに設定

			this->Play_NowStage = (int)PLAY_STAGE_RESULT;	//結果表示段階へ

		}

		//ゲームが始まるまで待つ
		if (this->WaitStartTime())	//スタート時間になったら
		{
			this->mark->SetIsDraw(true);		//マークを描画してよい
			this->StartTime = GetNowCount();	//マークを描画し始めた時間をスタート時間に設定
			this->GameStartFlg = true;			//ゲームスタート
		}
	}

	return;

}

//プレイ段階、結果表示のときの処理
void GAMEMANEGER::PlayStage_Result()
{

	//結果毎に処理を分岐
	switch (this->player->GetResult())
	{

	case (int)RESULT_WIN:		//プレイヤーが勝った時

		this->text_image->ChengeImage((int)TEXT_IMG_WIN);		//表示するテキストを勝利テキストに変更

		this->text_image->DrawCenter(GAME_WIDTH, TEXT_DRAW_Y);	//勝利テキスト描画

		if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//エンターキーを押されたら
		{
			this->Play_NowStage = (int)PLAY_STAGE_TEXT_DRAW;	//テキスト表示段階へ
			this->PlayReset();	//ゲームに使用したデータをリセット
		}


		break;		//プレイヤーが勝った時ここまで

	case (int)RESULT_LOSE:		//プレイヤーが負けたとき

		this->text_image->ChengeImage((int)TEXT_IMG_LOSE);	//表示するテキストを敗北テキストに変更

		this->text_image->DrawCenter(GAME_WIDTH, TEXT_DRAW_Y);	//敗北テキスト描画

		this->se->Play((int)SE_TYPE_GAMEOVER);		//ゲームオーバーの音を鳴らす

		if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//エンターキーを押されたら
		{
			this->NowScene = (int)SCENE_END;	//エンド画面へ
			this->PlayReset();	//ゲームに使用したデータをリセット
		}

		break;		//プレイヤーが負けたときここまで

	case (int)RESULT_DRAW:		//引き分けのとき


		this->text_image->ChengeImage((int)TEXT_IMG_DRAW);	//表示するテキストを引き分けテキストに変更

		this->text_image->DrawCenter(GAME_WIDTH, TEXT_DRAW_Y);	//引き分けテキスト描画

		if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//エンターキーを押されたら
		{
			this->Play_NowStage = (int)PLAY_STAGE_TEXT_DRAW;	//テキスト表示段階へ
			this->PlayReset();	//ゲームに使用したデータをリセット
		}

		break;		//引き分けのときここまで

	case (int)RESULT_OTETUKI:		//お手付きのとき

		this->text_image->ChengeImage((int)TEXT_IMG_OTETUKI);	//描画するテキストをお手付き画像に変更
		this->text_image->DrawCenter(GAME_WIDTH, TEXT_DRAW_Y);	//お手付き画像を描画

		if (this->keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//エンターキーを押されたら
		{
			this->Play_NowStage = (int)PLAY_STAGE_TEXT_DRAW;	//テキスト表示段階へ
			this->PlayReset();	//ゲームに使用したデータをリセット
		}

		break;		//お手付きのときここまで

	default:
		break;
	}

	return;
}
