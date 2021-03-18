#pragma once
#include <dshow.h>
#include "qedit.h"

#ifndef EWC_NCAMMAX
#define EWC_NCAMMAX 10	//カメラの最大認識数v2.2
#endif

#ifndef EWC_BUF_NUM
#define EWC_BUF_NUM	 1	//リングバッファ数（1以上の整数）v2.6
#endif

#define EWC_VPAMPMAX	10
#define EWC_CAMCTLMAX	7
#define EWC_ITEMMAX		(EWC_VPAMPMAX+EWC_CAMCTLMAX)

//構造体の定義
struct ewc_struct {
	int wx;					//画像の幅
	int wy;					//画像の高さ
	double fps;				//フレームレート（引数指定値）
	int device;				//物理デバイス番号（引数指定値）
	int devn;				//割り当てられた物理デバイス番号v2.2
	char* pdname;			//FriendlyName比較用v2.2
	char dname[256];		//取得したFriendlyName v2.2
	GUID mstype;			//出力画像のフォーマット
	char mstype_t[80];		//mstypeに対応する文字列v2.3
	GUID dev_mstype;		//デバイス出力ピンのフォーマットv2.3
	char dev_mstype_t[80];	//dev_mstypeに対応する文字列v2.3
	volatile int init;
	volatile int stop;
	volatile int errcode;
	int* pbuf;				//画像の保存先
	int* buffer;			//内部で確保したフレームバッファ
	volatile long bufsize;	//得られた画像データのバイト数
	volatile double ftime;	//フレーム周期(s)の実測値（最新値）
	volatile int w_count;	//writeしたカウンタ値v2.6
	volatile int r_count;	//readしたカウンタ値v2.6
	volatile int buffer_r;	//バッファの選択(read)v2.6
	volatile int buffer_w;	//バッファの選択(write)v2.6
	volatile double buf_stime[EWC_BUF_NUM];	//各バッファのサンプル時刻(s)v2.6
	volatile int buf_count[EWC_BUF_NUM];	//各バッファのカウンタ値v2.6
	int vflag[EWC_ITEMMAX];
	IGraphBuilder* pGraph;
	IBaseFilter* pF;
	ISampleGrabber* pGrab;
	ICaptureGraphBuilder2* pBuilder;
	IBaseFilter* pCap;
	IAMVideoProcAmp* pVPAmp;
	IAMCameraControl* pCamCtl;
	IMediaControl* pMediaControl;
	IAMStreamConfig* pConfig;
	IMoniker* pMoniker;
	IEnumMoniker* pEnum;
	ICreateDevEnum* pDevEnum;
	AM_MEDIA_TYPE* pmt;
	AM_MEDIA_TYPE mt;
	IPin* pSrcOut;
	IPin* pSGrabIn;
	IMediaEvent* pMediaEvent;
};

//フォーマット格納のための構造体v2.3
struct ewc_format {
	int width;
	int height;
	int bit;
	REFERENCE_TIME AvgTimePerFrame;
	double fps;
	GUID subtype;
	char subtype_t[80];	//subtypeに対応する文字列v2.3
};

extern GUID ewc_type;
extern GUID ewc_device_type;
extern ewc_struct ewc_s[EWC_NCAMMAX];

int EWC_Open(int num, int wx = 0, int wy = 0, double fps = 0, int device = -1, GUID mstype = ewc_type, GUID dev_mstype = ewc_device_type);
int EWC_Close(int num);
int EWC_GetCamera(void);
char* EWC_GetDeviceName(int num);
int EWC_GetFormat(int devn, ewc_format* fmt, int* nmax);

// 新しい画像が到着したかどうか v2.6
// num:カメラ番号  buffer_r:読み出すリングバッファの番号(0～)
// 戻り値: 前回実行以降に到着した画像枚数（未到着:0, 通常:1, コマ落ちがあれば2以上）
int EWC_IsCaptured(int num, int* buffer_r = NULL);

//カメラ(番号:num)の画像取得 v2.6
// num:カメラ番号  buffer:画像データを格納するアドレス　count:フレーム番号　stime:取得時刻(秒)
int EWC_GetImage(int num, void* buffer, int* count = NULL, double* stime = NULL);



void ESP_Printf(const char* format, ...);
void ESP_PrintfU(const char* format, ...);

#ifndef ESP_OpenTextWindow
#ifndef ESP_LIBRARY_MODE
#define ESP_OpenTextWindow(i,x0,y0,wx,wy) (esp_OpenTextWindow((i),(x0),(y0),(wx),(wy)))
#else
#define ESP_OpenTextWindow(i,x0,y0,wx,wy) (esp_RequestOpenTextWindow((i),(x0),(y0),(wx),(wy)))
#endif //ESP_LIBRARY_MODE
#endif // ESP_OpenTextWindow
//テキストウィンドウを開く v8.2
int esp_OpenTextWindow(int i, int x0, int y0, int wx, int wy);
void esp_RequestOpenTextWindow(int i, int x0, int y0, int wx, int wy);

//テキストウィンドウにおいて文字列入力を行う 7.0
void ESP_Input(char* buffer);

//v8.0
#ifndef ESP_CloseTextWindow
#ifndef ESP_LIBRARY_MODE
#define ESP_CloseTextWindow(i) (esp_CloseTextWindow((i)))
#else
#define ESP_CloseTextWindow(i) (esp_RequestCloseTextWindow((i)))
#endif
#endif // !ESP_CloseTextWindow
int esp_CloseTextWindow(int i);
int esp_RequestCloseTextWindow(int i);

void ESP_PutWindow(void* buf, int x0, int y0, int wx, int wy);

#ifndef ESP_Update
extern volatile int esp_i;			//現在選択されているイメージウィンドウ
#define ESP_Update() (ESP_Update_(esp_i))
#endif // !ESP_Update
int ESP_Update_(int i);

void ESP_Locate(int cx, int cy);
//ボタンの押された回数を 1 にする
void ESP_SetButtonBox(int i);

//次のフレームへ進める
int EVF_Next(int i, int step = 1);
//現在のフレーム番号
int EVF_Frame(int i);
//指定フレームまでシーク
int EVF_Seek(int i, int frame);
//画像を画像変換(24ビット->32ビット)しながらメモリへ格納
int EVF_GetFrame24to32(int i, int* dst);
