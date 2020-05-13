/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* IMAGE.cpp     																				　 */
/*       																						　 */

//########## ヘッダーファイル読み込み ##########
#include "IMAGE.hpp"

//########## クラスの定義 ##########

//コンストラクタ
//引　数：const char *：画像のディレクトリ
//引　数：const char *：画像の名前
IMAGE::IMAGE(const char *dir,const char *name)
{
	//メンバ変数を初期化
	this->FilePath = "";	//パス
	this->FileName = "";	//名前
	
	this->ImageKind = 0;	//読み込んだ画像の種類
	this->Draw_Num = 0;		//描画する画像の番号

	this->IsLoad = false;	//読み込めたか？

	//画像を読み込み
	std::string LoadfilePath;	//画像のファイルパスを作成
	LoadfilePath += dir;
	LoadfilePath += name;

	this->Handle.push_back(LoadGraph(LoadfilePath.c_str()));//画像を読み込み
	
	if (this->Handle.back() == -1)	//画像が読み込めなかったとき
	{
		std::string ErroeMsg(IMAGE_ERROR_MSG);	//エラーメッセージ作成
		ErroeMsg += TEXT('\n');					//改行
		ErroeMsg += LoadfilePath;				//画像のパス

		MessageBox(
			NULL, 
			ErroeMsg.c_str(),	//char * を返す
			TEXT(IMAGE_ERROR_TITLE),
			MB_OK);

		return;
	}

	this->FilePath = LoadfilePath;		//画像のパスを設定
	this->FileName = name;				//画像の名前を設定

	this->IsLoad = true;		//読み込めた

	this->IsDraw.push_back(true);	//描画してよい

	this->ImageKind = this->Handle.size();	//読み込んだ数を取得

	return;
}

//デストラクタ
IMAGE::~IMAGE()
{
	for (int handle : this->Handle)
	{
		DeleteGraph(handle);		//読み込んだ画像を削除
	}

	//vectorのメモリ解放を行う
	std::vector<int> v;			//空のvectorを作成する
	this->Handle.swap(v);		//空と中身を入れ替える

	std::vector<int>v2;
	this->Width.swap(v2);

	std::vector<int>v3;
	this->Height.swap(v3);

	std::vector<bool>v4;
	this->IsDraw.swap(v4);

	return;
}

//ファイルの名前を取得
std::string IMAGE::GetFileName(void)
{
	return this->FileName;
}

//サイズを設定する
void IMAGE::SetSize(void)
{
	this->Width.resize(this->Handle.size());	//サイズ変更
	this->Height.resize(this->Handle.size());	//サイズ変更
	//画像の数だけループする
	for (int i = 0; i < this->Handle.size(); ++i)
	{
		GetGraphSize(this->Handle[i], &this->Width[i], &this->Height[i]);	//画像サイズ取得
	}
	return;
}

//幅を取得
int IMAGE::GetWidth()
{
	return this->Width[this->Draw_Num];
}

//高さを取得
int IMAGE::GetHeight()
{
	return this->Height[this->Draw_Num];
}

//読み込めた？
bool IMAGE::GetIsLoad(void)
{
	return this->IsLoad;
}

//描画してよいか設定
void IMAGE::SetIsDraw(bool isdraw)
{
	this->IsDraw[this->Draw_Num] = isdraw;
	return;
}

//画像を描画
void IMAGE::Draw(int x, int y)
{
	
	if (this->IsDraw[this->Draw_Num])	//描画してよければ
	{
		DrawGraph(x, y, this->Handle[this->Draw_Num], TRUE);	//画像を描画
	}

	return;

}

//画像を描画（中央）
//引数：int：画面の横幅
//引数：int：描画する高さ
void IMAGE::DrawCenter(int width,int y)
{

	int x = 0;	//描画するX位置
	x = (width / 2) - (this->Width[this->Draw_Num] / 2);	//画面中央になるように計算

	if (this->IsDraw[this->Draw_Num])	//描画してよければ
	{
		DrawGraph(x, y, this->Handle[this->Draw_Num], TRUE);	//画像を描画
	}

	return;
}

//画像を追加
//引　数：const char *：画像のディレクトリ
//引　数：const char *：画像の名前
bool IMAGE::AddImage(const char *dir, const char *name)
{

	this->IsLoad = false;	//読み込めていない

	//画像を読み込み
	std::string LoadfilePath;	//画像のファイルパスを作成
	LoadfilePath += dir;
	LoadfilePath += name;

	this->Handle.push_back(LoadGraph(LoadfilePath.c_str()));	//画像を読み込み


	if (this->Handle.back() == -1)	//画像が読み込めなかったとき
	{
		std::string ErroeMsg(IMAGE_ERROR_MSG);	//エラーメッセージ作成
		ErroeMsg += TEXT('\n');					//改行
		ErroeMsg += LoadfilePath;				//画像のパス

		MessageBox(
			NULL,
			ErroeMsg.c_str(),	//char * を返す
			TEXT(IMAGE_ERROR_TITLE),
			MB_OK);

		return false;
	}

	this->IsLoad = true;		//読み込めた

	this->IsDraw.push_back(true);	//描画してよい

	this->ImageKind = this->Handle.size();	//読み込んだ数を取得

	return true;

}

//描画する画像を変更
void IMAGE::ChengeImage(int kind)
{
	this->Draw_Num = kind;
	return;
}

//指定された、画像をフェードアウトさせる
//引数：int：フェードアウトさせる、画像のX位置
//引数：int：フェードアウトさせる、画像のY位置
//引数：int：フェードアウトさせる、画像の種類
bool IMAGE::FadeOut(int x,int y,int kind)
{
	static int cnt = 0;				//カウント用
	static bool end_flg = false;	//フェード終了フラグ

	if (!end_flg)	//フェードアウト終了していなければ
	{
		//60フレーム分、待つ
		if (cnt < FADE_MAX_CNT)
		{
			++cnt;	//カウントアップ
		}
		else
		{
			end_flg = true;	//フェード終了
		}

		//フェードアウトの処理
		double ToukaPercent = cnt / (double)FADE_MAX_CNT;											//透過%を計算
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, ToukaPercent * TOUKA_MAX_VALUE);					//透過させる
		DrawBox(x, y, this->Width.at(kind), this->Height.at(kind), GetColor(0, 0, 0), TRUE);	//真っ暗な画面にする
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);												//透過をやめる

	}
	else if (end_flg)	//フェードアウト終了したら
	{
		cnt = 0;			//カウントリセット
		end_flg = false;	//終了フラグリセット
	}

	return true;

}
