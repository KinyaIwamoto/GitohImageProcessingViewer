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
	Setting,
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
BOOL glGetOpenFileName(
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
//MFCではinline関数にしないとテキストウインドウを破棄する時にエラーになる。
//void OpenRTextWindow(int txt_win_num, int txtw_w, int txtw_h, int imb_x, int imb_y, int width, int zoom_num, int margin);
inline void OpenRTextWindow(int txt_win_num, int txtw_w, int txtw_h, int imb_x, int imb_y, int width, int zoom_num, int margin)
{
	int txtw_x = imb_x + width * zoom_num / 100 + margin;
	int txtw_y = imb_y;
	ESP_OpenTextWindow(txt_win_num, txtw_x, txtw_y, txtw_w, txtw_h);
}

//カメラ用スレッド関数
unsigned __stdcall  PlayCamera(LPVOID lpParam);
//動画ファイル用スレッド関数
unsigned __stdcall  PlayVideo(LPVOID lpParam);

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
//common.hおよびgl*.h使用時は以下削除
//string型をwstring型に変換する。
std::wstring string_to_wstring(std::string const& src, UINT CodePage = CP_ACP);

//wstring型をstring型に変換する。
std::string wstring_to_string(std::wstring const& wsrc, UINT CodePage = CP_ACP);

//24bit Bitmapデータのサイズを設定する
void WINAPI glInitImageData(
	LPBYTE* BmpImage,		//Bitmapデータ
	long xsize,					//画像の幅サイズ
	long ysize						//画像の縦サイズ
);

//24bit Bitmapデータのサイズを設定する
LPBYTE glInitDIBImage(
	long xsize,					//画像の幅サイズ
	long ysize					//画像の縦サイズ
);

//BITMAPINFOの設定
void WINAPI glSetBmpInfo(
	LPBITMAPINFO* bmpinfo,	//BITMAPINFO
	long xsize,			//画像の幅サイズ
	long ysize,			//画像の縦サイズ
	long bitcount = 24		//1ピクセルあたりのビット数。この値は0,1,4,8,16,24,32のいずれかの値を取る。
);

//BGR形式の画像をDIBへ変換する
void glConvertBGRtoDIB(LPBYTE lpbyDib,
	LPBYTE lpbyBgr,
	const int width,
	const int height,
	const bool mode = TRUE
);

// イメージデータバッファの解放
void glDelImageBuffer(
	LPBYTE* CameraImage
);

//Bitmapデータのサイズを破棄する
void WINAPI glDeleteImageData(
	LPBYTE* BmpImage		//Bitmapデータ
);

//24bit Bitmapデータを上下反転する
 void WINAPI glBitmapFlipVertical(
	LPBYTE BmpImage24_in,	//元ビットマップデータ
	LPBYTE BmpImage24_out,	//上下反転後のビットマップデータ
	long width,				//元画像の幅サイズ
	long height,				//元画像の縦サイズ
	int* buf1Rimage = NULL,		//作業用画像バッファ
	int* buf1Gimage = NULL,		//作業用画像バッファ
	int* buf1Bimage = NULL,		//作業用画像バッファ
	int* buf2Rimage = NULL,		//作業用画像バッファ
	int* buf2Gimage = NULL,		//作業用画像バッファ
	int* buf2Bimage = NULL		//作業用画像バッファ
);

 //24Bit Bitmapデータ形式を32Bit Bitmapデータ形式に変換
void WINAPI glBmp24ToBmp32(
	 LPBYTE BmpImage24_in,			//24Bit Bitmap形式のデータ
	 LPBYTE BmpImage32_out,		//32Bit Bitmapデータ形式
	 long width,					//画像の幅サイズ
	 long height					//画像の縦サイズ
 );

//デバイスフォーマット文字列を対応するGUID値に変換する
GUID getStringAsMediaSubtype(tstring typestr);

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/