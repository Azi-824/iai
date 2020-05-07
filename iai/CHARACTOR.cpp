//CHARACTOR.cpp
//キャラクタークラス

//################# ヘッダファイル読み込み #####################
#include "CHARACTOR.hpp"

//################ クラス定義 ########################
//コンストラクタ
CHARACTOR::CHARACTOR()
{
	//メンバー変数初期化
	this->IsArive = false;	//死んでいる
	this->IsLoad = false;	//読み込めていない

	return;
}

//デストラクタ
CHARACTOR::~CHARACTOR()
{
	delete this->image;		//image削除
	delete this->sikaku_draw;	//sikaku_draw削除

	return;
}

//生きているか設定
void CHARACTOR::SetIsArive(bool Isarive)
{
	this->IsArive = Isarive;
	return;
}

//画像を設定
void CHARACTOR::SetImage(const char *dir, const char *name)
{
	this->image = new IMAGE(dir, name);
	this->IsLoad = this->image->GetIsLoad();	//読み込めたか設定

	return;

}

//横幅を取得
int CHARACTOR::GetWidth()
{
	return this->image->GetWidth(0);
}

//高さを取得
int CHARACTOR::GetHeight()
{
	return this->image->GetHeight(0);
}

//画像の位置を設定する
void CHARACTOR::SetImagePos(int x, int y)
{

	this->sikaku_draw->Left = x;
	this->sikaku_draw->Top = y;

	//描画領域
	this->sikaku_draw->SetValue(
		this->sikaku_draw->Left,
		this->sikaku_draw->Top,
		this->sikaku_draw->Width,
		this->sikaku_draw->Height
	);

}

//生きているか取得
bool CHARACTOR::GetIsArive()
{
	return this->IsArive;
}

//読み込めたか取得
bool CHARACTOR::GetIsLoad()
{
	return this->IsLoad;
}

//操作
void CHARACTOR::Operation(KEYDOWN *keydown)
{

	//if (keydown->IsKeyDown(KEY_INPUT_W))		//Wキーを押しているとき
	//{
	//	this->MoveUp();							//上へ移動
	//}
	//else if (keydown->IsKeyDown(KEY_INPUT_S))	//Sキーを押しているとき
	//{
	//	this->MoveDown();						//下へ移動
	//}
	//else if (keydown->IsKeyDown(KEY_INPUT_A))	//Aキーを押しているとき
	//{
	//	this->MoveLeft();						//左へ移動
	//}
	//else if (keydown->IsKeyDown(KEY_INPUT_D))	//Dキーを押しているとき
	//{
	//	this->MoveRight();						//右へ移動
	//}

	//描画領域再設定
	this->sikaku_draw->SetValue(
		this->sikaku_draw->Left,
		this->sikaku_draw->Top,
		this->sikaku_draw->Width,
		this->sikaku_draw->Height);

	return;
	
}

//初期化設定
void CHARACTOR::SetInit()
{

	this->image->SetSize();		//画像サイズ設定


	this->sikaku_draw = new SIKAKU();		//描画領域を作成
	this->sikaku_draw->SetValue(0, 0, this->image->GetWidth(), this->image->GetHeight());	//当たり判定の領域を設定

	this->IsArive = true;	//生きている

	return;

}

//描画
void CHARACTOR::Draw()
{
	if (this->IsArive)	//生きていれば
	{
			this->image->Draw(this->sikaku_draw->Left, this->sikaku_draw->Top);	//画像描画
	}
}
