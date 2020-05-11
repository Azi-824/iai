//EFFECT.cpp
//エフェクトクラス

//################## ヘッダファイル読み込み ##################
#include "EFFECT.hpp"

//################## クラス定義 #######################

//コンストラクタ
/*
引　数：const char *：画像のディレクトリ
引　数：const char *：画像の名前
引　数：int：画像の総分割数
引　数：int：画像の横向きの分割数
引　数：int：画像の縦向きの分割数
引　数：int：画像の分割された横の大きさ
引　数：int：画像の分割された縦の大きさ
引　数：double：次の画像に変更する速さ
引　数：bool：アニメーションをループするかどうか
引　数：int：FPSの速度
*/
EFFECT::EFFECT(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop,int fps_spd)
{

	this->IsLoad = false;			//読み込めたか？
	this->IsDrawEnd = false;		//描画終了したか?

	//画像を読み込み
	std::string LoadfilePath;		//画像のファイルパスを作成
	LoadfilePath += dir;
	LoadfilePath += name;

	std::vector<int> work(SplitNumALL);	//分割読み込みで得たハンドルを格納する配列を総分割数で初期化

	//画像を分割して読み込み
	LoadDivGraph(LoadfilePath.c_str(), SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, &work.front());
	this->Handle.push_back(work);
	
	if (this->Handle.front().front() == -1)	//画像が読み込めなかったとき
	{
		std::string ErrorMsg(EFFECT_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadfilePath;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(EFFECT_ERROR_TTILE),
			MB_OK);

		return;
	}

	this->ChangeMaxCnt.push_back(fps_spd * changeSpeed);
	this->ChangeCnt = 0;	//アニメーションするフレームのカウント

	this->NextChangeSpeed.push_back(changeSpeed);	//画像を変える速さ

	this->IsAnimeLoop.push_back(IsLoop);	//アニメーションがループするか
	this->IsAnimeStop.push_back(false);		//アニメーションを動かす

	this->Handle_itr = this->Handle.front().begin();	//先頭要素をイテレータに設定

	this->IsLoad = true;		//読み込めた

	//vectorのメモリ解放を行う
	std::vector<int> v;			//空のvectorを作成する
	work.swap(v);				//空と中身を入れ替える

	return;

}

//デストラクタ
EFFECT::~EFFECT()
{
	for (int i = 0; i < this->Handle.size(); ++i)
	{
		DeleteGraph(this->Handle[i][0]);
	}

	//vectorのメモリ解放を行う
	std::vector<std::vector<int>> v;			//空のvectorを作成する
	this->Handle.swap(v);						//空と中身を入れ替える

	std::vector<int> v2;
	this->Width.swap(v2);

	std::vector<int> v3;
	this->Height.swap(v3);

	std::vector<bool> v4;
	this->IsAnimeLoop.swap(v4);

	std::vector<bool> v5;
	this->IsAnimeStop.swap(v5);

	std::vector<double> v6;
	this->NextChangeSpeed.swap(v6);

	std::vector<int> v7;
	this->ChangeMaxCnt.swap(v7);

	return;

}

//幅を取得
int EFFECT::GetWidth(int type)
{
	return this->Width[type];
}

//高さを取得
int EFFECT::GetHeight(int type)
{
	return this->Height[type];
}

//読み込めた？
bool EFFECT::GetIsLoad(void)
{
	return this->IsLoad;
}

//アニメーションはストップしたかを取得
bool  EFFECT::GetIsAnimeStop(int type)
{
	return this->IsAnimeStop[type];
}

//描画終了したかどうか取得
bool EFFECT::GetIsDrawEnd()
{
	return this->IsDrawEnd;
}

//描画終了したか設定
void EFFECT::SetIsDrawEnd(bool isend)
{
	this->IsDrawEnd = isend;
	return;
}

//アニメーションがストップしたかをリセット
void EFFECT::ResetIsAnime(int type)
{
	this->IsAnimeStop[type] = false;
	this->IsDrawEnd = false;		
	return;
}

