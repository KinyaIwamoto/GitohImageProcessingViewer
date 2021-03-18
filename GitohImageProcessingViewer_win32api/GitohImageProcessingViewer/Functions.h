#pragma once
#include <tchar.h>
#include <vector>
#include <string>

#ifndef tstring
typedef std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> > tstring;
#endif // !tstring


#define MAXFORMAT 100   //取得数の上限

//	カメラフォーマットを保存するクラス
struct RES 
{
	std::string name;
	int	width;
	int height;
	double frame;
	std::string  format;
};

struct PARAM
{
	int device_num;
	RES format;
};

template<typename T>
struct SHRAEMEMORY 
{
	HANDLE handle;
	T* memory;
};

enum BUTTON_NUM
{
	Ope,
	OpenClose,
	StartStop,
	PauseRestart,
	Repeat,
	Exit
};

enum OPE_NUM
{
	Before = -1,
	Camera,
	Video,
	image,
	End
} ;

//ファイルを開くダイアログWin32APIのラッパー
BOOL GetOpenFileName(
	tstring* FileFullPath, 
	tstring* FileName, 
	tstring InitialDir, 
	const TCHAR* Filter
);

//イメージウインドウの位置、大きさ、表示倍率の算出
void ImageWindowPositioning(
	int width,				//画像の幅
	int height,				//画像の高さ
	int dtwidth,			//デスクトップの幅
	int bw_y,				//ボタンウインドウの上端
	int* imb_x,			//イメージウインドウの左上X座標
	int* imb_y,			//イメージウインドウの左上Y座標
	int* zoom_num		//表示倍率
);

//接続されているカメラの情報を集める
std::vector<std::vector<RES>> CamInit();

//共有メモリの初期化
HANDLE InitShareMemory(tstring memortname, size_t typesize, LPVOID* lpmemory);

template<typename T>
SHRAEMEMORY<T> InitShareMemory(tstring memortname)
{
	SHRAEMEMORY<T> memory;
	memory.handle = InitShareMemory(memortname, sizeof(T), (LPVOID*)&(memory.memory));
	return memory;
}

//共有メモリを開く
HANDLE OpenShareMemory(tstring memortname, LPVOID* lpmemory);

template<typename T>
SHRAEMEMORY<T> OpenShareMemory(tstring memortname)
{
	SHRAEMEMORY<T> memory;
	memory.handle = OpenShareMemory(memortname, (LPVOID*)&(memory.memory));
	return memory;
}

//共有メモリを閉じる
void CloseShareMemory(HANDLE hmemory, LPVOID* lpmemory);

template<typename T>
void CloseShareMemory(SHRAEMEMORY<T>memory)
{
	CloseShareMemory(memory.handle, (LPVOID*)&(memory.memory));
}

//カメラフォーマットの選択
RES SelectCameraFormat(const int dtcenter_x, const int bw_y, std::vector<std::vector<RES>> cam_formats, int& use_cam_num);

//イメージウインドウ右側のテキストウインドウを開く
void OpenRTextWindow(int txt_win_num, int txtw_w, int txtw_h, int imb_x, int imb_y, int width, int zoom_num, int margin);

//カメラ用スレッド関数
unsigned __stdcall  PlayCamera(LPVOID lpParam);
//動画ファイル用スレッド関数
unsigned __stdcall  PlayVideo(LPVOID lpParam);

//string型をwstring型に変換する。
std::wstring string_to_wstring(std::string const& src, UINT CodePage = CP_ACP);

//wstring型をstring型に変換する。
std::string wstring_to_string(std::wstring const& wsrc, UINT CodePage = CP_ACP);

//デバイスフォーマット文字列を対応するGUID値に変換する
GUID getStringAsMediaSubtype(tstring typestr);
