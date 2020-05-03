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
int IMAGE::GetWidth(int kind)
{
	return this->Width[kind];
}

//高さを取得
int IMAGE::GetHeight(int kind)
{
	return this->Height[kind];
}

//読み込めた？
bool IMAGE::GetIsLoad(void)
{
	return this->IsLoad;
}

//画像を描画（指定しない場合、先頭の画像）
void IMAGE::Draw(int x, int y, int type)
{
	DrawGraph(x, y, this->Handle[type], TRUE);	//指定された画像を描画
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

	this->ImageKind = this->Handle.size();	//読み込んだ数を取得

	return true;

}
