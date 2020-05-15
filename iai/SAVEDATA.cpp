//SAVEDATA.cpp
//セーブデータを管理するクラス

//################### ヘッダファイル読み込み ##################
#include "SAVEDATA.hpp"

//#################### クラス定義 #######################

//コンストラクタ
SAVEDATA::SAVEDATA()
{
	return;
}

//デストラクタ
SAVEDATA::~SAVEDATA()
{

	for (int i = 0; i < this->DataCode.size(); ++i)
	{
		delete this->DataCode.at(i);
	}

	//vectorのメモリ解放を行う
	std::vector<DATA*> v;			//空のvectorを作成する
	this->DataCode.swap(v);			//空と中身を入れ替える


	return;
}

//データ追加
void SAVEDATA::Add(int win_num)
{

	DATEDATA Date;		//現在時刻

	GetDateTime(&Date);	//現在時刻取得

	this->DataCode.push_back(new DATA(Date.Year,Date.Mon,Date.Day,win_num));	//データ情報追加

	return;

}

//セーブ
bool SAVEDATA::Save()
{

	struct stat statbuf;	//ディレクトリの存在確認に使用

	if (stat(SAVEDATA_DIR, &statbuf) != 0)//セーブデータ用のフォルダが作成されていない場合（初めてのセーブの場合）
	{
		_mkdir(SAVEDATA_DIR);	//セーブデータを格納するフォルダを作成
	}

	std::string LoadFile;
	LoadFile += SAVEDATA_DIR;
	LoadFile += SAVEDATA_NAME;

	std::ofstream ofs(LoadFile.c_str(), std::ios_base::ate);	//ファイルオープン

	if (!ofs)		//ファイルオープン失敗時
	{
		std::string ErrorMsg(DATA_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadFile;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(DATA_ERROR_TTILE),
			MB_OK);

		return false;		//セーブ失敗

	}

	//セーブデータを書き込む
	for (int i = 0; i < this->DataCode.size(); ++i)	//データの数だけループ
	{
		ofs << this->DataCode.at(i)->GetYear() << ',';				//年、書き出し
		ofs << this->DataCode.at(i)->GetMonth() << ',';				//月、書き出し
		ofs << this->DataCode.at(i)->GetDay() << ',';				//日、書き出し
		if (i == this->DataCode.size() - 1)	//最後の書き込みだったら
		{
			//終端文字を付ける
			ofs << this->DataCode.at(i)->GetWinNum() << '\0';			//勝ち数、書き出し
		}
		else	//最後の書き込みじゃなければ
		{
			//改行する
			ofs << this->DataCode.at(i)->GetWinNum() << '\n';			//勝ち数、書き出し
		}


	}

	return true;		//セーブ成功
}

//読み込み
bool SAVEDATA::Load()
{
	std::string LoadFile;
	LoadFile += SAVEDATA_DIR;
	LoadFile += SAVEDATA_NAME;

	std::ifstream ifs(LoadFile.c_str());	//ファイル読み取り

	if (!ifs)		//ファイルオープン失敗時
	{
		std::string ErrorMsg(DATA_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadFile;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(DATA_ERROR_TTILE),
			MB_OK);

		return false;	//読み込み失敗

	}


	std::string buf;
	int yy = 0, mm = 0, dd = 0, wn = 0;		//年、月、日、勝ち数

	while (!ifs.eof())				//最後の行まで読み込み
	{
		std::getline(ifs, buf,',');		//カンマまで読み込み
		yy = atoi(buf.c_str());			//年読み込み
		
		std::getline(ifs, buf, ',');	//カンマまで読み込み
		mm = atoi(buf.c_str());			//月読み込み

		std::getline(ifs, buf, ',');	//カンマまで読み込み
		dd = atoi(buf.c_str());			//日読み込み

		std::getline(ifs, buf, '\n');	//改行まで読み込み
		wn = atoi(buf.c_str());			//勝ち数読み込み

		this->DataCode.push_back(new DATA(yy, mm, dd, wn));		//データ追加

	}

	return true;	//読み込み成功
}

//**************** ソート関係 ******************
//セーブデータを降順に並べ替える
void SAVEDATA::Sort()
{

	this->QuiqSort(this->GetMinWinNum(), this->GetMaxWinNum());	//クイックソート

	return;
}

//クイックソート
void SAVEDATA::QuiqSort(int left, int right)
{
	int pivot = 0;

	if (left < right)
	{
		pivot = this->Partition(left, right);
		this->QuiqSort(left, pivot - 1);		//pivotを境に再帰的にクイックソート
		this->QuiqSort(pivot + 1, right);		//pivotを境に再帰的にクイックソート
	}
	return;
}

//pivotを決め、pivotを境目に振り分けをする
int SAVEDATA::Partition(int left,int right)
{

	int i = 0, j = 0, pivot = 0;	//初期化
	i = left;
	j = right + 1;
	pivot = left;		//先頭要素をpivotとする

	do
	{

		do { ++i; } while (this->DataCode.at(i)->GetWinNum() > this->DataCode.at(pivot)->GetWinNum());
		do { --j; } while (this->DataCode.at(pivot)->GetWinNum() > this->DataCode.at(j)->GetWinNum());

		//pivotより小さいものを左へ、大きいものを右へ
		if (i < j)
		{
			this->Swap(this->DataCode.at(pivot), this->DataCode.at(j));	//pivotを更新
		}

	} while (i<j);

	return;
}

//値を交換する
void SAVEDATA::Swap(DATA *i, DATA *j)
{
	auto temp = *i;	//値を一時保管する
	*i = *j;
	*j = temp;

	return;
}

//勝ち数の最大値を取得
int SAVEDATA::GetMaxWinNum()
{
	int max_value = 0;	//最大値格納用

	for (int i = 0; i < this->DataCode.size(); ++i)	//データの数分ループ
	{
		if (this->DataCode.at(i)->GetWinNum() > max_value)	//現在の最大値より大きかったら
		{
			max_value = this->DataCode.at(i)->GetWinNum();	//最大値更新
		}
	}

	return max_value;
}

//勝ち数の最小値を取得
int SAVEDATA::GetMinWinNum()
{
	int min_value = 99;		//最小値格納用

	for (int i = 0; i < this->DataCode.size(); ++i)
	{
		if (this->DataCode.at(i)->GetWinNum() < min_value)	//現在の最小値より大きかったら
		{
			min_value = this->DataCode.at(i)->GetWinNum();	//最小値更新
		}
	}

	return min_value;

}