//描画
/*
引数：int：Xの描画位置
引数：int：Yの描画位置
引数：int：描画するエフェクトの種類
*/
void EFFECT::Draw(int x, int y, int type)
{
	static bool setflg = false;	//ハンドル設定フラグ
	if (setflg == false)
	{
		this->Handle_itr = this->Handle[type].begin();		//指定されたエフェクトタイプのハンドルを代入
		setflg = true;	//ハンドル設定済み
	}

		if (this->IsAnimeStop[type] == false)	//アニメーションをストップさせないなら
		{
			DrawGraph(x, y, *this->Handle_itr, TRUE);	//イテレータ(ポインタ)を使用して描画
		}
		else
		{
			this->IsDrawEnd = true;		//描画終了
			setflg = false;				//ハンドル未設定
		}

		if (this->ChangeCnt == this->ChangeMaxCnt.at(type))	//次の画像を表示する時がきたら
		{
			//this->Handle.end()は、最後の要素の１個次のイテレータを返すので、-1している。
			if (this->Handle_itr == this->Handle[type].end() - 1)	//イテレータ(ポインタ)が最後の要素のときは
			{
				//アニメーションをループしないなら
				if (this->IsAnimeLoop[type] == false)
				{
					this->IsAnimeStop[type] = true;	//アニメーションを止める
				}

				//次回の描画に備えて、先頭の画像に戻しておく
				this->Handle_itr = this->Handle[type].begin();	//イテレータ(ポインタ)を要素の最初に戻す
			}
			else
			{
				this->Handle_itr++;	//次のイテレータ(ポインタ)(次の画像)に移動する
			}

			this->ChangeCnt = 0;	//カウント初期化
		}
		else
		{
			this->ChangeCnt++;	//カウントアップ
		}

	return;

}


//追加
/*
引　数：const char *：画像のディレクトリ
引　数：const char *：画像の名前
引　数：int：画像の総分割数
引　数：int：画像の横向きの分割数
引　数：int：画像の縦向きの分割数
引　数：int：画像の分割された横の大きさ
引　数：int：画像の分割された縦の大きさ
引　数：double：次の画像に変更する速さ
引　数：bool：アニメーションをループするかどうか
引　数：int：FPSの速度
*/
bool EFFECT::Add(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop,int fps_spd)
{
	this->IsAnimeLoop.push_back(IsLoop);		//アニメーションはループする？
	this->IsAnimeStop.push_back(false);			//アニメーションを動かす

	//画像を読み込み
	std::string LoadfilePath;		//画像のファイルパスを作成
	LoadfilePath += dir;
	LoadfilePath += name;

	std::vector<int> work(SplitNumALL);	//分割読み込みで得たハンドルを、格納する配列を総分割数で初期化

	//画像を分割して読み込み
	LoadDivGraph(LoadfilePath.c_str(), SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, &work.front());
	this->Handle.push_back(work);	//ハンドルを格納

	if (this->Handle.back().front() == -1)	//画像が読み込めなかったとき
	{
		std::string ErrorMsg(EFFECT_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadfilePath;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(EFFECT_ERROR_TTILE),
			MB_OK);

		return false;		//読み込み失敗
	}

	this->Handle_itr = this->Handle.back().begin();		//先頭要素をイテレータに設定

	this->ChangeMaxCnt.push_back(fps_spd * changeSpeed);
	this->NextChangeSpeed.push_back(changeSpeed);		//次の画像に変更する速さ

	//vectorのメモリ解放を行う
	std::vector<int> v;			//空のvectorを作成する
	work.swap(v);				//空と中身を入れ替える

	return true;		//読み込めた

}

//サイズ設定
void EFFECT::SetSize(void)
{
	//エフェクトの数だけループさせる
	for (int i = 0; i < this->Handle.size(); ++i)
	{
		GetGraphSize(this->Handle[i][0], &this->Width[i], &this->Height[i]);	//サイズ取得
	}
}
