// ESPLIB  [Easy Stereo Processing LIBrary] 
//              version 8.5
// Copyright (C) 2016-2020 I.N.  All rights reserved.

// OS: Windows 2000/XP/Vista/7/8/8.1/10 (x86/x64)
// Programmer: I.N.
// Compiler: Microsoft Visual C++ 2008-2017

// 2006.12.22 ver.7.0   remove BMPINFO, add ESP_GetImageInfo(),ESP_ImageOpen()
// 2007.12.26           int esp_gettime() -> unsigned int esp_gettime()
// 2008.01.24 ver.7.1   多重起動は10まで, ログファイル名の対応, ESP_Bezier(), ESP_BezierXOR()追加．
// 2009.01.07 ver.7.x   Vistaのウィンドウ枠に対応
// 2009.01.13 ver.7.x   ESP_CreateImageFL(),ESP_CreateImage8FL()
// 2009.01.21 ver.7.x   _WIN32_WINNT 0x0500をとる
// 2009.03.24 ver.7.2   完成
// 2009.03.30 ver.7.x   ESP_Printf():先頭が\nのときのバグを修正．ESP_STRMAXオプション追加．
// 2009.04.30 ver.7.3   WM_MOUSEWHEELを復活．ESP_OpenButtonBox()内int->long long
// 2010.03.02 ver.7.x   マイクロ秒精度のESP_GetClockus()を追加
// 2010.03.26 ver.7.4   デスクトップ領域の正確な認識
// 2010.06.24 ver.7.x   double型戻り値のESP_GetClockms()を追加．ESP_GetClockus()を廃止．
// 2011.03.01           ESP_Printf(),ESP_Input():半角カタカナの問題を修正
// 2011.03.01 ver.7.5   ESP_PlaceMain(),ESP_HideMain()追加,メインウィンドウ位置の記憶
// 2011.05.12           テキストおよびイメージウィンドウ生成で左上座標(-1,-1)を指定したときの問題を修正
// 2011.06.23           Window Info.の改行修正．ESP_PsetF()/ESP_PsetF8()の追加．
// 2011.06.23 ver.7.6   ログのファイル名に数字(日時)を付けた．ESP_CopyLog()仕様変更．
// 2012.05.02           ESP_Puts()追加,ESPLIB終了時のメモリリークがあった点を解消,ESP_Cls()は更新なしへ修正
// 2012.05.07           ESP_Puts(),ESP_Printf()は出力後に更新をしない
// 2012.05.07           ESP_PutsU(),ESP_PrintfU()は出力毎に更新をする
// 2012.06.08           ESP_ImageLoad()とESP_GetImageInfo()でオブジェクト解放をしていなかった点の修正
// 2012.06.08           ESPLIB起動時にESP_StartClock()は実行済み
// 2012.06.14 ver.7.7   release
// 2013.08.29 ver.7.8   タスクバーの位置によってメインウィンドウに位置ずれが生じる問題を解消．
//                      ESP_Puts/PutsU/Printf/PrintfU/PrintfBin()のマルチスレッド対応．
//                      ESP_EXITTIME追加．
// 2013.11.13 ver.x     不要なOSバージョン確認を削除
// 2014.03.14 ver.x     マニフェスト(ビジュアルスタイル)をソース中に記述
//                      VC++2013がESP_ImageSave()で出すエラーを修正
// 2014.04.21           ESP_SetInputBoxD()の有効桁数指定およびデフォルト値18
// 2014.04.21 ver.7.9   Altキーで全ウィンドウを同時に移動させる
// 2014.05.02-05.07     Altキー同時移動のバグ修正
// 2014.05.07           テキストウィンドウのサイズ変更の刻み幅を文字サイズとした，最下行まで使えるようにした
//                      ESP_OpenTextWindow()の引数を省略可能とした，デフォルトサイズの変更
//                      InputBoxでdouble型値も保存されるようにした
// 2014.05.07-09        ライブラリモードの開発開始,ESP_Start()追加,ESP_Exit()改訂
// 2014.05.09           ESP_HideMain()廃止し，代わりにESP_HIDE_MAINWINDOWを追加
// 2014.05.12           ライブラリモードの開発,ESP_GetLoadFileName(),ESP_GetSaveFileName()の修正
// 2014.05.14 ver.8.0   ESP_SetInputBoxD()の有効桁数デフォルト値を18から10へ戻す, ESP_Pause()仕様変更

//            ver.8.1
// 2015.11.9  L.266 int -> unsigned long (VC++2015のwarning対策)
//            L.2328 %d -> %I64d
// 2016.5.19  ESP_SetColor(), ESP_PrintfBin() 引数の仕様変更
// 2016.5.19  VC++2015, Release, x86で右メニューが出ない
//            リンカの最適化オプション /OPT:REF が関係している
//            (/OPT:NOREF, /LTCGにすると問題解消)
//            esp_mousegettingとesp_tw_inputflagにstaticにすると問題解消
// 2016.5.20  ESP_Paint()戻り値を追加
// 2016.5.24  Windows 10の1ドットウィンドウ幅への対応

//            ver.8.2
// 2016.6.17  TextWindowの左上座標がマイナスの場合，ウィンドウを出せない不具合修正
//            マイナス時にデフォルト位置にする機能は削除
// 2016.7.4   Exit時の内部処理のタイミング修正
// 2016.7.12  ESP_BoxFill()のfを省略可に変更
// 2016.8.22  ESP_CircleFill()のfを省略可に変更
// 2016.8.22  ESP_PrintfDateTime()の追加

//            ver.8.3
// 2017.5.10  ログファイルの拡張子を変更可能にした ESP_LOGEXTの定義で
// 2018.4.20  VC++2017用に修正（const char *関係）
// 2018.5.25  VC++2017用に修正（const char *関係）

//            ver.8.4
// 2018.10.20 ESP_SKIPANIMATIONの定義で起動時のアニメーションをスキップ可
// 2018.11.07 IWでキー入力,ESP_CheckKeyDown()の追加
// 2019.05.07 ImageWindowの左上座標がマイナス時にデフォルト位置にする機能を削除
//            ESP_Paint2()追加

//            ver.8.5
// 2020.01.06 WM_QUERYENDSESSIONが来たらEXIT処理する機能追加
//            ESP_FlushLog(),ESP_FlushAllLog()追加

#pragma once
#define ESP_STR_ABOUT "ESPLIB 8.5  2020/1/6  by I.N."

//Enabling Visual Styles (v7.9)
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <process.h>
#include <time.h>

#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib,"gdiplus.lib")
GdiplusStartupInput esp_gdiplusStartupInput;
ULONG_PTR esp_gdiplusToken;

//for DwmGetWindowAttribute() v8.1
#include <Dwmapi.h>
#pragma comment(lib,"Dwmapi.lib")

//プロトタイプ宣言
void ESP_Ready(void);
void ESP_Main(void);
void ESP_Finish(void);

//各ウィンドウのウィンドウ関数
LRESULT CALLBACK ESP_MWfunc(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK ESP_IWfunc(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK ESP_TWfunc(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK ESP_IBfunc(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK ESP_BBfunc(HWND,UINT,WPARAM,LPARAM);

//いろいろな文字列バッファの長さ
#define ESP_BUFMAX 256

// macro:Limit()  ... example Limit(0,Red,255);
#ifndef Limit
#define Limit(a,b,c) min(max((a),(b)),(c))
#endif

//共通関数（a<=bになるよう交換する）
__inline void esp_order(int *a, int *b)
{
	int t;
	if(*a > *b) t=*a, *a=*b, *b=t;
}

#ifndef random
#define random(n) (rand()%(n))
#endif

#define ESP_R    0x0001
#define ESP_G    0x0002
#define ESP_B    0x0004
#define ESP_H    0x0008
#define ESP_S    0x0010
#define ESP_V    0x0020
#define ESP_DOT  0x0040
#define ESP_LINE 0x0080
#define ESP_Y    0x0100
#define ESP_Cr   0x0200
#define ESP_Cb   0x0400
#define ESP_CrCb 0x0800
#define ESP_L    0x1000

#define ESP_COLOR_R  0xff0000
#define ESP_COLOR_G  0x00ff00
#define ESP_COLOR_B  0x0000ff
#define ESP_COLOR_H  0xffff00
#define ESP_COLOR_S  0xff00ff
#define ESP_COLOR_V  0x00ffff
#define ESP_COLOR_Y  0xffffff
#define ESP_COLOR_CR 0xff8888
#define ESP_COLOR_CB 0x8888ff
#define ESP_COLOR_L  0xffffff
				
#define C2R(c) ((int)(((c)&0xff0000)>>16))
#define C2G(c) ((int)(((c)&0xff00)>>8))
#define C2B(c) ((int)((c)&0xff))
#define RGB2C(r,g,b) ((r)*0x10000+(g)*0x100+(b))

// ver.5.9c~
//Y = 0.299R +0.587G +0.114B
//Cb=-0.169R -0.331G +0.500B
//Cr= 0.500R -0.419G -0.081B
#define RGB2Y(r,g,b)   ((19595*(r)+38470*(g)+7471*(b)+32768)/65536)
#define RGB2Cb(r,g,b)  ((-11076*(r)-21692*(g)+32768*(b)+32768)/65536)
#define RGB2Cr(r,g,b)  ((32768*(r)-27460*(g)-5308*(b)+32768)/65536)
//R = Y          +1.402Cr
//G = Y -0.344Cb -0.714Cr
//B = Y +1.772Cb
#define YCrCb2R(y,cr,cb) (Limit(0,(65536*(y)+91881*(cr)+32768)/65536,255))
#define YCrCb2G(y,cr,cb) (Limit(0,(65536*(y)-22544*(cb)-46793*(cr)+32768)/65536,255))
#define YCrCb2B(y,cr,cb) (Limit(0,(65536*(y)+116130*(cb)+32768)/65536,255))

// ver.5.9c~(new)
//Y = = 0.299R +0.587G +0.114B  (same as Y in YCrCb)
//u =(B-Y)/2.03 = -0.147R -0.289G +0.436B 
//v =(R-Y)/1.14 = +0.615R -0.515G -0.100B 
#define RGB2u(r,g,b)  ((-9634*(r)-18940*(g)+28574*(b)+32768)/65536)
#define RGB2v(r,g,b)  ((40305*(r)-33751*(g)-6554*(b)+32768)/65536)
//R = Y +0.000u +1.140v 
//G = Y -0.396u -0.581v 
//B = Y +2.029u +0.000v 
#define Yuv2R(y,u,v) (Limit(0,(65536*(y)+74711*(v)+32768)/65536,255))
#define Yuv2G(y,u,v) (Limit(0,(65536*(y)-25952*(u)-38076*(v)+32768)/65536,255))
#define Yuv2B(y,u,v) (Limit(0,(65536*(y)+132973*(u)+32768)/65536,255))

// ver.5.9c~(new)
//Y = +0.2990R +0.5870G +0.1140B  (same as Y in YCrCb)
//I = +0.5959R -0.2750G -0.3210B
//Q = +0.2065R -0.4969G +0.2904B
#define RGB2I(r,g,b)  ((39053*(r)-18022*(g)-21037*(b)+32768)/65536)
#define RGB2Q(r,g,b)  ((13533*(r)-32565*(g)+19032*(b)+32768)/65536)
//R = Y +0.9489I +0.6561Q
//G = Y -0.2645I -0.6847Q
//B = Y -1.1270I +1.8050Q
#define YIQ2R(y,i,q) (Limit(0,(65536*(y)+62187*(i)+42998*(q)+32768)/65536,255))
#define YIQ2G(y,i,q) (Limit(0,(65536*(y)-17334*(i)-44872*(q)+32768)/65536,255))
#define YIQ2B(y,i,q) (Limit(0,(65536*(y)-73859*(i)+118292*(q)+32768)/65536,255))

#define C2Y(c) (RGB2Y(C2R((c)),C2G((c)),C2B((c))))
#define C2Cr(c) (RGB2Cr(C2R((c)),C2G((c)),C2B((c))))
#define C2Cb(c) (RGB2Cb(C2R((c)),C2G((c)),C2B((c))))
#define YCrCb2C(y,cr,cb)  (RGB2C(YCrCb2R((y),(cr),(cb)),YCrCb2G((y),(cr),(cb)),YCrCb2B((y),(cr),(cb))))

#define C2u(c) (RGB2u(C2R((c)),C2G((c)),C2B((c))))
#define C2v(c) (RGB2v(C2R((c)),C2G((c)),C2B((c))))
#define Yuv2C(y,u,v)  (RGB2C(Yuv2R((y),(u),(v)),Yuv2G((y),(u),(v)),Yuv2B((y),(u),(v))))

#define C2I(c) (RGB2I(C2R((c)),C2G((c)),C2B((c))))
#define C2Q(c) (RGB2Q(C2R((c)),C2G((c)),C2B((c))))
#define YIQ2C(y,i,q)  (RGB2C(YIQ2R((y),(i),(q)),YIQ2G((y),(i),(q)),YIQ2B((y),(i),(q))))

__inline void C2YCrCb(int c, int *Y, int *Cr, int *Cb)
{
	*Y=C2Y(c);	
	*Cr=C2Cr(c);
	*Cb=C2Cb(c);
}

__inline void C2RGB(int c, int *R, int *G, int *B)
{
	*R=C2R(c);	
	*G=C2G(c);
	*B=C2B(c);
}

__inline void C2Yuv(int c, int *Y, int *u, int *v)
{
	*Y=C2Y(c);	
	*u=C2u(c);
	*v=C2v(c);
}

__inline void C2YIQ(int c, int *Y, int *I, int *Q)
{
	*Y=C2Y(c);	
	*I=C2I(c);
	*Q=C2Q(c);
}

#define ESPMAINWINDOW 10000
#define ESPTWBASE     11000
#define ESPINPUTBOX   12000
#define ESPBUTTONBOX  13000

//esp_get(),esp_release()用Mutex
HANDLE esp_ghMutex;
#define esp_get()		WaitForSingleObject(esp_ghMutex,INFINITE)
#define esp_release()	ReleaseMutex(esp_ghMutex)
//テキストウィンドウ用Mutex処理
#define esp_tw_get()		WaitForSingleObject(esp_tw_hmutex,INFINITE)
#define esp_tw_release()	ReleaseMutex(esp_tw_hmutex)
//WM_MOVING処理用Mutex v8.0
HANDLE esp_wmmoving_hmutex;
#define esp_wmmoving_get()		WaitForSingleObject(esp_wmmoving_hmutex,0)
#define esp_wmmoving_release()	ReleaseMutex(esp_wmmoving_hmutex)

//メインウィンドウ関連
#define ESP_MAINWINDOWMAX		10	//多重起動の最大数
int esp_id;							//起動番号[0-9]
#define ESP_MAINCLASSNAMEMAX	11
wchar_t esp_mw_classname[ESP_MAINCLASSNAMEMAX];
HWND esp_mw_hwnd;
HDC esp_mw_hdc;
HWND esp_mwtext_hwnd;
int esp_plt;
int esp_mw_x0,esp_mw_y0;			//標準位置
//強制終了待機時間(ms) v7.8
#ifndef ESP_EXITTIME
	#define ESP_EXITTIME	2000
#endif
static volatile int esp_running;	//1:ESPLIB稼働中 0:終了 v8.1
#ifdef ESP_HIDE_MAINWINDOW
int esp_mw_show= 0;			//0:メインウィンドウを表示しない
#else
int esp_mw_show= 1;			//1:メインウィンドウを表示する
#endif

//---イメージウィンドウ関連---
const wchar_t *esp_iw_classname=L"esp_iw";
#define ESP_IW_MAX 256		//イメージウィンドウの最大数
volatile int esp_i;			//現在選択されているイメージウィンドウ
int esp_LPx,esp_LPy;		//最後に描画された点
unsigned int  *ESP_VramPtr[ESP_IW_MAX];
unsigned char *ESP_VramPtr8[ESP_IW_MAX];
#define ESP_IWSELECT_HISTORY 8
int esp_iw_select_prev[ESP_IWSELECT_HISTORY];
const unsigned long esp_iw_wstyle[2]={		//0:フレーム無し 1:フレーム有り(標準)
	WS_OVERLAPPED | WS_POPUP | WS_VISIBLE,
	WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_SYSMENU | WS_VISIBLE
};
volatile int esp_keydown= -1;	//押されたキーコード

//ウィンドウ位置変更時の共通フラグ
int esp_setpos_flags= SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOSENDCHANGING;

struct ESP_IMAGEWINDOW {
	int show;	//存在フラグ[0 or 1]
	int bit;	//ビット数[8 or 32]
	int wx;		//イメージ幅
	int wy;		//イメージ高さ
	int wwx;	//ウィンドウ幅
	int wwy;	//ウィンドウ高さ
	int zoom;	//表示ズーム倍率
	int flag;	//フレームあり(1)／なし(0)
	HWND hwnd;
	HDC memdc;
	HDC hdc;
	HBITMAP hbitmap;
	HBITMAP hbitmapold;
	char *title;	//タイトル
};
struct ESP_IMAGEWINDOW esp_iw[ESP_IW_MAX];

//---テキストウィンドウ関連---
const wchar_t *esp_tw_classname=L"esp_twi";
#define ESP_TW_MAX 256			//テキストウィンドウの最大数
volatile int esp_twi;			//現在選択されているテキストウィンドウ
HANDLE esp_tw_hmutex;			//Mutexハンドル
#define ESP_TWSELECT_HISTORY 8
int esp_tw_select_prev[ESP_TWSELECT_HISTORY];
//テキストウィンドウのデフォルトサイズ
#define ESP_DEFTW_WX 400
#define ESP_DEFTW_WY 288	//v8.0
#define ESP_TWCOLOR_HISTORY 8
//入力中のときそのTW番号+1，非入力中なら0
static volatile int esp_tw_inputflag;	//v8.1
const int esp_tw_wstyle= WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_SYSMENU | WS_VISIBLE;	//v8.0

//入力中の文字を格納するバッファ
#define ESPTWBUFMAX 256
wchar_t esp_tw_buffer[ESPTWBUFMAX];
// wpはこれから書き込むアドレスを常に指す
// rp=-1のときはデータなし，それ以外は最後のデータ位置を指す
volatile int esp_tw_rp= -1;
volatile int esp_tw_wp= 0;

volatile int esp_tw_ctrl=0;	//キー状態
#define ESP_TWCTRL_HISTORY 1
#define ESP_TWCTRL_PASTE   2
//前回入力した文字列（履歴）
wchar_t esp_tw_history[ESPTWBUFMAX];

struct ESP_TEXTWINDOW {
	int show;	//存在フラグ[0 or 1]
	int wx;		//テキストウィンドウの幅
	int wy;		//テキストウィンドウの高さ
	int x;		//カーソル位置
	int y;		//カーソル位置
	int w;		//１文字の幅
	int h;		//１文字の高さ
	int fx;		//ウィンドウ枠の大きさ(横の合計)
	int fy;		//ウィンドウ枠の大きさ(縦の合計)
	int tcolor;	//テキスト文字色
	int bcolor;	//テキスト背景色
	int tcolor_prev[ESP_TWCOLOR_HISTORY];
	int bcolor_prev[ESP_TWCOLOR_HISTORY];
	HWND hwnd;
	HDC memdc;
	HDC hdc;
	HBITMAP hbit;
	HBITMAP hbitold;
	int logstatus;	//ログ情報 0:未使用 1:記録中 2:停止中
	FILE *logfile;	//ログファイル名
};
struct ESP_TEXTWINDOW esp_tw[ESP_TW_MAX];

//時間計測関連 6.1e/7.4
LARGE_INTEGER	esp_li_time0,esp_li_time1,esp_li_freq;
//esp_ld_fpmsはMFCでReleseモードのみスレッド間の変数のやりとりが出来ないのでローカル変数にした。
//esp_ld_fpusは使用されていない。 20210113 kinya iwamoto
//long double esp_ld_fpms, esp_ld_fpus;			
int esp_times;		//flag:計測中なら１
double esp_timems;	//result:計測結果(ms,double)

HINSTANCE esp_hInst;
HANDLE h_ESP_Loop;
int esp_color=0xffffff;

volatile int ESP_START;
static int ESP_STARTING;
static int esp_STOP;
int ESP_EXIT;
#define ESP_STOP (CM(),esp_STOP)

//---インプットボックス関連---
#define ESP_IB_MAX 30				//項目数の上限
HWND esp_ib_hwnd;
const wchar_t *esp_ib_classname=L"esp_ib";
int esp_ib_num;
int esp_renameib;		//renameメニュー実行時に使われる
int esp_ib_sizing;		//IBのサイズ変更に使われた辺の情報
HWND esp_ibhwndfocus;	//フォーカス中のハンドル
//インプットボックス（各項目用）
struct ESP_INPUTBOX {
	char *str;
	double val;
	HWND title_hwnd;	//項目名ハンドル
	HWND box_hwnd;		//入力欄ハンドル
};
struct ESP_INPUTBOX esp_ib[ESP_IB_MAX];
#define ESP_IB_STRMAX 256	//文字数制限

//ボタンボックス関連
#define ESP_BB_MAX 256
HWND esp_bb_hwnd=NULL;
int esp_bb_num,esp_bb_nx,esp_bb_ny;
HWND esp_btn_hwnd[ESP_BB_MAX];
const wchar_t *esp_bb_classname=L"esp_bb";
int esp_bb_count[ESP_BB_MAX];
#define ESP_BB_STRMAX 256
int esp_renamebb;		//renameメニュー実行時に使われる

//近くのウィンドウに吸い付く機能関連(IW*256,TW*256,MW,IB,BB) v8.0
struct {
	int x1,y1,x2,y2;
	HWND hwnd;
} esp_list[4+ESP_IW_MAX+ESP_TW_MAX+3];
int esp_list_n;				//リストへの登録数
#define ESP_EDGEFIT 8		//この値以下に近づくとその境界線へ吸着
//差分
int esp_wfdif_x1;
int esp_wfdif_x2;
int esp_wfdif_y1;
int esp_wfdif_y2;

//テキスト描画用
int esp_tx0,esp_tx,esp_ty,esp_tc;

//ログ関連
char esp_logbase[MAX_PATH];
wchar_t _esp_logbase[MAX_PATH];
//パス関連
char esp_gofn_path[MAX_PATH];
wchar_t _esp_gofn_path[MAX_PATH];
char esp_gsfn_path[MAX_PATH];
wchar_t _esp_gsfn_path[MAX_PATH];
int esp_first_gofn=1;		//初めて関数を呼ばれるとき１
int esp_first_gsfn=1;		//初めて関数を呼ばれるとき１
int esp_gofn_index=2;
int esp_gsfn_index=2;

COLORREF esp_CustColors[16];

//マウス情報リアルタイム読み取り用
int ESP_MX=0,ESP_MY=0,ESP_MW=-1;
int ESP_ML=0,ESP_MM=0;
int ESP_MOUSE;

//ver3.4
int ESP_MMX,ESP_MMY,ESP_MMF=0;
int ESP_MLX,ESP_MLY,ESP_MLF=0,ESP_MRF=0;
int ESP_SHIFT;
int ESP_CTRL;
static int esp_getting, esp_mousegetting;	//v8.1

#define ESPPTR  (ESP_VramPtr[esp_i]+mx*y+x)
#define ESPPTR8 (ESP_VramPtr8[esp_i]+((mx+3)&~3)*y+x)

// －－－－リクエスト関数－－－－
volatile int esp_req= 0;
#define ESP_REQ_CREATEIMAGE     9001
#define ESP_REQ_UPDATE          9002
#define ESP_REQ_IMAGELOAD       9003
#define ESP_REQ_DIBDISP         9004
#define ESP_REQ_OPENTEXTWINDOW  9005
#define ESP_REQ_OPENINPUTBOX    9006
#define ESP_REQ_OPENBUTTONBOX   9007
#define ESP_REQ_DESTROYIMAGE    9008
#define ESP_REQ_CLOSETEXTWINDOW 9009
#define ESP_REQ_CLOSEINPUTBOX   9010
#define ESP_REQ_CLOSEBUTTONBOX  9011

volatile int esp_req_i;
const char *esp_req_title;
const char *esp_req_filename;
HBITMAP esp_req_hbm;
int esp_req_x0;
int esp_req_y0;
int esp_req_wx;
int esp_req_wy;
int esp_req_zoom;
int esp_req_fin=1;
int esp_req_ret;
int esp_req_reso;
int esp_req_used;
int esp_req_bit;
int esp_req_flag;

//TrueTypeフォント描画用
HFONT esp_hfont;
int esp_ttwx=8;
int esp_ttwy=16;
int esp_tttc=0xffffff;
#define ESP_TT_ITALIC		1
#define ESP_TT_UNDERLINE	2
#define ESP_TT_STRIKEOUT	4
#define ESP_TT_BOLD			8
#define ESPTTFONTNAME L"ＭＳ ゴシック"

HMENU esp_hmenu;
#define ID_START     1001
#define ID_EXIT      1002
#define ID_STOP      1003
#define ID_LOADIMG   1004
#define ID_DESTROYI  1005
#define ID_DESTROYTW 1006
#define ID_ZOOM050   1007
#define ID_ZOOM100   1008
#define ID_ZOOM200   1009
#define ID_SAVEIMG   1010
#define ID_CUT       1011
#define ID_COPY      1012
#define ID_PASTETO   1013
#define ID_PASTE     1014
#define ID_INFOPIXEL		1015
#define ID_INFOLINERGB		1016
#define ID_INFOLINEHSV		1017
#define ID_INFOLINEYCRCB	1018
#define ID_CLIP				1019
#define ID_ABOUT		1020
#define ID_INFOLINECRCB 1021
#define ID_INFOAREACRCB 1022
#define ID_DESTROYIB    1023
#define ID_STARTLOG     1024
#define ID_STOPLOG      1025
#define ID_PASTETOMAIN  1026
#define ID_IMAGEWINDOW  1027
#define ID_TEXTWINDOW   1028
#define ID_COMMAND      1029

#define ID_COPYLOG      1030
#define ID_SELECTCOLOR  1031
#define ID_DRAWLINE     1032
#define ID_DRAWLINEX    1033
#define ID_DRAWHLINE    1034
#define ID_DRAWVLINE    1035
#define ID_DRAWBOX      1036
#define ID_DRAWBOXF     1037
#define ID_DRAWBOXFX    1038
#define ID_DRAWCIRCLE   1039
#define ID_DRAWCIRCLEF  1040
#define ID_DRAWCIRCLEFX 1041
#define ID_DRAWTEXT     1042
#define ID_DRAWPAINT    1043

#define ID_INPUTBOX     1044
#define ID_INFO         1045

#define ID_ZOOMANY		1046
#define ID_RESIZE		1047
#define ID_DRAWTTTEXT	1048
#define ID_SELECTFONT	1049

#define ID_DESTROYBB    1050
#define ID_BUTTONBOX    1051
#define ID_BB_BASE	    3000

#define ID_PICKCOLOR	1052
#define ID_TESTRGB		1053
#define ID_TESTHSV		1054
#define ID_TESTCRCB		1055

#define ID_RENAMEIB		1056
#define ID_RENAMEBB		1057

#define ID_INVERT		1058
#define ID_HFLIP		1059
#define ID_VFLIP		1060
#define ID_RROTATE		1061
#define ID_LROTATE		1062

#define ID_SIZE500		1063
#define ID_SIZE707		1064
#define ID_SIZE141		1065
#define ID_SIZE200		1066

#define ID_TESTUV		1067
#define ID_TESTIQ		1068

#define ID_SELECTTW		1069
#define ID_INFOLINEL	1070
#define ID_TESTGREY		1071

#define IDC_MAINTEXT	2001

#ifndef ESP_LIBRARY_MODE
	#define ESP_CreateImage(i,title,x0,y0,wx,wy,zoom)    (esp_CreateImageX((i),(title),(x0),(y0),(wx),(wy),(zoom),32,1))
	#define ESP_CreateImageFL(i,title,x0,y0,wx,wy,zoom)  (esp_CreateImageX((i),(title),(x0),(y0),(wx),(wy),(zoom),32,0))
	#define ESP_CreateImage8(i,title,x0,y0,wx,wy,zoom)   (esp_CreateImageX((i),(title),(x0),(y0),(wx),(wy),(zoom),8,1))
	#define ESP_CreateImage8FL(i,title,x0,y0,wx,wy,zoom) (esp_CreateImageX((i),(title),(x0),(y0),(wx),(wy),(zoom),8,0))
#else
	#define ESP_CreateImage(i,title,x0,y0,wx,wy,zoom)    (esp_RequestCreateImageX((i),(title),(x0),(y0),(wx),(wy),(zoom),32,1))
	#define ESP_CreateImageFL(i,title,x0,y0,wx,wy,zoom)  (esp_RequestCreateImageX((i),(title),(x0),(y0),(wx),(wy),(zoom),32,0))
	#define ESP_CreateImage8(i,title,x0,y0,wx,wy,zoom)   (esp_RequestCreateImageX((i),(title),(x0),(y0),(wx),(wy),(zoom),8,1))
	#define ESP_CreateImage8FL(i,title,x0,y0,wx,wy,zoom) (esp_RequestCreateImageX((i),(title),(x0),(y0),(wx),(wy),(zoom),8,0))
#endif

//スレッド関連追加	20210113 kinya iwamoto
#ifdef _MFC_VER
CWinThread* pRecvThread_esp_start = NULL;				//スレッドのオブジェクト(esp_start)
CWinThread* pRecvThread_esp_Loop = NULL;				//スレッドのオブジェクト(esp_Loop)
#endif // _MFC_VER


//QueryPerformanceCounter()を使ったGetTickCount()相当の関数
//v7.1 32bit以上のミリ秒が経過していた場合の不具合修正(int->unsigned int)
inline unsigned int esp_gettime(void)
{
	LARGE_INTEGER esp_li_time;
	long double esp_ld_fpms;				//esp_ld_fpmsをローカル変数にした 20210113 kinya iwamoto
	QueryPerformanceFrequency(&esp_li_freq);
	esp_ld_fpms = (long double)(1000.0 / esp_li_freq.QuadPart);

	QueryPerformanceCounter(&esp_li_time);
	//std::wstring tbuf = std::to_wstring(esp_li_time.QuadPart) + _T("\n") + std::to_wstring(esp_ld_fpms) + _T("\n");
	//OutputDebugString(tbuf.c_str());
	return (unsigned int)floor(esp_li_time.QuadPart*esp_ld_fpms);
}

//wchar_t型文字列をchar型文字列へ変換 7.0
__inline void wchar_t2char(const wchar_t *w, char *s, int ssize)
{
	WideCharToMultiByte(CP_ACP,0,w,-1,s,ssize,NULL,NULL);
}

//char型文字列をwchar_t型文字列へ変換 7.0
__inline void char2wchar_t(const char *s, wchar_t *w, int wsize)
{
	MultiByteToWideChar(CP_ACP,0,s,-1,w,wsize);
}

// TrueType Font 関連

void ESP_TTPosition(int x, int y)
{
	esp_tx0=esp_tx=x;
	esp_ty=y;
}

#define ESP_TTColor(c)	(esp_tttc=(c))

// ver.7.0
int ESP_TTFont(const char *fontname)
{
	wchar_t buf[LF_FACESIZE];

	char2wchar_t(fontname,buf,LF_FACESIZE);
	buf[LF_FACESIZE-1]=0;

	LOGFONT lf;
	GetObject(esp_hfont,sizeof(LOGFONT),&lf);
	DeleteObject(esp_hfont);

	wcscpy_s(lf.lfFaceName,LF_FACESIZE,buf);
	esp_hfont=CreateFontIndirect(&lf);

	if(!esp_hfont) return 1;
	return 0;
}

// ver.5.7
int ESP_TTStyle(int style)
{
	LOGFONT lf;
	GetObject(esp_hfont,sizeof(LOGFONT),&lf);
	DeleteObject(esp_hfont);

	if (style & ESP_TT_ITALIC)		lf.lfItalic   =TRUE;	else lf.lfItalic   =FALSE;
	if (style & ESP_TT_UNDERLINE)	lf.lfUnderline=TRUE;	else lf.lfUnderline=FALSE;
	if (style & ESP_TT_STRIKEOUT)	lf.lfStrikeOut=TRUE;	else lf.lfStrikeOut=FALSE;
	if (style & ESP_TT_BOLD)		lf.lfWeight   =FW_BOLD;	else lf.lfWeight   =FW_NORMAL;
	esp_hfont=CreateFontIndirect(&lf);

	if(!esp_hfont) return 1;
	return 0;
}

//GetWindowText()の代わり 7.0
void esp_getwindowtext(HWND hwnd, char *text, int count)
{
	wchar_t _text[ESP_BUFMAX];
	GetWindowText(hwnd,_text,count);
	wchar_t2char(_text,text,count);
}

//SetWindowText()の代わり 7.0
void esp_setwindowtext(HWND hwnd, const char *text)
{
	wchar_t _text[ESP_BUFMAX];
	char2wchar_t(text,_text,ESP_BUFMAX);
	SetWindowText(hwnd,_text);
}

// 7.0
void esp_status(const char *s)
{
	char buf[64];
	int i;
	
	FillMemory(buf,64,' ');
	buf[63]=0;
	i=18-(int)strlen(s)/2;
	i=Limit(0,i,63);
	strcpy_s(buf+i,64-i,s);
	esp_setwindowtext(esp_mwtext_hwnd,buf);
}

// 7.0
void esp_disp_color_mode(void)
{
	char s[16];
	sprintf_s(s,sizeof(s),"%d-bit color",esp_plt);
	esp_status(s);
}

// 7.0
void esp_AppendMenu(HMENU hmenu, UINT pos, UINT state, UINT id, const char *s)
{
	wchar_t w[ESP_BUFMAX];
	char2wchar_t(s,w,ESP_BUFMAX);

	MENUITEMINFO mii;

	ZeroMemory(&mii,sizeof(MENUITEMINFO));
	mii.cbSize=sizeof(MENUITEMINFO);
	mii.fMask=MIIM_TYPE|MIIM_ID|MIIM_STATE;
	mii.fType=MFT_STRING;
	mii.wID=id;
	mii.fState=state;
	mii.dwTypeData=w;
	InsertMenuItem(hmenu,pos,TRUE,&mii);
}

void esp_AppendMenuSEP(HMENU hmenu, UINT pos)
{
	MENUITEMINFO mii;

	ZeroMemory(&mii,sizeof(MENUITEMINFO));
	mii.cbSize=sizeof(MENUITEMINFO);
	mii.fMask=MIIM_TYPE;
	mii.fType=MFT_SEPARATOR;
	InsertMenuItem(hmenu,pos,TRUE,&mii);
}

// 7.0
void esp_AppendMenuSub(HMENU hmenu, UINT pos, HMENU hsubmenu, const char *s)
{
	wchar_t w[ESP_BUFMAX];
	char2wchar_t(s,w,ESP_BUFMAX);

	MENUITEMINFO mii;

	ZeroMemory(&mii,sizeof(MENUITEMINFO));
	mii.cbSize=sizeof(MENUITEMINFO);
	mii.fMask=MIIM_TYPE|MIIM_SUBMENU;
	mii.fType=MFT_STRING;
	mii.dwTypeData=w;
	mii.hSubMenu=hsubmenu;
	InsertMenuItem(hmenu,pos,TRUE,&mii);
}

//v8.0
#ifndef ESP_LIBRARY_MODE
int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
#else
int WINAPI esp_WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
#endif
{
    //esp_get()/esp_release()用Mutex
    esp_ghMutex= CreateMutex(NULL,FALSE,NULL);
	if(esp_ghMutex==NULL) return 1;

	//ウィンドウ移動用mutex
	esp_wmmoving_hmutex= CreateMutex(NULL,FALSE,NULL);
	if(esp_wmmoving_hmutex==NULL) return 1;

	//テキストウィンドウ用Mutex作成
    esp_tw_hmutex= CreateMutex(NULL,FALSE,NULL);
	if(esp_tw_hmutex==NULL) return 1;

   // ヒープメモリを確保
	//多重起動の確認
	//空いている番号のクラス名を作成
	for(esp_id=0; esp_id<ESP_MAINWINDOWMAX; esp_id++){
		swprintf_s(esp_mw_classname,ESP_MAINCLASSNAMEMAX,L"esplib_mw%d",esp_id);
		if(!FindWindow(esp_mw_classname,NULL)) break;
	}
	if(esp_id==ESP_MAINWINDOWMAX){
		MessageBox(HWND_DESKTOP,L"Over instance limit!",L"ESPLIB",MB_OK);
		return 1;
	}

	//GDI+の初期化
	GdiplusStartup(&esp_gdiplusToken, &esp_gdiplusStartupInput, 0);

	//時間計測関数のための準備
	QueryPerformanceFrequency(&esp_li_freq);
	//esp_ld_fpms = (long double)(1000.0 / esp_li_freq.QuadPart);
	//esp_ld_fpus=(long double)(1000000.0/esp_li_freq.QuadPart);
	esp_hInst= hThisInst;

	GetCurrentDirectory(MAX_PATH,_esp_gofn_path);
	wchar_t2char(_esp_gofn_path,esp_gofn_path,MAX_PATH);
	GetCurrentDirectory(MAX_PATH,_esp_gsfn_path);
	wchar_t2char(_esp_gsfn_path,esp_gsfn_path,MAX_PATH);

	GetCurrentDirectory(MAX_PATH,_esp_logbase);
	if(*(_esp_logbase+wcslen(_esp_logbase)-1)!=L'\\'){
		wcscat_s(_esp_logbase,MAX_PATH,L"\\");
	}
	wchar_t2char(_esp_logbase,esp_logbase,MAX_PATH);

	//テキストウィンドウ入力履歴の初期化
	esp_tw_history[0]=0;

	//カスタムカラーの初期化
	for(int i=0;i<16;i++) esp_CustColors[i]=0;

	WNDCLASSEX wcl;

	//ウィンドウクラス登録（メインウィンドウ）
	wcl.hInstance=esp_hInst;
	wcl.lpszClassName=esp_mw_classname;
	wcl.lpfnWndProc=ESP_MWfunc;
	wcl.style=CS_CLASSDC;
	wcl.cbSize=sizeof(WNDCLASSEX);
	wcl.hIcon=NULL;
	wcl.hIconSm=NULL;
	wcl.hCursor=LoadCursor(NULL, IDC_ARROW);
	wcl.lpszMenuName=NULL;
	wcl.cbClsExtra=0;
	wcl.cbWndExtra=0;
	wcl.hbrBackground=(HBRUSH)(COLOR_BTNFACE+1);
	if(!RegisterClassEx(&wcl)) return 1;

	//ウィンドウクラス登録（イメージウィンドウ）
	wcl.hInstance=esp_hInst;
	wcl.lpszClassName=esp_iw_classname;
	wcl.lpfnWndProc=ESP_IWfunc;
	wcl.style=CS_OWNDC;		//ver.4.2
	wcl.cbSize=sizeof(WNDCLASSEX);
	wcl.hIcon=NULL;
	wcl.hIconSm=NULL;
	wcl.hCursor=LoadCursor(NULL, IDC_ARROW);
	wcl.lpszMenuName=NULL;
	wcl.cbClsExtra=0;
	wcl.cbWndExtra=0;
	wcl.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	if(!RegisterClassEx(&wcl)) return 1;

	//ウィンドウクラス登録（テキストウィンドウ）
	wcl.hInstance=esp_hInst;
	wcl.lpszClassName=esp_tw_classname;
	wcl.lpfnWndProc=ESP_TWfunc;
	wcl.style=CS_OWNDC;		//ver.6.3
	wcl.cbSize=sizeof(WNDCLASSEX);
	wcl.hIcon=NULL;
	wcl.hIconSm=NULL;
	wcl.hCursor=LoadCursor(NULL, IDC_ARROW);
	wcl.lpszMenuName=NULL;
	wcl.cbClsExtra=0;
	wcl.cbWndExtra=0;
	wcl.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	if(!RegisterClassEx(&wcl)) return 1;

	//ウィンドウクラス登録（インプットボックス）
	wcl.hInstance=esp_hInst;
	wcl.lpszClassName=esp_ib_classname;
	wcl.lpfnWndProc=ESP_IBfunc;
	wcl.style=CS_DBLCLKS|CS_OWNDC;
	wcl.cbSize=sizeof(WNDCLASSEX);
	wcl.hIcon=NULL;
	wcl.hIconSm=NULL;
	wcl.hCursor=LoadCursor(NULL, IDC_ARROW);
	wcl.lpszMenuName=NULL;
	wcl.cbClsExtra=0;
	wcl.cbWndExtra=0;
	wcl.hbrBackground=(HBRUSH)(COLOR_BTNFACE+1);
	if(!RegisterClassEx(&wcl)) return 1;

	//ウィンドウクラス登録（ボタンボックス）
	wcl.hInstance=esp_hInst;
	wcl.lpszClassName=esp_bb_classname;
	wcl.lpfnWndProc=ESP_BBfunc;
	wcl.style=CS_DBLCLKS|CS_OWNDC;
	wcl.cbSize=sizeof(WNDCLASSEX);
	wcl.hIcon=NULL;
	wcl.hIconSm=NULL;
	wcl.hCursor=LoadCursor(NULL, IDC_ARROW);
	wcl.lpszMenuName=NULL;
	wcl.cbClsExtra=0;
	wcl.cbWndExtra=0;
	wcl.hbrBackground=(HBRUSH)(COLOR_BTNFACE+1);
	if(!RegisterClassEx(&wcl)) return 1;

	RECT rc;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rc,0);
	int xc=(rc.left+rc.right)/2;
	int yb=rc.bottom;
	
	//メニューの作成
	esp_hmenu=CreateMenu();
	esp_AppendMenu(esp_hmenu,0,MFS_ENABLED,ID_START,"Start(&S)");
	esp_AppendMenu(esp_hmenu,1,MFS_ENABLED,ID_STOP,"Stop(&C)");
	esp_AppendMenu(esp_hmenu,2,MFS_ENABLED,ID_EXIT,"Exit(&X)");

	RECT r;
	r.left=0;
	r.top=0;
	r.right=240;								// 240=横幅
	r.bottom=32+GetSystemMetrics(SM_CYMENU);	//  32=縦幅
	AdjustWindowRect(&r,WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_VISIBLE, FALSE);

	//MainWindowの標準位置
	esp_mw_x0 = xc-(r.right-r.left)/2;
	esp_mw_y0 = yb-(r.bottom-r.top);
	//MainWindow生成
	esp_mw_hwnd=CreateWindow(
		esp_mw_classname,
		TEXT(ESP_STR_ABOUT),
		WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | (esp_mw_show?WS_VISIBLE:0),
		esp_mw_x0, esp_mw_y0 - 55,				// 55=アニメーション移動合計量
		r.right-r.left, r.bottom-r.top,		
		HWND_DESKTOP, esp_hmenu, esp_hInst, NULL
	);
	esp_disp_color_mode();

	DragAcceptFiles(esp_mw_hwnd,TRUE);
	UpdateWindow(esp_mw_hwnd);

	//メインウィンドウＤＣの取得
	esp_mw_hdc=GetDC(esp_mw_hwnd);

	//フォントの作成
	esp_hfont=CreateFont(esp_ttwy,esp_ttwx,0,0,0,0,0,0,DEFAULT_CHARSET,
		OUT_TT_ONLY_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,ESPTTFONTNAME);

	ESP_TTColor(0xffffff);
	ESP_TTPosition(0,0);

	//ウィンドウ枠幅(差分)の取得
	RECT rc0, rc1;
	GetWindowRect(esp_mw_hwnd, &rc0);
	DwmGetWindowAttribute(esp_mw_hwnd, DWMWA_EXTENDED_FRAME_BOUNDS, &rc1, sizeof(rc1));
	esp_wfdif_x1= rc1.left - rc0.left;
	esp_wfdif_x2= rc1.right - rc0.right;
	esp_wfdif_y1= rc1.top - rc0.top;
	esp_wfdif_y2= rc1.bottom - rc0.bottom;

	esp_running= 1;
	MSG msg;
	//メインウィンドウのメッセージループ
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//スレッドの終了処理位置の変更 20210113 kinya iwamoto
	// スレッドの終了待ち
	DWORD dwExitCode = 0;
	::WaitForSingleObject(h_ESP_Loop, INFINITE);
	// スレッドの終了コードを取得
	::GetExitCodeThread(h_ESP_Loop, &dwExitCode);
#ifndef _MFC_VER
	//スレッドハンドルの解放
	CloseHandle(h_ESP_Loop);
	h_ESP_Loop = NULL;
#else
	//スレッドオブジェクトの解放
	//MFCではハンドルh_ESP_LoopはpRecvThread_esp_Loop->m_hThreadのため
	//スレッドオブジェクトを解放すれば自動的に解放される
	if (pRecvThread_esp_Loop) delete pRecvThread_esp_Loop;
	pRecvThread_esp_Loop = NULL;
#endif // !_MFC_VER

	//フォントの消滅
	DeleteObject(esp_hfont);

	//メニュー消滅
	DestroyMenu(esp_hmenu);

	//GDI+の終了処理
	GdiplusShutdown(esp_gdiplusToken);

	//Mutex終了
	CloseHandle(esp_tw_hmutex);
	CloseHandle(esp_wmmoving_hmutex);
	CloseHandle(esp_ghMutex);

	esp_running= 0;
	return 0;
}

//v8.0
int ESP_Pause(const char *msg)
{
	wchar_t w[ESP_BUFMAX];
	char2wchar_t(msg,w,ESP_BUFMAX);
	int r= MessageBox(HWND_DESKTOP,w,L"Pause",MB_OKCANCEL);
	if(r==IDOK) return 0; else return 1;
}

//メインウィンドウ宛メッセージのチェック
void CMmain(void)
{
	MSG msg;
	while(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)){
		GetMessage(&msg, NULL, 0, 0);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void esp_RequestDibDisp(HBITMAP hbm)
{
	while(esp_req) CMmain();
	esp_req_hbm= hbm;
	esp_req_fin= 0;
	esp_req= ESP_REQ_DIBDISP;
	while(!esp_req_fin) CMmain();
}

void ESP_Printf(const char *format, ...);
void CM(void);

int esp_RequestCreateImageX(int i,const char *title,int x0,int y0,int wx,int wy,int zoom,int bit,int flag)
{
	while(esp_req) CMmain();
	esp_req_fin= 0;
	esp_req_i= i;
	esp_req_title= title;
	esp_req_x0= x0;
	esp_req_y0= y0;
	esp_req_wx= wx;
	esp_req_wy= wy;
	esp_req_zoom= zoom;
	esp_req_bit= bit;
	esp_req_flag= flag;
	esp_req= ESP_REQ_CREATEIMAGE;
	while(!esp_req_fin) CMmain();
	return esp_req_ret;
}

//v8.0
int esp_RequestDestroyImage(int i)
{
	while (esp_req) CMmain();
	esp_req_fin = 0;
	esp_req_i = i;
	esp_req = ESP_REQ_DESTROYIMAGE;
	while (!esp_req_fin) CMmain();
	return esp_req_ret;
}

void esp_RequestOpenTextWindow(int i, int x0, int y0, int wx, int wy)
{
	if(esp_tw[i].show){
		SetForegroundWindow(esp_tw[i].hwnd);
		return;
	}
	while(esp_req) CMmain();
	esp_req_i= i;
	esp_req_x0= x0;
	esp_req_y0= y0;
	esp_req_wx= wx;
	esp_req_wy= wy;
	esp_req_fin= 0;
	esp_req= ESP_REQ_OPENTEXTWINDOW;
	while(!esp_req_fin) CMmain();
}

//v8.0
int esp_RequestCloseTextWindow(int i)
{
	while (esp_req) CMmain();
	esp_req_fin = 0;
	esp_req_i = i;
	esp_req = ESP_REQ_CLOSETEXTWINDOW;
	while (!esp_req_fin) CMmain();
	return esp_req_ret;
}

void esp_RequestOpenInputBox(int x0, int y0, int i)
{
	while(esp_req) CMmain();
	esp_req_x0= x0;
	esp_req_y0= y0;
	esp_req_i= i;
	esp_req_fin= 0;
	esp_req= ESP_REQ_OPENINPUTBOX;
	while(!esp_req_fin) CMmain();
}

//v8.0
int esp_RequestCloseInputBox(void)
{
	while (esp_req) CMmain();
	esp_req_fin = 0;
	esp_req = ESP_REQ_CLOSEINPUTBOX;
	while (!esp_req_fin) CMmain();
	return esp_req_ret;
}

void esp_RequestOpenButtonBox(int x0, int y0, int wx, int wy)
{
	while(esp_req) CMmain();
	esp_req_x0= x0;
	esp_req_y0= y0;
	esp_req_wx= wx;
	esp_req_wy= wy;
	esp_req_fin= 0;
	esp_req= ESP_REQ_OPENBUTTONBOX;
	while(!esp_req_fin) CMmain();
}

//v8.0
int esp_RequestCloseButtonBox(void)
{
	while (esp_req) CMmain();
	esp_req_fin = 0;
	esp_req = ESP_REQ_CLOSEBUTTONBOX;
	while (!esp_req_fin) CMmain();
	return esp_req_ret;
}

void esp_RequestUpdate_(int i)
{
	while(esp_req) CMmain();
	esp_req_i= i;
	esp_req= ESP_REQ_UPDATE;
	while(!esp_req_fin) CMmain();
}

// 7.0
int esp_RequestImageLoad(int i, const char *filename, int x0, int y0)
{
	while(esp_req) CMmain();
	esp_req_i= i;
	esp_req_filename= filename;
	esp_req_x0= x0;
	esp_req_y0= y0;
	esp_req_fin= 0;
	esp_req= ESP_REQ_IMAGELOAD;
	while(!esp_req_fin) CMmain();
	return esp_req_ret;
}

// メッセージの処理
void CM(void)
{
	MSG msg;

	while(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)){
		GetMessage(&msg, NULL, 0, 0);
		// TABキーなどのメッセージを処理するのに必要
		if(esp_ib_hwnd){
			if(IsDialogMessage(esp_ib_hwnd,&msg)) continue;
		}
		if(esp_bb_hwnd){
			if(IsDialogMessage(esp_bb_hwnd,&msg)) continue;
		}
		//それ以外のメッセージの処理
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

int ESP_SetForeground(int i)
{
	if((unsigned int)i<ESP_IW_MAX){
		if(esp_iw[i].show){
			SetForegroundWindow(esp_iw[i].hwnd);
		}else return 1;
	}else if((unsigned int)i>=ESPTWBASE && (unsigned int)i<(ESPTWBASE+ESP_TW_MAX)){
		if(esp_tw[i-ESPTWBASE].show){
			SetForegroundWindow(esp_tw[i-ESPTWBASE].hwnd);
		}
	}else if(i==ESPMAINWINDOW){
		SetForegroundWindow(esp_mw_hwnd);
	}else if(i==ESPINPUTBOX && esp_ib_hwnd){
		SetForegroundWindow(esp_ib_hwnd);
	}else if(i==ESPBUTTONBOX && esp_bb_hwnd){
		SetForegroundWindow(esp_bb_hwnd);
	}else return 1;
	return 0;
}

//hwndの座標，ハンドルをリストに追加 v8.1
void esp_add_list(HWND hwnd)
{
	RECT rc;
	GetWindowRect(hwnd,&rc);
	rc.left   += esp_wfdif_x1;	//v8.1
	rc.top    += esp_wfdif_y1;
	rc.right  += esp_wfdif_x2;
	rc.bottom += esp_wfdif_y2;

	esp_list[esp_list_n].x1= rc.left;
	esp_list[esp_list_n].y1= rc.top;
	esp_list[esp_list_n].x2= rc.right;
	esp_list[esp_list_n].y2= rc.bottom;
	esp_list[esp_list_n].hwnd= hwnd;
	esp_list_n++;
}

//v8.1
void esp_list_update(void)
{
	esp_list_n= 0;
	RECT rc;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rc,0);

	//デスクトップ領域(0-3)
	esp_list[esp_list_n].x1= -10000;
	esp_list[esp_list_n].y1= rc.top;
	esp_list[esp_list_n].x2= rc.left;
	esp_list[esp_list_n].y2= rc.bottom;
	esp_list[esp_list_n].hwnd= HWND_DESKTOP;
	esp_list_n++;
	esp_list[esp_list_n].x1= rc.left;
	esp_list[esp_list_n].y1= -10000;
	esp_list[esp_list_n].x2= rc.right;
	esp_list[esp_list_n].y2= rc.top;
	esp_list[esp_list_n].hwnd= HWND_DESKTOP;
	esp_list_n++;
	esp_list[esp_list_n].x1= rc.right;
	esp_list[esp_list_n].y1= rc.top;
	esp_list[esp_list_n].x2= rc.right+10000;
	esp_list[esp_list_n].y2= rc.bottom;
	esp_list[esp_list_n].hwnd= HWND_DESKTOP;
	esp_list_n++;
	esp_list[esp_list_n].x1= rc.left;
	esp_list[esp_list_n].y1= rc.bottom;
	esp_list[esp_list_n].x2= rc.right;
	esp_list[esp_list_n].y2= rc.bottom+10000;
	esp_list[esp_list_n].hwnd= HWND_DESKTOP;
	esp_list_n++;

	for(int i=0;i<ESP_IW_MAX;i++){
		if(esp_iw[i].show) esp_add_list(esp_iw[i].hwnd);
	}
	for(int i=0;i<ESP_TW_MAX;i++){
		if(esp_tw[i].show) esp_add_list(esp_tw[i].hwnd);
	}
	if(esp_ib_hwnd) esp_add_list(esp_ib_hwnd);
	if(esp_bb_hwnd) esp_add_list(esp_bb_hwnd);
	esp_add_list(esp_mw_hwnd);
}

//ウィンドウ移動中(WM_MOVING)に呼ばれる v8.1
//  hwnd:移動中のウィンドウ lParam:更新中のRECT
void esp_wm_moving(HWND hwnd, LPARAM lParam)
{
	if(esp_wmmoving_get()!=WAIT_OBJECT_0) return;

	//Ctrlキーの処理
	if(GetKeyState(VK_CONTROL)<0){

		int x1= ((LPRECT)lParam)->left   +esp_wfdif_x1;	//v8.1
		int y1= ((LPRECT)lParam)->top    +esp_wfdif_y1;
		int x2= ((LPRECT)lParam)->right  +esp_wfdif_x2;
		int y2= ((LPRECT)lParam)->bottom +esp_wfdif_y2;
		int flag= 0;

		int listnum= esp_list_n;
		if(GetKeyState(VK_MENU)<0) listnum= 4;	//Altキー併用時はデスクトップ境界のみ

		for(int i=0; i<listnum; i++){
			if(hwnd==esp_list[i].hwnd) continue;	//自分自身はスキップ
			int dx21= esp_list[i].x2 - x1;
			int dx12= esp_list[i].x1 - x2;
			int dx11= esp_list[i].x1 - x1;
			int dx22= esp_list[i].x2 - x2;
			int dy21= esp_list[i].y2 - y1;
			int dy12= esp_list[i].y1 - y2;
			int dy11= esp_list[i].y1 - y1;
			int dy22= esp_list[i].y2 - y2;
			int fx= (esp_list[i].x1<=x2 && esp_list[i].x2>=x1);
			int fy= (esp_list[i].y1<=y2 && esp_list[i].y2>=y1);
			
			if(!(flag & 1)){
			if(fy && abs(dx21)<ESP_EDGEFIT){
				((LPRECT)lParam)->left += dx21;
				((LPRECT)lParam)->right += dx21;
				flag|=1;
			}else if (fy && abs(dx12)<ESP_EDGEFIT){
				((LPRECT)lParam)->left += dx12;
				((LPRECT)lParam)->right += dx12;
				flag|=1;
			}
			}
			if(!(flag & 2)){
			if(flag & 1){
				if(fx && abs(dy11)<ESP_EDGEFIT){
					((LPRECT)lParam)->top += dy11;
					((LPRECT)lParam)->bottom += dy11;
					flag|=2;
				}else if(fx && abs(dy22)<ESP_EDGEFIT){
					((LPRECT)lParam)->top += dy22;
					((LPRECT)lParam)->bottom += dy22;
					flag|=2;
				}
			}
			}

			if(!(flag & 2)){
			if (fx && abs(dy21)<ESP_EDGEFIT){
				((LPRECT)lParam)->top += dy21;
				((LPRECT)lParam)->bottom += dy21;
				flag|=2;
			}else if (fx && abs(dy12)<ESP_EDGEFIT){
				((LPRECT)lParam)->top += dy12;
				((LPRECT)lParam)->bottom += dy12;
				flag|=2;
			}
			}
			if(!(flag & 1)){
			if(flag & 2){
				if(fy && abs(dx11)<ESP_EDGEFIT){
					((LPRECT)lParam)->left += dx11;
					((LPRECT)lParam)->right += dx11;
					flag|=1;
				}else if(fy && abs(dx22)<ESP_EDGEFIT){
					((LPRECT)lParam)->left += dx22;
					((LPRECT)lParam)->right += dx22;
					flag|=1;
				}
			}
			}
			if(flag==3) break;
		}
	}

	if(GetKeyState(VK_MENU)<0){
		//Altキー(VK_MENU)の処理 v8.1
		RECT rc;
		GetWindowRect(hwnd,&rc);
		int dx= ((LPRECT)lParam)->left - rc.left;
		int dy= ((LPRECT)lParam)->top  - rc.top;
		//ウィンドウの移動
		for(int i=4; i<esp_list_n; i++){
			esp_list[i].x1 += dx;
			esp_list[i].y1 += dy;
			esp_list[i].x2 += dx;
			esp_list[i].y2 += dy;
			SetWindowPos(esp_list[i].hwnd, NULL,
				esp_list[i].x1 - esp_wfdif_x1,
				esp_list[i].y1 - esp_wfdif_y1,
				0, 0, SWP_NOSIZE|esp_setpos_flags);
		}
	}else{
		//自分自身の座標更新 v8.1
		for(int i=4; i<esp_list_n; i++){
			if(hwnd==esp_list[i].hwnd){
				/*
				esp_list[i].x1= ((LPRECT)lParam)->left   ;
				esp_list[i].y1= ((LPRECT)lParam)->top    ;
				esp_list[i].x2= ((LPRECT)lParam)->right  ;
				esp_list[i].y2= ((LPRECT)lParam)->bottom ;
				*/
				
				esp_list[i].x1= ((LPRECT)lParam)->left   +esp_wfdif_x1;
				esp_list[i].y1= ((LPRECT)lParam)->top    +esp_wfdif_y1;
				esp_list[i].x2= ((LPRECT)lParam)->right  +esp_wfdif_x2;
				esp_list[i].y2= ((LPRECT)lParam)->bottom +esp_wfdif_y2;
				
			}
		}
	}

	esp_wmmoving_release();
}

#ifndef ESP_LIBRARY_MODE
	#define ESP_OpenTextWindow(i,x0,y0,wx,wy) (esp_OpenTextWindow((i),(x0),(y0),(wx),(wy)))
#else
	#define ESP_OpenTextWindow(i,x0,y0,wx,wy) (esp_RequestOpenTextWindow((i),(x0),(y0),(wx),(wy)))
#endif

//テキストウィンドウを開く v8.2
int esp_OpenTextWindow(int i,int x0,int y0,int wx,int wy)
{
	if((unsigned int)i>=ESP_TW_MAX) return 2;
	if(esp_tw[i].show){
		SetForegroundWindow(esp_tw[i].hwnd);
		esp_twi= i;
		return 1;
	}

	RECT rcd;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rcd,0);	//デスクトップ領域取得

	//負の値ならデフォルト値を設定
	//if(x0<0) x0=CW_USEDEFAULT; else x0+=rcd.left;	// v7.6 v8.2
	//if(y0<0) y0=CW_USEDEFAULT; else y0+=rcd.top;	// v7.6 v8.2
	x0 += rcd.left;
	y0 += rcd.top;
	if(wx<0) wx= ESP_DEFTW_WX;
	if(wy<0) wy= ESP_DEFTW_WY;

	esp_tw[i].wx= wx;
	esp_tw[i].wy= wy;
	esp_twi= i;
	esp_tw[i].tcolor= 0xffffff;
	esp_tw[i].bcolor= 0x000000;

	wchar_t buf[ESP_BUFMAX];
	swprintf_s(buf,ESP_BUFMAX,L"TextWindow %d",i);

	RECT r;

	//ウィンドウ枠の幅を取得
	r.left=0;
	r.top=0;
	r.right=200;
	r.bottom=200;
	AdjustWindowRect(&r, esp_tw_wstyle, FALSE);
	esp_tw[i].fx= r.right - r.left - 200;
	esp_tw[i].fy= r.bottom - r.top - 200;

	//ウィンドウサイズの決定
	r.left= 0;
	r.top= 0;
	r.right= wx;
	r.bottom= wy;
	AdjustWindowRect(&r, esp_tw_wstyle, FALSE);

	esp_tw[i].hwnd= CreateWindow(
		esp_tw_classname,buf,WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_SYSMENU | WS_VISIBLE,
		x0, y0, r.right-r.left, r.bottom-r.top,
		esp_mw_hwnd, NULL,esp_hInst,NULL
	);

	//MFCのリリースモードの時だけテキストウインドウを生成するときにCreateWindowでesp_hInstが書き換わってします;20210109 kinya iwamoto
	//コールバック関数のESP_TWfuncの処理も確認しましたが、どこで値が入れ替わっているか摑めていない。他のウインドウのCreateWindowでは
	//このような現象が起こっていないので、CreateWindow関数の仕様ではないと思います。
	//MFCが原因なのかライブラリモード原因なのかはっきりしませんが、大幅に環境が変わることからMFCが原因ではないかと推測します。
	//応急処置としてMFCのリリースモードだけesp_hInstに再度、値を代入する処理を加えました。
#ifdef _MFC_VER
#ifndef DEBUG
	esp_hInst = GetModuleHandle(NULL);		
#endif // !DEBUG
#endif // _MFC_VER
	esp_tw[i].hdc= GetDC(esp_tw[i].hwnd);
	esp_tw[i].memdc= CreateCompatibleDC(esp_tw[i].hdc);
	esp_tw[i].hbit= CreateCompatibleBitmap(esp_tw[i].hdc,esp_tw[i].wx,esp_tw[i].wy);

	SelectObject(esp_tw[i].memdc,GetStockObject(BLACK_BRUSH));
	SelectObject(esp_tw[i].memdc,GetStockObject(OEM_FIXED_FONT));
	esp_tw[i].hbitold=(HBITMAP)SelectObject(esp_tw[i].memdc,esp_tw[i].hbit);
	esp_tw[i].x= 0;
	esp_tw[i].y= 0;
	SetTextColor(esp_tw[i].memdc,esp_tw[i].tcolor);
	SetBkColor(esp_tw[i].memdc,esp_tw[i].bcolor);
	TEXTMETRIC tm;
	GetTextMetrics(esp_tw[i].memdc,&tm);
	esp_tw[i].w= tm.tmAveCharWidth;
	esp_tw[i].h= tm.tmHeight;

	//色変更履歴の初期化
	for(int j=0;j<ESP_TWCOLOR_HISTORY;j++){
		esp_tw[i].tcolor_prev[j]= esp_tw[i].tcolor;
		esp_tw[i].bcolor_prev[j]= esp_tw[i].bcolor;
	}

	esp_tw[i].show= 1;
	esp_list_update();
	//ログ情報の初期化
	esp_tw[i].logstatus= 0;

	UpdateWindow(esp_tw[i].hwnd);
	SetForegroundWindow(esp_tw[i].hwnd);
	return 0;
}

//同じスレッド用
void esp_DefaultTextWindow(void)
{
	if(!esp_tw[esp_twi].show){
		int wx=GetSystemMetrics(SM_CXFULLSCREEN);
		int wy=GetSystemMetrics(SM_CYFULLSCREEN);
		esp_OpenTextWindow(0,wx/2-ESP_DEFTW_WX/2,wy/2-ESP_DEFTW_WY/2,ESP_DEFTW_WX,ESP_DEFTW_WY);
	}else{
		SetForegroundWindow(esp_tw[esp_twi].hwnd);
	}
}

void ESP_DefaultTextWindow(void)
{
	if(!esp_tw[esp_twi].show){
		int wx=GetSystemMetrics(SM_CXFULLSCREEN);
		int wy=GetSystemMetrics(SM_CYFULLSCREEN);
		ESP_OpenTextWindow(0,wx/2-ESP_DEFTW_WX/2,wy/2-ESP_DEFTW_WY/2,ESP_DEFTW_WX,ESP_DEFTW_WY);
	}else{
		SetForegroundWindow(esp_tw[esp_twi].hwnd);
	}
}

int ESP_GetForeground(void)
{
	HWND hwnd = GetForegroundWindow();

	for(int i=0;i<ESP_IW_MAX;i++){
		if(esp_iw[i].show){
			if(esp_iw[i].hwnd==hwnd){
				return i;
			}
		}
	}
	for(int i=0;i<ESP_TW_MAX;i++){
		if(esp_tw[i].show){
			if(esp_tw[i].hwnd==hwnd){
				return ESPTWBASE+i;;	
			}
		}
	}
	if(hwnd==esp_mw_hwnd) return ESPMAINWINDOW;
	if(hwnd==esp_ib_hwnd) return ESPINPUTBOX;
	if(hwnd==esp_bb_hwnd) return ESPBUTTONBOX;
	return -1;
}

__inline int esp_tw_scrollcheck(int i)
{
	int h = esp_tw[i].h;
	if(esp_tw[i].y+h > esp_tw[i].wy){	//v8.0
		BitBlt(esp_tw[i].memdc,0,0,esp_tw[i].wx,esp_tw[i].y-h,esp_tw[i].memdc,0,h,SRCCOPY);
		esp_tw[i].y-=h;
		PatBlt(esp_tw[i].memdc,0,esp_tw[i].y,esp_tw[i].wx,esp_tw[i].y+h,PATCOPY);
		return 1;
	}
	return 0;
}

__inline int esp_return(int i)
{
	esp_tw[i].x= 0;
	esp_tw[i].y += esp_tw[i].h;
	return esp_tw_scrollcheck(i);
}

// n : 文字数
// n2: 描画する幅文字数 7.0
__inline void esp_textout(HDC hdc, int x0, int y0, wchar_t *s, int n, int n2)
{
	TextOut(hdc,x0,y0,s,n);

	RECT rc;
	rc.left= x0;
	rc.top= y0;
	rc.right= x0+esp_tw[esp_twi].w*n2;
	rc.bottom= y0+esp_tw[esp_twi].h;

	InvalidateRect(esp_tw[esp_twi].hwnd,&rc,FALSE);
}

//最大文字数 for ESP_Puts()/ESP_Printf()/ESP_Gprintf()
#ifndef ESP_STRMAX
#define ESP_STRMAX 4096
#endif
wchar_t esp_wbuf[ESP_STRMAX];
char esp_buf[ESP_STRMAX];

//ESP_Puts/PutsU/Printf/PrintfU/PrintfBin/PrintfDateTimeから呼ばれる v7.8
//高速化版 v7.0
//先頭が\nのときのバグ修正 v7.3
//半角カタカナ(unicode)対応 v7.5
//書式指定(%で始まる)文字列は変換せずそのまま表示
//\nは処理する
//画面の更新行わない v7.7
void esp_puts_(const char *s)
{
	//TextWindowの存在チェック
	if(!esp_tw[esp_twi].show) return;
	
	char2wchar_t(s, esp_wbuf, ESP_STRMAX);

	wchar_t *pw, *pw0;
	pw0=pw=esp_wbuf;

	//ログの記録
	if(esp_tw[esp_twi].logstatus==1){
		fputs(s, esp_tw[esp_twi].logfile);
	}

	//文字の幅(半角換算)
	int w=esp_tw[esp_twi].w;

	int nw=0;	//文字数(UNICODE数)
	int x=esp_tw[esp_twi].x;

	for(;;){
		wchar_t c = *pw++;
		if(c==L'\0') break;
		if(c==L'\n'){
			if(nw){
				TextOut(esp_tw[esp_twi].memdc,esp_tw[esp_twi].x,esp_tw[esp_twi].y,pw0,nw);
				nw=0;
			}
			pw0=pw;		//ver.7.3
			esp_return(esp_twi);
			x=0;
		}
		else if(c<0x80 || (c>=0xFF61 && c<=0xFF9f)){
			//半角
			//半角カタカナ(UNICODE: FF61h-FF9Fh)
			if(x+w > esp_tw[esp_twi].wx){
				TextOut(esp_tw[esp_twi].memdc,esp_tw[esp_twi].x,esp_tw[esp_twi].y,pw0,nw);
				pw0=pw-1;
				nw=0;
				esp_return(esp_twi);
				x=0;
			}
			nw++;
			x+=w;
		}
		else{
			//全角
			if(x+2*w > esp_tw[esp_twi].wx){
				TextOut(esp_tw[esp_twi].memdc,esp_tw[esp_twi].x,esp_tw[esp_twi].y,pw0,nw);
				pw0=pw-1;
				nw=0;
				esp_return(esp_twi);
				x=0;
			}
			nw++;
			x+=2*w;
		}
	}

	if(nw){
		TextOut(esp_tw[esp_twi].memdc,esp_tw[esp_twi].x,esp_tw[esp_twi].y,pw0,nw);
		esp_tw[esp_twi].x=x;
	}

	InvalidateRect(esp_tw[esp_twi].hwnd,NULL,FALSE);

	//CM();	//comment out v7.7
}

//Mutexを導入 v7.8
void ESP_Puts(const char *s)
{
	//Mutex取得
	esp_tw_get();

	esp_puts_(s);

	//Mutex解放
	esp_tw_release();
}

//文字出力後に更新処理を行う
//Mutexを導入 v7.8
void ESP_PutsU(const char *s)
{
	//Mutex取得
	esp_tw_get();

	esp_puts_(s);
	CM();

	//Mutex解放
	esp_tw_release();
}

//"%20\n"等で固まる→ESP_Puts()を使う
//画面の更新行わない v7.7
//Mutexを導入 v7.8
void ESP_Printf(const char *format, ...)
{
	//Mutex取得
	esp_tw_get();

	//TextWindowの存在チェック
	if(!esp_tw[esp_twi].show) return;

	va_list vl;
	va_start(vl,format);

	vsprintf_s(esp_buf,ESP_STRMAX,format,vl);

	esp_puts_(esp_buf);

	//Mutex解放
	esp_tw_release();
}

//文字出力後に更新処理を行う
//Mutexを導入 v7.8
void ESP_PrintfU(const char *format, ...)
{
	//Mutex取得
	esp_tw_get();

	//TextWindowの存在チェック
	if(!esp_tw[esp_twi].show) return;

	va_list vl;
	va_start(vl,format);

	vsprintf_s(esp_buf,ESP_STRMAX,format,vl);

	esp_puts_(esp_buf);
	CM();

	//Mutex解放
	esp_tw_release();
}

//Mutexを導入 v7.8
//引数の仕様変更 v8.1
void ESP_PrintfBin(unsigned long long data, int bit)
{
	esp_tw_get();	//Mutex取得

	char buf[65];

	bit= Limit(1,bit,64);
	for(int i=0;i<bit;i++){
		unsigned long long a = 1ULL<<(bit-i-1);
		if(data & a) buf[i]='1'; else buf[i]='0';
	}
	buf[bit]='\0';
	esp_puts_(buf);

	esp_tw_release();	//Mutex解放
}

//現在日時の表示 "Date-Time 20**/**/**-**:**:**\n"
void ESP_PrintfDateTime(void)
{
	char ss[32], buf[32], outtext[256];

	strcpy_s(outtext,sizeof(outtext),"Date-Time ");

	_strdate_s(buf,sizeof(buf));
	ss[0]='2';
	ss[1]='0';
	*(short *)(ss+2)= *(short *)(buf+6);
	ss[4]='/';
	*(short *)(ss+5)= *(short *)(buf+0);
	ss[7]='/';
	*(short *)(ss+8)= *(short *)(buf+3);
	ss[10]= '-';
	_strtime_s(buf,sizeof(buf));
	*(short *)(ss+11)= *(short *)(buf+0);
	ss[13]=':';
	*(short *)(ss+14)= *(short *)(buf+3);
	ss[16]=':';
	*(short *)(ss+17)= *(short *)(buf+6);
	ss[19]= '\n';
	ss[20]= '\0';

	strcat_s(outtext,sizeof(outtext),ss);

	esp_tw_get();		//Mutex取得
	esp_puts_(outtext);
	esp_tw_release();	//Mutex解放
}

//テキストウィンドウ関連

//共通関数（TW:ウィンドウ番号iのチェック）
//戻り値：0正常(存在する), 1範囲外, 2存在しない
__inline int esp_tw_check(int i)
{
	if((unsigned int)i>=ESP_TW_MAX) return 1;
	if(!esp_tw[i].show) return 2;
	return 0;
}

//v8.0
#ifndef ESP_LIBRARY_MODE
#define ESP_CloseTextWindow(i) (esp_CloseTextWindow((i)))
#else
#define ESP_CloseTextWindow(i) (esp_RequestCloseTextWindow((i)))
#endif
int esp_CloseTextWindow(int i)
{
	if(esp_tw_check(i)) return 1;

	esp_tw[i].show=0;

	//閉じるTW番号が選択中のとき
	if(esp_twi==i){
		//他のTWがあればそれを選択する
		for(int j=0;j<ESP_TW_MAX;j++){
			if(esp_tw[j].show){
				esp_twi=j;
				break;
			}
		}
	}
	if(esp_tw_inputflag==i+1) esp_tw_inputflag=0;

	SelectObject(esp_tw[i].memdc,esp_tw[i].hbitold);
	DeleteObject(esp_tw[i].hbit);
	DeleteDC(esp_tw[i].memdc);
	ReleaseDC(esp_tw[i].hwnd,esp_tw[i].hdc);

	if (!DestroyWindow(esp_tw[i].hwnd)){
		MessageBox(esp_mw_hwnd, L"DestroyWindow[TW] Error", L"ESPLIB Error!", MB_OK | MB_ICONERROR);
	}
	return 0;
}

int ESP_SelectTW(int i)
{
	if(esp_tw_check(i)) return 1;
		
	for(int j=(ESP_TWSELECT_HISTORY-1);j>0;j--){
		esp_tw_select_prev[j]=esp_tw_select_prev[j-1];
	}
	esp_tw_select_prev[0]=esp_twi;
	esp_twi=i;

	return 0;
}

int ESP_UnSelectTW(void)
{
	int i=esp_tw_select_prev[0];

	if(esp_tw_check(i)) return 1;
		
	esp_twi=i;

	for(i=0;i<(ESP_TWSELECT_HISTORY-1);i++){
		esp_tw_select_prev[i]=esp_tw_select_prev[i+1];
	}
	return 0;
}

//キーバッファから１文字を取り出す 7.0
wchar_t esp_tw_key(void){
	//入力文字があるかチェック
	int rp = esp_tw_rp;
	if(rp<0) return 0;

	//文字読み出し
	wchar_t r=esp_tw_buffer[rp++];

	if(rp==ESPTWBUFMAX) rp=0;
	if(rp==esp_tw_wp) rp=-1;
	esp_tw_rp = rp;

	return r;
}

// 7.0
__inline void esp_cursor(int type)
{
	wchar_t c = (type&1) ? L'_' : L' ';
	esp_textout(esp_tw[esp_twi].memdc,esp_tw[esp_twi].x,esp_tw[esp_twi].y,&c,1,1);
}

// 7.0
void esp_pastetext(void)
{
	//クリップボードが空のとき
	if (!IsClipboardFormatAvailable(CF_UNICODETEXT)) return;
	//クリップボードのオープンに失敗したとき
	if (!OpenClipboard(NULL)) return;

	// CF_TEXT
	//HANDLE ht=GetClipboardData(CF_TEXT);
	//CF_UNICODETEXT 7.0
	HANDLE ht=GetClipboardData(CF_UNICODETEXT);
	if(!ht){
		CloseClipboard();
		return;
	}

	wchar_t *p = (wchar_t *)GlobalLock(ht);

	for(;;){
		wchar_t c = *p++;
		if(c==0 || c==L'\xA' || c==L'\xD') break;

		if (esp_tw_wp == esp_tw_rp) break;		//buffer full
		esp_tw_buffer[esp_tw_wp]=c;
		if (esp_tw_rp<0) esp_tw_rp=esp_tw_wp;
		if ((esp_tw_wp+1) == ESPTWBUFMAX) esp_tw_wp=0; else esp_tw_wp++;
	}
	GlobalUnlock(ht);
	CloseClipboard();
}

#define ESPTWLINEMAX 100

//テキストウィンドウにおいて文字列入力を行う 7.0
void ESP_Input(char *buffer)
{
	if(!esp_tw[esp_twi].show) return;

	SetForegroundWindow(esp_tw[esp_twi].hwnd);

	buffer[0]=0;
	esp_status("Input text");
	
	int startposx=esp_tw[esp_twi].x;
	int w=esp_tw[esp_twi].w;
	int h=esp_tw[esp_twi].h;
	unsigned int t0=esp_gettime();
	esp_tw_inputflag=esp_twi+1;
	
	wchar_t _buffer[ESPTWBUFMAX];
	int returnposx[ESPTWLINEMAX];
	int cursor=1;
	int type=1;
	int i=0;
	int line=0;
	int wt;

	while(1){
		CM();
		wchar_t key=esp_tw_key();
		if(key==VK_TAB) key=L' ';	//TABキー処理
		if(key==VK_RETURN) break;	//入力決定(Enter)

		//制御キーが押下されている場合
		switch(esp_tw_ctrl){
			case ESP_TWCTRL_HISTORY:	//履歴の利用(Arrow-Up)
				for(int j=0;j<ESPTWBUFMAX;j++){
					if(esp_tw_history[j]){
						SendMessage(esp_tw[esp_twi].hwnd,WM_CHAR,esp_tw_history[j],0);
					}else{
						break;
					}
				}
				esp_tw_ctrl=0;
				break;
			case ESP_TWCTRL_PASTE:		//Ctrl+V
				esp_pastetext();
				esp_tw_ctrl=0;
				break;
		}

		if(!esp_tw_inputflag) goto fin_input;
		
		if(key==VK_BACK){			//BSキー処理
		if(i>0){
			//カーソルを消す
			wchar_t c=L' ';
			esp_textout(esp_tw[esp_twi].memdc,esp_tw[esp_twi].x,esp_tw[esp_twi].y,&c,1,1);

			i--;
			if(_buffer[i]<0x80 || (_buffer[i]>=0xFF61 && _buffer[i]<=0xFF9f)){
				//半角のとき
				wt=1;
			}else{
				//全角のとき
				wt=2;
			}
			
			if(line>0 && esp_tw[esp_twi].x==0){
				esp_tw[esp_twi].x = returnposx[--line];
				esp_tw[esp_twi].y -= h;
			}else{
				esp_tw[esp_twi].x -= wt*w;
			}

			if(wt==2){			//全角のとき
				c=L'　';
				esp_textout(esp_tw[esp_twi].memdc,esp_tw[esp_twi].x,esp_tw[esp_twi].y,&c,1,2);
				if(line>0 && esp_tw[esp_twi].x==0){
					if(returnposx[line-1]>=esp_tw[esp_twi].wx){
						esp_tw[esp_twi].x = returnposx[--line]-2*w;
						esp_tw[esp_twi].y -= h;
					}
				}
			}
		}
		}else if(key && i<ESPTWBUFMAX-1){		//通常の文字入力
			if(key<0x80 || (key>=0xFF61 && key<=0xFF9f)){
				//半角文字のとき
				wt=1;
			}else{
				//全角文字のとき
				if(esp_tw[esp_twi].x > esp_tw[esp_twi].wx-2*w){
					//残りスペースが全角未満のとき
					//カーソルを消す
					wchar_t c=L' ';
					esp_textout(esp_tw[esp_twi].memdc,esp_tw[esp_twi].x,esp_tw[esp_twi].y,&c,1,1);
					returnposx[line++]=esp_tw[esp_twi].x+2*w;
					esp_tw[esp_twi].x=0;
					esp_tw[esp_twi].y+=h;
					//スクロールチェック
					if(esp_tw_scrollcheck(esp_twi))InvalidateRect(esp_tw[esp_twi].hwnd,NULL,FALSE);
				}
				wt=2;
			}
			//文字描画
			esp_textout(esp_tw[esp_twi].memdc,esp_tw[esp_twi].x,esp_tw[esp_twi].y,&key,1,wt);
			//文字幅wwを使って残りスペースのチェック
			if(esp_tw[esp_twi].x+wt*w > esp_tw[esp_twi].wx-w){
				//残りスペースが半角未満のとき
				returnposx[line++]=esp_tw[esp_twi].x;
				esp_tw[esp_twi].x=0;
				esp_tw[esp_twi].y+=h;
				//スクロールチェック
				if(esp_tw_scrollcheck(esp_twi))InvalidateRect(esp_tw[esp_twi].hwnd,NULL,FALSE);
			}else{
				esp_tw[esp_twi].x += wt*w;
			}
			_buffer[i++]=key;	//入力文字の格納
			cursor=1;			//カーソル表示フラグのセット
		}
		
		if(cursor){
			esp_cursor(type);
			cursor=0;
		}
		if(esp_gettime()-t0>200){
			t0=esp_gettime();
			type=1-type;
			cursor=1;
		}
	}
	esp_tw_inputflag=0;
	esp_cursor(0);
	esp_tw[esp_twi].x=0;
	esp_tw[esp_twi].y+=esp_tw[esp_twi].h;
	//スクロールチェック
	if(esp_tw_scrollcheck(esp_twi)) InvalidateRect(esp_tw[esp_twi].hwnd,NULL,FALSE);
	_buffer[i]=0;
	//---history
	wcscpy_s(esp_tw_history,ESPTWBUFMAX,_buffer);
	esp_tw_history[ESPTWBUFMAX-1]=0;
	//wchar_t to char
	wchar_t2char(_buffer,buffer,ESPTWBUFMAX);
	if(esp_tw[esp_twi].logstatus==1){
		fputs(buffer,esp_tw[esp_twi].logfile);
		fputc('\n',esp_tw[esp_twi].logfile);
	}
fin_input:;
	esp_disp_color_mode();
}

//-----インプットボックス関連-----

//共通関数（IB:項目番号iのチェック）
//戻り値：0正常，1:IBがない，2:範囲外 
__inline int esp_ib_check(int i)
{
	if(!esp_ib_hwnd) return 1;
	if((unsigned int)i>=(unsigned int)esp_ib_num) return 2;
	return 0;
}

#define ESP_IB_XOFFS 4
#define ESP_IB_YOFFS 4
#define ESP_IB_YSIZE 24
#define ESP_IB_YDIST (ESP_IB_YSIZE+ESP_IB_YOFFS)

//ラベル部の幅
#define ESP_IB_ISIZE 80
int _ESP_IB_ISIZE=ESP_IB_ISIZE;
//入力部の幅
#define ESP_IB_ESIZE 70
int _ESP_IB_ESIZE=ESP_IB_ESIZE;

//v8.0
#ifndef ESP_LIBRARY_MODE
#define ESP_CloseInputBox() (esp_CloseInputBox())
#else
#define ESP_CloseInputBox() (esp_RequestCloseInputBox())
#endif
int esp_CloseInputBox(void)
{
	if(!esp_ib_hwnd) return 1;

	if (!DestroyWindow(esp_ib_hwnd)){
		MessageBox(esp_mw_hwnd, L"DestroyWindow[IB] Error", L"ESPLIB Error!", MB_OK | MB_ICONERROR);
	}
	for(int i=0;i<esp_ib_num;i++){
		delete[] esp_ib[i].str;
	}
	esp_ib_hwnd= NULL;
	return 0;
}

void ESP_SetInputBoxTitle(int i,const char *title)
{
	if(esp_ib_check(i)) return;
	esp_setwindowtext(esp_ib[i].title_hwnd,"                    ");
	esp_setwindowtext(esp_ib[i].title_hwnd,title);
}

void esp_RenameIB(int i)
{
	char buf2[ESP_BUFMAX];
	esp_getwindowtext(esp_ib[i].title_hwnd,buf2,ESP_BUFMAX);
	esp_DefaultTextWindow();
	ESP_Printf("%d '%s' ->",i,buf2);

	char buf[ESPTWBUFMAX];
	ESP_Input(buf);
	if(buf[0])ESP_SetInputBoxTitle(i,buf);
}

#ifndef ESP_LIBRARY_MODE
	#define ESP_OpenInputBox(x0,y0,item_num) (esp_OpenInputBox((x0),(y0),(item_num)))
#else
	#define ESP_OpenInputBox(x0,y0,item_num) (esp_RequestOpenInputBox((x0),(y0),(item_num)))
#endif

//インプットボックスを開く
void esp_OpenInputBox(int x0,int y0,int item_num)
{
	if(esp_ib_hwnd) return;

	item_num=Limit(1,item_num,ESP_IB_MAX);
	esp_ib_num=item_num;

	RECT r;
	r.left  = 0;
	r.top   = 0;
	r.right = (3*ESP_IB_XOFFS+_ESP_IB_ISIZE+_ESP_IB_ESIZE);
	r.bottom= ESP_IB_YDIST*esp_ib_num+ESP_IB_YOFFS/2;		//6.7
	AdjustWindowRect(&r, WS_OVERLAPPED | WS_CAPTION	| WS_SYSMENU | WS_VISIBLE | WS_SIZEBOX, FALSE);

	RECT rcd;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rcd,0);	//デスクトップ領域取得

	esp_ib_hwnd=CreateWindow(
		esp_ib_classname,L"InputBox",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_SIZEBOX,
		x0+rcd.left, y0+rcd.top, r.right-r.left, r.bottom-r.top,
		esp_mw_hwnd,NULL,esp_hInst,NULL
	);

	for(int i=0;i<esp_ib_num;i++){
		wchar_t buf[10];
		swprintf_s(buf,10,L"Item %d",i);

		esp_ib[i].title_hwnd=CreateWindow(L"STATIC",buf,
				SS_SIMPLE | SS_LEFT | WS_CHILD | WS_VISIBLE,
				ESP_IB_XOFFS,ESP_IB_YOFFS+3+ESP_IB_YDIST*i,_ESP_IB_ISIZE,ESP_IB_YSIZE,
				esp_ib_hwnd,0,esp_hInst,NULL);

		esp_ib[i].val= 0.0;
		esp_ib[i].str = new char[ESP_IB_STRMAX];
		strcpy_s(esp_ib[i].str,ESP_IB_STRMAX,"0");
		wchar_t _esp_ib_str[ESP_IB_STRMAX];
		char2wchar_t(esp_ib[i].str,_esp_ib_str,ESP_IB_STRMAX);

		esp_ib[i].box_hwnd=CreateWindowEx(WS_EX_CLIENTEDGE,L"EDIT",_esp_ib_str,
				ES_AUTOHSCROLL |WS_CHILD| WS_VISIBLE |WS_TABSTOP|WS_GROUP,
				2*ESP_IB_XOFFS+_ESP_IB_ISIZE,ESP_IB_YOFFS+ESP_IB_YDIST*i,_ESP_IB_ESIZE,ESP_IB_YSIZE,
				esp_ib_hwnd,NULL,esp_hInst,NULL);
	}

	UpdateWindow(esp_ib_hwnd);
	SetForegroundWindow(esp_ib_hwnd);
	SetFocus(esp_ib[0].box_hwnd);
}

//インプットボックスのサイズ変更
//ipart,epart=各サイズ，０：変更しない，－１：デフォルト値
void ESP_ResizeInputBox(int ipart,int epart)
{
	if(!esp_ib_hwnd) return;

	if (ipart==0) ipart=_ESP_IB_ISIZE;
	else if (ipart<0) ipart=ESP_IB_ISIZE;

	if (epart==0) epart=_ESP_IB_ESIZE;
	else if (epart<0) epart=ESP_IB_ESIZE;

	_ESP_IB_ISIZE=ipart;
	_ESP_IB_ESIZE=epart;

	for(int i=0;i<esp_ib_num;i++){
		SetWindowPos(esp_ib[i].title_hwnd,0,0,0, ipart, ESP_IB_YSIZE, SWP_NOMOVE|esp_setpos_flags);
		SetWindowPos(esp_ib[i].box_hwnd,0,2*ESP_IB_XOFFS+_ESP_IB_ISIZE,ESP_IB_YOFFS+ESP_IB_YDIST*i, 
			epart, ESP_IB_YSIZE, esp_setpos_flags);
	}

	RECT r;
	r.left  = 0;
	r.top   = 0;
	r.right = (3*ESP_IB_XOFFS+_ESP_IB_ISIZE+_ESP_IB_ESIZE);
	r.bottom= ESP_IB_YDIST*esp_ib_num+ESP_IB_YOFFS/2;		//6.7
	AdjustWindowRect(&r, WS_OVERLAPPED | WS_CAPTION	| WS_SYSMENU | WS_VISIBLE | WS_SIZEBOX, FALSE);
	SetWindowPos(esp_ib_hwnd,0,0,0, r.right-r.left, r.bottom-r.top, SWP_NOMOVE|esp_setpos_flags);
}

//インプットボックスのウィンドウ関数
LRESULT CALLBACK ESP_IBfunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT rc;
	char s[ESP_IB_STRMAX];
	int i,y;
	POINT CurPos;
	HMENU esp_hpopmenu;

	switch(message){
	case WM_SIZING:
		GetWindowRect(hwnd,&rc);
		((LPRECT)lParam)->bottom= rc.bottom;
		((LPRECT)lParam)->top= rc.top;
		esp_ib_sizing= (int)wParam;
		break;
	case WM_SIZE:
		if(esp_ib_sizing%3==1){
			_ESP_IB_ISIZE=max(1,LOWORD(lParam) -3*ESP_IB_XOFFS -_ESP_IB_ESIZE);
		}else{
			_ESP_IB_ESIZE=max(1,LOWORD(lParam) -3*ESP_IB_XOFFS -_ESP_IB_ISIZE);
		}
		for(i=0;i<esp_ib_num;i++){
			SetWindowPos(esp_ib[i].title_hwnd,0,0,0, _ESP_IB_ISIZE, ESP_IB_YSIZE, SWP_NOMOVE|esp_setpos_flags);
			SetWindowPos(esp_ib[i].box_hwnd,0,2*ESP_IB_XOFFS+_ESP_IB_ISIZE,ESP_IB_YOFFS+ESP_IB_YDIST*i, 
				_ESP_IB_ESIZE, ESP_IB_YSIZE, esp_setpos_flags);
		}
		esp_list_update();	//v8.0
		break;
	case WM_MOVING:
		esp_wm_moving(hwnd,lParam);
		break;
	case WM_LBUTTONDBLCLK:
		esp_RenameIB( HIWORD(lParam)/ESP_IB_YDIST );
		break;
	case WM_RBUTTONDOWN:
		y=HIWORD(lParam);
		esp_renameib = y/ESP_IB_YDIST;
		GetCursorPos(&CurPos);
		esp_hpopmenu=CreatePopupMenu();
		esp_AppendMenu(esp_hpopmenu,0,MFS_ENABLED,ID_RENAMEIB,"Rename");
		TrackPopupMenu(esp_hpopmenu,TPM_LEFTALIGN|TPM_RIGHTBUTTON,CurPos.x,CurPos.y,0,hwnd,NULL);
		DestroyMenu(esp_hpopmenu);
		break;
	case WM_NCRBUTTONDOWN:
		GetCursorPos(&CurPos);
		esp_hpopmenu=CreatePopupMenu();
		esp_AppendMenu(esp_hpopmenu,0,MFS_ENABLED,ID_DESTROYIB,"Destroy");
		TrackPopupMenu(esp_hpopmenu,TPM_LEFTALIGN|TPM_RIGHTBUTTON,CurPos.x,CurPos.y,0,hwnd,NULL);
		DestroyMenu(esp_hpopmenu);
		break;
	case WM_ACTIVATE:
		if(esp_ibhwndfocus==0) esp_ibhwndfocus= esp_ib[0].box_hwnd;
		SetFocus(esp_ibhwndfocus);
		esp_getwindowtext(esp_ib[0].box_hwnd,s,sizeof(s));
		PostMessage(esp_ib[0].box_hwnd,EM_SETSEL,0,strlen(s));
		break;
	case WM_COMMAND:
		if(lParam==0 && wParam==1){
			lParam= (LPARAM)esp_ibhwndfocus;
			goto ib_update;
		}
		switch(HIWORD(wParam)){
		case EN_KILLFOCUS:
		ib_update:
			for(i=0; i<esp_ib_num; i++){
				if(esp_ib[i].box_hwnd==(HWND)lParam) break;
			}
			if(i==esp_ib_num) break;
			esp_getwindowtext(esp_ib[i].box_hwnd,s,sizeof(s));
			strcpy_s(esp_ib[i].str,ESP_IB_STRMAX,s);
			esp_ib[i].val= atof(s);	//v8.0
			break;
		case EN_SETFOCUS:
			esp_ibhwndfocus= (HWND)lParam;
			break;
		}
		switch(LOWORD(wParam)){
		case ID_RENAMEIB:
			esp_RenameIB(esp_renameib);
			break;
		case ID_DESTROYIB:
			esp_CloseInputBox();
			break;
		}
		break;
	case WM_CLOSE:
		esp_CloseInputBox();
	case WM_DESTROY:
		break;
	default:
		return DefWindowProc(hwnd,message,wParam,lParam);
	}
	return 0;
}

int ESP_GetInputBoxI(int i)
{
	if(esp_ib_check(i)) return 0;
	return atoi(esp_ib[i].str);
}

//v8.0
double ESP_GetInputBoxD(int i)
{
	if(esp_ib_check(i)) return 0.0;
	return esp_ib[i].val;
}

// 7.0
void ESP_GetInputBoxS(int i,char *buf, int bufsize)
{
	if(esp_ib_check(i)){
		buf[0]=0;
		return;
	}
	strcpy_s(buf,bufsize,esp_ib[i].str);
}

char ESP_GetInputBoxC(int i)
{
	if(esp_ib_check(i)) return 0;
	return esp_ib[i].str[0];
}

void ESP_SetInputBoxI(int i,int n)
{
	if(esp_ib_check(i)) return;
	_itoa_s(n,esp_ib[i].str,ESP_IB_STRMAX,10);
	esp_setwindowtext(esp_ib[i].box_hwnd,esp_ib[i].str);
}

//digits:有効桁数 v8.0
void ESP_SetInputBoxD(int i, double d, int digits=10)
{
	if(esp_ib_check(i)) return;
	esp_ib[i].val= d;	//v8.0
	_gcvt_s(esp_ib[i].str,ESP_IB_STRMAX,d,digits);	//v7.9
	esp_setwindowtext(esp_ib[i].box_hwnd,esp_ib[i].str);
}

void ESP_SetInputBoxS(int i, const char *s)
{
	if(esp_ib_check(i)) return;
	if(strlen(s)>ESP_IB_STRMAX-1){
		strncpy_s(esp_ib[i].str,ESP_IB_STRMAX,s,ESP_IB_STRMAX-1);
	}else{
		strcpy_s(esp_ib[i].str,ESP_IB_STRMAX,s);
	}
	esp_setwindowtext(esp_ib[i].box_hwnd,esp_ib[i].str);
}

void ESP_SetInputBoxC(int i,char c)
{
	if(esp_ib_check(i)) return;
	esp_ib[i].str[0]=c;
	esp_ib[i].str[1]=0;
	esp_setwindowtext(esp_ib[i].box_hwnd,esp_ib[i].str);
}

void ESP_SelectInputBox(int i)
{
	char str[ESP_IB_STRMAX];
	if(esp_ib_check(i)) return;
	ESP_SetForeground(ESPINPUTBOX);
	SetFocus(esp_ib[i].box_hwnd);
	esp_getwindowtext(esp_ib[i].box_hwnd,str,ESP_IB_STRMAX);
	PostMessage(esp_ib[i].box_hwnd,EM_SETSEL,0,strlen(str));
}

//-----ボタンボックス関連-----
#define ESP_BB_XOFFS 4
#define ESP_BB_YOFFS 4
#define ESP_BB_XSIZE 98
#define ESP_BB_YSIZE 26
int _ESP_BB_XSIZE=ESP_BB_XSIZE;
int _ESP_BB_YSIZE=ESP_BB_YSIZE;
#define ESP_BB_XDIST (_ESP_BB_XSIZE+ESP_BB_XOFFS)
#define ESP_BB_YDIST (_ESP_BB_YSIZE+ESP_BB_YOFFS)

//v8.0
#ifndef ESP_LIBRARY_MODE
#define ESP_CloseButtonBox() (esp_CloseButtonBox())
#else
#define ESP_CloseButtonBox() (esp_RequestCloseButtonBox())
#endif
int esp_CloseButtonBox(void)
{
	if(!esp_bb_hwnd) return 1;

	if(!DestroyWindow(esp_bb_hwnd)){
		MessageBox(esp_mw_hwnd,L"DestroyWindow[BB] error",L"ESPLIB error!",MB_OK|MB_ICONERROR);
	}
	esp_bb_hwnd=0;
	return 0;
}

void ESP_SetButtonBoxTitle(int i,const char *title)
{
	if(!esp_bb_hwnd) return;
	if(i<0 || i>esp_bb_num-1) return;
	esp_setwindowtext(esp_btn_hwnd[i],title);
}

//ボタンボックスの項目名変更 v8.0
void esp_RenameBB(int i)
{
	char buf[2*ESP_BB_STRMAX];
	char buf2[2*ESP_BB_STRMAX];

	esp_getwindowtext(esp_btn_hwnd[i],buf2,sizeof(buf2));
	esp_DefaultTextWindow();
	ESP_Printf("%d '%s' ->",i,buf2);
	ESP_Input(buf);
	if(buf[0]) ESP_SetButtonBoxTitle(i,buf);
}

#ifndef ESP_LIBRARY_MODE
	#define ESP_OpenButtonBox(x0,y0,nx,ny) (esp_OpenButtonBox((x0),(y0),(nx),(ny)))
#else
	#define ESP_OpenButtonBox(x0,y0,nx,ny) (esp_RequestOpenButtonBox((x0),(y0),(nx),(ny)))
#endif

//横数，縦数を指定してボタンボックスを開く  ver.6.0
void esp_OpenButtonBox(int x0,int y0,int nx, int ny)
{
	wchar_t buf[ESP_BUFMAX];
	
	if(esp_bb_hwnd) return;
	if(nx<=0 || ny<=0 || (nx*ny)>ESP_BB_MAX) return;

	esp_bb_num=nx*ny;
	esp_bb_nx=nx;
	esp_bb_ny=ny;

	RECT r;
	r.left  = 0;
	r.top   = 0;
	r.right = ESP_BB_XDIST*nx+ESP_BB_XOFFS;
	r.bottom= ESP_BB_YDIST*ny+ESP_BB_YOFFS;
	AdjustWindowRect(&r, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_SIZEBOX, FALSE);

	RECT rcd;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rcd,0);	//デスクトップ領域取得

	//HINSTANCE esp_hInst0 = NULL;
	esp_bb_hwnd=CreateWindow(
		esp_bb_classname,L"ButtonBox",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_SIZEBOX,
		x0+rcd.left, y0+rcd.top, r.right-r.left, r.bottom-r.top,
		esp_mw_hwnd,NULL,esp_hInst,NULL
	);

	for(int j=0;j<ny;j++){
	for(int i=0;i<nx;i++){
		long long k= i+j*nx;
		swprintf_s(buf,ESP_BUFMAX,L"%I64d",k);	//ver.8.1
		esp_btn_hwnd[k]=CreateWindow(L"BUTTON",buf,
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_MULTILINE,
				ESP_BB_XOFFS+ESP_BB_XDIST*i,ESP_BB_YOFFS+ESP_BB_YDIST*j,_ESP_BB_XSIZE,_ESP_BB_YSIZE,
				esp_bb_hwnd,(HMENU)(ID_BB_BASE+k),esp_hInst,NULL);	//ver.7.2
		//memo: ver.7.2 BS_NOTIFYはBN_SETFOCUSを送るだけなので不要

		//ボタンカウントの初期化
		esp_bb_count[k]=0;
	}
	}

	UpdateWindow(esp_bb_hwnd);
	SetForegroundWindow(esp_bb_hwnd);
}

//---ボタンボックスのサイズ（クライアント領域）を変更する---ver.6.0
// wx,wy=正の数：各サイズ　０：変更しない	－１：デフォルト値
void ESP_ResizeButtonBox(int wx,int wy)
{
	if(!esp_bb_hwnd) return;

	RECT r;

	GetClientRect(esp_bb_hwnd,&r);
	if(wx==0)wx=r.right;
	else if(wx<0){
		_ESP_BB_XSIZE=ESP_BB_XSIZE;
		wx=ESP_BB_XDIST*esp_bb_nx+ESP_BB_XOFFS;
	}
	
	if(wy==0)wy=r.bottom;
	else if(wy<0){
		_ESP_BB_YSIZE=ESP_BB_YSIZE;
		wy=ESP_BB_YDIST*esp_bb_ny+ESP_BB_YOFFS;
	}

	r.left  = 0;
	r.top   = 0;
	r.right = wx;
	r.bottom= wy;
	AdjustWindowRect(&r, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_SIZEBOX, FALSE);
	SetWindowPos(esp_bb_hwnd,0,0,0, r.right-r.left, r.bottom-r.top,SWP_NOMOVE|esp_setpos_flags);
}

//ボタンボックスのウィンドウ関数
LRESULT CALLBACK ESP_BBfunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i,j,k,x,y;

	switch(message){
	case WM_COMMAND:
		switch(HIWORD(wParam)){
			case BN_CLICKED:
				SetFocus(esp_bb_hwnd);	//ver.7.2 これがないとキーボード0-9入力ができない
				esp_bb_count[LOWORD(wParam)-ID_BB_BASE]++;
				break;
		}
		switch(LOWORD(wParam)){
			case ID_RENAMEBB:
				esp_RenameBB(esp_renamebb);
				break;
			case ID_DESTROYBB:
				esp_CloseButtonBox();
				break;
		}
		break;
	case WM_SIZE:
		//x,y are client size
		x=max(1,LOWORD(lParam)-ESP_BB_XOFFS*(esp_bb_nx+1));
		y=max(1,HIWORD(lParam)-ESP_BB_YOFFS*(esp_bb_ny+1));
		_ESP_BB_XSIZE=x/esp_bb_nx;
		_ESP_BB_YSIZE=y/esp_bb_ny;
		for(j=0;j<esp_bb_ny;j++){
		for(i=0;i<esp_bb_nx;i++){
			k=i+j*esp_bb_nx;
			SetWindowPos(esp_btn_hwnd[k],0,
				ESP_BB_XOFFS+ESP_BB_XDIST*i,ESP_BB_YOFFS+ESP_BB_YDIST*j,
				_ESP_BB_XSIZE,_ESP_BB_YSIZE,esp_setpos_flags);
		}
		}
		esp_list_update();
		break;
	case WM_MOVING:
		esp_wm_moving(hwnd,lParam);
		break;
	case WM_LBUTTONDBLCLK:
		x=LOWORD(lParam);
		y=HIWORD(lParam);
		i = Limit(0,x/ESP_BB_XDIST,esp_bb_nx-1);
		j = Limit(0,y/ESP_BB_YDIST,esp_bb_ny-1);
		esp_RenameBB(i+esp_bb_nx*j);
		break;
	case WM_NCRBUTTONDOWN:
		{
		POINT CurPos;
		GetCursorPos(&CurPos);
		HMENU menu1=CreatePopupMenu();
		esp_AppendMenu(menu1,0,MFS_ENABLED,ID_DESTROYBB,"&Destroy\tCtrl+Q");
		TrackPopupMenu(menu1,TPM_LEFTALIGN|TPM_RIGHTBUTTON,CurPos.x,CurPos.y,0,hwnd,NULL);
		DestroyMenu(menu1);
		}
		break;
	case WM_RBUTTONDOWN:
		{
		HMENU menu1;
		POINT CurPos;
		x=LOWORD(lParam);
		y=HIWORD(lParam);
		i = Limit(0,x/ESP_BB_XDIST,esp_bb_nx-1);
		j = Limit(0,y/ESP_BB_YDIST,esp_bb_ny-1);
		esp_renamebb = i+esp_bb_nx*j;
		GetCursorPos(&CurPos);
		menu1=CreatePopupMenu();
		esp_AppendMenu(menu1,0,MFS_ENABLED,ID_RENAMEBB,"Rename");
		TrackPopupMenu(menu1,TPM_LEFTALIGN|TPM_RIGHTBUTTON,CurPos.x,CurPos.y,0,hwnd,NULL);
		DestroyMenu(menu1);
		}
		break;
	case WM_KEYDOWN:
		if(GetKeyState(VK_CONTROL)<0){
			if(wParam=='Q'){PostMessage(esp_bb_hwnd,WM_CLOSE,0,0);break;}	//Ctrl+Q
		}else{
			if(wParam=='X' || wParam==VK_ESCAPE){PostMessage(esp_mw_hwnd,WM_KEYDOWN,wParam,0);break;}	//X or ESC
			if(wParam=='S'){PostMessage(esp_mw_hwnd,WM_KEYDOWN,wParam,0);break;}						//S
			if(wParam=='C'){PostMessage(esp_mw_hwnd,WM_KEYDOWN,wParam,0);break;}						//C		
			//通常の0-9
			if(wParam>='0' && wParam<='9'){					//ver.7.2
				esp_bb_count[wParam-'0']++; break;
			}
			//テンキーの0-9
			if(wParam>=VK_NUMPAD0 && wParam<=VK_NUMPAD9){	//ver.7.2
				esp_bb_count[wParam-VK_NUMPAD0]++; break;
			}
		}
		break;
	case WM_CLOSE:
		esp_CloseButtonBox();
		break;
	case WM_DESTROY:
		break;
	default:
		return DefWindowProc(hwnd,message,wParam,lParam);
	}
	return 0;
}

//ボタンの押された回数を返す
int ESP_GetButtonBox(int i)
{
	int n=0;
	if(esp_bb_hwnd && i>=0 && i<esp_bb_num){
		n=esp_bb_count[i];
		esp_bb_count[i]=0;
	}
	return n;
}

//ボタンの押された回数を初期化する
void ESP_ClearButtonBox(void)
{
	if(!esp_bb_hwnd) return;
	for(int i=0;i<esp_bb_num;i++) esp_bb_count[i]=0;
}

//ボタンの押された回数を 1 にする
void ESP_SetButtonBox(int i)
{
	if(esp_bb_hwnd && i>=0 && i<esp_bb_num){
		esp_bb_count[i]=1;
	}
}

//テキストウィンドウの文字色，背景色の指定
//過去の変更履歴も記憶 6.3
//第１引数=-1時は変更しない 8.1
//第２引数の省略時は変更しない 8.1
void ESP_SetColor(int tc, int bc=-1)
{
	if(!esp_tw[esp_twi].show) return;

	for(int i=(ESP_TWCOLOR_HISTORY-1);i>0;i--){
		esp_tw[esp_twi].tcolor_prev[i]= esp_tw[esp_twi].tcolor_prev[i-1];
		esp_tw[esp_twi].bcolor_prev[i]= esp_tw[esp_twi].bcolor_prev[i-1];
	}
	esp_tw[esp_twi].tcolor_prev[0]= esp_tw[esp_twi].tcolor;
	esp_tw[esp_twi].bcolor_prev[0]= esp_tw[esp_twi].bcolor;

	int r,g,b;

	if(tc<0){
		;
	}else{
		esp_tw[esp_twi].tcolor= tc;
		C2RGB(tc, &r, &g, &b);
		SetTextColor(esp_tw[esp_twi].memdc, RGB(r,g,b));
	}

	if(bc<0){
		;
	}else{
		esp_tw[esp_twi].bcolor= bc;
		C2RGB(bc, &r, &g, &b);
		SetBkColor(esp_tw[esp_twi].memdc, RGB(r,g,b));
	}
}

//テキストウィンドウの文字色，背景色の復元
void ESP_RestoreColor(void)
{
	int r,g,b,tc,bc;

	if(!esp_tw[esp_twi].show) return;

	tc=esp_tw[esp_twi].tcolor=esp_tw[esp_twi].tcolor_prev[0];
	bc=esp_tw[esp_twi].bcolor=esp_tw[esp_twi].bcolor_prev[0];

	for(int i=0;i<(ESP_TWCOLOR_HISTORY-1);i++){
		esp_tw[esp_twi].tcolor_prev[i]=esp_tw[esp_twi].tcolor_prev[i+1];
		esp_tw[esp_twi].bcolor_prev[i]=esp_tw[esp_twi].bcolor_prev[i+1];
	}

	C2RGB(tc,&r,&g,&b);
	SetTextColor(esp_tw[esp_twi].memdc,RGB(r,g,b));
	C2RGB(bc,&r,&g,&b);
	SetBkColor(esp_tw[esp_twi].memdc,RGB(r,g,b));
}


//---ログ処理関数---

#ifndef ESP_LOGEXT
	//ログファイル拡張子のデフォルト v8.3
	#define ESP_LOGEXT	".log"
#endif

//ログ記録の開始/再開 v7.6
int ESP_StartLog(int i)
{
	char buf[MAX_PATH];

	if(esp_tw_check(i)) return 3;

	switch(esp_tw[i].logstatus){
		case 0:			// New
			int r;
			SYSTEMTIME st;
			GetLocalTime(&st);
			sprintf_s(buf,sizeof(buf),"%sESPLIB%d%d-%d%02d%02d-%02d%02d%02d" ESP_LOGEXT,esp_logbase,esp_id,i,
				st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
			r=fopen_s(&esp_tw[i].logfile, buf, "w+t");
			if(r){
				MessageBox(HWND_DESKTOP,L"Can't create log file!",L"Error",MB_OK);
				return 2;
			};
			esp_tw[i].logstatus=1;
			break;
		case 1:			// Logging
			return 1;	
		case 2:			// Resume
			esp_tw[i].logstatus=1;
			break;
	}
	return 0;
}

//全TWについてログ記録の開始/再開
void ESP_StartAllLog(void)
{
	for(int i=0;i<ESP_TW_MAX;i++){
		if(esp_tw[i].show) ESP_StartLog(i);
	}
}

//ログファイルの手動フラッシュ ver.8.5
int ESP_FlushLog(int i)
{
	if(esp_tw_check(i)) return 2;
	if(!esp_tw[i].logstatus) return 1;
	fflush(esp_tw[i].logfile);
	return 0;
}

//ログファイルの手動フラッシュ（全TW） ver.8.5
void ESP_FlushAllLog(void)
{
	for(int i=0;i<ESP_TW_MAX;i++){
		if(esp_tw[i].show && esp_tw[i].logstatus) ESP_FlushLog(i);
	}
}

//ログ記録の終了（ファイルを閉じる）
int ESP_EndLog(int i)
{
	if(esp_tw_check(i)) return 2;
	if(!esp_tw[i].logstatus) return 1;
	fclose(esp_tw[i].logfile);
	esp_tw[i].logstatus=0;
	return 0;
}

//全TWについてログ記録の終了（ファイルを閉じる）
void ESP_EndAllLog(void)
{
	for(int i=0;i<ESP_TW_MAX;i++){
		if(esp_tw[i].show && esp_tw[i].logstatus) ESP_EndLog(i);
	}
}

//ログ記録の一時休止（ファイルは閉じない）
int ESP_StopLog(int i)
{
	if(esp_tw_check(i)) return 2;
	if(!esp_tw[i].logstatus) return 1;
	if(esp_tw[i].logstatus==1) esp_tw[i].logstatus=2;
	return 0;
}

//全TWについてログ記録の一時休止（ファイルは閉じない）
void ESP_StopAllLog(void)
{
	for(int i=0;i<ESP_TW_MAX;i++){
		if(esp_tw[i].show) ESP_StopLog(i);
	}
}

//ログファイル内容のコピー v7.6
int ESP_CopyLog(int i)
{
	int rtn=0;
	int p=0;
	unsigned char *m =NULL;

	if(esp_tw_check(i)) return 4;
	if(!OpenClipboard(NULL)) return 1;
	if(!esp_tw[i].logstatus) return 2;
	
	EmptyClipboard();

	//内容を書き出す
	fflush(esp_tw[i].logfile);
	int size=ftell(esp_tw[i].logfile);

	rewind(esp_tw[i].logfile);
	p=0;
	
	HGLOBAL hm=GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE,size+1);
	if(!hm){
		ESP_Pause("No enough memory (copy log)");
		rtn=3;
		goto fin002;
	}
	m= (unsigned char *)GlobalLock(hm);

	for(int k=0;k<size;k++){
		int c=fgetc(esp_tw[i].logfile);
		if(c==0x0A){
			m[p++]=0x0D;
			m[p++]=0x0A;
			k++;
		}else{
			m[p++]=c;
		}
	}
	m[size]=0;
	
	GlobalUnlock(hm);
	SetClipboardData(CF_TEXT,hm);
fin002:
	CloseClipboard();
	fseek(esp_tw[i].logfile,0,SEEK_END);
	return rtn;
}

//共通関数（IW:ウィンドウ番号iのチェック）
//戻り値：0正常(存在する), 1範囲外, 2存在しない
__inline int esp_iw_check(int i)
{
	if((unsigned int)i>=ESP_IW_MAX) return 1;
	if(!esp_iw[i].show) return 2;
	return 0;
}

//イメージウィンドウの消滅 v8.0
#ifndef ESP_LIBRARY_MODE
#define ESP_DestroyImage(i) (esp_DestroyImage((i)))
#else
#define ESP_DestroyImage(i) (esp_RequestDestroyImage((i)))
#endif
int esp_DestroyImage(int i)
{
	if(esp_iw_check(i)) return 1;

	esp_iw[i].show=0;

	SelectObject(esp_iw[i].memdc,esp_iw[i].hbitmapold);
	DeleteObject(esp_iw[i].hbitmap);
	DeleteDC(esp_iw[i].memdc);

	ReleaseDC(esp_iw[i].hwnd,esp_iw[i].hdc);
	delete[] esp_iw[i].title;

	if(!DestroyWindow(esp_iw[i].hwnd))
		MessageBox(esp_mw_hwnd,L"DestroyWindow[IW] Error",L"ESPLIB Error!",MB_OK|MB_ICONERROR);
	return 0;
}

//ウィンドウの最小サイズ，最大サイズを取得（フレームフラグにより変化）
void esp_WindowSizeMinMax(int *xmin, int *ymin, int *xmax, int *ymax, int flag)
{
	if(flag==1){
		*xmin = -GetSystemMetrics(SM_CXFRAME)*2
				+GetSystemMetrics(SM_CXMIN);
		*ymin = -GetSystemMetrics(SM_CXFRAME)*2
				-GetSystemMetrics(SM_CYCAPTION)
				+GetSystemMetrics(SM_CYMIN);
		*xmax = GetSystemMetrics(SM_CXSCREEN);
		*ymax = GetSystemMetrics(SM_CYSCREEN)-GetSystemMetrics(SM_CYCAPTION);
	}

	if(flag==0){
		*xmin = 1;
		*ymin = 1;
		*xmax = 2*GetSystemMetrics(SM_CXSCREEN);
		*ymax = 2*GetSystemMetrics(SM_CYSCREEN);
	}
}

void esp_set_title(char *buf,int buf_size,const char *title,int zm,int bit)
{
	if(bit==8){
		sprintf_s(buf,buf_size,"%s(%d%%)[8bit]",title,zm);
	}else{
		sprintf_s(buf,buf_size,"%s(%d%%)",title,zm);
	}
}

#define esp_invalid(i) InvalidateRect(esp_iw[(i)].hwnd,NULL,FALSE)

void esp_update_title(int i)
{
	char buf[2*ESP_BUFMAX];

	esp_set_title(buf,ESP_BUFMAX,esp_iw[i].title,esp_iw[i].zoom,esp_iw[i].bit);
	
	if(GetStretchBltMode(esp_iw[i].memdc)==HALFTONE) strcat_s(buf,sizeof(buf),"*");

	esp_setwindowtext(esp_iw[i].hwnd,buf);
}


int ESP_Update_(int i)
{
	if(esp_iw_check(i)) return 1;

	if(esp_iw[i].zoom!=100){
		StretchBlt(esp_iw[i].hdc,0,0,esp_iw[i].wwx,esp_iw[i].wwy,esp_iw[i].memdc,0,0,esp_iw[i].wx,esp_iw[i].wy,SRCCOPY);
	}else{
		BitBlt(esp_iw[i].hdc,0,0,esp_iw[i].wx,esp_iw[i].wy,esp_iw[i].memdc,0,0,SRCCOPY);
	}
	return 0;
}

void ESP_UpdateAll(void)
{
	for(int i=0;i<ESP_IW_MAX;i++){
		if(esp_iw[i].show){
			esp_invalid(i);
		}
	}
}

#define ESP_Update() (ESP_Update_(esp_i))

//イメージウィンドウ（８ビット）のパレット設定
int ESP_SetColorTable(int *rgb, int n=256)
{
	if(!esp_iw[esp_i].show) return 1;
	if(esp_iw[esp_i].bit!=8) return 2;

	SetDIBColorTable(esp_iw[esp_i].memdc,0,n,(RGBQUAD *)rgb);
	
	esp_invalid(esp_i);
	
	return 0;
}

//イメージウィンドウ（８ビット）のパレット取得
int ESP_GetColorTable(int *rgb)
{
	if(!esp_iw[esp_i].show) return 1;
	if(esp_iw[esp_i].bit!=8) return 2;

	GetDIBColorTable(esp_iw[esp_i].memdc,0,256,(RGBQUAD *)rgb);
	
	return 0;
}

int ESP_Select(int i)
{
	if(esp_iw_check(i)) return 1;
		
	for(int j=(ESP_IWSELECT_HISTORY-1);j>0;j--){
		esp_iw_select_prev[j]=esp_iw_select_prev[j-1];
	}
	esp_iw_select_prev[0]=esp_i;
	esp_i=i;

	return 0;
}

int ESP_UnSelect(void)
{
	int i=esp_iw_select_prev[0];

	if(esp_iw_check(i)) return 1;
		
	esp_i=i;

	for(i=0;i<(ESP_IWSELECT_HISTORY-1);i++){
		esp_iw_select_prev[i]=esp_iw_select_prev[i+1];
	}

	return 0;
}

// v8.4
// イメージウィンドウの作成 [32bit and 8bit]
// wx...106- wy...2- zoom...~100~
// flag=1:フレームあり（標準タイプ） 0:フレームなし，サイズ・ズームチェックなし
// return : 0...no error
int esp_CreateImageX(int i,const char *title,int x0,int y0,int wx,int wy,int zoom,int bit=32,int flag=1)
{
	if((unsigned int)i>=ESP_IW_MAX) return 4;
	if(esp_iw[i].show) return 1;

	if(bit!=8 && bit!=32) return 3;
	esp_iw[i].bit=bit;

	if(flag!=1 && flag!=0) return 3;
	esp_iw[i].flag=flag;

	wx=esp_iw[i].wx=max(1,wx);
	wy=esp_iw[i].wy=max(1,wy);

	int winxmin,winymin,winxmax,winymax;
	esp_WindowSizeMinMax(&winxmin,&winymin,&winxmax,&winymax,esp_iw[i].flag);

	//ウィンドウ最大サイズのチェック
	double dwx=max(1,min(wx*zoom/100.0,(double)winxmax));
	double dwy=max(1,min(wy*zoom/100.0,(double)winymax));
	double zwx=dwx*100.0/(double)wx;
	double zwy=dwy*100.0/(double)wy;
	int zm=(int)min(zwx,zwy);
	int wx2=wx*zm/100;
	int wy2=wy*zm/100;

	//ウィンドウ最小サイズのチェック
	if(wx2<winxmin || wy2<winymin){
		double zwx=winxmin*100.0/wx;
		double zwy=winymin*100.0/wy;
		zm=(int)max(ceil(zwx),ceil(zwy));	// debug ver.5.4
		wx2=wx*zm/100;
		wy2=wy*zm/100;
		if(wx2>winxmax || wy2>winymax){
			return 2;
		}
	}

	esp_iw[i].wwx=wx2;
	esp_iw[i].wwy=wy2;
	esp_iw[i].zoom=zm;
	
	RECT rcd;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rcd,0);	//デスクトップ領域取得

	//if(x0==-1) x0=CW_USEDEFAULT; else x0+=rcd.left;	// v7.6
	//if(y0==-1) y0=CW_USEDEFAULT; else y0+=rcd.top;	// v7.6
	x0+=rcd.left;	// v8.4
	y0+=rcd.top;	// v8.4
	
	RECT r;
	r.left=0;
	r.top=0;
	r.right=wx2;
	r.bottom=wy2;
	AdjustWindowRect(&r, esp_iw_wstyle[flag], FALSE);

	int titlelen= (int)(strlen(title)+1);
	esp_iw[i].title= new char[titlelen];
	strcpy_s(esp_iw[i].title, titlelen, title);
	char buf[ESP_BUFMAX];
	esp_set_title(buf,ESP_BUFMAX,title,zm,bit);
	wchar_t _buf[ESP_BUFMAX];
	char2wchar_t(buf,_buf,ESP_BUFMAX);

	esp_iw[i].hwnd=CreateWindow(
		esp_iw_classname, _buf, esp_iw_wstyle[flag]
		,x0, y0, r.right-r.left, r.bottom-r.top,
		esp_mw_hwnd,NULL,esp_hInst,NULL
	);

	UpdateWindow(esp_iw[i].hwnd);
	SetForegroundWindow(esp_iw[i].hwnd);
	DragAcceptFiles(esp_iw[i].hwnd,TRUE);

	esp_iw[i].hdc=GetDC(esp_iw[i].hwnd);
		SetStretchBltMode(esp_iw[i].hdc,COLORONCOLOR);
		SetBrushOrgEx(esp_iw[i].hdc,0,0,NULL);
	esp_iw[i].memdc=CreateCompatibleDC(esp_iw[i].hdc);
		SetStretchBltMode(esp_iw[i].memdc,COLORONCOLOR);
		SetBrushOrgEx(esp_iw[i].memdc,0,0,NULL);

	BITMAPINFOHEADER *pbih=(BITMAPINFOHEADER *)new BYTE[sizeof(BITMAPINFOHEADER)+256*sizeof(RGBQUAD)];

	ZeroMemory(pbih,sizeof(BITMAPINFOHEADER));
	pbih->biSize=sizeof(BITMAPINFOHEADER);
	pbih->biBitCount=bit;
	pbih->biWidth=wx;
	pbih->biHeight=-wy;
	pbih->biPlanes=1;

	//デフォルトのパレット設定
	for(int j=0;j<256;j++){
		*((int *)(pbih+1)+j)=RGB2C(j,j,j);
	}

	esp_iw[i].hbitmap=CreateDIBSection(0,(BITMAPINFO *)pbih,DIB_RGB_COLORS,(void **)&ESP_VramPtr[i],0,0);
	if(!esp_iw[i].hbitmap) return 3;
	delete[] pbih;
	esp_iw[i].hbitmapold=(HBITMAP)SelectObject(esp_iw[i].memdc,esp_iw[i].hbitmap);

	ESP_VramPtr8[i]=(unsigned char *)ESP_VramPtr[i];
	ZeroMemory(ESP_VramPtr[i],wx*wy*(bit/8));

	esp_iw[i].show=1;
	esp_list_update();
	ESP_Select(i);
	return 0;
}


// クリップボードのビットマップのハンドルを得る 7.0
HBITMAP esp_GetBitmapFromCB(RGBQUAD *rgb, int *used)
{
	*used=0;

	if (IsClipboardFormatAvailable(CF_DIB)) {
		//CF_DIB
		if (!OpenClipboard(NULL)) return NULL;
		HANDLE hcb=GetClipboardData(CF_DIB);
		if(!hcb){
			CloseClipboard();
			return NULL;
		}
		BITMAPINFOHEADER *pbih=(BITMAPINFOHEADER *)GlobalLock(hcb);
		// BITMAP作成
		HDC hdc = GetDC(NULL);
		char *p=(char *)pbih;
		p+=sizeof(BITMAPINFOHEADER);
		if(pbih->biBitCount <=8){		//ver.5.8
			if(pbih->biClrUsed == 0){
				*used = 1<<pbih->biBitCount;
			}else{
				*used = pbih->biClrUsed;
			}
			CopyMemory(rgb,p, *used * sizeof(RGBQUAD));
			p += *used * sizeof(RGBQUAD);
			//ESP_Printf("used:%d\n",*used);
		}
		HBITMAP hbm=CreateDIBitmap(hdc,(BITMAPINFOHEADER *)pbih,CBM_INIT,p,(BITMAPINFO *)pbih,DIB_RGB_COLORS);
		ReleaseDC(NULL,hdc);
		GlobalUnlock(hcb);
		CloseClipboard();
		return hbm;
	}
	if (IsClipboardFormatAvailable(CF_BITMAP)) {
		//CF_BITMAP
		if (!OpenClipboard(NULL)) return NULL;
		HANDLE hcb;
		if ((hcb = GetClipboardData(CF_BITMAP)) == NULL) {
			CloseClipboard();
			return NULL;
		}
		HBITMAP	hcbbm=(HBITMAP)GlobalLock(hcb);
		// ビットマップのコピー
		HBITMAP hbm=(HBITMAP)CopyImage(hcbbm,IMAGE_BITMAP,0,0,LR_COPYRETURNORG);
		GlobalUnlock(hcb);
		CloseClipboard();
		return hbm;
	}
	return NULL;
}

// 7.0
void esp_DibDisp(HBITMAP hbm, int x0, int y0)
{
	HDC hdc=CreateCompatibleDC(esp_iw[esp_i].memdc);
	HBITMAP holdbm=(HBITMAP)SelectObject(hdc,hbm);

	BITMAP bm;
	GetObject(hbm,sizeof(BITMAP),&bm);
	int wx=bm.bmWidth;
	int wy=bm.bmHeight;
	BitBlt(esp_iw[esp_i].memdc,x0,y0,wx,wy,hdc,0,0,SRCCOPY);

	SelectObject(hdc,holdbm);
	DeleteObject(hbm);
	DeleteDC(hdc);
}

//BMP読み込み 7.0
int ESP_BmpLoad(const char *filename, int x0, int y0)
{
	if(esp_iw_check(esp_i)) return 3;

	FILE *fp;
	int r = fopen_s(&fp,filename,"rb");
	if(r) return 2;

	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	fread(&bfh,sizeof(bfh),1,fp);
	fread(&bih,sizeof(bih),1,fp);

	if(bih.biBitCount<=8){
		int used;
		if(bih.biClrUsed == 0){
			used = 1<< bih.biBitCount;
		}else{
			used = bih.biClrUsed;
		}
		RGBQUAD rgb[256];
		fread(rgb,used*sizeof(RGBQUAD),1,fp);
		ESP_SetColorTable((int *)rgb);
	}
	fclose(fp);

	wchar_t _filename[MAX_PATH];
	char2wchar_t(filename,_filename,MAX_PATH);
	HBITMAP hbm=(HBITMAP)LoadImage(0,_filename,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	if(!hbm) return 1;
	esp_DibDisp(hbm,x0,y0);

	return 0;
}

// 7.0
void ESP_GetWindow(void *buf,int x0,int y0,int wx,int wy)
{
	if((unsigned int)esp_i>=ESP_IW_MAX) return;
	if(!esp_iw[esp_i].show) return;

	unsigned int mx = esp_iw[esp_i].wx;
	unsigned int my = esp_iw[esp_i].wy;

	if(esp_iw[esp_i].bit==32){
		//32bit
		int *ip = (int *)buf;
		int x,y;
		for(int j=0;j<wy;j++){
		for(int i=0;i<wx;i++){
			x=x0+i;
			y=y0+j;
			if((unsigned int)x>=mx || (unsigned int)y>=my) *(ip+i+j*wx)=0;
			else *(ip+i+j*wx)=*ESPPTR;
		}
		}
	}else{
		//8bit
		unsigned char *ucp = (unsigned char *)buf;
		int x,y;
		for(int j=0;j<wy;j++){
		for(int i=0;i<wx;i++){
			x=x0+i;
			y=y0+j;
			if((unsigned int)x>=mx || (unsigned int)y>=my) *(ucp+i+j*wx)=0;
			else *(ucp+i+j*wx)=*ESPPTR8;
		}
		}
	}
}

// 7.0
void ESP_PutWindow(void *buf,int x0,int y0,int wx,int wy)
{
	if((unsigned int)esp_i>=ESP_IW_MAX) return;
	if(!esp_iw[esp_i].show) return;

	unsigned int mx=esp_iw[esp_i].wx;
	unsigned int my=esp_iw[esp_i].wy;

	if(esp_iw[esp_i].bit==32){
		//32bit
		int *ip=(int *)buf;
		int x,y;
		for(int j=0;j<wy;j++){
		for(int i=0;i<wx;i++){
			x=x0+i;
			y=y0+j;
			if((unsigned int)x>=mx || (unsigned int)y>=my);
			else *ESPPTR=*(ip+i+j*wx);
		}
		}
	}else{
		//8bit
		unsigned char *ucp=(unsigned char *)buf;
		int x,y;
		for(int j=0;j<wy;j++){
		for(int i=0;i<wx;i++){
			x=x0+i;
			y=y0+j;
			if((unsigned int)x>=mx || (unsigned int)y>=my);
			else *ESPPTR8=*(ucp+i+j*wx);
		}
		}
	}
}

// ファイル名fileの拡張子をextに整えてbufに格納する(char)
void esp_filename_ext(const char *file, const char *ext, char *buf, int bufsize)
{
	//ファイル名のコピー
	strcpy_s(buf,bufsize,file);
	//拡張子の設定
	int len=(int)strlen(buf);
	if (len>=4) {
		//最後の４文字が'.bmp'かどうか
		char e[5];
		strcpy_s(e,5,buf+len-4);
		_strlwr_s(e,5);
		if (!strstr(e,ext)) strcat_s(buf,bufsize,ext);
	}else{
		strcat_s(buf,bufsize,ext);
	}
}

// ファイル名file(size:MAX_PATH)の拡張子をextに整える(wchar_t) v8.0
void esp_wfilename_ext(wchar_t *file, wchar_t *ext)
{
	int len= (int)wcslen(file);
	if (len>=4) {
		//最後の４文字がextかどうか
		wchar_t e[5];
		wcscpy_s(e,sizeof(e),file+len-4);	//最後４文字を抽出
		_wcslwr_s(e,sizeof(e));				//小文字変換
		if (!wcsstr(e,ext)) wcscat_s(file,MAX_PATH,ext);	//extと一致しなければ追加
	}else{
		wcscat_s(file,MAX_PATH,ext);
	}
}

//-----時間計測関連-----
// ver.6.1eよりQueryPerformanceCounter()を使う

//時間取得(単位：ミリ秒，double型戻り値)v.7.5
double ESP_GetClockms(void)
{
	double t;
	long double esp_ld_fpms;	//esp_ld_fpmsをローカル変数にした 20210113 kinya iwamoto
	QueryPerformanceFrequency(&esp_li_freq);
	esp_ld_fpms = (long double)(1000.0 / esp_li_freq.QuadPart);

	if(esp_times){
		QueryPerformanceCounter(&esp_li_time1);
		t = (esp_li_time1.QuadPart - esp_li_time0.QuadPart)*esp_ld_fpms;
	}else{
		t=esp_timems;
	}
	return t;
}

//時間取得(単位：ミリ秒，int型戻り値) v7.7
#define ESP_GetClock() ((int)floor(ESP_GetClockms()+0.5))

void ESP_ResetClock(void)
{
	esp_times=0;
	
	//計測結果の初期化
	esp_timems=0;
}

void ESP_StartClock(void)
{
	if(!esp_times){
		esp_times=1;
		QueryPerformanceCounter(&esp_li_time0);
	}
}

//7.5
void ESP_StopClock(void)
{
	if(esp_times){
		esp_timems = ESP_GetClockms();
		esp_times=0;
	}
}

//7.5
int ESP_DispClock(void)
{
	wchar_t _buf[32];
	int t = ESP_GetClock();
	swprintf_s(_buf,32,L"TIME : %.3f sec",t/1000.0);
	MessageBox(esp_mw_hwnd,_buf,L"ESP_DispClock",MB_OK);
	return t;
}

// --- GDI+を利用する関数 ---

#ifndef ESP_LIBRARY_MODE
	#define ESP_ImageLoad(filename,x0,y0,zoom) (esp_ImageLoad((filename),(x0),(y0),(zoom)))
#else
	#define ESP_ImageLoad(filename,x0,y0,zoom) (esp_RequestImageLoad((esp_i),(filename),(x0),(y0),(zoom)))
#endif

//BMP,ICON,GIF,JPEG,PNG,TIFF,WMF,EMFに対応した画像読み込み v7.7
//8bitウィンドウの場合はパレットも読み込む
//zoomが負の時：画像の横幅を-zoomに拡大縮小して描画
int esp_ImageLoad(const char *filename, int x0, int y0, int zoom)
{
	if(esp_iw_check(esp_i)) return 2;

	wchar_t file[MAX_PATH];
	char2wchar_t(filename,file,MAX_PATH);

	Image *pImg = Image::FromFile(file);

	int wx = pImg->GetWidth();
	int wy = pImg->GetHeight();
		
	if(!wx || !wy){
		delete pImg;
		return 1;
	}

	//get palette
	if(esp_iw[esp_i].bit==8){
		int sz = pImg->GetPaletteSize();
		ColorPalette *cp = (ColorPalette *)new BYTE[sz];
		pImg->GetPalette(cp,sz);
		int n=(sz-8)/4;
		int rgb[256];
		for(int i=0;i<n;i++)rgb[i]=(cp->Entries[i])&0xffffff;
		ESP_SetColorTable(rgb,n);
		delete[] cp;
	}

	Graphics *pGrp=Graphics::FromHDC(esp_iw[esp_i].memdc);

	if(zoom>=0){
		pGrp->DrawImage(pImg,x0,y0,wx*zoom/100,wy*zoom/100);
	}else{
		pGrp->DrawImage(pImg,x0,y0,-zoom,-zoom*wy/wx);
	}

	delete pGrp;
	delete pImg;
	return 0;
}

// v7.7
int ESP_GetImageInfo(const char *filename, int *wx, int *wy, int *bit)
{
	wchar_t file[MAX_PATH];
	char2wchar_t(filename,file,MAX_PATH);

	Image *pImg = Image::FromFile(file);
	if(!pImg) return 1;

	*wx = pImg->GetWidth();
	*wy = pImg->GetHeight();
	if(*wx==0 || *wy==0) return 1;

	switch(pImg->GetPixelFormat()){
		case PixelFormat1bppIndexed:
			*bit=1;
			break;
		case PixelFormat4bppIndexed:
			*bit=4;
			break;
		case PixelFormat8bppIndexed:
			*bit=8;
			break;
		case PixelFormat16bppARGB1555:
			*bit=16;
			break;
		case PixelFormat16bppGrayScale:
			*bit=16;
			break;
		case PixelFormat16bppRGB555:
			*bit=16;
			break;
		case PixelFormat16bppRGB565:
			*bit=16;
			break;
		case PixelFormat24bppRGB:
			*bit=24;
			break;
		case PixelFormat32bppARGB:
			*bit=32;
			break;
		case PixelFormat32bppPARGB:
			*bit=32;
			break;
		case PixelFormat32bppRGB:
			*bit=32;
			break;
		case PixelFormat48bppRGB:
			*bit=48;
			break;
		case PixelFormat64bppARGB:
			*bit=64;
			break;
		case PixelFormat64bppPARGB:
			*bit=64;
			break;
	}

	delete pImg;
	return 0;
}

// 7.0
void esp_GetEncid(const wchar_t *format, CLSID *id)
{
	UINT n=0,size=0;

	ImageCodecInfo *pImageCodecInfo=NULL;
	GetImageEncodersSize(&n, &size);

	pImageCodecInfo=(ImageCodecInfo *) new BYTE[size];
	GetImageEncoders(n,size,pImageCodecInfo);

	for(UINT i=0;i<n;i++){
		if(!wcscmp(pImageCodecInfo[i].MimeType,format)){
			*id=pImageCodecInfo[i].Clsid;
			break;
		}    
	}
	delete[] pImageCodecInfo;
}

//JPEG保存時の画質 0-100[%]
int esp_jpegquality=100;

void ESP_JpegQuality(int quality)
{
	esp_jpegquality=Limit(0,quality,100);
}

#define ESP_BMP  0
#define ESP_JPEG 1
#define ESP_GIF  2
#define ESP_PNG  3
#define ESP_TIFF 4

//各種形式で保存 7.0 / ファイル名変換順番を入れ替え v8.2
//format : EPS_BMP, ESP_JPEG, ESP_GIF, ESP_PNG, ESP_TIFF
int ESP_ImageSave(int format, const char *filename, int x0, int y0, int wx, int wy)
{
	if(esp_iw_check(esp_i)) return 3;
	if(!wx || !wy) return 2;
	if(format<0 || format>4) return 4;

	Bitmap *bm;

	if(esp_iw[esp_i].bit==32){
		BYTE *p = new BYTE[wx*wy*4];
		ESP_GetWindow(p,x0,y0,wx,wy);
		Bitmap *bm1 = new Bitmap(wx,wy,4*wx,PixelFormat32bppRGB,p);
		bm = bm1->Clone(Rect(0,0,wx,wy),PixelFormat24bppRGB);
		delete[] p;
		delete bm1;
	}
	else if(esp_iw[esp_i].bit==8){
		BITMAPINFOHEADER *pbih;
		pbih = (BITMAPINFOHEADER *) new BYTE[sizeof(BITMAPINFOHEADER)+256*sizeof(RGBQUAD)];
		SecureZeroMemory(pbih,sizeof(BITMAPINFOHEADER));
		pbih->biSize=sizeof(BITMAPINFOHEADER);
		pbih->biBitCount=8;
		pbih->biWidth=wx;
		pbih->biHeight=-wy;
		pbih->biPlanes=1;
		pbih->biXPelsPerMeter=2834; //XPels/Meter (2834=72dpi)
		pbih->biYPelsPerMeter=2834; //YPels/Meter (2834=72dpi)
		ESP_GetColorTable((int *)(pbih+1));
		BYTE *p;
		HBITMAP hbm=CreateDIBSection(0,(BITMAPINFO *)pbih,DIB_RGB_COLORS,(void **)&p,0,0);
		ESP_GetWindow(p,x0,y0,wx,wy);
		bm=new Bitmap((BITMAPINFO *)pbih,p);
		delete[] pbih;
	}
	else{
		return 5;
	}

	CLSID encid;
	const wchar_t *fmt[5]= {L"image/bmp", L"image/jpeg", L"image/gif", L"image/png", L"image/tiff"};
	esp_GetEncid(fmt[format], &encid);

	const char *ext[5]={".bmp", ".jpg", ".gif", ".png", ".tif"};
	char file[MAX_PATH];
	esp_filename_ext(filename,ext[format],file,sizeof(file));

	wchar_t wfile[MAX_PATH];
	char2wchar_t(file,wfile,sizeof(wfile));

	Status s;
	if(format==ESP_JPEG){
		EncoderParameters encParam;
		encParam.Count = 1;
		encParam.Parameter[0].Guid = EncoderQuality;
		encParam.Parameter[0].Type = EncoderParameterValueTypeLong;
		encParam.Parameter[0].NumberOfValues = 1;
		ULONG quality = (ULONG)esp_jpegquality;
		encParam.Parameter[0].Value = &quality;
		s = bm->Save(wfile,&encid,&encParam);
	}else{
		s = bm->Save(wfile,&encid,0);
	}
	delete bm;
	if(s==Ok) return 0; else return 1;
}

void esp_reqf(void)
{
	switch(esp_req){
		case ESP_REQ_CREATEIMAGE:
			esp_req_ret= esp_CreateImageX(esp_req_i,esp_req_title,esp_req_x0,esp_req_y0,esp_req_wx,esp_req_wy,esp_req_zoom,esp_req_bit,esp_req_flag);
			esp_req_fin= 1;
			esp_req= 0;
			break;
		case ESP_REQ_UPDATE:
			ESP_Update_(esp_req_i);
			esp_req_fin= 1;
			esp_req= 0;
			break;
		case ESP_REQ_IMAGELOAD:
			ESP_Select(esp_req_i);
			esp_req_ret= esp_ImageLoad(esp_req_filename,esp_req_x0,esp_req_y0,100);
			ESP_UnSelect();
			esp_req_fin= 1;
			esp_req= 0;
			break;
		case ESP_REQ_DIBDISP:
			esp_DibDisp(esp_req_hbm,0,0);
			esp_req_fin= 1;
			esp_req= 0;
			break;
		case ESP_REQ_OPENTEXTWINDOW:
			esp_OpenTextWindow(esp_req_i,esp_req_x0,esp_req_y0,esp_req_wx,esp_req_wy);
			esp_req_fin= 1;
			esp_req= 0;
			break;
		case ESP_REQ_OPENINPUTBOX:
			if(esp_ib_hwnd)	esp_CloseInputBox();
			esp_OpenInputBox(esp_req_x0,esp_req_y0,esp_req_i);
			esp_req_fin= 1;
			esp_req= 0;
			break;
		case ESP_REQ_OPENBUTTONBOX:
			if(esp_bb_hwnd)	esp_CloseButtonBox();
			esp_OpenButtonBox(esp_req_x0,esp_req_y0,esp_req_wx,esp_req_wy);
			esp_req_fin= 1;
			esp_req= 0;
			break;
		case ESP_REQ_DESTROYIMAGE:
			esp_req_ret = esp_DestroyImage(esp_req_i);
			esp_req_fin = 1;
			esp_req = 0;
			break;
		case ESP_REQ_CLOSETEXTWINDOW:
			esp_req_ret = esp_CloseTextWindow(esp_req_i);
			esp_req_fin = 1;
			esp_req = 0;
			break;
		case ESP_REQ_CLOSEINPUTBOX:
			esp_req_ret = esp_CloseInputBox();
			esp_req_fin = 1;
			esp_req = 0;
			break;
		case ESP_REQ_CLOSEBUTTONBOX:
			esp_req_ret = esp_CloseButtonBox();
			esp_req_fin = 1;
			esp_req = 0;
			break;
	}
}

//スレッド
// _beginthreadex()呼び出しへ変更 v7.7 
unsigned __stdcall ESP_Loop(void *arglist)
{
	ESP_StartClock();	//v7.7
	ESP_Ready();
	esp_list_update();
	esp_hInst = GetModuleHandle(NULL);
	while(!ESP_EXIT){
		Sleep(1);	//ver.6.1~
		//esp_hInst = GetModuleHandle(NULL);
		CM();
		if(esp_req) esp_reqf();
		//esp_hInst = GetModuleHandle(NULL);
		if(ESP_START && !ESP_STARTING){
			DragAcceptFiles(esp_mw_hwnd,FALSE);
			ESP_STARTING=1;
			ESP_START=0;
			esp_STOP=0;
			ESP_Main();
			if(ESP_EXIT) break;
			ESP_STARTING=0;
			esp_STOP=0;
			DragAcceptFiles(esp_mw_hwnd,TRUE);
		}
	}
	ESP_Finish();
	ESP_EXIT=2;
	//各ウィンドウが残っていたらクローズ v7.7
	esp_CloseInputBox();
	esp_CloseButtonBox();
	for(int i=0;i<ESP_IW_MAX;i++) { esp_DestroyImage(i); }
	for(int i=0;i<ESP_TW_MAX;i++) { esp_CloseTextWindow(i); }
#ifndef _MFC_VER
	//スレッド終了処理 v7.7
	//CloseHandle(h_ESP_Loop);
	//h_ESP_Loop=NULL;
	::_endthreadex(0);
#else
	::AfxEndThread(0);
#endif // !_MFC_VER

	return 0;
}

//メインウィンドウ関連
LRESULT CALLBACK ESP_MWfunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	int b;
	int rtn,j;
	HDROP hDrop;
	char buf[2*MAX_PATH];
	HMENU esp_hpopmenu;
	POINT CurPos;
	int wx,wy,bit;
	int x1,y1;
	RECT rc;
	HBITMAP hbm;
	BITMAP bm;
	RGBQUAD rgb[256];
	int used;
	char title[ESP_BUFMAX];
	int c1;

	switch(message){
	case WM_SIZING:
		//サイズ変更を制限する
		GetWindowRect(hwnd,&rc);
		((LPRECT)lParam)->left  = rc.left;
		((LPRECT)lParam)->top   = rc.top;
		((LPRECT)lParam)->right = rc.right;
		((LPRECT)lParam)->bottom= rc.bottom;
		break;
	case WM_MOVING:
		esp_wm_moving(hwnd,lParam);
		break;
	case WM_NCRBUTTONDOWN:
	case WM_RBUTTONDOWN:
		if(esp_mousegetting) break;
		//ESP_Main()実行中または入力中ならメニューの一部をグレーにする
		b = (ESP_STARTING==1 || esp_tw_inputflag) ? MFS_GRAYED : MFS_ENABLED;
		GetCursorPos(&CurPos);
		esp_hpopmenu=CreatePopupMenu();
		esp_AppendMenu   (esp_hpopmenu, 0,b,ID_PASTETOMAIN,"Paste\tCtrl+V");
		esp_AppendMenuSEP(esp_hpopmenu, 1);
		esp_AppendMenu   (esp_hpopmenu, 2,b,ID_START,"Start");
		esp_AppendMenu   (esp_hpopmenu, 3,MFS_ENABLED,ID_STOP,"Stop");
		esp_AppendMenu   (esp_hpopmenu, 4,MFS_ENABLED,ID_EXIT,"E&xit");
		esp_AppendMenuSEP(esp_hpopmenu, 5);
		esp_AppendMenu   (esp_hpopmenu, 6,b,ID_IMAGEWINDOW,"Image Window");
		esp_AppendMenu   (esp_hpopmenu, 7,b,ID_TEXTWINDOW,"Text Window");
		esp_AppendMenu   (esp_hpopmenu, 8,b,ID_INPUTBOX,"Input Box");
		esp_AppendMenu   (esp_hpopmenu, 9,b,ID_BUTTONBOX,"Button Box");
		esp_AppendMenuSEP(esp_hpopmenu,10);
		esp_AppendMenu   (esp_hpopmenu,11,b,ID_INFO,"&Window Info.\tCtrl+W");
		TrackPopupMenu(esp_hpopmenu,TPM_LEFTALIGN|TPM_RIGHTBUTTON
			,CurPos.x,CurPos.y,0,hwnd,NULL);
		DestroyMenu(esp_hpopmenu);
		break;
	case WM_DROPFILES:
		hDrop=(HDROP)wParam; 
		c1=DragQueryFile(hDrop,-1,NULL,0);	//Count of dropped file
		j=0;
		for(int di=0; di<c1; di++){
			wchar_t _file[MAX_PATH];
			char file[MAX_PATH];
			wchar_t *_fname;
			char fname[MAX_PATH];
			wchar_t _path[MAX_PATH];

			DragQueryFile(hDrop,di,_file,MAX_PATH);
			GetFullPathName(_file,MAX_PATH,_path,&_fname);
			if(_fname==0) continue;	//ファイルではないとき（ディレクトリ等）

			Image *pImg = new Image(_path);
			int wx = pImg->GetWidth();
			int wy = pImg->GetHeight();
			wchar_t2char(_path,file,MAX_PATH);
			wchar_t2char(_fname,fname,MAX_PATH);

			if(wx && wy){
				retry:
				sprintf_s(title,ESP_BUFMAX,"%03d %s",j,fname);
				rtn= esp_RequestCreateImageX(j,title,-1,-1,wx,wy,100,32,1);
				if(rtn){
					j++;
					if(rtn==1 && j<ESP_IW_MAX)goto retry;
					else continue;
				}
				esp_RequestImageLoad(j,file,0,0);
				esp_RequestUpdate_(j);
				ESP_UnSelect();
				j++;
			}
		}
		DragFinish(hDrop);
		break;
	case WM_CREATE:
		esp_mwtext_hwnd=CreateWindow(L"STATIC",L"Ready",
				SS_LEFT | WS_CHILD | WS_VISIBLE,
				0,6,234,20,
				hwnd, (HMENU)IDC_MAINTEXT, esp_hInst, NULL);

		if(esp_mw_show){
			int yy[28]={1,2,3,4,5,6,7,8,9,10,-6,-5,-4,-3,-2,-1,1,2,3,4,5,6,-3,-2,-1,1,2,3};
		#ifdef ESP_SKIPANIMATION
			int yy_final= 0;
			for(int i=0;i<28;i++) yy_final += yy[i];
			GetWindowRect(hwnd,&rc);
			SetWindowPos(hwnd,0,rc.left,rc.top+yy_final,0,0,SWP_NOSIZE|SWP_SHOWWINDOW|esp_setpos_flags); //v8.0
		#else
			unsigned int t0= esp_gettime();
			for(int i=0;i<28;i++){
				GetWindowRect(hwnd,&rc);
				SetWindowPos(hwnd,0,rc.left,rc.top+yy[i],0,0,SWP_NOSIZE|SWP_SHOWWINDOW|esp_setpos_flags); //v8.0
				while((esp_gettime()-t0)<20);
				t0=esp_gettime();
			}
			while((esp_gettime()-t0)<500);
		#endif
		}

		hdc=GetDC(hwnd);
		esp_plt=GetDeviceCaps(hdc,BITSPIXEL);
		ReleaseDC(hwnd,hdc);
#ifndef _MFC_VER
		h_ESP_Loop = (HANDLE)_beginthreadex(NULL, 0, ESP_Loop, NULL, 0, NULL);	// v7.7
#else
		pRecvThread_esp_Loop = ::AfxBeginThread(ESP_Loop, NULL, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
		h_ESP_Loop = pRecvThread_esp_Loop->m_hThread;
		pRecvThread_esp_Loop->m_bAutoDelete = FALSE;	// 自動破棄フラグクリア
		pRecvThread_esp_Loop->ResumeThread();			// サスペンド解除
#endif // !_MFC_VER

		break;
	case WM_KEYDOWN:
		if(GetKeyState(VK_CONTROL)<0){
			if(wParam=='V'){PostMessage(hwnd,WM_COMMAND,ID_PASTETOMAIN,0);break;}	//Ctrl+V
			if(wParam=='W'){PostMessage(hwnd,WM_COMMAND,ID_INFO,0);break;}			//Ctrl+W
		}else{
			if(wParam=='X' || wParam==VK_ESCAPE)goto push_x;	//X or ESC
			if(wParam=='S')goto push_s;							//S
			if(wParam=='C')goto push_c;							//C
		}
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam)){
			case ID_INFO:
				//TWがなければOpenする
				if(!esp_tw[esp_twi].show){
					esp_RequestOpenTextWindow(0,0,0,-1,-1);
				}
				PostMessage(esp_tw[esp_twi].hwnd,WM_COMMAND,ID_INFO,0);
				break;
			case ID_IMAGEWINDOW:
				esp_RequestOpenTextWindow(0,0,0,-1,-1);
				ESP_Printf("Creating ImageWindow...\n");
				ESP_Printf(" Width=");
				ESP_Input(buf);
					if(ESP_EXIT) break;
				wx=atoi(buf);
				ESP_Printf("Height=");
				ESP_Input(buf);
					if(ESP_EXIT) break;
				wy=atoi(buf);
				ESP_Printf("Bit[32 or 8]=");
				ESP_Input(buf);
					if(ESP_EXIT) break;
				bit=atoi(buf);
				if(bit!=32 && bit!=8) break;

				for(int i=0; i<ESP_IW_MAX; i++){
					if(!esp_iw[i].show){
						sprintf_s(title,ESP_BUFMAX,"%03d",i);
						esp_RequestCreateImageX(i,title,-1,-1,wx,wy,100,bit,1);
						break;
					}
				}
				break;
			case ID_INPUTBOX:
				esp_RequestOpenTextWindow(0,0,0,-1,-1);
				ESP_Printf("Creating InpuxBox...\n");
				ESP_Printf("How many items? >");
				ESP_Input(buf);
				esp_RequestOpenInputBox(0,0,atoi(buf));
				break;
			case ID_BUTTONBOX:
				esp_RequestOpenTextWindow(0,0,0,-1,-1);
				ESP_Printf("Creating ButtonBox...\n");
				ESP_Printf("Number[X]=>");
				ESP_Input(buf);
				x1=atoi(buf);
				ESP_Printf("Number[Y]=>");
				ESP_Input(buf);
				y1=atoi(buf);
				esp_RequestOpenButtonBox(0,0,x1,y1);
				break;
			case ID_TEXTWINDOW:
				//TWを１つ追加Openする
				for(int i=0;i<ESP_TW_MAX;i++){
					if(!esp_tw[i].show){
						esp_RequestOpenTextWindow(i,0,0,-1,-1);
						break;
					}
				}
				break;
			case ID_PASTETOMAIN:
				if(ESP_STARTING) break;

				hbm=esp_GetBitmapFromCB(rgb,&used);
				if(!hbm) break;

				GetObject(hbm,sizeof(BITMAP),&bm);
				wx=bm.bmWidth;
				wy=bm.bmHeight;

				for(int i=0;i<ESP_IW_MAX;i++){
					sprintf_s(title,ESP_BUFMAX,"%03d",i);
					rtn= esp_RequestCreateImageX(i,title,-1,-1,wx,wy,100,32,1);
					if(!rtn){
						esp_RequestDibDisp(hbm);
						esp_RequestUpdate_(i);
						ESP_UnSelect();
						break;
					}
				}
				if(rtn){
					DeleteObject(hbm);
				}
				break;
			case ID_START:
				push_s:
				if(!ESP_STARTING) ESP_START=1;
				break;
			case ID_STOP:
				push_c:
				esp_STOP=1;
				break;
			case ID_EXIT:	// v7.7
				push_x:
				ESP_EndAllLog();	// v8.2
				esp_tw_inputflag=0;
				esp_STOP=1;
				ESP_EXIT=1;
				Sleep(1);			// v8.2
				//MFCのリリースモードで終了できなかった原因はesp_gettime関数で使用されていたグローバル変数esp_ld_fpmsがスレッド間での
				//値の引き継ぎが出来ず0が代入されていたためesp_gettime() - t0 の値が0であった。非MFCやMFCデバッグモードではこの現象は
				//起こっていなかった。
				//h_ESP_Loopも元の解放処理では解放出来ていなかったので、結果としてforループを抜け出せなかった。20210113 kinya iwamoto、
				unsigned int t0=esp_gettime();
				for(;;){
					static int i = 0;
					CM();
					if (!h_ESP_Loop || (esp_gettime() - t0 > ESP_EXITTIME)) break;
				}
				if(ESP_EXIT==1){
					ESP_Finish();
					ESP_EXIT=2;
				}
				if(h_ESP_Loop){
					TerminateThread(h_ESP_Loop,1);
				}
				DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_QUERYENDSESSION:
		//ver.8.5
		SendMessage(esp_mw_hwnd,WM_COMMAND,ID_EXIT,0);
		Sleep(ESP_EXITTIME);
		return TRUE;
	default:
		return DefWindowProc(hwnd,message,wParam,lParam);
	}
	return 0;
}

//esp_hstartをESP_Exitで解放するため宣言をここに移動した 20210113 kinya iwamoto
#ifdef ESP_LIBRARY_MODE
HANDLE esp_hstart;
#endif // ESP_LIBRARY_MODE
//v8.0
void ESP_Exit(void)
{
	if(!esp_running) return;
	PostMessage(esp_mw_hwnd,WM_KEYDOWN,VK_ESCAPE,0);	//ESC code
	Sleep(1);

#ifdef ESP_LIBRARY_MODE
	//スレッドの終了処理位置の変更 20210113 kinya iwamoto
	// スレッドの終了待ち
	DWORD dwExitCode_esp = 0;
	::WaitForSingleObject(esp_hstart, INFINITE);
	// スレッドの終了コードを取得
	::GetExitCodeThread(esp_hstart, &dwExitCode_esp);
#ifndef _MFC_VER
	//スレッドハンドルの解放
	CloseHandle(esp_hstart);
	esp_hstart = NULL;
#else
	//スレッドオブジェクトの解放
	//MFCではハンドルesp_hstartはpRecvThread_esp_start->m_hThreadのため
	//スレッドオブジェクトを解放すれば自動的に解放される
	if (pRecvThread_esp_start) delete pRecvThread_esp_start;
	pRecvThread_esp_start = NULL;
#endif // !_MFC_VER
	while(esp_running) Sleep(1);
#endif
}

int ESP_Command(void)
{
	char s[2*ESPTWBUFMAX];
	ESP_Printf("Cmd>");
	ESP_Input(s);
	if(!strcmp(s,"exit")){
		ESP_Exit();
	}else if(!strcmp(s,"start")){
		PostMessage(esp_mw_hwnd,WM_KEYDOWN,'S',0);		//S
	}else if(!strcmp(s,"help")){
		ESP_Printf("Command list:exit help start ver color\n");
	}else if(!strcmp(s,"ver")){
		PostMessage(esp_tw[esp_twi].hwnd,WM_COMMAND,ID_ABOUT,0);
	}else if(!strcmp(s,"color")){
		ESP_Printf("Red  :%3d\n",C2R(esp_color));
		ESP_Printf("Green:%3d\n",C2G(esp_color));
		ESP_Printf("Blue :%3d\n",C2B(esp_color));
		ESP_Printf("esp_tttc=%06x\n",esp_tttc);
		ESP_Printf("esp_tc=%06x\n",esp_tc);
	}else{
		ESP_Printf("Invalid command\n");
		return 1;
	}
	return 0;
}

//---点描画，取得関数---

__inline void ESP_Pset(int x,int y,int c)
{
	unsigned int mx=esp_iw[esp_i].wx;
	unsigned int my=esp_iw[esp_i].wy;
	esp_LPx=x;
	esp_LPy=y;
	if((unsigned int)x>=mx || (unsigned int)y>=my) return;
	if(esp_iw[esp_i].bit==32){
		*ESPPTR=c;
	}else{
		*ESPPTR8=c;
	}
}

//ラストポイント更新なし Pset
__inline void ESP_Pset_(int x,int y,int c)
{
	unsigned int mx=esp_iw[esp_i].wx;
	unsigned int my=esp_iw[esp_i].wy;
	if((unsigned int)x>=mx || (unsigned int)y>=my) return;
	if(esp_iw[esp_i].bit==32){
		*ESPPTR=c;
	}else{
		*ESPPTR8=c;
	}
}

//点描画（高速版）No-check,32bit専用
__inline void ESP_PsetF(int x,int y,int c)
{
	unsigned int mx=esp_iw[esp_i].wx;
	unsigned int my=esp_iw[esp_i].wy;
	*ESPPTR=c;
}

//点描画（高速版）No-check,8bit専用
__inline void ESP_PsetF8(int x,int y,int c)
{
	unsigned int mx=esp_iw[esp_i].wx;
	unsigned int my=esp_iw[esp_i].wy;
	*ESPPTR8=c;
}

__inline void ESP_PsetRGB(int x,int y,int r,int g,int b)
{
	unsigned int mx=esp_iw[esp_i].wx;
	unsigned int my=esp_iw[esp_i].wy;
	esp_LPx=x;
	esp_LPy=y;
	if((unsigned int)x>=mx || (unsigned int)y>=my) return;
	if(esp_iw[esp_i].bit==32){
		*ESPPTR=RGB2C(r,g,b);
	}else{
		*ESPPTR8=RGB2C(r,g,b);
	}
}

__inline void ESP_PsetB(int x,int y,int c)
{
	unsigned int mx=esp_iw[esp_i].wx;
	unsigned int my=esp_iw[esp_i].wy;
	if((unsigned int)x>=mx || (unsigned int)y>=my) return;
	unsigned char *p=(unsigned char *)ESPPTR;
	*p=c;
}

__inline void ESP_PsetG(int x,int y,int c)
{
	unsigned int mx=esp_iw[esp_i].wx;
	unsigned int my=esp_iw[esp_i].wy;
	if((unsigned int)x>=mx || (unsigned int)y>=my) return;
	unsigned char *p=(unsigned char *)ESPPTR;
	*(p+1)=c;
}

__inline void ESP_PsetR(int x,int y,int c)
{
	unsigned int mx=esp_iw[esp_i].wx;
	unsigned int my=esp_iw[esp_i].wy;
	if((unsigned int)x>=mx || (unsigned int)y>=my) return;
	unsigned char *p=(unsigned char *)ESPPTR;
	*(p+2)=c;
}

__inline int ESP_Point(int x,int y)
{
	unsigned int mx=esp_iw[esp_i].wx;
	unsigned int my=esp_iw[esp_i].wy;
	if((unsigned int)x>=mx || (unsigned int)y>=my) return 0;
	if(esp_iw[esp_i].bit==32){
		return *ESPPTR;
	}else{
		return *ESPPTR8;
	}
}

// 範囲外の座標でcを返す for ESP_Paint(),ESP_Paint2()
__inline int _ESP_Point(int x,int y,int c=-1)
{
	unsigned int mx=esp_iw[esp_i].wx;
	unsigned int my=esp_iw[esp_i].wy;
	if((unsigned int)x>=mx || (unsigned int)y>=my) return c;
	if(esp_iw[esp_i].bit==32){
		return *ESPPTR;
	}else{
		return *ESPPTR8;
	}
}

// for ESP_Paint2() function 範囲外の座標でcを返す
__inline int _ESP_Point2(int x,int y,int c)
{
	unsigned int mx=esp_iw[esp_i].wx;
	unsigned int my=esp_iw[esp_i].wy;
	if((unsigned int)x>=mx || (unsigned int)y>=my) return c;
	if(esp_iw[esp_i].bit==32){
		return *ESPPTR;
	}else{
		return *ESPPTR8;
	}
}

__inline void ESP_PsetXOR(int x,int y)
{
	unsigned int mx=esp_iw[esp_i].wx;
	unsigned int my=esp_iw[esp_i].wy;
	esp_LPx=x;
	esp_LPy=y;
	if((unsigned int)x>=mx || (unsigned int)y>=my) return;
	if(esp_iw[esp_i].bit==32){
		*ESPPTR^=0xffffff;
	}else{
		*ESPPTR8^=0xff;
	}
}

__inline void ESP_PsetXOR_(int x,int y)
{
	unsigned int mx=esp_iw[esp_i].wx;
	unsigned int my=esp_iw[esp_i].wy;
	if((unsigned int)x>=mx || (unsigned int)y>=my) return;
	if(esp_iw[esp_i].bit==32){
		*ESPPTR^=0xffffff;
	}else{
		*ESPPTR8^=0xff;
	}
}

#define ESP_PointR(x,y) C2R(ESP_Point((x),(y)))
#define ESP_PointG(x,y) C2G(ESP_Point((x),(y)))
#define ESP_PointB(x,y) C2B(ESP_Point((x),(y)))

//BMP保存 7.0
int ESP_BmpSave(const char *filename, int x0, int y0, int wx, int wy)
{
	if(esp_iw_check(esp_i)) return 2;

	char buf[MAX_PATH];
	esp_filename_ext(filename,".bmp",buf,MAX_PATH);
	FILE *fp;
	int r=fopen_s(&fp,buf,"wb");
	if(r) return 1;

	int pp;
	if(esp_iw[esp_i].bit==32){
		pp=(wx*3+3) & ~3;
	}else{
		pp=(wx+3) & ~3;
	}

	BITMAPFILEHEADER bfh;
	ZeroMemory(&bfh,sizeof(bfh));
	bfh.bfType='B'+'M'*0x100;
	
	BITMAPINFOHEADER bih;
	ZeroMemory(&bih,sizeof(bih));
	bih.biSize=sizeof(bih);
	bih.biWidth=wx;
	bih.biHeight=wy;
	bih.biPlanes=1;
	bih.biSizeImage=pp*wy;
	bih.biXPelsPerMeter=2834; //XPels/Meter (2834=72dpi)
	bih.biYPelsPerMeter=2834; //YPels/Meter (2834=72dpi)

	if(esp_iw[esp_i].bit==32){
		bfh.bfSize=sizeof(bfh)+sizeof(bih)+pp*wy;
		bfh.bfOffBits=sizeof(bfh)+sizeof(bih);
		bih.biBitCount=24;
	}else{
		bfh.bfSize=sizeof(bfh)+sizeof(bih)+pp*wy +256*sizeof(RGBQUAD);
		bfh.bfOffBits=sizeof(bfh)+sizeof(bih) +256*sizeof(RGBQUAD);
		bih.biBitCount=8;
	}

	fwrite(&bfh,sizeof(bfh),1,fp);
	fwrite(&bih,sizeof(bih),1,fp);

	int mx=esp_iw[esp_i].wx;

	//ラインバッファ確保
	unsigned char *p0 = new BYTE[pp];	

	if(esp_iw[esp_i].bit==32){
		//32bit
		for (int y=y0+wy-1; y>=y0; y--) {
			unsigned char *p=p0;
			for (int x=x0; x<x0+wx; x++) {
				int c=*ESPPTR;
				*p++ = (c & 0xff);
				*p++ = (c & 0xff00)>>8;
				*p++ = (c & 0xff0000)>>16;
			}
			fwrite(p0,pp,1,fp);
		}
	}else{
		//8bit
		RGBQUAD rgb[256];
		GetDIBColorTable(esp_iw[esp_i].memdc,0,256,rgb);
		fwrite(rgb,256*sizeof(RGBQUAD),1,fp);
		for (int y=y0+wy-1; y>=y0; y--) {
			unsigned char *p=p0;
			for (int x=x0; x<x0+wx; x++) {
				*p++ = *ESPPTR8;
			}
			fwrite(p0,pp,1,fp);
		}
	}

	delete[] p0;
	fclose(fp);
	return 0;
}

// c=0rgb 
// h=0-359 , s=0-255, v=0-255
// ver.5.0
void C2HSV(int c,int *ph,int *ps,int *pv)
{
	int h,s,v,x;

	int r=C2R(c);
	int g=C2G(c);
	int b=C2B(c);

	v=max(max(r,g),b);
	x=min(min(r,g),b);
	s=v-x;

	if(s==0){ h=0; goto fin_c2hsv; }

		   if(v==r && x==b){
		h=(g-b)*60/s;
	} else if(v==g && x==b){
		h=60+(g-r)*60/s;
	} else if(v==g && x==r){
		h=60*2+(b-r)*60/s;
	} else if(v==b && x==r){
		h=60*3+(b-g)*60/s;
	} else if(v==b && x==g){
		h=60*4+(r-g)*60/s;
	} else if(v==r && x==g){
		h=60*5+(r-b)*60/s;
	}
fin_c2hsv:
	*ph=h; *ps=s; *pv=v;
}

int C2H(int c)
{
	int h,s,v;
	C2HSV(c,&h,&s,&v);
	return h;
}

int C2S(int c)
{
	int h,s,v;
	C2HSV(c,&h,&s,&v);
	return s;
}

int C2V(int c)
{
	int h,s,v;
	C2HSV(c,&h,&s,&v);
	return v;
}

// H=0-359,S=0-255,V=0-255
// C=0rgb
// ver.5.0
int HSV2C(int h,int s,int v)
{
	int r,g,b;
	if(h<=59){
		r=v;
		b=max(0,r-s);
		g=b+(r-b)*h/60;
	}else if(h<=59+60){
		h-=60;
		g=v;
		b=max(0,g-s);
		r=b+(g-b)*(60-h)/60;
	}else if(h<=59+60*2){
		h-=60*2;
		g=v;
		r=max(0,g-s);
		b=r+(g-r)*h/60;
	}else if(h<=59+60*3){
		h-=60*3;
		b=v;
		r=max(0,b-s);
		g=r+(b-r)*(60-h)/60;
	}else if(h<=59+60*4){
		h-=60*4;
		b=v;
		g=max(0,b-s);
		r=g+(b-g)*h/60;
	}else{
		h-=60*5;
		r=v;
		g=max(0,r-s);
		b=g+(r-g)*(60-h)/60;
	}
	return RGB2C(r,g,b);
}

//clear 範囲チェックなし
void esp_clearimage(int i)
{
	int pp;

	if(esp_iw[i].bit==32){
		//32bit
		pp=esp_iw[i].wx*sizeof(int);
	}else{
		//8bit
		pp=(esp_iw[i].wx+3) & ~3;
	}

	ZeroMemory(ESP_VramPtr[i], pp*esp_iw[i].wy);
}

//イメージウィンドウの消去 v7.7
void ESP_Cls(void)
{
	if((unsigned int)esp_i>=ESP_IW_MAX) return;
	if(!esp_iw[esp_i].show) return;

	esp_clearimage(esp_i);
	//esp_invalid(esp_i); //removed v7.7
}

//テキスト(8x14)用フォントデータ
unsigned char esp_fontpat[96][14]={
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
,{0x00,0x00,0x18,0x3C,0x3C,0x3C,0x18,0x18,0x00,0x18,0x18,0x00,0x00,0x00}
,{0x00,0x00,0x66,0x66,0x66,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
,{0x00,0x00,0x36,0x36,0x7F,0x36,0x36,0x36,0x7F,0x36,0x36,0x00,0x00,0x00}
,{0x18,0x18,0x3C,0x66,0x60,0x30,0x18,0x0C,0x06,0x66,0x3C,0x18,0x18,0x00}
,{0x00,0x70,0xD8,0xDA,0x76,0x0C,0x18,0x30,0x6E,0x5B,0x1B,0x0E,0x00,0x00}
,{0x00,0x00,0x38,0x6C,0x6C,0x38,0x60,0x6F,0x66,0x66,0x3B,0x00,0x00,0x00}
,{0x00,0x00,0x18,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
,{0x00,0x00,0x0C,0x18,0x18,0x30,0x30,0x30,0x30,0x30,0x18,0x18,0x0C,0x00}
,{0x00,0x00,0x30,0x18,0x18,0x0C,0x0C,0x0C,0x0C,0x0C,0x18,0x18,0x30,0x00}
,{0x00,0x00,0x00,0x00,0x36,0x1C,0x7F,0x1C,0x36,0x00,0x00,0x00,0x00,0x00}
,{0x00,0x00,0x00,0x00,0x18,0x18,0x7E,0x18,0x18,0x00,0x00,0x00,0x00,0x00}
,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x1C,0x0C,0x18,0x00}
,{0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x1C,0x00,0x00,0x00}
,{0x00,0x00,0x06,0x06,0x0C,0x0C,0x18,0x18,0x30,0x30,0x60,0x60,0x00,0x00}
,{0x00,0x00,0x1E,0x33,0x37,0x37,0x33,0x3B,0x3B,0x33,0x1E,0x00,0x00,0x00}
,{0x00,0x00,0x0C,0x1C,0x7C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x00,0x00,0x00}
,{0x00,0x00,0x3C,0x66,0x66,0x06,0x0C,0x18,0x30,0x60,0x7E,0x00,0x00,0x00}
,{0x00,0x00,0x3C,0x66,0x66,0x06,0x1C,0x06,0x66,0x66,0x3C,0x00,0x00,0x00}
,{0x00,0x00,0x30,0x30,0x36,0x36,0x36,0x66,0x7F,0x06,0x06,0x00,0x00,0x00}
,{0x00,0x00,0x7E,0x60,0x60,0x60,0x7C,0x06,0x06,0x0C,0x78,0x00,0x00,0x00}
,{0x00,0x00,0x1C,0x18,0x30,0x7C,0x66,0x66,0x66,0x66,0x3C,0x00,0x00,0x00}
,{0x00,0x00,0x7E,0x06,0x0C,0x0C,0x18,0x18,0x30,0x30,0x30,0x00,0x00,0x00}
,{0x00,0x00,0x3C,0x66,0x66,0x76,0x3C,0x6E,0x66,0x66,0x3C,0x00,0x00,0x00}
,{0x00,0x00,0x3C,0x66,0x66,0x66,0x66,0x3E,0x0C,0x18,0x38,0x00,0x00,0x00}
,{0x00,0x00,0x00,0x00,0x1C,0x1C,0x00,0x00,0x00,0x1C,0x1C,0x00,0x00,0x00}
,{0x00,0x00,0x00,0x00,0x1C,0x1C,0x00,0x00,0x00,0x1C,0x1C,0x0C,0x18,0x00}
,{0x00,0x00,0x06,0x0C,0x18,0x30,0x60,0x30,0x18,0x0C,0x06,0x00,0x00,0x00}
,{0x00,0x00,0x00,0x00,0x00,0x7E,0x00,0x7E,0x00,0x00,0x00,0x00,0x00,0x00}
,{0x00,0x00,0x60,0x30,0x18,0x0C,0x06,0x0C,0x18,0x30,0x60,0x00,0x00,0x00}
,{0x00,0x00,0x3C,0x66,0x66,0x0C,0x18,0x18,0x00,0x18,0x18,0x00,0x00,0x00}
,{0x00,0x00,0x7E,0xC3,0xC3,0xCF,0xDB,0xDB,0xCF,0xC0,0x7F,0x00,0x00,0x00}
,{0x00,0x00,0x18,0x3C,0x66,0x66,0x66,0x7E,0x66,0x66,0x66,0x00,0x00,0x00}
,{0x00,0x00,0x7C,0x66,0x66,0x66,0x7C,0x66,0x66,0x66,0x7C,0x00,0x00,0x00}
,{0x00,0x00,0x3C,0x66,0x66,0x60,0x60,0x60,0x66,0x66,0x3C,0x00,0x00,0x00}
,{0x00,0x00,0x78,0x6C,0x66,0x66,0x66,0x66,0x66,0x6C,0x78,0x00,0x00,0x00}
,{0x00,0x00,0x7E,0x60,0x60,0x60,0x7C,0x60,0x60,0x60,0x7E,0x00,0x00,0x00}
,{0x00,0x00,0x7E,0x60,0x60,0x60,0x7C,0x60,0x60,0x60,0x60,0x00,0x00,0x00}
,{0x00,0x00,0x3C,0x66,0x66,0x60,0x60,0x6E,0x66,0x66,0x3E,0x00,0x00,0x00}
,{0x00,0x00,0x66,0x66,0x66,0x66,0x7E,0x66,0x66,0x66,0x66,0x00,0x00,0x00}
,{0x00,0x00,0x3C,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x3C,0x00,0x00,0x00}
,{0x00,0x00,0x06,0x06,0x06,0x06,0x06,0x06,0x66,0x66,0x3C,0x00,0x00,0x00}
,{0x00,0x00,0x66,0x66,0x6C,0x6C,0x78,0x6C,0x6C,0x66,0x66,0x00,0x00,0x00}
,{0x00,0x00,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x7E,0x00,0x00,0x00}
,{0x00,0x00,0x63,0x63,0x77,0x6B,0x6B,0x6B,0x63,0x63,0x63,0x00,0x00,0x00}
,{0x00,0x00,0x63,0x63,0x73,0x7B,0x6F,0x67,0x63,0x63,0x63,0x00,0x00,0x00}
,{0x00,0x00,0x3C,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x3C,0x00,0x00,0x00}
,{0x00,0x00,0x7C,0x66,0x66,0x66,0x7C,0x60,0x60,0x60,0x60,0x00,0x00,0x00}
,{0x00,0x00,0x3C,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x3C,0x0C,0x06,0x00}
,{0x00,0x00,0x7C,0x66,0x66,0x66,0x7C,0x6C,0x66,0x66,0x66,0x00,0x00,0x00}
,{0x00,0x00,0x3C,0x66,0x60,0x30,0x18,0x0C,0x06,0x66,0x3C,0x00,0x00,0x00}
,{0x00,0x00,0x7E,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x00,0x00,0x00}
,{0x00,0x00,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x3C,0x00,0x00,0x00}
,{0x00,0x00,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x3C,0x18,0x00,0x00,0x00}
,{0x00,0x00,0x63,0x63,0x63,0x6B,0x6B,0x6B,0x36,0x36,0x36,0x00,0x00,0x00}
,{0x00,0x00,0x66,0x66,0x34,0x18,0x18,0x2C,0x66,0x66,0x66,0x00,0x00,0x00}
,{0x00,0x00,0x66,0x66,0x66,0x66,0x3C,0x18,0x18,0x18,0x18,0x00,0x00,0x00}
,{0x00,0x00,0x7E,0x06,0x06,0x0C,0x18,0x30,0x60,0x60,0x7E,0x00,0x00,0x00}
,{0x00,0x00,0x3C,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x3C}
,{0x00,0x00,0x60,0x60,0x30,0x30,0x18,0x18,0x0C,0x0C,0x06,0x06,0x00,0x00}
,{0x00,0x00,0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x3C}
,{0x18,0x3C,0x66,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF}
,{0x38,0x18,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
,{0x00,0x00,0x00,0x00,0x3C,0x06,0x06,0x3E,0x66,0x66,0x3E,0x00,0x00,0x00}
,{0x00,0x00,0x60,0x60,0x7C,0x66,0x66,0x66,0x66,0x66,0x7C,0x00,0x00,0x00}
,{0x00,0x00,0x00,0x00,0x3C,0x66,0x60,0x60,0x60,0x66,0x3C,0x00,0x00,0x00}
,{0x00,0x00,0x06,0x06,0x3E,0x66,0x66,0x66,0x66,0x66,0x3E,0x00,0x00,0x00}
,{0x00,0x00,0x00,0x00,0x3C,0x66,0x66,0x7E,0x60,0x60,0x3C,0x00,0x00,0x00}
,{0x00,0x00,0x1E,0x30,0x30,0x30,0x7E,0x30,0x30,0x30,0x30,0x00,0x00,0x00}
,{0x00,0x00,0x00,0x00,0x3E,0x66,0x66,0x66,0x66,0x66,0x3E,0x06,0x06,0x7C}
,{0x00,0x00,0x60,0x60,0x7C,0x66,0x66,0x66,0x66,0x66,0x66,0x00,0x00,0x00}
,{0x00,0x18,0x18,0x00,0x78,0x18,0x18,0x18,0x18,0x18,0x7E,0x00,0x00,0x00}
,{0x00,0x0C,0x0C,0x00,0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x78}
,{0x00,0x00,0x60,0x60,0x66,0x66,0x6C,0x78,0x6C,0x66,0x66,0x00,0x00,0x00}
,{0x00,0x00,0x78,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x7E,0x00,0x00,0x00}
,{0x00,0x00,0x00,0x00,0x7E,0x6B,0x6B,0x6B,0x6B,0x6B,0x63,0x00,0x00,0x00}
,{0x00,0x00,0x00,0x00,0x7C,0x66,0x66,0x66,0x66,0x66,0x66,0x00,0x00,0x00}
,{0x00,0x00,0x00,0x00,0x3C,0x66,0x66,0x66,0x66,0x66,0x3C,0x00,0x00,0x00}
,{0x00,0x00,0x00,0x00,0x7C,0x66,0x66,0x66,0x66,0x66,0x7C,0x60,0x60,0x60}
,{0x00,0x00,0x00,0x00,0x3E,0x66,0x66,0x66,0x66,0x66,0x3E,0x06,0x06,0x06}
,{0x00,0x00,0x00,0x00,0x66,0x6E,0x70,0x60,0x60,0x60,0x60,0x00,0x00,0x00}
,{0x00,0x00,0x00,0x00,0x3E,0x60,0x60,0x3C,0x06,0x06,0x7C,0x00,0x00,0x00}
,{0x00,0x00,0x30,0x30,0x7E,0x30,0x30,0x30,0x30,0x30,0x1E,0x00,0x00,0x00}
,{0x00,0x00,0x00,0x00,0x66,0x66,0x66,0x66,0x66,0x66,0x3E,0x00,0x00,0x00}
,{0x00,0x00,0x00,0x00,0x66,0x66,0x66,0x66,0x66,0x3C,0x18,0x00,0x00,0x00}
,{0x00,0x00,0x00,0x00,0x63,0x6B,0x6B,0x6B,0x6B,0x36,0x36,0x00,0x00,0x00}
,{0x00,0x00,0x00,0x00,0x66,0x66,0x3C,0x18,0x3C,0x66,0x66,0x00,0x00,0x00}
,{0x00,0x00,0x00,0x00,0x66,0x66,0x66,0x66,0x66,0x66,0x3C,0x0C,0x18,0xF0}
,{0x00,0x00,0x00,0x00,0x7E,0x06,0x0C,0x18,0x30,0x60,0x7E,0x00,0x00,0x00}
,{0x00,0x00,0x0C,0x18,0x18,0x18,0x30,0x60,0x30,0x18,0x18,0x18,0x0C,0x00}
,{0x00,0x00,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18}
,{0x00,0x00,0x30,0x18,0x18,0x18,0x0C,0x06,0x0C,0x18,0x18,0x18,0x30,0x00}
,{0x00,0x00,0x71,0xDB,0x8E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
};

// 7.0
void ESP_Gputc(unsigned char c)
{
	if(c=='\n') goto espgtxtcr;
	if(c<0x20 || c>0x7F) return;
	c-=0x20;
	for(int y=0;y<14;y++){
		for(int x=0;x<8;x++){
			if(esp_fontpat[c][y]&(0x80>>x)){
				ESP_Pset(esp_tx+x,esp_ty+y-14,esp_tc);
			}
		}
	}
	esp_tx+=8;
	if(esp_tx>esp_iw[esp_i].wx-8){
		espgtxtcr:
		esp_tx=esp_tx0;
		esp_ty+=16;	
	}
}

void ESP_Glocate(int x,int y)
{
	esp_tx0=esp_tx=x;
	esp_ty=y;
}

#define ESP_Gtextcolor(c) (esp_tc=(c))

// 7.0
void ESP_Gputs(const char *s)
{
	while(*s){
		ESP_Gputc(*s++);
	}
}

// 7.0
void ESP_Gprintf(const char *format, ...)
{
	va_list vl;
	va_start(vl,format);

	char buf[ESP_STRMAX];
	vsprintf_s(buf,ESP_STRMAX,format,vl);

	ESP_Gputs(buf);
}

// 7.0
int ESP_CheckLine(int x1,int y1,int x2,int y2,int c)
{
	int t,wx,wy,s;

	esp_LPx=x2;
	esp_LPy=y2;
	
	if(x1==x2){
		esp_order(&y1,&y2);
		for(int j=y1;j<=y2;j++)	if(_ESP_Point(x1,j)==c) return 1;
	}else if(y1==y2){
		esp_order(&x1,&x2);
		for(int i=x1;i<=x2;i++)	if(_ESP_Point(i,y1)==c) return 1;
	}else{
		if(x1>x2){t=x1;x1=x2;x2=t;t=y1;y1=y2;y2=t;}
		wx=x2-x1;
		if(y1<y2){
			wy=y2-y1;
			if(wx>=wy){
				s=(wx+1)/2;		//ver.5.8
				lineloop1:
				if(_ESP_Point(x1,y1)==c) return 1;
				if(x1==x2)goto linefin;
				x1++;s-=wy;if(s<=0){s+=wx;y1++;}
				goto lineloop1;
			}else{
				s=(wy+1)/2;		//ver.5.8
				lineloop2:
				if(_ESP_Point(x1,y1)==c) return 1;
				if(y1==y2)goto linefin;
				y1++;s-=wx;if(s<=0){s+=wy;x1++;}
				goto lineloop2;
			}
		}else{
			wy=y1-y2;
			if(wx>=wy){
				s=(wx+1)/2;		//ver.5.8
				lineloop3:
				if(_ESP_Point(x1,y1)==c) return 1;
				if(x1==x2)goto linefin;
				x1++;s-=wy;if(s<=0){s+=wx;y1--;}
				goto lineloop3;
			}else{
				s=(wy+1)/2;		//ver.5.8
				lineloop4:
				if(_ESP_Point(x1,y1)==c) return 1;
				if(y1==y2)goto linefin;
				y1--;s-=wx;if(s<=0){s+=wy;x1++;}
				goto lineloop4;
			}
		}
	}
	linefin:;
	return 0;
}

// 7.0
void ESP_Line(int x1,int y1,int x2,int y2,int c)
{
	int t,wx,wy,s;

	esp_LPx=x2;
	esp_LPy=y2;
	
	if(x1==x2){
		esp_order(&y1,&y2);
		for(int j=y1;j<=y2;j++)	ESP_Pset_(x1,j,c);
	}else if(y1==y2){
		esp_order(&x1,&x2);
		for(int i=x1;i<=x2;i++)	ESP_Pset_(i,y1,c);
	}else{
		if(x1>x2){t=x1;x1=x2;x2=t;t=y1;y1=y2;y2=t;}
		wx=x2-x1;
		if(y1<y2){
			wy=y2-y1;
			if(wx>=wy){
				s=(wx+1)/2;		//ver.5.8
				lineloop1:
				ESP_Pset_(x1,y1,c);
				if(x1==x2)goto linefin;
				x1++;s-=wy;if(s<=0){s+=wx;y1++;}
				goto lineloop1;
			}else{
				s=(wy+1)/2;		//ver.5.8
				lineloop2:
				ESP_Pset_(x1,y1,c);
				if(y1==y2)goto linefin;
				y1++;s-=wx;if(s<=0){s+=wy;x1++;}
				goto lineloop2;
			}
		}else{
			wy=y1-y2;
			if(wx>=wy){
				s=(wx+1)/2;		//ver.5.8
				lineloop3:
				ESP_Pset_(x1,y1,c);
				if(x1==x2)goto linefin;
				x1++;s-=wy;if(s<=0){s+=wx;y1--;}
				goto lineloop3;
			}else{
				s=(wy+1)/2;		//ver.5.8
				lineloop4:
				ESP_Pset_(x1,y1,c);
				if(y1==y2)goto linefin;
				y1--;s-=wx;if(s<=0){s+=wy;x1++;}
				goto lineloop4;
			}
		}
	}
	linefin:;
}

// 7.0
void ESP_LineXOR(int x1,int y1,int x2,int y2)
{
	int t,wx,wy,s;

	esp_LPx=x2;
	esp_LPy=y2;

	if(x1==x2){
		esp_order(&y1,&y2);
		for(int j=y1;j<=y2;j++)	ESP_PsetXOR_(x1,j);
	}else if(y1==y2){
		esp_order(&x1,&x2);
		for(int i=x1;i<=x2;i++)	ESP_PsetXOR_(i,y1);
	}else{
		if(x1>x2){t=x1;x1=x2;x2=t;t=y1;y1=y2;y2=t;}
		wx=x2-x1;
		if(y1<y2){
			wy=y2-y1;
			if(wx>=wy){
				s=(wx+1)/2;		//ver.5.8
				linexloop1:
				ESP_PsetXOR_(x1,y1);
				if(x1==x2)goto linexfin;
				x1++;s-=wy;if(s<=0){s+=wx;y1++;}
				goto linexloop1;
			}else{
				s=(wy+1)/2;		//ver.5.8
				linexloop2:
				ESP_PsetXOR_(x1,y1);
				if(y1==y2)goto linexfin;
				y1++;s-=wx;if(s<=0){s+=wy;x1++;}
				goto linexloop2;
			}
		}else{
			wy=y1-y2;
			if(wx>=wy){
				s=(wx+1)/2;		//ver.5.8
				linexloop3:
				ESP_PsetXOR_(x1,y1);
				if(x1==x2)goto linexfin;
				x1++;s-=wy;if(s<=0){s+=wx;y1--;}
				goto linexloop3;
			}else{
				s=(wy+1)/2;		//ver.5.8
				linexloop4:
				ESP_PsetXOR_(x1,y1);
				if(y1==y2)goto linexfin;
				y1--;s-=wx;if(s<=0){s+=wy;x1++;}
				goto linexloop4;
			}
		}
	}
	linexfin:;
}

void ESP_LineTo(int x,int y,int c)
{
	ESP_Line(esp_LPx,esp_LPy,x,y,c);
}

void ESP_LineToXOR(int x,int y)
{
	ESP_LineXOR(esp_LPx,esp_LPy,x,y);
}

#define PaintStackMax 4000

//v7.0
//v8.1 戻り値：面積（単位：ピクセル）
int ESP_Paint(int x,int y,int c)
{
	int n= 0;	//for counting area

	if((unsigned int)x>=(unsigned int)esp_iw[esp_i].wx || (unsigned int)y>=(unsigned int)esp_iw[esp_i].wy) return 0;

	int mtmp=_ESP_Point(x,y);
	if(mtmp==c) return n;

	int xx[PaintStackMax];
	int yy[PaintStackMax];

	int cx=0;

	paintloop:	
	int ft=1;
	int fb=1;

	//左方向へ探索
	paint1:
	if(_ESP_Point(--x,y)==mtmp)goto paint1;
	x++;

	int x0=x;
	int y0=y;

	paint2:
	if(mtmp==_ESP_Point(x,y)){
		if(ft){
			if(_ESP_Point(x,y-1)==mtmp){
				if(cx<PaintStackMax){
					xx[cx]=x;
					yy[cx]=y-1;
					cx++;
					ft=0;
				}
			}
		}else{
			if(_ESP_Point(x,y-1)!=mtmp)ft=1;
		}
		if(fb){
			if(_ESP_Point(x,y+1)==mtmp){
				if(cx<PaintStackMax){
					xx[cx]=x;
					yy[cx]=y+1;
					cx++;
					fb=0;
				}
			}
		}else{
			if(_ESP_Point(x,y+1)!=mtmp)fb=1;
		}
		x++;
		goto paint2;
	}else{
		x--;
	}

	ESP_Line(x0,y0,x,y,c);
	n += abs(x0-x)+1;

	paint3:
	if(cx==0) return n;
	cx--;
	x=xx[cx];
	y=yy[cx];
		
	if(_ESP_Point(x,y)!=mtmp)goto paint3;	//v5.7
	goto paintloop;
}

//v8.4 色c1で境界色c2までを塗りつぶす　戻り値：面積（単位：ピクセル）
int ESP_Paint2(int x,int y,int c1,int c2)
{
	int n= 0;	//for counting area

	if((unsigned int)x>=(unsigned int)esp_iw[esp_i].wx || (unsigned int)y>=(unsigned int)esp_iw[esp_i].wy) return 0;

	if(_ESP_Point(x,y,c2)==c2) return n;

	int xx[PaintStackMax];
	int yy[PaintStackMax];

	int cx= 0;

	paintloop:	
	int ft= 1;
	int fb= 1;

	//左方向へ探索
	paint1:
	if(_ESP_Point(--x,y,c2)!=c2) goto paint1;
	x++;

	int x0= x;
	int y0= y;

	paint2:
	if(c2!=_ESP_Point(x,y,c2)){
		int tchk= _ESP_Point(x,y-1,c2)!=c2 && _ESP_Point(x,y-1,c2)!=c1;
		if(ft){
			if(tchk){
				if(cx<PaintStackMax){
					xx[cx]= x;
					yy[cx]= y-1;
					cx++;
					ft= 0;
				}
			}
		}else{
			if(!tchk) ft=1;
		}
		int bchk= _ESP_Point(x,y+1,c2)!=c2 && _ESP_Point(x,y+1,c2)!=c1;
		if(fb){
			if(bchk){
				if(cx<PaintStackMax){
					xx[cx]= x;
					yy[cx]= y+1;
					cx++;
					fb= 0;
				}
			}
		}else{
			if(!bchk) fb=1;
		}
		x++;
		goto paint2;
	}else{
		x--;
	}

	ESP_Line(x0,y0,x,y,c1);
	n += abs(x0-x)+1;

	paint3:
	if(cx==0) return n;
	cx--;
	x= xx[cx];
	y= yy[cx];
		
	if(_ESP_Point(x,y,c2)==c2) goto paint3;
	goto paintloop;
}

int ESP_CheckBox(int x1,int y1,int x2,int y2,int c)
{
	if(ESP_CheckLine(x1,y1,x2,y1,c)) return 1;
	if(ESP_CheckLine(x2,y1,x2,y2,c)) return 1;
	if(ESP_CheckLine(x2,y2,x1,y2,c)) return 1;
	if(ESP_CheckLine(x1,y2,x1,y1,c)) return 1;
	return 0;
}

void ESP_Box(int x1,int y1,int x2,int y2,int c)
{
	ESP_Line(x1,y1,x2,y1,c);
	ESP_Line(x2,y1,x2,y2,c);
	ESP_Line(x2,y2,x1,y2,c);
	ESP_Line(x1,y2,x1,y1,c);
}

void ESP_BoxXOR(int x1,int y1,int x2,int y2)
{
	esp_order(&x1,&x2);
	esp_order(&y1,&y2);
	ESP_LineXOR(x1,y1,x2,y1);
	if(y1!=y2)ESP_LineXOR(x1,y2,x2,y2);
	if(abs(y2-y1)>1){
		ESP_LineXOR(x1,y1+1,x1,y2-1);
		ESP_LineXOR(x2,y1+1,x2,y2-1);
	}
}

//v8.2(f省略時はcと同じ色で)
void ESP_BoxFill(int x1,int y1,int x2,int y2,int c,int f=-1)
{
	esp_order(&x1,&x2);
	esp_order(&y1,&y2);
	int wx= x2-x1;
	int wy= y2-y1;
	ESP_Line(x1,y1,x2,y1,c);
	ESP_Line(x2,y1,x2,y2,c);
	ESP_Line(x2,y2,x1,y2,c);
	ESP_Line(x1,y2,x1,y1,c);

	if(wx<2||wy<2) return;

	if(f<0) f= c;
	wy--;
	while(wy--){
		y1++;
		ESP_Line(x1+1,y1,x2-1,y1,f);
	}
}

// 7.0
void ESP_BoxFillXOR(int x1,int y1,int x2,int y2)
{
	esp_order(&x1,&x2);
	esp_order(&y1,&y2);
	for(int y=y1;y<=y2;y++){
		ESP_LineXOR(x1,y,x2,y);
	}
}

#define ESP_PI 3.1415926535897932384626433
#define DEG2RAD(deg) ((deg)*ESP_PI/180.0)
#define RAD2DEG(rad) ((rad)*180.0/ESP_PI)

void esp_set4arc(int x0,int y0,int r,double th1,double th2,int *x1,int *y1,int *x2,int *y2,int *flag,int *flag0,int *flag1,int *flag2,int *flag3)
{
	*flag0=0x00ff00;
	*flag1=0x000080;
	*flag2=0x00ff00;
	*flag3=0x010000;

	*x1=x0+(int)((double)r*cos(th1));
	*y1=y0-(int)((double)r*sin(th1));
	*x2=x0+(int)((double)r*cos(th2));
	*y2=y0-(int)((double)r*sin(th2));

	if(th1>(0.0*ESP_PI/4.0)) *flag0<<=1, *flag1<<=1;
	if(th1>(1.0*ESP_PI/4.0)) *flag0<<=1, *flag1<<=1; 
	if(th1>(2.0*ESP_PI/4.0)) *flag0<<=1, *flag1<<=1; 
	if(th1>(3.0*ESP_PI/4.0)) *flag0<<=1, *flag1<<=1; 
	if(th1>(4.0*ESP_PI/4.0)) *flag0<<=1, *flag1<<=1; 
	if(th1>(5.0*ESP_PI/4.0)) *flag0<<=1, *flag1<<=1; 
	if(th1>(6.0*ESP_PI/4.0)) *flag0<<=1, *flag1<<=1; 
	if(th1>(7.0*ESP_PI/4.0)) *flag0<<=1, *flag1<<=1; 

	if(th2<(8.0*ESP_PI/4.0)) *flag2>>=1, *flag3>>=1; 
	if(th2<(7.0*ESP_PI/4.0)) *flag2>>=1, *flag3>>=1; 
	if(th2<(6.0*ESP_PI/4.0)) *flag2>>=1, *flag3>>=1; 
	if(th2<(5.0*ESP_PI/4.0)) *flag2>>=1, *flag3>>=1; 
	if(th2<(4.0*ESP_PI/4.0)) *flag2>>=1, *flag3>>=1; 
	if(th2<(3.0*ESP_PI/4.0)) *flag2>>=1, *flag3>>=1; 
	if(th2<(2.0*ESP_PI/4.0)) *flag2>>=1, *flag3>>=1; 
	if(th2<(1.0*ESP_PI/4.0)) *flag2>>=1, *flag3>>=1; 
	
	if(th1<=th2)*flag=(*flag0 & *flag2);
	else *flag=(*flag0 | *flag2);
	*flag>>=8;
	*flag1>>=8;
	*flag3>>=8;
}

// 7.0
void ESP_Arc(int x0,int y0,int r,int c,double th1,double th2)
{
	int x1,y1,x2,y2;
	int flag,flag0,flag1,flag2,flag3;
	esp_set4arc(x0,y0,r,th1,th2,&x1,&y1,&x2,&y2,&flag,&flag0,&flag1,&flag2,&flag3);

	int rsqr2=(r*5)/7;
	int s=r;
	int cx=0;

	if(flag1==flag3 && th1<=th2)goto arcloop2;
arcloop:
	if(flag&32 || (flag1&32 && x0-cx>=x1) || (flag3&32 && x0-cx<=x2))ESP_Pset(x0-cx,y0+r,c);
	if(flag&2 || (flag1&2 && x0+cx<=x1) || (flag3&2 && x0+cx>=x2))ESP_Pset(x0+cx,y0-r,c);
	
	if(cx &&cx!=r){
		if(flag&64 || (flag1&64 && x0+cx>=x1) || (flag3&64 && x0+cx<=x2))ESP_Pset(x0+cx,y0+r,c);
		if(flag&4 || (flag1&4 && x0-cx<=x1) || (flag3&4 && x0-cx>=x2))ESP_Pset(x0-cx,y0-r,c);
		if(flag&1 || (flag1&1 && y0-cx<=y1) || (flag3&1 && y0-cx>=y2))ESP_Pset(x0+r,y0-cx,c);
		if(flag&16 || (flag1&16 && y0+cx>=y1) || (flag3&16 && y0+cx<=y2))ESP_Pset(x0-r,y0+cx,c);
	}
	
	if(flag&128 || (flag1&128 && y0+cx<=y1) || (flag3&128 && y0+cx>=y2))ESP_Pset(x0+r,y0+cx,c);
	if(flag&8 || (flag1&8 && y0-cx>=y1) || (flag3&8 && y0-cx<=y2))ESP_Pset(x0-r,y0-cx,c);

	s-=cx*2+1;
	if(s<=0){s+=r*2-2;r--;}
	cx++;
	if(cx>rsqr2) return;
	if(cx>r) return;
	goto arcloop;

arcloop2:
	if(flag&32 || (flag1&32 && x0-cx>=x1) && (flag3&32 && x0-cx<=x2))ESP_Pset(x0-cx,y0+r,c);
	if(flag&2 || (flag1&2 && x0+cx<=x1) && (flag3&2 && x0+cx>=x2))ESP_Pset(x0+cx,y0-r,c);
	
	if(cx &&cx!=r){
		if(flag&64 || (flag1&64 && x0+cx>=x1) && (flag3&64 && x0+cx<=x2))ESP_Pset(x0+cx,y0+r,c);
		if(flag&4 || (flag1&4 && x0-cx<=x1) && (flag3&4 && x0-cx>=x2))ESP_Pset(x0-cx,y0-r,c);
		if(flag&1 || (flag1&1 && y0-cx<=y1) && (flag3&1 && y0-cx>=y2))ESP_Pset(x0+r,y0-cx,c);
		if(flag&16 || (flag1&16 && y0+cx>=y1) && (flag3&16 && y0+cx<=y2))ESP_Pset(x0-r,y0+cx,c);
	}
	
	if(flag&128 || (flag1&128 && y0+cx<=y1) && (flag3&128 && y0+cx>=y2))ESP_Pset(x0+r,y0+cx,c);
	if(flag&8 || (flag1&8 && y0-cx>=y1) && (flag3&8 && y0-cx<=y2))ESP_Pset(x0-r,y0-cx,c);

	s-=cx*2+1;
	if(s<=0){s+=r*2-2;r--;}
	cx++;
	if(cx>rsqr2) return;
	if(cx>r) return;
	goto arcloop2;
}

void ESP_ArcXOR(int x0,int y0,int r,double th1,double th2)
{
	int x1,y1,x2,y2;
	int flag,flag0,flag1,flag2,flag3;
	esp_set4arc(x0,y0,r,th1,th2,&x1,&y1,&x2,&y2,&flag,&flag0,&flag1,&flag2,&flag3);

	int rsqr2=(r*5)/7;
	int s=r;
	int cx=0;

	if(flag1==flag3 && th1<=th2)goto arcxloop2;
arcxloop:
	if(flag&32 || (flag1&32 && x0-cx>=x1) || (flag3&32 && x0-cx<=x2))ESP_PsetXOR(x0-cx,y0+r);
	if(flag&2 || (flag1&2 && x0+cx<=x1) || (flag3&2 && x0+cx>=x2))ESP_PsetXOR(x0+cx,y0-r);
	
	if(cx &&cx!=r){
		if(flag&64 || (flag1&64 && x0+cx>=x1) || (flag3&64 && x0+cx<=x2))ESP_PsetXOR(x0+cx,y0+r);
		if(flag&4 || (flag1&4 && x0-cx<=x1) || (flag3&4 && x0-cx>=x2))ESP_PsetXOR(x0-cx,y0-r);
		if(flag&1 || (flag1&1 && y0-cx<=y1) || (flag3&1 && y0-cx>=y2))ESP_PsetXOR(x0+r,y0-cx);
		if(flag&16 || (flag1&16 && y0+cx>=y1) || (flag3&16 && y0+cx<=y2))ESP_PsetXOR(x0-r,y0+cx);
	}
	
	if(flag&128 || (flag1&128 && y0+cx<=y1) || (flag3&128 && y0+cx>=y2))ESP_PsetXOR(x0+r,y0+cx);
	if(flag&8 || (flag1&8 && y0-cx>=y1) || (flag3&8 && y0-cx<=y2))ESP_PsetXOR(x0-r,y0-cx);

	s-=cx*2+1;
	if(s<=0){s+=r*2-2;r--;}
	cx++;
	if(cx>rsqr2) return;
	if(cx>r) return;
	goto arcxloop;

arcxloop2:
	if(flag&32 || (flag1&32 && x0-cx>=x1) && (flag3&32 && x0-cx<=x2))ESP_PsetXOR(x0-cx,y0+r);
	if(flag&2 || (flag1&2 && x0+cx<=x1) && (flag3&2 && x0+cx>=x2))ESP_PsetXOR(x0+cx,y0-r);
	
	if(cx &&cx!=r){
		if(flag&64 || (flag1&64 && x0+cx>=x1) && (flag3&64 && x0+cx<=x2))ESP_PsetXOR(x0+cx,y0+r);
		if(flag&4 || (flag1&4 && x0-cx<=x1) && (flag3&4 && x0-cx>=x2))ESP_PsetXOR(x0-cx,y0-r);
		if(flag&1 || (flag1&1 && y0-cx<=y1) && (flag3&1 && y0-cx>=y2))ESP_PsetXOR(x0+r,y0-cx);
		if(flag&16 || (flag1&16 && y0+cx>=y1) && (flag3&16 && y0+cx<=y2))ESP_PsetXOR(x0-r,y0+cx);
	}
	
	if(flag&128 || (flag1&128 && y0+cx<=y1) && (flag3&128 && y0+cx>=y2))ESP_PsetXOR(x0+r,y0+cx);
	if(flag&8 || (flag1&8 && y0-cx>=y1) && (flag3&8 && y0-cx<=y2))ESP_PsetXOR(x0-r,y0-cx);

	s-=cx*2+1;
	if(s<=0){s+=r*2-2;r--;}
	cx++;
	if(cx>rsqr2) return;
	if(cx>r) return;
	goto arcxloop2;
}

// 7.0
int ESP_CheckArc(int x0,int y0,int r,int c,double th1,double th2)
{
	int x1,y1,x2,y2;
	int flag,flag0,flag1,flag2,flag3;
	esp_set4arc(x0,y0,r,th1,th2,&x1,&y1,&x2,&y2,&flag,&flag0,&flag1,&flag2,&flag3);

	int rsqr2=(r*5)/7;
	int s=r;
	int cx=0;

	if(flag1==flag3 && th1<=th2)goto chkarcloop2;
chkarcloop:
	if(flag&32 || (flag1&32 && x0-cx>=x1) || (flag3&32 && x0-cx<=x2))if(_ESP_Point(x0-cx,y0+r)==c) return 1;
	if(flag&2 || (flag1&2 && x0+cx<=x1) || (flag3&2 && x0+cx>=x2))if(_ESP_Point(x0+cx,y0-r)==c) return 1;
	
	if(cx &&cx!=r){
		if(flag&64 || (flag1&64 && x0+cx>=x1) || (flag3&64 && x0+cx<=x2))if(_ESP_Point(x0+cx,y0+r)==c) return 1;
		if(flag&4 || (flag1&4 && x0-cx<=x1) || (flag3&4 && x0-cx>=x2))if(_ESP_Point(x0-cx,y0-r)==c) return 1;
		if(flag&1 || (flag1&1 && y0-cx<=y1) || (flag3&1 && y0-cx>=y2))if(_ESP_Point(x0+r,y0-cx)==c) return 1;
		if(flag&16 || (flag1&16 && y0+cx>=y1) || (flag3&16 && y0+cx<=y2))if(_ESP_Point(x0-r,y0+cx)==c) return 1;
	}
	
	if(flag&128 || (flag1&128 && y0+cx<=y1) || (flag3&128 && y0+cx>=y2))if(_ESP_Point(x0+r,y0+cx)==c) return 1;
	if(flag&8 || (flag1&8 && y0-cx>=y1) || (flag3&8 && y0-cx<=y2))if(_ESP_Point(x0-r,y0-cx)==c) return 1;

	s-=cx*2+1;
	if(s<=0){s+=r*2-2;r--;}
	cx++;
	if(cx>rsqr2) return 0;
	if(cx>r) return 0;
	goto chkarcloop;

chkarcloop2:
	if(flag&32 || (flag1&32 && x0-cx>=x1) && (flag3&32 && x0-cx<=x2))if(_ESP_Point(x0-cx,y0+r)==c) return 1;
	if(flag&2 || (flag1&2 && x0+cx<=x1) && (flag3&2 && x0+cx>=x2))if(_ESP_Point(x0+cx,y0-r)==c) return 1;
	
	if(cx &&cx!=r){
		if(flag&64 || (flag1&64 && x0+cx>=x1) && (flag3&64 && x0+cx<=x2))if(_ESP_Point(x0+cx,y0+r)==c) return 1;
		if(flag&4 || (flag1&4 && x0-cx<=x1) && (flag3&4 && x0-cx>=x2))if(_ESP_Point(x0-cx,y0-r)==c) return 1;
		if(flag&1 || (flag1&1 && y0-cx<=y1) && (flag3&1 && y0-cx>=y2))if(_ESP_Point(x0+r,y0-cx)==c) return 1;
		if(flag&16 || (flag1&16 && y0+cx>=y1) && (flag3&16 && y0+cx<=y2))if(_ESP_Point(x0-r,y0+cx)==c) return 1;
	}
	
	if(flag&128 || (flag1&128 && y0+cx<=y1) && (flag3&128 && y0+cx>=y2))if(_ESP_Point(x0+r,y0+cx)==c) return 1;
	if(flag&8 || (flag1&8 && y0-cx>=y1) && (flag3&8 && y0-cx<=y2))if(_ESP_Point(x0-r,y0-cx)==c) return 1;

	s-=cx*2+1;
	if(s<=0){s+=r*2-2;r--;}
	cx++;
	if(cx>rsqr2) return 0;
	if(cx>r) return 0;
	goto chkarcloop2;
}

// 7.0
int ESP_CheckCircle(int x0,int y0,int r,int c)
{
	int rsqr2=(r*5)/7;
	int s=r;
	int cx=0;

	chkcircleloop:
	if(_ESP_Point(x0-cx,y0+r)==c) return 1;
	if(_ESP_Point(x0+cx,y0-r)==c) return 1;
	if(cx &&cx!=r){
		if(_ESP_Point(x0+cx,y0+r)==c) return 1;
		if(_ESP_Point(x0-cx,y0-r)==c) return 1;
		if(_ESP_Point(x0+r,y0-cx)==c) return 1;
		if(_ESP_Point(x0-r,y0+cx)==c) return 1;
	}
	if(_ESP_Point(x0+r,y0+cx)==c) return 1;
	if(_ESP_Point(x0-r,y0-cx)==c) return 1;

	s-=cx*2+1;
	if(s<=0){s+=r*2-2;r--;}
	cx++;
	if(cx>rsqr2) return 0;
	if(cx>r) return 0;
	goto chkcircleloop;
}

// 7.0
void ESP_Circle(int x0,int y0,int r,int c)
{
	int rsqr2=(r*5)/7;
	int s=r;
	int cx=0;

	circleloop:
	ESP_Pset(x0-cx,y0+r,c);
	ESP_Pset(x0+cx,y0-r,c);
	if(cx &&cx!=r){
		ESP_Pset(x0+cx,y0+r,c);
		ESP_Pset(x0-cx,y0-r,c);
		ESP_Pset(x0+r,y0-cx,c);
		ESP_Pset(x0-r,y0+cx,c);
	}
	ESP_Pset(x0+r,y0+cx,c);
	ESP_Pset(x0-r,y0-cx,c);

	s-=cx*2+1;
	if(s<=0){s+=r*2-2;r--;}
	cx++;
	if(cx>rsqr2) return;
	if(cx>r) return;
	goto circleloop;
}

// 7.0
void ESP_CircleXOR(int x0,int y0,int r)
{
	int rsqr2=(r*5)/7;
	int s=r;
	int cx=0;

	circlexloop:
	ESP_PsetXOR(x0-cx,y0+r);
	ESP_PsetXOR(x0+cx,y0-r);
	if(cx &&cx!=r){
		ESP_PsetXOR(x0+cx,y0+r);
		ESP_PsetXOR(x0-cx,y0-r);
		ESP_PsetXOR(x0+r,y0-cx);
		ESP_PsetXOR(x0-r,y0+cx);
	}
	ESP_PsetXOR(x0+r,y0+cx);
	ESP_PsetXOR(x0-r,y0-cx);

	s-=cx*2+1;
	if(s<=0){s+=r*2-2;r--;}
	cx++;
	if(cx>rsqr2) return;
	if(cx>r) return;
	goto circlexloop;
}

//v8.2(f省略時はcと同じ色で)
void ESP_CircleFill(int x0,int y0,int r,int c,int f=-1)
{
	if(f<0) f= c;
	int rsqr2=(r*5)/7;
	int s,r0;
	r0=s=r;
	int cx=0;

	int rf;

	for(;;){
		rf=1;
		if(r!=cx)ESP_Line(x0-r,y0+cx,x0+r,y0+cx,f);
		if(r!=cx && cx)ESP_Line(x0-r,y0-cx,x0+r,y0-cx,f);
		s-=cx*2+1;
		if(s<=0){
			if(rf){
				ESP_Line(x0-cx,y0+r,x0+cx,y0+r,f);
				ESP_Line(x0-cx,y0-r,x0+cx,y0-r,f);
				rf=0;
			}
			s+=r*2-2;r--;
		}
		cx++;
		if(cx>rsqr2) break;
		if(cx>r) break;
	}
	cx--;
	if(rf){
		ESP_Line(x0-cx,y0+r,x0+cx,y0+r,f);
		ESP_Line(x0-cx,y0-r,x0+cx,y0-r,f);
	}
	ESP_Circle(x0,y0,r0,c);
}

// 7.0
void ESP_CircleFillXOR(int x0,int y0,int r)
{
	int rsqr2=(r*5)/7;
	int s=r;
	int cx=0;

	int rf;

	for(;;){
		rf=1;
		if(r!=cx)ESP_LineXOR(x0-r,y0+cx,x0+r,y0+cx);
		if(r!=cx && cx)ESP_LineXOR(x0-r,y0-cx,x0+r,y0-cx);
		s-=cx*2+1;
		if(s<=0){
			if(rf){
				ESP_LineXOR(x0-cx,y0+r,x0+cx,y0+r);
				ESP_LineXOR(x0-cx,y0-r,x0+cx,y0-r);
				rf=0;
			}
			s+=r*2-2;r--;
		}
		cx++;
		if(cx>rsqr2) break;
		if(cx>r) break;
	}
	cx--;
	if(rf){
		ESP_LineXOR(x0-cx,y0+r,x0+cx,y0+r);
		ESP_LineXOR(x0-cx,y0-r,x0+cx,y0-r);
	}
}
// type ... ESP_R/G/B/H/S/V/Y/Cr/Cb/L , ESP_DOT, ESP_LINE  7.0
void ESP_GraphLine(void *buf,int x0,int y0,int wx,int wy,int type,int c)
{
	int *p=(int *)buf;
	unsigned char *ucp=(unsigned char *)buf;

	int ymax=255;

	for(int i=0;i<wx;i++){
		int e;
		     if(type&ESP_R) e=C2R(p[i]);
		else if(type&ESP_G) e=C2G(p[i]);
		else if(type&ESP_B) e=C2B(p[i]);
		else if(type&ESP_H){e=C2H(p[i]);ymax=359;}
		else if(type&ESP_S) e=C2S(p[i]);
		else if(type&ESP_V) e=C2V(p[i]);
		else if(type&ESP_Y) e=C2Y(p[i]);
		else if(type&ESP_Cr)e=C2Cr(p[i])+128;
		else if(type&ESP_Cb)e=C2Cb(p[i])+128;
		else if(type&ESP_L) e=ucp[i];
		
		int x=x0+i;
		int y=y0+wy-1-e*(wy-1)/ymax;
		if(type&ESP_DOT){
			ESP_Pset(x,y,c);
		}else if(type&ESP_LINE){
			if(i==0){
				ESP_Pset(x,y,c);
			}else{
				ESP_LineTo(x,y,c);
			}
		}
	}
}

// type ... ESP_CrCb , ESP_DOT, ESP_LINE   7.0
// scan Line
void ESP_GraphXYL(int *buff,int w,int x0,int y0,int wx,int wy,int type,int c)
{
	x0=(x0+wx)/2;
	y0=(y0+wy)/2;
	ESP_Line(x0-wx/2,y0,x0+wx/2,y0,0x808080);
	ESP_Line(x0,y0-wy/2,x0,y0+wy/2,0x808080);
	ESP_Glocate(x0-18,16);ESP_Gtextcolor(0xff8888);ESP_Gputs("Cr");
	ESP_Glocate(wx-18,y0+16);ESP_Gtextcolor(0x8888ff);ESP_Gputs("Cb");
	for(int i=0;i<w;i++){
		int e=0, f=0;
		if(type&ESP_CrCb){
			e=C2Cb(buff[i]);
			f=-C2Cr(buff[i]);
		}
		int x=x0+e*wx/256;
		int y=y0+f*wy/256;

		if(type&ESP_DOT){
			ESP_Pset(x,y,c);
		}else if(type&ESP_LINE){
			if(i==0){
				ESP_Pset(x,y,c);
			}else{
				ESP_LineTo(x,y,c);
			}
		}
		c^=0x00ff00;
	}
}

// type ... ESP_CrCb , ESP_DOT, ESP_LINE    7.0
// scan Window
void ESP_GraphXYW(int *buff,int w,int h,int x0,int y0,int wx,int wy,int type,int c)
{
	x0=(x0+wx)/2;
	y0=(y0+wy)/2;
	ESP_Line(x0-wx/2,y0,x0+wx/2,y0,0x808080);
	ESP_Line(x0,y0-wy/2,x0,y0+wy/2,0x808080);
	ESP_Glocate(x0-18,16);ESP_Gtextcolor(0xff8888);ESP_Gputs("Cr");
	ESP_Glocate(wx-18,y0+16);ESP_Gtextcolor(0x8888ff);ESP_Gputs("Cb");

	for(int j=0;j<h;j++){
	for(int i=0;i<w;i++){
		int e=0,f=0;
		if(type&ESP_CrCb){
			e=C2Cb(buff[i+w*j]);
			f=-C2Cr(buff[i+w*j]);
		}
		int x=x0+e*wx/256;
		int y=y0+f*wy/256;

		if(type&ESP_DOT){
			ESP_Pset(x,y,c);
		}else if(type&ESP_LINE){
			if(i==0){
				ESP_Pset(x,y,c);
			}else{
				ESP_LineTo(x,y,c);
			}
		}
	}
	}
}

// 7.0
void ESP_GetLine(void *buf,int x0,int y0,int wx)
{
	if((unsigned int)esp_i>=ESP_IW_MAX) return;
	if(!esp_iw[esp_i].show) return;

	unsigned int mx=esp_iw[esp_i].wx;
	unsigned int my=esp_iw[esp_i].wy;

	if(esp_iw[esp_i].bit==32){
		//32bit
		int *ip=(int *)buf;
		int x,y;
		y=y0;
		for(int i=0;i<wx;i++){
			x=x0+i;
			if((unsigned int)x>=mx || (unsigned int)y>=my)ip[i]=0;
			else ip[i]=*ESPPTR;
		}
	}else{
		//8bit
		unsigned char *ucp=(unsigned char *)buf;
		int x,y;
		y=y0;
		for(int i=0;i<wx;i++){
			x=x0+i;
			if((unsigned int)x>=mx || (unsigned int)y>=my)ucp[i]=0;
			else ucp[i]=*ESPPTR8;
		}
	}
}

// 7.0
void ESP_PutLine(int *buf,int x0,int y0,int wx)
{
	if((unsigned int)esp_i>=ESP_IW_MAX) return;
	if(!esp_iw[esp_i].show) return;

	unsigned int mx=esp_iw[esp_i].wx;
	unsigned int my=esp_iw[esp_i].wy;

	if(esp_iw[esp_i].bit==32){
		//32bit
		int *ip=(int *)buf;
		int x,y;
		y=y0;
		for(int i=0;i<wx;i++){
			x=x0+i;
			if((unsigned int)x>=mx || (unsigned int)y>=my);
			else *ESPPTR=ip[i];
		}
	}else{
		//8bit
		unsigned char *ucp=(unsigned char *)buf;
		int x,y;
		y=y0;
		for(int i=0;i<wx;i++){
			x=x0+i;
			if((unsigned int)x>=mx || (unsigned int)y>=my);
			else *ESPPTR8=ucp[i];
		}
	}
}

//テストパターンの描画

// 7.0
void ESP_TestPat_RGB(void)
{
	if(!esp_iw[esp_i].show) return;

	for(int y=0;y<esp_iw[esp_i].wy;y++){
		for(int x=0;x<esp_iw[esp_i].wx;x++){
			int r=x*255/esp_iw[esp_i].wx;
			int g=y*255/esp_iw[esp_i].wy;
			int b=(x+y)*255/(esp_iw[esp_i].wx+esp_iw[esp_i].wy);
			b=255-b;
			ESP_Pset(x,y,RGB2C(r,g,b));
		}
	}
}

// 7.0
void ESP_TestPat_Grey(void)
{
	if(esp_iw[esp_i].bit==8){
		//8bit
		int rgb[256];
		for(int i=0;i<256;i++){
			rgb[i]=RGB2C(i,i,i);
		}
		ESP_SetColorTable(rgb);
	}

	for(int x=0;x<esp_iw[esp_i].wx;x++){
		int c=255*x/esp_iw[esp_i].wx;
		int c1=RGB2C(c,c,c);
		c=255-c;
		int c2=RGB2C(c,c,c);
		ESP_Line(x,0,x,esp_iw[esp_i].wy/2-1,c1);
		ESP_Line(x,esp_iw[esp_i].wy/2,x,esp_iw[esp_i].wy-1,c2);
	}
}

// 7.0
void ESP_TestPat_HSV(void)
{
	if(!esp_iw[esp_i].show) return;

	for(int y=0;y<esp_iw[esp_i].wy;y++){
		for(int x=0;x<esp_iw[esp_i].wx;x++){
			int h,s,v;
			h=x*359/esp_iw[esp_i].wx;
			if(y<esp_iw[esp_i].wy/2){
				s=y*255/(esp_iw[esp_i].wy/2);
			}else{
				s=255;
			}
			if(y<esp_iw[esp_i].wy/2){
				v=255;
			}else{
				v=(y-esp_iw[esp_i].wy/2)*255/(esp_iw[esp_i].wy/2);
				v=255-v;
			}
			ESP_Pset(x,y,HSV2C(h,s,v));
		}
	}
}

// 7.0
void ESP_TestPat_CrCb(void)
{
	if(!esp_iw[esp_i].show) return;

	for(int y=0;y<esp_iw[esp_i].wy;y++){
		for(int x=0;x<esp_iw[esp_i].wx;x++){
			int ii=(x-esp_iw[esp_i].wx/2)*255/esp_iw[esp_i].wx;
			int jj=(y-esp_iw[esp_i].wy/2)*255/esp_iw[esp_i].wy;
			int Y=(int)sqrt(5.0*(double)(ii*ii)+5.0*(double)(jj*jj));
			int cr=-jj;
			int cb=ii;
			ESP_Pset(x,y,YCrCb2C(Y,cr,cb));
		}
	}
}

// 7.0
void ESP_TestPat_uv(void)
{
	if(!esp_iw[esp_i].show) return;

	for(int y=0;y<esp_iw[esp_i].wy;y++){
		for(int x=0;x<esp_iw[esp_i].wx;x++){
			int ii=(x-esp_iw[esp_i].wx/2)*255/esp_iw[esp_i].wx;
			int jj=(y-esp_iw[esp_i].wy/2)*255/esp_iw[esp_i].wy;
			int Y=(int)sqrt(5.0*(double)(ii*ii)+5.0*(double)(jj*jj));
			int v=-jj;
			int u=ii;
			ESP_Pset(x,y,Yuv2C(Y,u,v));
		}
	}
}

// 7.0
void ESP_TestPat_IQ(void)
{
	if(!esp_iw[esp_i].show) return;

	for(int y=0;y<esp_iw[esp_i].wy;y++){
		for(int x=0;x<esp_iw[esp_i].wx;x++){
			int ii=(x-esp_iw[esp_i].wx/2)*255/esp_iw[esp_i].wx;
			int jj=(y-esp_iw[esp_i].wy/2)*255/esp_iw[esp_i].wy;
			int Y=(int)sqrt(5.0*(double)(ii*ii)+5.0*(double)(jj*jj));
			int I=-jj;
			int Q=ii;
			ESP_Pset(x,y,YIQ2C(Y,I,Q));
		}
	}
}

//------------マウスによる座標入力関数----------------

//共通関数（開始）
void esp_get_begin(int i)
{
	DragAcceptFiles(esp_mw_hwnd,FALSE);
	ESP_Select(i);
	ESP_MLF=0;
	esp_STOP=0;
	esp_getting=i;
	esp_mousegetting=1;
}

//共通関数（終了）
void esp_get_end(void)
{
	esp_disp_color_mode();
	esp_mousegetting=0;
	esp_getting=-1;
	DragAcceptFiles(esp_mw_hwnd,TRUE);
}

// マウスのシングルクリックを２回要求し，座標を得る
// 選択中は反転ボックスを表示する
int ESP_GetRect(int i,int *x1,int *y1,int *x2,int *y2)
{
	if(esp_iw_check(i)) return 2;

	*x1=*y1=*x2=*y2=0;
	esp_status("Click the first point");
	esp_get_begin(i);

	int rtn=0;
	int s=0;	//state

	while(!ESP_STOP){
		if(s==2) break;
		if(ESP_MLF && s==0){
			ESP_MLF=0;
			s=1;
			*x1 = *x2 = ESP_MLX;
			*y1 = *y2 = ESP_MLY;
			ESP_BoxXOR(*x1,*y1,*x2,*y2);
			esp_invalid(esp_i);
			esp_status("Click the second point");
		}
		if(ESP_MLF && s==1){
			ESP_MLF=0;
			s=2;
			ESP_BoxXOR(*x1,*y1,*x2,*y2);
			esp_invalid(esp_i);
			*x2=ESP_MLX;
			*y2=ESP_MLY;
			esp_order(x1,x2);
			esp_order(y1,y2);
		}
		if(ESP_MRF && s==0){
			ESP_MRF=0;
			rtn=1;
			break;
		}
		if(ESP_MRF && s==1){
			ESP_MRF=0;
			s=0;
			ESP_BoxXOR(*x1,*y1,*x2,*y2);
			esp_invalid(esp_i);
			esp_status("Click the first point");
		}
		if(ESP_MMF && s==1){
			ESP_MMF=0;
			ESP_BoxXOR(*x1,*y1,*x2,*y2);
			*x2=ESP_MMX;
			*y2=ESP_MMY;
			ESP_BoxXOR(*x1,*y1,*x2,*y2);
			esp_invalid(esp_i);
		}
	}
	esp_get_end();
	return rtn;
}

// マウスのシングルクリックを２回要求し，座標を得る
// 選択中は反転ラインを表示する
int ESP_GetRectL(int i,int *x1,int *y1,int *x2,int *y2)
{
	if(esp_iw_check(i)) return 2;

	*x1=*y1=*x2=*y2=0;
	esp_status("Click the first point");
	esp_get_begin(i);

	int rtn=0;
	int s=0;	//state

	while(!ESP_STOP){
		if(s==2) break;
		if(ESP_MLF && s==0){
			ESP_MLF=0;
			s=1;
			*x1 = *x2 = ESP_MLX;
			*y1 = *y2 = ESP_MLY;
			ESP_LineXOR(*x1,*y1,*x2,*y2);
			esp_invalid(esp_i);
			esp_status("Click the second point");
		}
		if(ESP_MLF && s==1){
			ESP_MLF=0;
			s=2;
			ESP_LineXOR(*x1,*y1,*x2,*y2);
			esp_invalid(esp_i);
			*x2=ESP_MLX;
			*y2=ESP_MLY;
		}
		if(ESP_MRF && s==0){
			ESP_MRF=0;
			rtn=1;
			break;
		}
		if(ESP_MRF && s==1){
			ESP_MRF=0;
			s=0;
			ESP_LineXOR(*x1,*y1,*x2,*y2);
			esp_invalid(esp_i);
			esp_status("Click the first point");
		}
		if(s==1){
			if(ESP_MMF){
				ESP_MMF=0;
				ESP_LineXOR(*x1,*y1,*x2,*y2);
				*x2=ESP_MMX;
				*y2=ESP_MMY;
				ESP_LineXOR(*x1,*y1,*x2,*y2);
				esp_invalid(esp_i);
			}
		}
	}
	esp_get_end();
	return rtn;
}

// マウスのシングルクリックを１回要求し，座標を得る 7.0
// 選択中は反転ラインを表示する
// 第１点目はx1,y1で与える
int ESP_GetRectL2(int i,int x1,int y1,int *x2,int *y2)
{
	if(esp_iw_check(i)) return 2;

	*x2=*y2=0;
	esp_status("Click a point");
	esp_get_begin(i);

	*x2=x1;
	*y2=y1;
	ESP_LineXOR(x1,y1,*x2,*y2);
	esp_invalid(esp_i);

	int rtn=0;
	int s=1;	//state
	
	while(!ESP_STOP){
		if(s==2) break;
		if(ESP_MLF && s==1){
			ESP_MLF=0;
			s=2;
			ESP_LineXOR(x1,y1,*x2,*y2);
			esp_invalid(esp_i);
			*x2=ESP_MLX;
			*y2=ESP_MLY;
		}
		if(ESP_MRF && s==1){
			ESP_MRF=0;
			ESP_LineXOR(x1,y1,*x2,*y2);
			esp_invalid(esp_i);
			rtn=1;
			break;
		}
		if(s==1){
			if(ESP_MMF){
				ESP_MMF=0;
				ESP_LineXOR(x1,y1,*x2,*y2);
				*x2=ESP_MMX;
				*y2=ESP_MMY;
				ESP_LineXOR(x1,y1,*x2,*y2);
				esp_invalid(esp_i);
			}
		}
	}
	esp_get_end();
	return rtn;
}

// マウスのシングルクリックを２回要求し，座標と半径を得る
// 選択中は反転サークルを表示する
int ESP_GetRectC(int i,int *x1,int *y1,int *r)
{
	if(esp_iw_check(i)) return 2;

	*x1=*y1=*r=0;
	esp_status("Click the first point");
	esp_get_begin(i);

	int rtn=0;
	int s=0;	//state

	while(!ESP_STOP){
		if(s==2) break;
		if(ESP_MLF && s==0){
			ESP_MLF=0;
			s=1;
			*x1 = ESP_MLX;
			*y1 = ESP_MLY;
			*r=(int)(sqrt((double)(ESP_MLX - *x1)*(ESP_MLX - *x1)+(ESP_MLY - *y1)*(ESP_MLY - *y1))+0.5);
			ESP_CircleXOR(*x1,*y1,*r);
			esp_invalid(esp_i);
			esp_status("Click the second point");
		}
		if(ESP_MLF && s==1){
			ESP_MLF=0;
			s=2;
			ESP_CircleXOR(*x1,*y1,*r);
			esp_invalid(esp_i);
			*r=(int)(sqrt((double)(ESP_MLX-*x1)*(ESP_MLX-*x1)+(ESP_MLY-*y1)*(ESP_MLY-*y1))+0.5);
		}
		if(ESP_MRF && s==0){
			ESP_MRF=0;
			rtn=1;
			break;
		}
		if(ESP_MRF && s==1){
			ESP_MRF=0;
			s=0;
			ESP_CircleXOR(*x1,*y1,*r);
			esp_invalid(esp_i);
			esp_status("Click the first point");
		}
		if(s==1){
			if(ESP_MMF){
				ESP_MMF=0;
				ESP_CircleXOR(*x1,*y1,*r);
				*r=(int)(sqrt((double)(ESP_MMX - *x1)*(ESP_MMX - *x1)+(ESP_MMY - *y1)*(ESP_MMY - *y1))+0.5);
				ESP_CircleXOR(*x1,*y1,*r);
				esp_invalid(esp_i);
			}
		}
	}
	esp_get_end();
	return rtn;
}

// マウスのシングルクリックを要求し，座標を得る 7.0
// 選択中は何も表示しない
int ESP_GetPoint(int i,int *x,int *y)
{
	if(esp_iw_check(i)) return 2;

	*x=*y=0;
	esp_status("Click a point");
	esp_get_begin(i);

	int rtn=0;
	int s=0;	//state

	while(!ESP_STOP){
		if(s==1) break;
		if(ESP_MLF && s==0){
			ESP_MLF=0;
			s=1;
			*x = ESP_MLX;
			*y = ESP_MLY;
		}
		if(ESP_MRF && s==0){
			ESP_MRF=0;
			rtn=1;
			break;
		}
	}
	esp_get_end();
	return rtn;
}

// マウスのシングルクリックを要求し，座標を得る 7.0
// 選択中は反転水平ラインを表示する
int ESP_GetPointH(int i,int *x,int *y)
{
	if(esp_iw_check(i)) return 2;

	*x=*y=0;
	esp_status("Click a point");
	esp_get_begin(i);

	int yy=ESP_MMY;
	ESP_LineXOR(0,yy,esp_iw[i].wx-1,yy);
	esp_invalid(esp_i);

	int rtn=0;
	int s=0;	//state

	while(!ESP_STOP){
		if(s==1) break;
		if(ESP_MMF){
			ESP_MMF=0;
			ESP_LineXOR(0,yy,esp_iw[i].wx-1,yy);
			yy=ESP_MMY;
			ESP_LineXOR(0,yy,esp_iw[i].wx-1,yy);
			esp_invalid(esp_i);
		}
		if(ESP_MLF){
			ESP_MLF=0;
			ESP_LineXOR(0,yy,esp_iw[i].wx-1,yy);
			esp_invalid(esp_i);
			s=1;
			*x = ESP_MLX;
			*y = ESP_MLY;
		}
		if(ESP_MRF && s==0){
			ESP_MRF=0;
			ESP_LineXOR(0,yy,esp_iw[i].wx-1,yy);
			esp_invalid(esp_i);
			rtn=1;
			break;
		}
	}
	esp_get_end();
	return rtn;
}

// マウスのシングルクリックを要求し，座標を得る
// 選択中は反転垂直ラインを表示する 7.0
int ESP_GetPointV(int i,int *x,int *y)
{
	if(esp_iw_check(i)) return 2;

	*x=*y=0;
	esp_status("Click a point");
	esp_get_begin(i);

	int xx=ESP_MMX;
	ESP_LineXOR(xx,0,xx,esp_iw[i].wy-1);
	esp_invalid(esp_i);

	int rtn=0;
	int s=0;	//state

	while(!ESP_STOP){
		if(s==1) break;
		if(ESP_MMF){
			ESP_MMF=0;
			ESP_LineXOR(xx,0,xx,esp_iw[i].wy-1);
			xx=ESP_MMX;
			ESP_LineXOR(xx,0,xx,esp_iw[i].wy-1);
			esp_invalid(esp_i);
		}
		if(ESP_MLF){
			ESP_MLF=0;
			ESP_LineXOR(xx,0,xx,esp_iw[i].wy-1);
			esp_invalid(esp_i);
			s=1;
			*x = ESP_MLX;
			*y = ESP_MLY;
		}
		if(ESP_MRF && s==0){
			ESP_MRF=0;
			ESP_LineXOR(xx,0,xx,esp_iw[i].wy-1);
			esp_invalid(esp_i);
			rtn=1;
			break;
		}
	}
	esp_get_end();
	return rtn;
}

// マウスのシングルクリックを要求し，座標(x,y)を得る
// 選択中は指定サイズ(wx,wy)の反転ボックスを表示する
// wx,wyが８以上なら反転Xラインも表示
int ESP_GetPointR(int i,int *x,int *y,int wx,int wy)
{
	if(esp_iw_check(i)) return 2;

	*x=*y=0;
	esp_status("Click a point");
	esp_get_begin(i);

	int xx=ESP_MMX;
	int yy=ESP_MMY;
	int x1,y1,x2,y2;
	x1=xx-wx/2; y1=yy-wy/2;	x2=x1+wx-1; y2=y1+wy-1;
	ESP_BoxXOR(x1,y1,x2,y2);
	if(wx>8 && wy>8)ESP_LineXOR(x1+1,y1+1,x2-1,y2-1),ESP_LineXOR(x2-1,y1+1,x1+1,y2-1);
	esp_invalid(esp_i);

	int rtn=0;
	int s=0;	//state

	while(!ESP_STOP){
		if(s==1) break;
		if(ESP_MMF){
			ESP_MMF=0;
			ESP_BoxXOR(x1,y1,x2,y2);
			if(wx>8 && wy>8)ESP_LineXOR(x1+1,y1+1,x2-1,y2-1),ESP_LineXOR(x2-1,y1+1,x1+1,y2-1);
			xx=ESP_MMX;
			yy=ESP_MMY;
			x1=xx-wx/2; y1=yy-wy/2; x2=x1+wx-1; y2=y1+wy-1;
			ESP_BoxXOR(x1,y1,x2,y2);
			if(wx>8 && wy>8)ESP_LineXOR(x1+1,y1+1,x2-1,y2-1),ESP_LineXOR(x2-1,y1+1,x1+1,y2-1);
			esp_invalid(esp_i);
		}
		if(ESP_MLF){
			ESP_MLF=0;
			ESP_BoxXOR(x1,y1,x2,y2);
			if(wx>8 && wy>8)ESP_LineXOR(x1+1,y1+1,x2-1,y2-1),ESP_LineXOR(x2-1,y1+1,x1+1,y2-1);
			esp_invalid(esp_i);
			s=1;
			*x = ESP_MLX;
			*y = ESP_MLY;
		}
		if(ESP_MRF && s==0){
			ESP_MRF=0;
			ESP_BoxXOR(x1,y1,x2,y2);
			if(wx>8 && wy>8)ESP_LineXOR(x1+1,y1+1,x2-1,y2-1),ESP_LineXOR(x2-1,y1+1,x1+1,y2-1);
			esp_invalid(esp_i);
			rtn=1;
			break;
		}
	}
	esp_get_end();
	return rtn;
}

//32bit and 8bit  7.0
void esp_copyimage(int i)
{
	if(esp_iw_check(i)) return;

	if (!OpenClipboard(NULL)) return;
	EmptyClipboard();
	
	//画像サイズの計算
	int wx=esp_iw[i].wx;
	int wy=esp_iw[i].wy;
	int pp;
	if(esp_iw[i].bit==32){
		//32bit
		pp=(wx*3+3) & ~3;
	}else{
		//8bit
		pp=(wx+3) & ~3;
	}
	int size=pp*wy;
	
	//メモリ確保
	HGLOBAL hm;
	if(esp_iw[i].bit==32){
		hm=GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE,sizeof(BITMAPINFOHEADER)+size);
	}else{
		hm=GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE,sizeof(BITMAPINFOHEADER)+256*sizeof(RGBQUAD)+size);
	}
	if(!hm){
		ESP_Pause("No enough memory for copy");
		return;
	}
	unsigned char *m = (unsigned char *)GlobalLock(hm);
	BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER *)m;

	//データ格納
	ZeroMemory(pbih,sizeof(BITMAPINFOHEADER));
	pbih->biSize=sizeof(BITMAPINFOHEADER);
	pbih->biWidth=wx;
	pbih->biHeight=wy;
	pbih->biPlanes=1;

	m+=sizeof(BITMAPINFOHEADER);
	if(esp_iw[i].bit==32){
		//32bit
		pbih->biBitCount=24;
	}else{
		//8bit
		pbih->biBitCount=8;
		RGBQUAD *rgb=(RGBQUAD *)m;
		GetDIBColorTable(esp_iw[i].memdc,0,256,rgb);
		m+=256*sizeof(RGBQUAD);
	}
	GetDIBits(esp_iw[i].memdc,esp_iw[i].hbitmap,0,esp_iw[i].wy,m,(BITMAPINFO *)pbih,DIB_RGB_COLORS);

	GlobalUnlock(hm);
	SetClipboardData(CF_DIB,hm);
	CloseClipboard();
}

//選択ＩＷのコピー
void ESP_CopyImage(void)
{
	if((unsigned int)esp_i>=ESP_IW_MAX) return;
	if(!esp_iw[esp_i].show) return;

	esp_copyimage(esp_i);
}

//選択ＩＷのカット
void ESP_CutImage(void)
{
	if((unsigned int)esp_i>=ESP_IW_MAX) return;
	if(!esp_iw[esp_i].show) return;

	esp_copyimage(esp_i);
	esp_clearimage(esp_i);
	esp_invalid(esp_i);
}

// x0=y0=-1のとき，座標はマウス入力 7.0
void esp_pasteimage(int i, int x0, int y0)
{
	if(esp_iw_check(i)) return;

	RGBQUAD rgb[256];
	int used;
	HBITMAP hbm=esp_GetBitmapFromCB(rgb,&used);
	if(!hbm) return;

	HDC hdc=CreateCompatibleDC(esp_iw[i].memdc);
	HBITMAP holdbm=(HBITMAP)SelectObject(hdc,hbm);

	BITMAP bm;
	GetObject(hbm,sizeof(BITMAP),&bm);
	int wx=bm.bmWidth;
	int wy=bm.bmHeight;

	int r=0;
	if (x0==-1 || y0==-1){
		int x,y;
		r=ESP_GetPointR(i,&x,&y,wx,wy);
		x0=x-wx/2;
		y0=y-wy/2;
	}
	if(!r){
		if(used){
			SetDIBColorTable(esp_iw[i].memdc,0,used,rgb);
		}
		BitBlt(esp_iw[i].memdc,x0,y0,wx,wy,hdc,0,0,SRCCOPY);
		esp_invalid(i);
	}

	SelectObject(hdc,holdbm);
	DeleteObject(hbm);
	DeleteDC(hdc);
}

void ESP_PasteImage(int x0, int y0)
{
	esp_pasteimage(esp_i,x0,y0);
}

int ESP_GetDisplayMode(int i)
{
	if(esp_iw_check(i)) return 0;
	return GetStretchBltMode(esp_iw[i].hdc);
}

int ESP_SetDisplayMode(int i, int mode)
{
	if(esp_iw_check(i)) return 1;

	if(mode==HALFTONE || mode==COLORONCOLOR){
		SetStretchBltMode(esp_iw[i].hdc,mode);
		SetBrushOrgEx(esp_iw[i].hdc,0,0,NULL);
		SetStretchBltMode(esp_iw[i].memdc,mode);
		SetBrushOrgEx(esp_iw[i].memdc,0,0,NULL);
	}
	esp_invalid(i);
	esp_update_title(i);
	return 0;
}

// zoom... ~100~   7.0
int ESP_ZoomImage(int i,int zoom)
{
	if(esp_iw_check(i)) return 1;

	esp_iw[i].show=0;

	int wx=esp_iw[i].wx;
	int wy=esp_iw[i].wy;

	int winxmin,winymin,winxmax,winymax;
	esp_WindowSizeMinMax(&winxmin,&winymin,&winxmax,&winymax,esp_iw[i].flag);

	//ウィンドウ最大サイズのチェック
	double dwx=max(1,min(wx*zoom/100.0,(double)winxmax));
	double dwy=max(1,min(wy*zoom/100.0,(double)winymax));
	double zwx=dwx*100.0/(double)wx;
	double zwy=dwy*100.0/(double)wy;
	int zm=(int)min(zwx,zwy);
	int wx2=wx*zm/100;
	int wy2=wy*zm/100;

	//ウィンドウ最小サイズのチェック
	if(wx2<winxmin || wy2<winymin){
		double zwx=winxmin*100.0/wx;
		double zwy=winymin*100.0/wy;
		zm=(int)max(ceil(zwx),ceil(zwy));	// debug ver.5.4
		wx2=wx*zm/100;
		wy2=wy*zm/100;
		if(wx2>winxmax || wy2>winymax){
			return 2;
		}
	}

	esp_iw[i].zoom=zm;
	
	RECT rc;
	GetWindowRect(esp_iw[i].hwnd,&rc);
	SetWindowPos(esp_iw[i].hwnd,0,0,0,wx2+(rc.right-rc.left-esp_iw[i].wwx),wy2+(rc.bottom-rc.top-esp_iw[i].wwy),SWP_NOMOVE|esp_setpos_flags);

	esp_iw[i].wwx=wx2;
	esp_iw[i].wwy=wy2;
	esp_iw[i].show=1;

	esp_invalid(i);
	esp_update_title(i);
	esp_list_update();
	return 0;
}

// v8.0
// BMP,ICON,GIF,JPEG,Exif,PNG,TIFF,WMF,EMFに対応
// 0...open   1...cancel or close
int ESP_GetOpenFileName(char *file, const char *title=NULL, const char *path=NULL)
{
	if(esp_first_gofn && path!=NULL){
		strcpy_s(esp_gofn_path,MAX_PATH,path);
	}
	esp_first_gofn=0;
	char2wchar_t(esp_gofn_path,_esp_gofn_path,MAX_PATH);

	wchar_t filename[2*MAX_PATH];
	const wchar_t *esp_wildcard[10]={
		NULL,
		L"*.*",
		L"*.BMP;*.RLE;*.DIB",
		L"*.JPG;*.JPEG;*.JPE",
		L"*.GIF",
		L"*.PNG",
		L"*.TIF;*.TIFF",
		L"*.WMF",
		L"*.EMF",
		L"*.ICO"
	};
	wcscpy_s(filename,MAX_PATH,esp_wildcard[esp_gofn_index]);

	wchar_t _title[ESP_BUFMAX];
	wchar_t *_ptitle;
	_ptitle= _title;
	if(title) char2wchar_t(title,_ptitle,ESP_BUFMAX);
	else _ptitle= NULL;

	const wchar_t *filter=
		L"All Files (*.*)\0*.*\0"
		L"BMP (*.BMP;*.RLE;*.DIB)\0*.BMP;*.RLE;*.DIB\0"
		L"JPEG (*.JPG;*.JPEG;*.JPE)\0*.JPG;*.JPEG;*.JPE\0"
		L"CompuServe GIF (*.GIF)\0*.GIF\0"
		L"PNG (*.PNG)\0*.PNG\0"
		L"TIFF (*.TIF;*.TIFF)\0*.TIF;*.TIFF\0"
		L"WMF (*.WMF)\0*.WMF\0"
		L"EMF (*.EMF)\0*.EMF\0"
		L"ICO (*.ICO)\0*.ICO\0"
		L"\0";

	OPENFILENAME ofn;
	ZeroMemory(&ofn,sizeof(ofn));
	ofn.lStructSize=sizeof(ofn);
	ofn.lpstrFilter=filter;
	ofn.nFilterIndex=esp_gofn_index;
	ofn.lpstrFile=filename;
	ofn.nMaxFile=MAX_PATH;
	ofn.lpstrInitialDir=_esp_gofn_path;
	ofn.lpstrTitle=_ptitle;
	ofn.Flags=OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_HIDEREADONLY;

	if(!GetOpenFileName(&ofn)){
		file[0]=0;
		return 1;	//クローズまたはキャンセルのとき
	}
	
	//ファイル名を格納
	wchar_t2char(filename,file,MAX_PATH);
	//種類インデックスを保存
	esp_gofn_index=ofn.nFilterIndex;
	//パス情報を保存
	wchar_t *filepart;
	GetFullPathName(filename,MAX_PATH,_esp_gofn_path,&filepart);
	*filepart=0;
	wchar_t2char(_esp_gofn_path,esp_gofn_path,MAX_PATH);
	return 0;
}

// v8.0
// BMP,GIF,JPEG,PNG,TIFFに対応
// 0...save   1...cancel or close
int ESP_GetSaveFileName(char *file, const char *title=NULL, const char *path=NULL)
{
	if(esp_first_gsfn && path!=NULL){
		strcpy_s(esp_gsfn_path,MAX_PATH,path);
	}
	esp_first_gsfn=0;
	char2wchar_t(esp_gsfn_path,_esp_gsfn_path,MAX_PATH);

	wchar_t _title[ESP_BUFMAX];
	wchar_t *_ptitle;
	_ptitle= _title;
	if(title) char2wchar_t(title,_ptitle,ESP_BUFMAX);
	else _ptitle= NULL;

	const wchar_t *filter=
		L"All Files (*.*)\0*.*\0"
		L"BMP (*.BMP;*.RLE;*.DIB)\0*.BMP;*.RLE;*.DIB\0"
		L"JPEG (*.JPG;*.JPEG;*.JPE)\0*.JPG;*.JPEG;*.JPE\0"
		L"CompuServe GIF (*.GIF)\0*.GIF\0"
		L"PNG (*.PNG)\0*.PNG\0"
		L"TIFF (*.TIF;*.TIFF)\0*.TIF;*.TIFF\0"
		L"\0";
	
	wchar_t _filename[MAX_PATH]=L"noname";

	OPENFILENAME ofn;
	ZeroMemory(&ofn,sizeof(ofn));
	ofn.lStructSize=sizeof(ofn);
	ofn.lpstrFilter=filter;
	ofn.nFilterIndex=esp_gsfn_index;
	ofn.lpstrFile=_filename;
	ofn.nMaxFile=MAX_PATH;
	ofn.lpstrInitialDir=_esp_gsfn_path;
	ofn.lpstrTitle=_ptitle;
	ofn.Flags=OFN_PATHMUSTEXIST|OFN_OVERWRITEPROMPT;

	if(!GetSaveFileName(&ofn)){
		file[0]=0;
		return 1;	//クローズまたはキャンセルのとき
	}

	//ファイル名を格納
	wchar_t2char(_filename,file,MAX_PATH);
	//種類インデックスを保存
	esp_gsfn_index=ofn.nFilterIndex;
	//パス情報を保存
	wchar_t *filepart;
	GetFullPathName(_filename,MAX_PATH,_esp_gsfn_path,&filepart);
	*filepart=0;
	wchar_t2char(_esp_gsfn_path,esp_gsfn_path,MAX_PATH);
	return 0;
}

//イメージウィンドウのサイズ変更 v8.0
#ifndef ESP_LIBRARY_MODE
#define ESP_ResizeImage(i,wx,wy)  esp_ResizeImageX((i),(wx),(wy))
#else
#define ESP_ResizeImage(i,wx,wy)  esp_ResizeImageX((i),(wx),(wy),1)
#endif
// flag=1:異なるスレッド対応(request経由)
int esp_ResizeImageX(int i,int wx,int wy,int flag=0)
{
	if(esp_iw_check(i)) return 1;

	int bit=esp_iw[i].bit;
	char title[ESP_BUFMAX];
	strcpy_s(title,ESP_BUFMAX,esp_iw[i].title);
	RECT rc;
	GetWindowRect(esp_iw[i].hwnd,&rc);
	int x0=rc.left;
	int y0=rc.top;
	int zm=esp_iw[i].zoom;
	int mode=ESP_GetDisplayMode(i);

	RGBQUAD rgb[256];
	if(bit==8){
		GetDIBColorTable(esp_iw[i].memdc,0,256,rgb);
	}

	if(!flag) esp_DestroyImage(i); else ESP_DestroyImage(i);

	int r;
	if(!flag){
		r= esp_CreateImageX(i,title,x0,y0,wx,wy,zm,bit);
	}else{
		if(bit==32) r= ESP_CreateImage(i,title,x0,y0,wx,wy,zm);
		else r= ESP_CreateImage8(i,title,x0,y0,wx,wy,zm);
	}
	if(r) return r;

	if(bit==8){
		SetDIBColorTable(esp_iw[i].memdc,0,256,rgb);
	}
	ESP_SetDisplayMode(i,mode);
	
	return 0;
}

//ウィンドウハンドルからイメージウィンドウの番号を探す
int ESP_SearchImageWindow(HWND hwnd)
{
	for(int i=0;i<ESP_IW_MAX;i++){
		if(esp_iw[i].show && esp_iw[i].hwnd==hwnd){
				return i;
		}
	}
	return -1;
}

//ウィンドウハンドルからイメージウィンドウの番号を探し選択する 7.0
int ESP_SearchSelectImageWindow(HWND hwnd)
{
	int i=ESP_SearchImageWindow(hwnd);
	ESP_Select(i);
	return i;
}

//ウィンドウハンドルからテキストウィンドウの番号を探す 7.0
int ESP_SearchTextWindow(HWND hwnd)
{
	for(int i=0;i<ESP_TW_MAX;i++){
		if(esp_tw[i].show && esp_tw[i].hwnd==hwnd){
				return i;
		}
	}
	return -1;
}

//１文字描画（全角対応）7.0
void ESP_TTPutc(int c)
{
	LOGFONT lf;

	if (c<0x20) {
		if(c=='\n'){
			esp_tx=esp_tx0;
			esp_ty+=esp_ttwy;
		}else if(c=='\1'){
			GetObject(esp_hfont,sizeof(LOGFONT),&lf);
			DeleteObject(esp_hfont);
			lf.lfItalic=TRUE;
			esp_hfont=CreateFontIndirect(&lf);
		}else if(c=='\2'){
			GetObject(esp_hfont,sizeof(LOGFONT),&lf);
			DeleteObject(esp_hfont);
			lf.lfItalic=FALSE;
			esp_hfont=CreateFontIndirect(&lf);
		}else if(c=='\3'){
			GetObject(esp_hfont,sizeof(LOGFONT),&lf);
			DeleteObject(esp_hfont);
			lf.lfWeight=FW_BOLD;
			esp_hfont=CreateFontIndirect(&lf);
		}else if(c=='\4'){
			GetObject(esp_hfont,sizeof(LOGFONT),&lf);
			DeleteObject(esp_hfont);
			lf.lfWeight=FW_NORMAL;
			esp_hfont=CreateFontIndirect(&lf);
		}else if(c=='\5'){
			GetObject(esp_hfont,sizeof(LOGFONT),&lf);
			DeleteObject(esp_hfont);
			lf.lfUnderline=TRUE;
			esp_hfont=CreateFontIndirect(&lf);
		}else if(c=='\6'){
			GetObject(esp_hfont,sizeof(LOGFONT),&lf);
			DeleteObject(esp_hfont);
			lf.lfUnderline=FALSE;
			esp_hfont=CreateFontIndirect(&lf);
		}
		return;
	}

	char buf[4];

	if(c>=0x100){
		buf[0]=HIBYTE(c);
		buf[1]=LOBYTE(c);
	}else{
		buf[0]=LOBYTE(c);
		buf[1]=0;
	}
	buf[2]=buf[3]=0;

	wchar_t _buf[2];
	char2wchar_t(buf,_buf,2);

	int r,g,b;
	C2RGB(esp_tttc,&r,&g,&b);
	SetTextColor(esp_iw[esp_i].memdc,RGB(r,g,b));
	SetBkMode(esp_iw[esp_i].memdc,TRANSPARENT);

	HFONT hold = (HFONT)SelectObject(esp_iw[esp_i].memdc,esp_hfont);

	TextOut(esp_iw[esp_i].memdc,esp_tx,esp_ty-esp_ttwy+1,_buf,1);

	ABC abc;
	r=GetCharABCWidths(esp_iw[esp_i].memdc,*_buf,*_buf,&abc);
	if(!r){
		int w;
		GetCharWidth(esp_iw[esp_i].memdc,*_buf,*_buf,&w);
		esp_tx+=w;
	}else{
		esp_tx+=abc.abcA+abc.abcB+abc.abcC;
	}

	SelectObject(esp_iw[esp_i].memdc,hold);
}

// 7.0
void ESP_TTPuts(const char *s)
{
	while(*s){
		unsigned char c1=*s++;
		if((c1>=0x81 && c1<=0x9F)||(c1>=0xE0 && c1<=0xFC)){
			unsigned char c2=*s++;
			if(c2)ESP_TTPutc((c1<<8)|c2);
			else return;
		}else{
			ESP_TTPutc(c1);
		}
	}
}

// 7.0
void ESP_TTPrintf(const char *format, ...)
{
	va_list vl;
	va_start(vl,format);

	char buf[2*ESP_STRMAX];
	vsprintf_s(buf,ESP_STRMAX,format,vl);

	ESP_TTPuts(buf);
}

int ESP_TTSize(int wx,int wy)
{
	esp_ttwx=wx/2;
	esp_ttwy=wy;

	LOGFONT lf;
	GetObject(esp_hfont,sizeof(LOGFONT),&lf);
	DeleteObject(esp_hfont);

	lf.lfWidth  = esp_ttwx;
	lf.lfHeight = esp_ttwy;
	esp_hfont=CreateFontIndirect(&lf);

	if(!esp_hfont) return 1;
	return 0;
}

HMENU esp_im_menu1(HWND hwnd)
{
	HMENU hmenu=CreatePopupMenu();
	esp_AppendMenu   (hmenu, 0,MFS_ENABLED,ID_CUT,"Cut\tCtrl+X");
	esp_AppendMenu   (hmenu, 1,MFS_ENABLED,ID_COPY,"Copy\tCtrl+C");
	esp_AppendMenu   (hmenu, 2,MFS_ENABLED,ID_PASTETO,"Paste\tCtrl+V");
	esp_AppendMenuSEP(hmenu, 3);
	esp_AppendMenu   (hmenu, 4,MFS_ENABLED,ID_LOADIMG,"&Load image file");
	esp_AppendMenu   (hmenu, 5,MFS_ENABLED,ID_SAVEIMG,"&Save as");
	esp_AppendMenuSEP(hmenu, 6);
	int i=ESP_SearchImageWindow(hwnd);
	int b=(esp_iw[i].zoom== 50)?MFS_CHECKED:0;
	esp_AppendMenu   (hmenu, 7,MFS_ENABLED|b,ID_ZOOM050,"Zoom: 50%");
	b=(esp_iw[i].zoom==100)?MFS_CHECKED:0;
	esp_AppendMenu   (hmenu, 8,MFS_ENABLED|b,ID_ZOOM100,"Zoom:100%\tCtrl+0");
	b=(esp_iw[i].zoom==200)?MFS_CHECKED:0;
	esp_AppendMenu   (hmenu, 9,MFS_ENABLED|b,ID_ZOOM200,"Zoom:200%");
	esp_AppendMenu   (hmenu,10,MFS_ENABLED,ID_ZOOMANY,"&Zoom...");
	esp_AppendMenuSEP(hmenu,11);
	esp_AppendMenu   (hmenu,12,MFS_ENABLED,ID_RESIZE,"&Resize...");
	esp_AppendMenu   (hmenu,13,MFS_ENABLED,ID_DESTROYI,"&Destroy\tCtrl+Q");

	return hmenu;
}

// i...Number of image window  7.0
HMENU esp_im_menu2(int i)
{
	HMENU hmenu=CreatePopupMenu();

	HMENU hmenu4=CreatePopupMenu();
	esp_AppendMenu   (hmenu4,0,MFS_ENABLED,ID_INFOPIXEL,"Pixel");
	if(esp_iw[i].bit==32){
		esp_AppendMenu   (hmenu4,1,MFS_ENABLED,ID_INFOLINERGB,"Line(RGB)");
		esp_AppendMenu   (hmenu4,2,MFS_ENABLED,ID_INFOLINEHSV,"Line(HSV)");
		esp_AppendMenu   (hmenu4,3,MFS_ENABLED,ID_INFOLINEYCRCB,"Line(YCrCb)");
		esp_AppendMenu   (hmenu4,4,MFS_ENABLED,ID_INFOLINECRCB,"Line(CrCb)");
		esp_AppendMenuSEP(hmenu4,5);
		esp_AppendMenu   (hmenu4,6,MFS_ENABLED,ID_INFOAREACRCB,"Area(CrCb)");
	}else{
		esp_AppendMenu   (hmenu4,1,MFS_ENABLED,ID_INFOLINEL,"Line(Lumi)");
	}

	HMENU hmenu3=CreatePopupMenu();
	esp_AppendMenu   (hmenu3,0,MFS_ENABLED,ID_TESTRGB,"RGB");
	esp_AppendMenu   (hmenu3,1,MFS_ENABLED,ID_TESTHSV,"HSV");
	esp_AppendMenu   (hmenu3,2,MFS_ENABLED,ID_TESTCRCB,"YCrCb");
	esp_AppendMenu   (hmenu3,3,MFS_ENABLED,ID_TESTUV,"Yuv");
	esp_AppendMenu   (hmenu3,4,MFS_ENABLED,ID_TESTIQ,"YIQ");
	esp_AppendMenu   (hmenu3,5,MFS_ENABLED,ID_TESTGREY,"Grey");

	HMENU hmenu2=CreatePopupMenu();
	esp_AppendMenu   (hmenu2, 0,MFS_ENABLED,ID_INVERT,"Invert");
	esp_AppendMenuSEP(hmenu2, 1);
	esp_AppendMenu   (hmenu2, 2,MFS_ENABLED,ID_RROTATE,"R. Rotate");
	esp_AppendMenu   (hmenu2, 3,MFS_ENABLED,ID_LROTATE,"L. Rotate");
	esp_AppendMenuSEP(hmenu2, 4);
	esp_AppendMenu   (hmenu2, 5,MFS_ENABLED,ID_HFLIP,"Horz. Flip");
	esp_AppendMenu   (hmenu2, 6,MFS_ENABLED,ID_VFLIP,"Vert. Flip");
	esp_AppendMenuSEP(hmenu2, 7);
	esp_AppendMenu   (hmenu2, 8,MFS_ENABLED,ID_SIZE500,"Size 50.0%");
	esp_AppendMenu   (hmenu2, 9,MFS_ENABLED,ID_SIZE707,"Size 70.7%");
	esp_AppendMenu   (hmenu2,10,MFS_ENABLED,ID_SIZE141,"Size 141.4%");
	esp_AppendMenu   (hmenu2,11,MFS_ENABLED,ID_SIZE200,"Size 200.0%");
	
	HMENU hmenu5=CreatePopupMenu();
	esp_AppendMenu   (hmenu5,0,MFS_ENABLED,ID_DRAWLINE,"Normal");
	esp_AppendMenu   (hmenu5,1,MFS_ENABLED,ID_DRAWHLINE,"Horz.");
	esp_AppendMenu   (hmenu5,2,MFS_ENABLED,ID_DRAWVLINE,"Vert.");

	HMENU hmenu6=CreatePopupMenu();
	esp_AppendMenu   (hmenu6,0,MFS_ENABLED,ID_DRAWBOX,"Normal");
	esp_AppendMenu   (hmenu6,1,MFS_ENABLED,ID_DRAWBOXF,"Fill");
	esp_AppendMenu   (hmenu6,2,MFS_ENABLED,ID_DRAWBOXFX,"Fill XOR");

	HMENU hmenu7=CreatePopupMenu();
	esp_AppendMenu   (hmenu7,0,MFS_ENABLED,ID_DRAWCIRCLE,"Normal");
	esp_AppendMenu   (hmenu7,1,MFS_ENABLED,ID_DRAWCIRCLEF,"Fill");
	esp_AppendMenu   (hmenu7,2,MFS_ENABLED,ID_DRAWCIRCLEFX,"Fill XOR");

	HMENU hmenu8=CreatePopupMenu();
	esp_AppendMenu   (hmenu8,0,MFS_ENABLED,ID_SELECTCOLOR,"Change");
	esp_AppendMenu   (hmenu8,1,MFS_ENABLED,ID_PICKCOLOR,"Pick");
	
	HMENU hmenu9=CreatePopupMenu();
	esp_AppendMenu   (hmenu9,0,MFS_ENABLED,ID_DRAWTTTEXT,"Draw");
	esp_AppendMenu   (hmenu9,1,MFS_ENABLED,ID_SELECTFONT,"Font Change");

	esp_AppendMenuSub(hmenu, 0,hmenu2,"Process...");
	esp_AppendMenuSEP(hmenu, 1);
	esp_AppendMenuSub(hmenu, 2,hmenu4,"Information...");
	esp_AppendMenuSEP(hmenu, 3);
	esp_AppendMenuSub(hmenu, 4,hmenu3,"Test Pattern...");
	esp_AppendMenuSEP(hmenu, 5);
	esp_AppendMenu   (hmenu, 6,MFS_ENABLED,ID_CLIP,"Clipping\tCtrl+R");
	esp_AppendMenuSEP(hmenu, 7);
	esp_AppendMenuSub(hmenu, 8,hmenu8,"Color...");
	esp_AppendMenuSub(hmenu, 9,hmenu5,"Draw Line...");
	esp_AppendMenuSub(hmenu,10,hmenu6,"Draw Box...");
	esp_AppendMenuSub(hmenu,11,hmenu7,"Draw Circle...");
	esp_AppendMenuSub(hmenu,12,hmenu9,"TrueType...");
	esp_AppendMenu   (hmenu,13,MFS_ENABLED,ID_DRAWTEXT,"Draw Text");
	esp_AppendMenu   (hmenu,14,MFS_ENABLED,ID_DRAWPAINT,"Paint");

	return hmenu;
}

//押されたキーを返す
int ESP_CheckKeyDown(void)
{
	int k= esp_keydown;
	esp_keydown= -1;
	return k;
}

//イメージウィンドウ共通のウィンドウ関数
LRESULT CALLBACK ESP_IWfunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HMENU hmenu;
	HDC hdc;
	PAINTSTRUCT ps;
	POINT CurPos;
	int i,j,r,g,b,x,y, pp0,pp1;
	char buf[2*ESP_BUFMAX];
	wchar_t _buf[ESP_BUFMAX];
	HDROP hDrop;
	int wx,wy,wx0,wy0,zm;
	int x1,y1,x2,y2;
	CHOOSEFONT cf;
	LOGFONT lf;
	CHOOSECOLOR cc;
	COLORREF c;
	RECT rc;
	int *p;
	unsigned char *ucp;
	HBITMAP hbm,holdbm;
			
	switch(message){
	case WM_PAINT:
		BeginPaint(hwnd,&ps);
		i=ESP_SearchImageWindow(hwnd);
		ESP_Update_(i);
		EndPaint(hwnd,&ps);
		break;
	case WM_SIZING:
		//サイズ変更を制限する
		GetWindowRect(hwnd,&rc);
		((LPRECT)lParam)->left  = rc.left;
		((LPRECT)lParam)->top   = rc.top;
		((LPRECT)lParam)->right = rc.right;
		((LPRECT)lParam)->bottom= rc.bottom;
		break;
	case WM_MOVING:
		esp_wm_moving(hwnd,lParam);
		break;
	case WM_DROPFILES:
		hDrop=(HDROP)wParam; 
		DragQueryFile(hDrop,0,_buf,ESP_BUFMAX);
		ESP_SearchSelectImageWindow(hwnd);
		wchar_t2char(_buf,buf,ESP_BUFMAX);
		esp_ImageLoad(buf,0,0,100);
		esp_invalid(esp_i);
		ESP_UnSelect();
		DragFinish(hDrop);
		SetForegroundWindow(hwnd);
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam)){
			case ID_SIZE500:	zm= 500;	goto change_size;
			case ID_SIZE707:	zm= 707;	goto change_size;
			case ID_SIZE141:	zm=1414;	goto change_size;
			case ID_SIZE200:	zm=2000;	goto change_size;
			change_size:
				i=ESP_SearchSelectImageWindow(hwnd);
				wx0=esp_iw[i].wx;
				wy0=esp_iw[i].wy;
				hdc=CreateCompatibleDC(esp_iw[i].memdc);
				hbm=CreateCompatibleBitmap(esp_iw[i].memdc,wx0,wy0);
				holdbm=(HBITMAP)SelectObject(hdc,hbm);
				BitBlt(hdc,0,0,wx0,wy0,esp_iw[i].memdc,0,0,SRCCOPY);
				wx=(wx0*zm+500)/1000;
				wy=(wy0*zm+500)/1000;
				j=esp_ResizeImageX(i,wx,wy);
				if(!j){
					StretchBlt(esp_iw[i].memdc,0,0,wx,wy,hdc,0,0,wx0,wy0,SRCCOPY);
					esp_invalid(i);
				}
				SelectObject(hdc,holdbm);
				DeleteObject(hbm);
				DeleteDC(hdc);
				break;
			case ID_RROTATE:
			case ID_LROTATE:
				i=ESP_SearchSelectImageWindow(hwnd);
				if(esp_iw[i].bit==32){
					//32bit
					pp0=esp_iw[i].wx*sizeof(int);
					pp1=esp_iw[i].wy*sizeof(int);
				}else{
					//8bit
					pp0=esp_iw[i].wx;
					pp1=(esp_iw[i].wy+3) & ~3;
				}
				j=pp0*esp_iw[i].wy;
				p=new int[j];
				ucp=(unsigned char *)p;
				ESP_GetWindow(p,0,0,esp_iw[i].wx,esp_iw[i].wy);
				j=esp_ResizeImageX(i,esp_iw[i].wy,esp_iw[i].wx);
				if(j) goto end_rotate;

				//右回転の場合
				if(LOWORD(wParam)==ID_RROTATE){
					if(esp_iw[i].bit==32){
						//32bit
						for(y=0;y<esp_iw[i].wy;y++){
						for(x=0;x<esp_iw[i].wx;x++){
							*(ESP_VramPtr[i]+x+esp_iw[i].wx*y) = *(p+y+esp_iw[i].wy*(esp_iw[i].wx-1-x));
						}
						}
					}else{
						//8bit
						for(y=0;y<esp_iw[i].wy;y++){
						for(x=0;x<esp_iw[i].wx;x++){
							*(ESP_VramPtr8[i]+x+pp1*y) = *(ucp+y+esp_iw[i].wy*(esp_iw[i].wx-1-x));
						}
						}
					}
				}
				//左回転の場合
				if(LOWORD(wParam)==ID_LROTATE){
					if(esp_iw[i].bit==32){
						//32bit
						for(y=0;y<esp_iw[i].wy;y++){
						for(x=0;x<esp_iw[i].wx;x++){
							*(ESP_VramPtr[i]+x+esp_iw[i].wx*y) = *(p+esp_iw[i].wy-1-y+esp_iw[i].wy*x);
						}
						}
					}else{
						//8bit
						for(y=0;y<esp_iw[i].wy;y++){
						for(x=0;x<esp_iw[i].wx;x++){
							*(ESP_VramPtr8[i]+x+pp1*y) = *(ucp+esp_iw[i].wy-1-y+esp_iw[i].wy*x);
						}
						}
					}
				}
				end_rotate:
				delete[] p;
				esp_invalid(esp_i);
				break;
			case ID_HFLIP:
				i=ESP_SearchImageWindow(hwnd);
				StretchBlt(esp_iw[i].memdc,esp_iw[i].wx-1,0,-esp_iw[i].wx,esp_iw[i].wy,esp_iw[i].memdc,0,0,esp_iw[i].wx,esp_iw[i].wy,SRCCOPY);
				esp_invalid(i);
				break;
			case ID_VFLIP:
				i=ESP_SearchImageWindow(hwnd);
				StretchBlt(esp_iw[i].memdc,0,esp_iw[i].wy-1,esp_iw[i].wx,-esp_iw[i].wy,esp_iw[i].memdc,0,0,esp_iw[i].wx,esp_iw[i].wy,SRCCOPY);
				esp_invalid(i);
				break;
			case ID_INVERT:
				i=ESP_SearchImageWindow(hwnd);
				rc.left=0;
				rc.top=0;
				rc.right=esp_iw[i].wx;
				rc.bottom=esp_iw[i].wy;
				InvertRect(esp_iw[i].memdc,&rc);
				esp_invalid(i);
				break;
			case ID_PICKCOLOR:
				i=ESP_SearchImageWindow(hwnd);
				if(ESP_GetPoint(i,&x,&y)) break;
				ESP_Select(i);
				esp_color=ESP_Point(x,y);
				ESP_UnSelect();
				if(esp_iw[i].bit==32){
					//32bit
					ESP_TTColor(esp_color);
				}else{
					//8bit
					RGBQUAD rgb;
					GetDIBColorTable(esp_iw[i].memdc,esp_color,1,&rgb);
					ESP_TTColor(RGB2C(rgb.rgbRed,rgb.rgbGreen,rgb.rgbBlue));
				}
				break;
			case ID_SELECTCOLOR:
				C2RGB(esp_color,&r,&g,&b);
				cc.lStructSize=sizeof(CHOOSECOLOR);
				cc.hwndOwner=hwnd;
				cc.rgbResult=RGB(r,g,b);
				cc.Flags=CC_RGBINIT|CC_FULLOPEN;
				cc.lpCustColors=esp_CustColors;
				ChooseColor(&cc);
				c=cc.rgbResult;
				b=C2R(c);
				g=C2G(c);
				r=C2B(c);
				esp_color=RGB2C(r,g,b);
				ESP_TTColor(esp_color);
				ESP_Gtextcolor(esp_color);
                break;
			case ID_SELECTFONT:
				GetObject(esp_hfont,sizeof(LOGFONT),&lf);
				DeleteObject(esp_hfont);

				//CHOOSEFONT構造体の設定
				cf.lStructSize=sizeof(CHOOSEFONT); 
				cf.hwndOwner=hwnd;
				cf.lpLogFont=&lf;
				cf.Flags=CF_SCREENFONTS|CF_INITTOLOGFONTSTRUCT|CF_ANSIONLY|CF_EFFECTS;
				cf.nFontType=SCREEN_FONTTYPE;
				ChooseFont(&cf);
				esp_hfont=CreateFontIndirect(&lf);
				break;
			case ID_DRAWPAINT:
				i=ESP_SearchSelectImageWindow(hwnd);
				if(ESP_GetPoint(i,&x,&y)) break;
				ESP_Paint(x,y,esp_color);
				esp_invalid(esp_i);
				break;
			case ID_DRAWLINE:
				i=ESP_SearchSelectImageWindow(hwnd);
				if(ESP_GetRectL(i,&x1,&y1,&x2,&y2)) break;
				ESP_Line(x1,y1,x2,y2,esp_color);
				esp_invalid(esp_i);
				break;
			case ID_DRAWVLINE:
				i=ESP_SearchSelectImageWindow(hwnd);
				if(ESP_GetPointV(i,&x,&y)) break;
				ESP_Line(x,0,x,esp_iw[i].wy-1,esp_color);
				esp_invalid(esp_i);
				break;
			case ID_DRAWHLINE:
				i=ESP_SearchSelectImageWindow(hwnd);
				if(ESP_GetPointH(i,&x,&y)) break;
				ESP_Line(0,y,esp_iw[i].wx-1,y,esp_color);
				esp_invalid(esp_i);
				break;
			case ID_DRAWBOX:
				i=ESP_SearchSelectImageWindow(hwnd);
				if(ESP_GetRect(i,&x1,&y1,&x2,&y2)) break;
				ESP_Box(x1,y1,x2,y2,esp_color);
				esp_invalid(esp_i);
				break;
			case ID_DRAWBOXF:
				i=ESP_SearchSelectImageWindow(hwnd);
				if(ESP_GetRect(i,&x1,&y1,&x2,&y2)) break;
				ESP_BoxFill(x1,y1,x2,y2,esp_color,esp_color);
				esp_invalid(esp_i);
				break;
			case ID_DRAWBOXFX:
				i=ESP_SearchSelectImageWindow(hwnd);
				if(ESP_GetRect(i,&x1,&y1,&x2,&y2)) break;
				ESP_BoxFillXOR(x1,y1,x2,y2);
				esp_invalid(esp_i);
				break;
			case ID_DRAWCIRCLE:
				i=ESP_SearchSelectImageWindow(hwnd);
				if(ESP_GetRectC(i,&x,&y,&r)) break;
				ESP_Circle(x,y,r,esp_color);
				esp_invalid(esp_i);
				break;
			case ID_DRAWCIRCLEF:
				i=ESP_SearchSelectImageWindow(hwnd);
				if(ESP_GetRectC(i,&x,&y,&r)) break;
				ESP_CircleFill(x,y,r,esp_color,esp_color);
				esp_invalid(esp_i);
				break;
			case ID_DRAWCIRCLEFX:
				i=ESP_SearchSelectImageWindow(hwnd);
				if(ESP_GetRectC(i,&x,&y,&r)) break;
				ESP_CircleFillXOR(x,y,r);
				esp_invalid(esp_i);
				break;
			case ID_DRAWTEXT:
				i=ESP_SearchSelectImageWindow(hwnd);
				if(ESP_GetPoint(i,&x1,&y1)) break;
				esp_DefaultTextWindow();
				ESP_Printf("Text>");
				ESP_Input(buf);
				ESP_Glocate(x1,y1);
				ESP_Gtextcolor(esp_color);
				ESP_Gprintf("%s",buf);
				esp_invalid(esp_i);
				break;
			case ID_DRAWTTTEXT:
				i=ESP_SearchSelectImageWindow(hwnd);
				if(ESP_GetRect(i,&x1,&y1,&x2,&y2)) break;
				esp_DefaultTextWindow();
				ESP_Printf("Text>");
				ESP_Input(buf);
				ESP_TTPosition(x1,y2);
				ESP_TTColor(esp_tttc);
				ESP_TTSize(x2-x1+1,y2-y1+1);
				ESP_TTPuts(buf);
				esp_invalid(esp_i);
				break;
			case ID_TESTRGB:
				ESP_SearchSelectImageWindow(hwnd);
				ESP_TestPat_RGB();
				esp_invalid(esp_i);
				break;
			case ID_TESTHSV:
				ESP_SearchSelectImageWindow(hwnd);
				ESP_TestPat_HSV();
				esp_invalid(esp_i);
				break;
			case ID_TESTCRCB:
				ESP_SearchSelectImageWindow(hwnd);
				ESP_TestPat_CrCb();
				esp_invalid(esp_i);
				break;
			case ID_TESTUV:
				ESP_SearchSelectImageWindow(hwnd);
				ESP_TestPat_uv();
				esp_invalid(esp_i);
				break;
			case ID_TESTIQ:
				ESP_SearchSelectImageWindow(hwnd);
				ESP_TestPat_IQ();
				esp_invalid(esp_i);
				break;
			case ID_TESTGREY:
				ESP_SearchSelectImageWindow(hwnd);
				ESP_TestPat_Grey();
				esp_invalid(esp_i);
				break;
			case ID_COPY:
			case ID_CUT:
				i=ESP_SearchImageWindow(hwnd);
				esp_copyimage(i);
				if (LOWORD(wParam)==ID_CUT){
					esp_clearimage(i);
					esp_invalid(i);
				}
				break;
			case ID_PASTE:
				i=ESP_SearchImageWindow(hwnd);
				esp_pasteimage(i,0,0);
				break;
			case ID_PASTETO:
				i=ESP_SearchImageWindow(hwnd);
				esp_pasteimage(i,-1,-1);
				break;
			case ID_LOADIMG:	// 7.0
				ESP_SearchSelectImageWindow(hwnd);
				if(! ESP_GetOpenFileName(buf,"Load image file",NULL)){
					esp_ImageLoad(buf,0,0,100);
					esp_invalid(esp_i);
				}
				break;
			case ID_SAVEIMG:	// 7.0
				ESP_SearchSelectImageWindow(hwnd);
				if(! ESP_GetSaveFileName(buf,"Save as",NULL)){
					int _q=esp_jpegquality;
					switch(esp_gsfn_index){
						case 1:		//all
						case 2:		//bmp
							ESP_ImageSave(ESP_BMP,buf,0,0,esp_iw[esp_i].wx,esp_iw[esp_i].wy);
							break;
						case 3:		//jpeg
							esp_jpegquality=100;
							ESP_ImageSave(ESP_JPEG,buf,0,0,esp_iw[esp_i].wx,esp_iw[esp_i].wy);
							esp_jpegquality=_q;
							break;
						case 4:		//gif
							ESP_ImageSave(ESP_GIF,buf,0,0,esp_iw[esp_i].wx,esp_iw[esp_i].wy);
							break;
						case 5:		//png
							ESP_ImageSave(ESP_PNG,buf,0,0,esp_iw[esp_i].wx,esp_iw[esp_i].wy);
							break;
						case 6:		//tiff
							ESP_ImageSave(ESP_TIFF,buf,0,0,esp_iw[esp_i].wx,esp_iw[esp_i].wy);
							break;
					}
				}
				break;
			case ID_ZOOM050:
				i=ESP_SearchImageWindow(hwnd);
				ESP_ZoomImage(i,50);
				break;
			case ID_ZOOM100:
				i=ESP_SearchImageWindow(hwnd);
				ESP_ZoomImage(i,100);
				break;
			case ID_ZOOM200:
				i=ESP_SearchImageWindow(hwnd);
				ESP_ZoomImage(i,200);
				break;
			case ID_ZOOMANY:
				i=ESP_SearchImageWindow(hwnd);
				esp_DefaultTextWindow();
				ESP_Printf("[%d] Zoom(%%)=",i);
				ESP_Input(buf);
				zm=atoi(buf);
				ESP_ZoomImage(i,zm);
				break;
			case ID_RESIZE:
				i=ESP_SearchImageWindow(hwnd);
				esp_DefaultTextWindow();
				ESP_Printf("[%d] New x-size(pixel)=",i);
				ESP_Input(buf);
				x=atoi(buf);
				ESP_Printf("[%d] New y-size(pixel)=",i);
				ESP_Input(buf);
				y=atoi(buf);
				esp_ResizeImageX(i,x,y);
				break;
			case ID_INFOPIXEL:
				i=ESP_SearchImageWindow(hwnd);
				if(ESP_GetPoint(i,&x,&y)) break;
				c=ESP_Point(x,y);
				esp_DefaultTextWindow();
				ESP_Printf("(X,Y)=(%d,%d)\n",x,y);
				if(esp_iw[i].bit==32){
					//32bit
					ESP_Printf("(R,G,B)=(%d,%d,%d)\n",C2R(c),C2G(c),C2B(c));
					ESP_Printf("(H,S,V)=(%d,%d,%d)\n",C2H(c),C2S(c),C2V(c));
					ESP_Printf("(Y,Cr,Cb)=(%d,%d,%d)\n",C2Y(c),C2Cr(c),C2Cb(c));
					ESP_Printf("(Y,u,v)=(%d,%d,%d)\n",C2Y(c),C2u(c),C2v(c));
					ESP_Printf("(Y,I,Q)=(%d,%d,%d)\n\n",C2Y(c),C2I(c),C2Q(c));
				}else{
					//8bit
					ESP_Printf("(Luminance)=(%d)\n\n",c);
				}
				break;
			case ID_INFOLINERGB:
				i=ESP_SearchImageWindow(hwnd);
				if(ESP_GetPointH(i,&x,&y)) break;
				wx=esp_iw[i].wx;
				sprintf_s(buf,sizeof(buf),"RGB(Y=%d)",y);
				p=new int[wx];
				ESP_GetLine(p,0,y,wx);
				for(j=0;j<ESP_IW_MAX;j++){
					if(!esp_CreateImageX(j,buf,0,0,wx+12,128,100)) break;
				}
				if(j==ESP_IW_MAX) goto fin_inforgb;
				ESP_GraphLine(p,12,0,wx,128,ESP_R|ESP_LINE,ESP_COLOR_R);
				ESP_GraphLine(p,12,0,wx,128,ESP_G|ESP_LINE,ESP_COLOR_G);
				ESP_GraphLine(p,12,0,wx,128,ESP_B|ESP_LINE,ESP_COLOR_B);
				ESP_Glocate(2,24+16); ESP_Gtextcolor(ESP_COLOR_R);ESP_Gputc('R');
				ESP_Glocate(2,56+16); ESP_Gtextcolor(ESP_COLOR_G);ESP_Gputc('G');
				ESP_Glocate(2,88+16); ESP_Gtextcolor(ESP_COLOR_B);ESP_Gputc('B');
				esp_invalid(esp_i);
			fin_inforgb:
				delete[] p;
				break;
			case ID_INFOLINEHSV:
				i=ESP_SearchImageWindow(hwnd);
				if(ESP_GetPointH(i,&x,&y)) break;
				wx=esp_iw[i].wx;
				sprintf_s(buf,sizeof(buf),"HSV(Y=%d)",y);
				p=new int[wx];
				ESP_GetLine(p,0,y,wx);
				for(j=0;j<ESP_IW_MAX;j++){
					if(!esp_CreateImageX(j,buf,0,0,wx+12,128,100)) break;
				}
				if(j==ESP_IW_MAX) goto fin_infohsv;
				ESP_GraphLine(p,12,0,wx,128,ESP_H|ESP_LINE,ESP_COLOR_H);
				ESP_GraphLine(p,12,0,wx,128,ESP_S|ESP_LINE,ESP_COLOR_S);
				ESP_GraphLine(p,12,0,wx,128,ESP_V|ESP_LINE,ESP_COLOR_V);
				ESP_Glocate(2,24+16); ESP_Gtextcolor(ESP_COLOR_H);ESP_Gputc('H');
				ESP_Glocate(2,56+16); ESP_Gtextcolor(ESP_COLOR_S);ESP_Gputc('S');
				ESP_Glocate(2,88+16); ESP_Gtextcolor(ESP_COLOR_V);ESP_Gputc('V');
				esp_invalid(esp_i);
			fin_infohsv:
				delete[] p;
				break;
			case ID_INFOLINEYCRCB:
				i=ESP_SearchImageWindow(hwnd);
				if(ESP_GetPointH(i,&x,&y)) break;
				wx=esp_iw[i].wx;
				sprintf_s(buf,sizeof(buf),"YCrCb(Y=%d)",y);
				p=new int[wx];
				ESP_GetLine(p,0,y,wx);
				for(j=0;j<ESP_IW_MAX;j++){
					if(!esp_CreateImageX(j,buf,0,0,wx+20,128,100)) break;
				}
				if(j==ESP_IW_MAX) goto fin_infoycrcb;
				ESP_GraphLine(p,20,0,wx,128,ESP_Y|ESP_LINE,ESP_COLOR_Y);
				ESP_GraphLine(p,20,0,wx,128,ESP_Cr|ESP_LINE,ESP_COLOR_CR);
				ESP_GraphLine(p,20,0,wx,128,ESP_Cb|ESP_LINE,ESP_COLOR_CB);
				ESP_Glocate(4,24+16); ESP_Gtextcolor(ESP_COLOR_Y);ESP_Gputc('Y');
				ESP_Glocate(2,56+16); ESP_Gtextcolor(ESP_COLOR_CR);ESP_Gputs("Cr");
				ESP_Glocate(2,88+16); ESP_Gtextcolor(ESP_COLOR_CB);ESP_Gputs("Cb");
				esp_invalid(esp_i);
			fin_infoycrcb:
				delete[] p;
				break;
			case ID_INFOLINECRCB:
				i=ESP_SearchImageWindow(hwnd);
				if(ESP_GetPointH(i,&x,&y)) break;
				wx=esp_iw[i].wx;
				sprintf_s(buf,sizeof(buf),"CrCb(Y=%d)",y);
				p=new int[wx];
				ESP_GetLine(p,0,y,wx);
				for(j=0;j<ESP_IW_MAX;j++){
					if(!esp_CreateImageX(j,buf,0,0,256,256,100)) break;
				}
				if(j==ESP_IW_MAX) goto fin_infocrcb;
				ESP_GraphXYL(p,wx,0,0,256,256,ESP_CrCb|ESP_LINE,0xffffff);
				esp_invalid(esp_i);
			fin_infocrcb:
				delete[] p;
				break;
			case ID_INFOLINEL:
				i=ESP_SearchImageWindow(hwnd);
				if(ESP_GetPointH(i,&x,&y)) break;
				wx=esp_iw[i].wx;
				sprintf_s(buf,sizeof(buf),"Luminance(Y=%d)",y);
				ucp = new BYTE[wx];
				ESP_GetLine(ucp,0,y,wx);
				for(j=0;j<ESP_IW_MAX;j++){
					if(!esp_CreateImageX(j,buf,0,0,wx+12,128,100)) break;
				}
				if(j==ESP_IW_MAX) goto fin_infol;
				ESP_GraphLine(ucp,12,0,wx,128,ESP_L|ESP_LINE,ESP_COLOR_L);
				ESP_Glocate(2,24+16); ESP_Gtextcolor(ESP_COLOR_L);ESP_Gputc('L');
				esp_invalid(esp_i);
			fin_infol:
				delete[] ucp;
				break;
			case ID_INFOAREACRCB:
				i=ESP_SearchImageWindow(hwnd);
				if(ESP_GetRect(i,&x1,&y1,&x2,&y2)) break;
				sprintf_s(buf,sizeof(buf),"CrCb(%d,%d)-(%d,%d)",x1,y1,x2,y2);
				wx=x2-x1+1;
				wy=y2-y1+1;
				p=new int[wx*wy];
				ESP_GetWindow(p,x1,y1,wx,wy);
				for(j=0;j<ESP_IW_MAX;j++){
					if(!esp_CreateImageX(j,buf,0,0,256,256,100)) break;
				}
				if(j==ESP_IW_MAX) goto fin_infoacrcb;
				ESP_GraphXYW(p,wx,wy,0,0,256,256,ESP_CrCb|ESP_LINE,0xffffff);
				ESP_Update();
			fin_infoacrcb:
				delete[] p;
				break;
			case ID_CLIP:
				i=ESP_SearchImageWindow(hwnd);
				if(ESP_GetRect(i,&x1,&y1,&x2,&y2)) break;
				sprintf_s(buf,sizeof(buf),"(%d,%d)-(%d,%d)",x1,y1,x2,y2);
				wx=x2-x1+1;wy=y2-y1+1;
				for(j=0;j<ESP_IW_MAX;j++){
					if(esp_iw[i].bit==32){
						//32bit
						if(!esp_CreateImageX(j,buf,0,0,wx,wy,100)) break;
					}else{
						//8bit
						if(!esp_CreateImageX(j,buf,0,0,wx,wy,100,8)) break;
					}
				}
				if(j==ESP_IW_MAX) break;
				if(esp_iw[i].bit==8){
					RGBQUAD rgb[256];
					//8bit
					GetDIBColorTable(esp_iw[i].memdc,0,256,rgb);
					SetDIBColorTable(esp_iw[j].memdc,0,256,rgb);
				}
				BitBlt(esp_iw[j].memdc,0,0,wx,wy,esp_iw[i].memdc,x1,y1,SRCCOPY);
				ESP_Update();
				break;
			case ID_DESTROYI:
				i=ESP_SearchImageWindow(hwnd);
				esp_DestroyImage(i);
				break;
		}
		break;
	case WM_MOUSEWHEEL:
		if(LOWORD(wParam) & MK_CONTROL){
			if((short)HIWORD(wParam)<0){
			_zoomin:
				i=ESP_SearchImageWindow(hwnd);
				zm=(esp_iw[i].zoom*10+4)/9;
				ESP_ZoomImage(i,zm);
				break;
			}
			if((short)HIWORD(wParam)>0){
			_zoomout:
				i=ESP_SearchImageWindow(hwnd);
				zm=(esp_iw[i].zoom*9+5)/10;
				ESP_ZoomImage(i,zm);
				break;
			}
		}
		break;
	case WM_MOUSEMOVE:
		if(ESP_MOUSE){
			ESP_MW=ESP_SearchImageWindow(hwnd);
			ESP_MX=LOWORD(lParam)*100/esp_iw[ESP_MW].zoom;
			ESP_MY=HIWORD(lParam)*100/esp_iw[ESP_MW].zoom;
			ESP_ML=(int)wParam & MK_LBUTTON;
			ESP_MM=(int)wParam & MK_MBUTTON;
			ESP_CTRL=(int)wParam & MK_CONTROL;
			ESP_SHIFT=(int)wParam & MK_SHIFT;
		}
		if(esp_mousegetting){
		if(esp_iw[esp_getting].hwnd==hwnd){
			ESP_MMX=LOWORD(lParam)*100/esp_iw[esp_getting].zoom;
			ESP_MMY=HIWORD(lParam)*100/esp_iw[esp_getting].zoom;
			ESP_MMF=1;
		}}
		break;
	case WM_MBUTTONDOWN:
		if(ESP_MOUSE){
			ESP_MW=ESP_SearchImageWindow(hwnd);
			ESP_MX=LOWORD(lParam)*100/esp_iw[ESP_MW].zoom;
			ESP_MY=HIWORD(lParam)*100/esp_iw[ESP_MW].zoom;
			ESP_ML=(int)wParam & MK_LBUTTON;
			ESP_MM=(int)wParam & MK_MBUTTON;
			ESP_CTRL=(int)wParam & MK_CONTROL;
			ESP_SHIFT=(int)wParam & MK_SHIFT;
		}
		wParam |= MK_CONTROL;
		goto rbuttondown;
	case WM_LBUTTONDOWN:
		if(ESP_MOUSE){
			ESP_MW=ESP_SearchImageWindow(hwnd);
			ESP_MX=LOWORD(lParam)*100/esp_iw[ESP_MW].zoom;
			ESP_MY=HIWORD(lParam)*100/esp_iw[ESP_MW].zoom;
			ESP_ML=(int)wParam & MK_LBUTTON;
			ESP_MM=(int)wParam & MK_MBUTTON;
			ESP_CTRL=(int)wParam & MK_CONTROL;
			ESP_SHIFT=(int)wParam & MK_SHIFT;
		}
		if(esp_mousegetting){
		if(esp_iw[esp_getting].hwnd==hwnd){
			ESP_MLX=LOWORD(lParam)*100/esp_iw[esp_getting].zoom;
			ESP_MLY=HIWORD(lParam)*100/esp_iw[esp_getting].zoom;
			ESP_MLF=1;
			if (wParam & MK_SHIFT) ESP_SHIFT=1;else ESP_SHIFT=0;
		}}
		break;
	case WM_RBUTTONDOWN:
	rbuttondown:
		if(esp_mousegetting){
			if(esp_iw[esp_getting].hwnd==hwnd){
				ESP_MRF=1;
			}
			break;
		}
		if(esp_tw_inputflag) break;

		i=ESP_SearchImageWindow(hwnd);
		GetCursorPos(&CurPos);
		if(wParam & MK_CONTROL){
			hmenu=esp_im_menu2(i);
			TrackPopupMenu(hmenu,TPM_LEFTALIGN|TPM_RIGHTBUTTON,CurPos.x,CurPos.y,0,hwnd,NULL);
			DestroyMenu(hmenu);
		}else{
			hmenu=esp_im_menu1(hwnd);
			TrackPopupMenu(hmenu,TPM_LEFTALIGN|TPM_RIGHTBUTTON,CurPos.x,CurPos.y,0,hwnd,NULL);
			DestroyMenu(hmenu);
		}
		break;
	case WM_KEYDOWN:
		if(esp_mousegetting) break;
		
		esp_keydown= (int)wParam;

		if(GetKeyState(VK_CONTROL)<0){
			if(wParam=='X'){PostMessage(hwnd,WM_COMMAND,ID_CUT  ,0);break;}		//Ctrl+X
			if(wParam=='C'){PostMessage(hwnd,WM_COMMAND,ID_COPY ,0);break;}		//Ctrl+C
			if(wParam=='V'){PostMessage(hwnd,WM_COMMAND,ID_PASTE,0);break;}		//Ctrl+V
			if(wParam=='Q'){PostMessage(hwnd,WM_COMMAND,ID_DESTROYI,0);break;}	//Ctrl+Q
			if(wParam=='R'){PostMessage(hwnd,WM_COMMAND,ID_CLIP,0);break;}		//Ctrl+R
		
			if(wParam==VK_ADD) goto _zoomin;									//Ctrl+'+'
			if(wParam==VK_SUBTRACT) goto _zoomout;								//Ctrl+'-'
			if(wParam==VK_NUMPAD0){												//Ctrl+0
				i=ESP_SearchImageWindow(hwnd);
				ESP_ZoomImage(i,100);
				break;
			}
		}

		if(wParam=='X' || wParam==VK_ESCAPE){PostMessage(esp_mw_hwnd,WM_KEYDOWN,wParam,0);break;}	//X or ESC
		if(wParam=='S'){PostMessage(esp_mw_hwnd,WM_KEYDOWN,wParam,0);break;}	//S
		if(wParam=='C'){PostMessage(esp_mw_hwnd,WM_KEYDOWN,wParam,0);break;}	//C

		if(wParam==VK_TAB){
			i=ESP_SearchImageWindow(hwnd);
			if(ESP_GetDisplayMode(i)==COLORONCOLOR){
				ESP_SetDisplayMode(i,HALFTONE);
			}else{
				ESP_SetDisplayMode(i,COLORONCOLOR);
			}
			break;
		}
		
		break;
	case WM_CLOSE:
		i=ESP_SearchImageWindow(hwnd);
		esp_DestroyImage(i);
		break;
	case WM_DESTROY:
		break;
	default:
		return DefWindowProc(hwnd,message,wParam,lParam);
	}
	return 0;
}

//v8.0
int ESP_PlaceImage(int i,int x,int y)
{
	if(esp_iw_check(i)) return 1;

	SetWindowPos(esp_iw[i].hwnd,0,x,y,0,0,SWP_NOSIZE|esp_setpos_flags);
	
	return 0;
}

//v7.8
void ESP_PlaceMain(int x,int y)
{
	RECT rcd;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rcd,0);	//デスクトップ領域取得

	SetWindowPos(esp_mw_hwnd,0, x+rcd.left, y+rcd.top, 0,0,SWP_NOSIZE|esp_setpos_flags);
}

#define ESP_SRCBUFSIZE 30000

//テキストウィンドウ共通のウィンドウ関数
LRESULT CALLBACK ESP_TWfunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	POINT CurPos;
	HMENU esp_hpopmenu;
	int r,g,b;
	int x1,y1;
	int i,j,wx,wy,w,h,hmin,fx,fy;
	char *srcbuf;
	HGLOBAL hm;
	char *m;
	char buf[2*ESP_BUFMAX],buf2[2*ESP_BUFMAX];
	RECT rc,rcd;
	int slen;

	switch(message){
	case WM_MOVING:
		esp_wm_moving(hwnd,lParam);
		break;
	case WM_SIZING:	//v8.0
		i= ESP_SearchTextWindow(hwnd);
		if(GetKeyState(VK_SHIFT)<0){
			w= 1;
			h= 1;

		}else{
			w= esp_tw[i].w;
			h= esp_tw[i].h;
		}
		hmin= esp_tw[i].h;
		fx= esp_tw[i].fx;
		fy= esp_tw[i].fy;
		wx= ((((LPRECT)lParam)->right -((LPRECT)lParam)->left) -fx +w-1)/w*w +fx;
		wy= max(((((LPRECT)lParam)->bottom -((LPRECT)lParam)->top) -fy +h-1)/h*h,hmin) +fy;
		if(wParam%3==1) ((LPRECT)lParam)->left = ((LPRECT)lParam)->right - wx;
		else if(wParam%3==2) ((LPRECT)lParam)->right = ((LPRECT)lParam)->left + wx;
		if(wParam/3==1) ((LPRECT)lParam)->top = ((LPRECT)lParam)->bottom - wy;
		else if(wParam/3==2) ((LPRECT)lParam)->bottom = ((LPRECT)lParam)->top + wy;
		break;
	case WM_SIZE:
		//TextWindowのサイズが変更された
		i=ESP_SearchTextWindow(hwnd);
		esp_tw[i].wx=LOWORD(lParam);
		esp_tw[i].wy=HIWORD(lParam);

		SelectObject(esp_tw[i].memdc,esp_tw[i].hbitold);
		DeleteObject(esp_tw[i].hbit);
		DeleteDC(esp_tw[i].memdc);
		ReleaseDC(esp_tw[i].hwnd,esp_tw[i].hdc);

		esp_tw[i].hdc=GetDC(esp_tw[i].hwnd);
		esp_tw[i].memdc=CreateCompatibleDC(esp_tw[i].hdc);
		esp_tw[i].hbit=CreateCompatibleBitmap(esp_tw[i].hdc,esp_tw[i].wx,esp_tw[i].wy);
		SelectObject(esp_tw[i].memdc,GetStockObject(BLACK_BRUSH));
		SelectObject(esp_tw[i].memdc,GetStockObject(OEM_FIXED_FONT));
		esp_tw[i].hbitold=(HBITMAP)SelectObject(esp_tw[i].memdc,esp_tw[i].hbit);
		PatBlt(esp_tw[i].memdc,0,0,esp_tw[i].wx,esp_tw[i].wy,PATCOPY);	//for Windows95
		esp_tw[i].x=0;
		esp_tw[i].y=0;

		C2RGB(esp_tw[i].tcolor,&r,&g,&b);
		SetTextColor(esp_tw[i].memdc,RGB(r,g,b));
		C2RGB(esp_tw[i].bcolor,&r,&g,&b);
		SetBkColor(esp_tw[i].memdc,RGB(r,g,b));
		esp_list_update();
		InvalidateRect(hwnd,NULL,FALSE);
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam)){
			case ID_INFO:
				//ウィンドウ情報
				i=ESP_SearchTextWindow(hwnd);
				ESP_SelectTW(i);
				SystemParametersInfo(SPI_GETWORKAREA,0,&rcd,0);	//デスクトップ領域取得

				srcbuf = new char[ESP_SRCBUFSIZE];

				ESP_SetColor(0xffffff,0);
				ESP_SetColor(0xffff00,0);
				ESP_Printf("******* Window information *******\n");
				strcpy_s(srcbuf,ESP_SRCBUFSIZE,"\t// ESPLIB --- Automatic Source Generator\r\n");
				ESP_RestoreColor();

				//ImageWindowがあるかどうかのチェック
				j=0;
				for(i=0;i<ESP_IW_MAX;i++) if(esp_iw[i].show)j++;
				if(j){
					//ImageWindowが１つでもあれば
					ESP_SetColor(0x00ff00,0);
					ESP_Printf("[Image Window]\n");
					ESP_RestoreColor();
					strcat_s(srcbuf,ESP_SRCBUFSIZE,"\t// [Image Window]\r\n");
					for(i=0;i<ESP_IW_MAX;i++){
						if(esp_iw[i].show){
							GetWindowRect(esp_iw[i].hwnd,&rc);
							x1=rc.left-rcd.left;
							y1=rc.top-rcd.top;
							//ウィンドウ番号
							ESP_Printf(" %d ",i);
							//ビット数
							ESP_SetColor(0x0080ff,0);
							ESP_Printf("%d ",esp_iw[i].bit);
							ESP_RestoreColor();
							//フラグ
							ESP_SetColor(0xff00ff,0);
							ESP_Printf("%d ",esp_iw[i].flag);
							ESP_RestoreColor();
							//残りの情報
							ESP_Printf(" '%s' X:%d Y:%d W:%d H:%d ZM:%d%%\n",esp_iw[i].title,x1,y1,esp_iw[i].wx,esp_iw[i].wy,esp_iw[i].zoom);
							if(esp_iw[i].bit==32){
								//32bit
								if(esp_iw[i].flag){
									sprintf_s(buf,sizeof(buf),"\tESP_CreateImage(%d,\x22%s\x22,%d,%d,%d,%d,%d);\r\n",i,esp_iw[i].title,x1,y1,esp_iw[i].wx,esp_iw[i].wy,esp_iw[i].zoom);
								}else{
									sprintf_s(buf,sizeof(buf),"\tESP_CreateImageFL(%d,\x22%s\x22,%d,%d,%d,%d,%d);\r\n",i,esp_iw[i].title,x1,y1,esp_iw[i].wx,esp_iw[i].wy,esp_iw[i].zoom);
								}
							}else{
								//8bit
								if(esp_iw[i].flag){
									sprintf_s(buf,sizeof(buf),"\tESP_CreateImage8(%d,\x22%s\x22,%d,%d,%d,%d,%d);\r\n",i,esp_iw[i].title,x1,y1,esp_iw[i].wx,esp_iw[i].wy,esp_iw[i].zoom);
								}else{
									sprintf_s(buf,sizeof(buf),"\tESP_CreateImage8FL(%d,\x22%s\x22,%d,%d,%d,%d,%d);\r\n",i,esp_iw[i].title,x1,y1,esp_iw[i].wx,esp_iw[i].wy,esp_iw[i].zoom);
								}
							}
							strcat_s(srcbuf,ESP_SRCBUFSIZE,buf);
						}
					}
				}
				//TextWindow
				ESP_SetColor(0x00ff00,0);
				ESP_Printf("[Text Window]\n");
				ESP_RestoreColor();
				strcat_s(srcbuf,ESP_SRCBUFSIZE,"\t// [Text Window]\r\n");
				for(i=0;i<ESP_TW_MAX;i++){
					if(esp_tw[i].show){
						GetWindowRect(esp_tw[i].hwnd,&rc);
						x1=rc.left-rcd.left;
						y1=rc.top-rcd.top;
						ESP_Printf(" %d X:%d Y:%d W:%d H:%d\n",i,x1,y1,esp_tw[i].wx,esp_tw[i].wy);
						sprintf_s(buf,sizeof(buf),"\tESP_OpenTextWindow(%d,%d,%d,%d,%d);\r\n",i,x1,y1,esp_tw[i].wx,esp_tw[i].wy);
						strcat_s(srcbuf,ESP_SRCBUFSIZE,buf);
					}
				}
				//InputBox
				if(esp_ib_hwnd){
					ESP_SetColor(0x00ff00,0);
					ESP_Printf("[Input Box]\n");
					ESP_RestoreColor();
					strcat_s(srcbuf,ESP_SRCBUFSIZE,"\t// [Input Box]\r\n");
					GetWindowRect(esp_ib_hwnd,&rc);
					x1=rc.left-rcd.left;
					y1=rc.top-rcd.top;
					ESP_Printf(" X:%d Y:%d ITEM:%d ",x1,y1,esp_ib_num);
					sprintf_s(buf,sizeof(buf),"\tESP_OpenInputBox(%d,%d,%d);\r\n",x1,y1,esp_ib_num);
					strcat_s(srcbuf,ESP_SRCBUFSIZE,buf);
					ESP_Printf("ISIZE:%d ESIZE:%d\n",_ESP_IB_ISIZE,_ESP_IB_ESIZE);
					sprintf_s(buf,sizeof(buf),"\tESP_ResizeInputBox(%d,%d);\r\n",_ESP_IB_ISIZE,_ESP_IB_ESIZE);
					strcat_s(srcbuf,ESP_SRCBUFSIZE,buf);
					for(i=0;i<esp_ib_num;i++){
						esp_getwindowtext(esp_ib[i].title_hwnd,buf2,255);
						sprintf_s(buf,sizeof(buf),"\tESP_SetInputBoxTitle(%d,\x22%s\x22);\r\n",i,buf2);
						strcat_s(srcbuf,ESP_SRCBUFSIZE,buf);
					}
				}
				//ButtonBox
				if(esp_bb_hwnd){
					ESP_SetColor(0x00ff00,0);
					ESP_Printf("[Button Box]\n");
					ESP_RestoreColor();
					strcat_s(srcbuf,ESP_SRCBUFSIZE,"\t// [Button Box]\r\n");
					GetWindowRect(esp_bb_hwnd,&rc);
					x1=rc.left-rcd.left;
					y1=rc.top-rcd.top;
					ESP_Printf(" X:%d Y:%d NX:%d NY:%d ",x1,y1,esp_bb_nx,esp_bb_ny);
					sprintf_s(buf,sizeof(buf),"\tESP_OpenButtonBox(%d,%d,%d,%d);\r\n",x1,y1,esp_bb_nx,esp_bb_ny);
					strcat_s(srcbuf,ESP_SRCBUFSIZE,buf);

					GetClientRect(esp_bb_hwnd,&rc);
					x1=rc.right;
					y1=rc.bottom;
					ESP_Printf("SIZE:%dx%d\n",x1,y1);
					sprintf_s(buf,sizeof(buf),"\tESP_ResizeButtonBox(%d,%d);\r\n",x1,y1);
					strcat_s(srcbuf,ESP_SRCBUFSIZE,buf);

					for(i=0;i<esp_bb_num;i++){
						char *s,*ss;
						sprintf_s(buf,sizeof(buf),"\tESP_SetButtonBoxTitle(%d,\x22",i);
						strcat_s(srcbuf,ESP_SRCBUFSIZE,buf);
						esp_getwindowtext(esp_btn_hwnd[i],buf,255);
						s=buf;
						buf2[0]=0;
						//ボタンタイトルに含まれている改行コードの処理("\n"に置き換える)
						for(;;){
							ss=strchr(s,'\n');
							if(!ss){
								strcat_s(buf2,sizeof(buf2),s);
								break;
							}else{
								*ss=0;
								strcat_s(buf2,sizeof(buf2),s);
								strcat_s(buf2,sizeof(buf2),"\\n");
								s=ss+1;
							}
						}
						strcat_s(srcbuf,ESP_SRCBUFSIZE,buf2);
						strcat_s(srcbuf,ESP_SRCBUFSIZE,"\x22);\r\n");
					}
				}
				//MainWindow v7.8
				strcat_s(srcbuf,ESP_SRCBUFSIZE,"\t// [Main Window]\r\n");
				GetWindowRect(esp_mw_hwnd,&rc);
				if(esp_mw_x0 != rc.left || esp_mw_y0 != rc.top){
					rc.left -= rcd.left;
					rc.top -= rcd.top;
					sprintf_s(buf,sizeof(buf),"\tESP_PlaceMain(%d,%d);\r\n",rc.left,rc.top);
					strcat_s(srcbuf,ESP_SRCBUFSIZE,buf);
					ESP_SetColor(0x00ff00,0);
					ESP_Printf("[Main Window]\n");
					ESP_RestoreColor();
					ESP_Printf(" X:%d Y:%d\n",rc.left,rc.top);
				}
				strcat_s(srcbuf,ESP_SRCBUFSIZE,"\tESP_SetForeground(ESPMAINWINDOW);\r\n");

				ESP_SetColor(0xffff00,0);
				ESP_Printf("**********************************\n");
				ESP_RestoreColor();

				if (!OpenClipboard(NULL)) goto esp_fin_info;
				EmptyClipboard();
				slen=(int)strlen(srcbuf)+1;
				hm=GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE,slen);
				if(hm){
					m=(char *)GlobalLock(hm);
					strcpy_s(m,slen,srcbuf);
					GlobalUnlock(hm);
					SetClipboardData(CF_TEXT,hm);
					CloseClipboard();
					ESP_SetColor(0xffff00,0x80);
					ESP_Printf("クリップボードにレイアウト作成ソースリストを保存しました．\n");
					ESP_RestoreColor();
				}else{
					ESP_Pause("GlobalAlloc() failed. (ID_INFO)");
				}

			esp_fin_info:
				delete[] srcbuf;
				ESP_RestoreColor();
				break;
			case ID_COPYLOG:
				i=ESP_SearchTextWindow(hwnd);
				ESP_CopyLog(i);
				break;
			case ID_COMMAND:
				ESP_Command();
				break;
			case ID_STARTLOG:
				i=ESP_SearchTextWindow(hwnd);
				ESP_StartLog(i);
				break;
			case ID_STOPLOG:
				i=ESP_SearchTextWindow(hwnd);
				ESP_StopLog(i);
				break;
			case ID_ABOUT:
				i=ESP_SearchTextWindow(hwnd);
				ESP_SelectTW(i);
				ESP_SetColor(0x50ff50,0x505050);
				ESP_Printf(ESP_STR_ABOUT "\n");
				ESP_RestoreColor();
				break;
			case ID_SELECTTW:
				i=ESP_SearchTextWindow(hwnd);
				ESP_SelectTW(i);
				break;
			case ID_DESTROYTW:
				i=ESP_SearchTextWindow(hwnd);
				esp_CloseTextWindow(i);
				break;
		}
		break;
	case WM_RBUTTONDOWN:
		if(esp_tw_inputflag) break;
		if(esp_mousegetting) break;
		i=ESP_SearchTextWindow(hwnd);
		GetCursorPos(&CurPos);
		esp_hpopmenu=CreatePopupMenu();
		b=(esp_twi==i)?MFS_CHECKED:0;
		esp_AppendMenu   (esp_hpopmenu,0,MFS_ENABLED|b,ID_SELECTTW,"&Select\tCtrl+S");
		esp_AppendMenu   (esp_hpopmenu,1,MFS_ENABLED,ID_INFO,"&Window Info.\tCtrl+W");
		esp_AppendMenu   (esp_hpopmenu,2,MFS_ENABLED,ID_COMMAND,"Command");
		esp_AppendMenuSEP(esp_hpopmenu,3);
		b=(esp_tw[i].logstatus==1)?MFS_CHECKED:0;
		esp_AppendMenu   (esp_hpopmenu,4,MFS_ENABLED|b,ID_STARTLOG,"Start Log");
		b=(esp_tw[i].logstatus==2)?MFS_CHECKED:0;
		esp_AppendMenu   (esp_hpopmenu,5,MFS_ENABLED|b,ID_STOPLOG,"Stop Log");
		sprintf_s(buf,sizeof(buf),"&Copy ESPLIB%d%d.log\tCtrl+C",esp_id,i);
		esp_AppendMenu   (esp_hpopmenu,6,MFS_ENABLED,ID_COPYLOG,buf);
		esp_AppendMenuSEP(esp_hpopmenu,7);
		esp_AppendMenu   (esp_hpopmenu,8,MFS_ENABLED,ID_ABOUT,"&About ESPLIB\tCtrl+A");
		esp_AppendMenuSEP(esp_hpopmenu,9);
		esp_AppendMenu   (esp_hpopmenu,10,MFS_ENABLED,ID_DESTROYTW,"&Destroy\tCtrl+Q");
		TrackPopupMenu(esp_hpopmenu,TPM_LEFTALIGN|TPM_RIGHTBUTTON
			,CurPos.x,CurPos.y,0,hwnd,NULL);
		DestroyMenu(esp_hpopmenu);
		break;
	case WM_KEYDOWN:
		if(esp_tw_inputflag){
			if(!esp_tw_ctrl){
				if(wParam==VK_UP) esp_tw_ctrl=ESP_TWCTRL_HISTORY;
				if(wParam=='V' && GetKeyState(VK_CONTROL)<0) esp_tw_ctrl=ESP_TWCTRL_PASTE;
			}
			break;
		}

		i=ESP_SearchTextWindow(hwnd);
		if(GetKeyState(VK_CONTROL)<0){
			if(wParam=='A'){PostMessage(esp_tw[i].hwnd,WM_COMMAND,ID_ABOUT,0);break;}		//Ctrl+A
			if(wParam=='C'){PostMessage(esp_tw[i].hwnd,WM_COMMAND,ID_COPYLOG,0);break;}		//Ctrl+C
			if(wParam=='W'){PostMessage(esp_tw[i].hwnd,WM_COMMAND,ID_INFO,0);break;}		//Ctrl+W
			if(wParam=='Q'){PostMessage(esp_tw[i].hwnd,WM_COMMAND,ID_DESTROYTW,0);break;}	//Ctrl+Q
			if(wParam=='S'){PostMessage(esp_tw[i].hwnd,WM_COMMAND,ID_SELECTTW,0);break;}	//Ctrl+S
		}else{
			if(wParam=='X' || wParam==VK_ESCAPE){PostMessage(esp_mw_hwnd,WM_KEYDOWN,wParam,0);break;}	//X or ESC
			if(wParam=='S'){PostMessage(esp_mw_hwnd,WM_KEYDOWN,wParam,0);break;}							//S
			if(wParam=='C'){PostMessage(esp_mw_hwnd,WM_KEYDOWN,wParam,0);break;}							//C		
			if(wParam==VK_SPACE){															//SPACE
				CM();	//v7.7
				ESP_SelectTW(i);
				ESP_Command();
				break;
			}
		}
		break;
	case WM_CHAR:
		if(esp_tw_inputflag){
			if(GetKeyState(VK_CONTROL)<0) break;
			if (esp_tw_wp == esp_tw_rp) break;		//buffer full
			esp_tw_buffer[esp_tw_wp]=(wchar_t)wParam;
			if (esp_tw_rp<0) esp_tw_rp=esp_tw_wp;
			if ((esp_tw_wp+1) == ESPTWBUFMAX) esp_tw_wp=0; else esp_tw_wp++;
		}
		break;
	case WM_PAINT:
		esp_tw_get();		//v7.8
		i=ESP_SearchTextWindow(hwnd);
		BeginPaint(hwnd,&ps);
		BitBlt(esp_tw[i].hdc,
			ps.rcPaint.left,
			ps.rcPaint.top,
			ps.rcPaint.right - ps.rcPaint.left,
			ps.rcPaint.bottom - ps.rcPaint.top,
			esp_tw[i].memdc,
			ps.rcPaint.left,
			ps.rcPaint.top,
			SRCCOPY);
		EndPaint(hwnd,&ps);
		esp_tw_release();	//v7.8
		break;
	case WM_DESTROY:
		break;
	case WM_CLOSE:
		i=ESP_SearchTextWindow(hwnd);
		esp_CloseTextWindow(i);
		break;
	default:
		return DefWindowProc(hwnd,message,wParam,lParam);
	}
	return 0;
}

void ESP_ClearTextWindow(void)
{
	if(!esp_tw[esp_twi].show) return;

	PatBlt(esp_tw[esp_twi].memdc,0,0,esp_tw[esp_twi].wx,esp_tw[esp_twi].wy,PATCOPY);
	esp_tw[esp_twi].x=0;
	esp_tw[esp_twi].y=0;
	InvalidateRect(esp_tw[esp_twi].hwnd,NULL,FALSE);
	if(esp_tw[esp_twi].logstatus==1){
		fputc('\n',esp_tw[esp_twi].logfile);
	}
}

//7.0 (cx,cy...-1:don't care)
void ESP_Locate(int cx,int cy)
{
	if(!esp_tw[esp_twi].show) return;

	if(cx!=-1){
		int w=esp_tw[esp_twi].w;
		int nx=cx*w;	
		if(nx>=0 && nx+w<esp_tw[esp_twi].wx){
			esp_tw[esp_twi].x=nx;
		}
	}

	if(cy!=-1){
		int h=esp_tw[esp_twi].h;
		int ny=cy*h;	
		if(ny>=0 && ny+h<esp_tw[esp_twi].wy){
			esp_tw[esp_twi].y=ny;
		}
	}
}

// 7.0
int ESP_ImageOpen(const char *name,int x0,int y0,int zoom,int *i,int *wx,int *wy)
{
	int b;
	int r=ESP_GetImageInfo(name,wx,wy,&b);
	*i=0;
	if(r) return r;

	for(int j=0;j<ESP_IW_MAX;j++){
		r=ESP_CreateImage(j,name,x0,y0,*wx,*wy,zoom);
		if(!r){
			*i=j;
			esp_ImageLoad(name,0,0,100);
			ESP_Update();
			return 0;
		}
	}
	return 2;
}


// 双線形補間(Bilinear Interpolation)によるサブピクセル精度でのカラー情報の取得
int ESP_PointBLI(double x, double y)
{
	double intvalue;

	double ax=modf(x,&intvalue);
	int ix=(int)intvalue;	// 111% speed up
	double ay=modf(y,&intvalue);
	int iy=(int)intvalue;	// 111% speed up

	int c1=ESP_Point(ix  ,iy  );
	int c2=ESP_Point(ix+1,iy  );
	int c3=ESP_Point(ix  ,iy+1);
	int c4=ESP_Point(ix+1,iy+1);

	int i1,i2,i3,i4;

	i1=C2R(c1); i2=C2R(c2); i3=C2R(c3); i4=C2R(c4);
	int r=Limit(0,(int)floor(i1*(1.0-ax)*(1.0-ay)+i2*(ax)*(1.0-ay)+i3*(1.0-ax)*(ay)+i4*(ax)*(ay)+0.5),255);
	//r=Limit(0, (int)floor(ax*ay*(i1-i2-i3+i4)+ay*(i3-i1)+ax*(i2-i1)+i1+0.5) ,255);

	i1=C2G(c1); i2=C2G(c2); i3=C2G(c3); i4=C2G(c4);
	int g=Limit(0,(int)floor(i1*(1.0-ax)*(1.0-ay)+i2*(ax)*(1.0-ay)+i3*(1.0-ax)*(ay)+i4*(ax)*(ay)+0.5),255);
	//g=Limit(0, (int)floor(ax*ay*(i1-i2-i3+i4)+ay*(i3-i1)+ax*(i2-i1)+i1+0.5) ,255);

	i1=C2B(c1); i2=C2B(c2); i3=C2B(c3); i4=C2B(c4);
	int b=Limit(0,(int)floor(i1*(1.0-ax)*(1.0-ay)+i2*(ax)*(1.0-ay)+i3*(1.0-ax)*(ay)+i4*(ax)*(ay)+0.5),255);
	//b=Limit(0, (int)floor(ax*ay*(i1-i2-i3+i4)+ay*(i3-i1)+ax*(i2-i1)+i1+0.5) ,255);

	return RGB2C(r,g,b);
}

// 画像縮小用Point関数（バイリニア補間）
// x,y ... 注目する座標
// zx,zy ... 平均をとるピクセル幅（範囲：1.0~3.0）
int ESP_PointZoom(double x, double y, double zx, double zy)
{
	double area=zx*zy;
	double x0=x-zx/2.0;
	double y0=y-zy/2.0;
	
	double a[4],b[4];
	double i;

	a[0]=1.0-modf(x0,&i);
	int ix0=(int)i;
	zx-=a[0];
	if(zx>=1.0){
		a[1]=1.0;
		zx-=1.0;
	}else{
		a[1]=zx;
		zx-=zx;
	}
	if(zx>=1.0){
		a[2]=1.0;
		zx-=1.0;
	}else{
		a[2]=zx;
		zx-=zx;
	}
	a[3]=zx;

	b[0]=1.0-modf(y0,&i);
	int iy0=(int)i;
	zy-=b[0];
	if(zy>=1.0){
		b[1]=1.0;
		zy-=1.0;
	}else{
		b[1]=zy;
		zy-=zy;
	}
	if(zy>=1.0){
		b[2]=1.0;
		zy-=1.0;
	}else{
		b[2]=zy;
		zy-=zy;
	}
	b[3]=zy;

	double dr,dg,db;

	dr = a[0]*b[0]*ESP_PointR(ix0,iy0  ) + a[1]*b[0]*ESP_PointR(ix0+1,iy0  ) + a[2]*b[0]*ESP_PointR(ix0+2,iy0  ) + a[3]*b[0]*ESP_PointR(ix0+3,iy0  )
	   + a[0]*b[1]*ESP_PointR(ix0,iy0+1) + a[1]*b[1]*ESP_PointR(ix0+1,iy0+1) + a[2]*b[1]*ESP_PointR(ix0+2,iy0+1) + a[3]*b[1]*ESP_PointR(ix0+3,iy0+1)
	   + a[0]*b[2]*ESP_PointR(ix0,iy0+2) + a[1]*b[2]*ESP_PointR(ix0+1,iy0+2) + a[2]*b[2]*ESP_PointR(ix0+2,iy0+2) + a[3]*b[2]*ESP_PointR(ix0+3,iy0+2)
	   + a[0]*b[3]*ESP_PointR(ix0,iy0+3) + a[1]*b[3]*ESP_PointR(ix0+1,iy0+3) + a[2]*b[3]*ESP_PointR(ix0+2,iy0+3) + a[3]*b[3]*ESP_PointR(ix0+3,iy0+3);
	int R=(int)(dr/area);

	dg = a[0]*b[0]*ESP_PointG(ix0,iy0  ) + a[1]*b[0]*ESP_PointG(ix0+1,iy0  ) + a[2]*b[0]*ESP_PointG(ix0+2,iy0  ) + a[3]*b[0]*ESP_PointG(ix0+3,iy0  )
	   + a[0]*b[1]*ESP_PointG(ix0,iy0+1) + a[1]*b[1]*ESP_PointG(ix0+1,iy0+1) + a[2]*b[1]*ESP_PointG(ix0+2,iy0+1) + a[3]*b[1]*ESP_PointG(ix0+3,iy0+1)
	   + a[0]*b[2]*ESP_PointG(ix0,iy0+2) + a[1]*b[2]*ESP_PointG(ix0+1,iy0+2) + a[2]*b[2]*ESP_PointG(ix0+2,iy0+2) + a[3]*b[2]*ESP_PointG(ix0+3,iy0+2)
	   + a[0]*b[3]*ESP_PointG(ix0,iy0+3) + a[1]*b[3]*ESP_PointG(ix0+1,iy0+3) + a[2]*b[3]*ESP_PointG(ix0+2,iy0+3) + a[3]*b[3]*ESP_PointG(ix0+3,iy0+3);
	int G=(int)(dg/area);

	db = a[0]*b[0]*ESP_PointB(ix0,iy0  ) + a[1]*b[0]*ESP_PointB(ix0+1,iy0  ) + a[2]*b[0]*ESP_PointB(ix0+2,iy0  ) + a[3]*b[0]*ESP_PointB(ix0+3,iy0  )
	   + a[0]*b[1]*ESP_PointB(ix0,iy0+1) + a[1]*b[1]*ESP_PointB(ix0+1,iy0+1) + a[2]*b[1]*ESP_PointB(ix0+2,iy0+1) + a[3]*b[1]*ESP_PointB(ix0+3,iy0+1)
	   + a[0]*b[2]*ESP_PointB(ix0,iy0+2) + a[1]*b[2]*ESP_PointB(ix0+1,iy0+2) + a[2]*b[2]*ESP_PointB(ix0+2,iy0+2) + a[3]*b[2]*ESP_PointB(ix0+3,iy0+2)
	   + a[0]*b[3]*ESP_PointB(ix0,iy0+3) + a[1]*b[3]*ESP_PointB(ix0+1,iy0+3) + a[2]*b[3]*ESP_PointB(ix0+2,iy0+3) + a[3]*b[3]*ESP_PointB(ix0+3,iy0+3);
	int B=(int)(db/area);

	return RGB2C(R,G,B);
}

//for 0 <= t < 1
__inline double esp_fBCI1(double t)
{
	return 1.0 -2.0*t*t +t*t*t;
}

//for 1 <= t <= 2
__inline double esp_fBCI2(double t)
{
	return 4.0 -8.0*t +5.0*t*t -t*t*t;
}

// 共３次畳み込み内挿法によるサブピクセル精度でのカラー情報の取得 ver.6.6
//（双３次補間/Bicuibc interpolation）
int ESP_PointBCI(double x, double y)
{
	double intvalue;

	double ax=modf(x,&intvalue);
	int ix=(int)intvalue;	// 111% speed up
	double ay=modf(y,&intvalue);
	int iy=(int)intvalue;	// 111% speed up

	int c11=ESP_Point(ix-1,iy-1);
	int c21=ESP_Point(ix  ,iy-1);
	int c31=ESP_Point(ix+1,iy-1);
	int c41=ESP_Point(ix+2,iy-1);
	int c12=ESP_Point(ix-1,iy  );
	int c22=ESP_Point(ix  ,iy  );
	int c32=ESP_Point(ix+1,iy  );
	int c42=ESP_Point(ix+2,iy  );
	int c13=ESP_Point(ix-1,iy+1);
	int c23=ESP_Point(ix  ,iy+1);
	int c33=ESP_Point(ix+1,iy+1);
	int c43=ESP_Point(ix+2,iy+1);
	int c14=ESP_Point(ix-1,iy+2);
	int c24=ESP_Point(ix  ,iy+2);
	int c34=ESP_Point(ix+1,iy+2);
	int c44=ESP_Point(ix+2,iy+2);

	double d;
	int i11,i21,i31,i41;
	int i12,i22,i32,i42;
	int i13,i23,i33,i43;
	int i14,i24,i34,i44;

	//red
	i11=C2R(c11); i21=C2R(c21); i31=C2R(c31); i41=C2R(c41);
	i12=C2R(c12); i22=C2R(c22); i32=C2R(c32); i42=C2R(c42);
	i13=C2R(c13); i23=C2R(c23); i33=C2R(c33); i43=C2R(c43);
	i14=C2R(c14); i24=C2R(c24); i34=C2R(c34); i44=C2R(c44);
	d =  esp_fBCI2(1.0+ax)*esp_fBCI2(1.0+ay)*i11
		+esp_fBCI1(    ax)*esp_fBCI2(1.0+ay)*i21
		+esp_fBCI1(1.0-ax)*esp_fBCI2(1.0+ay)*i31
		+esp_fBCI2(2.0-ax)*esp_fBCI2(1.0+ay)*i41
	    +esp_fBCI2(1.0+ax)*esp_fBCI1(    ay)*i12
	    +esp_fBCI1(    ax)*esp_fBCI1(    ay)*i22
	    +esp_fBCI1(1.0-ax)*esp_fBCI1(    ay)*i32
	    +esp_fBCI2(2.0-ax)*esp_fBCI1(    ay)*i42
	    +esp_fBCI2(1.0+ax)*esp_fBCI1(1.0-ay)*i13
	    +esp_fBCI1(    ax)*esp_fBCI1(1.0-ay)*i23
	    +esp_fBCI1(1.0-ax)*esp_fBCI1(1.0-ay)*i33
	    +esp_fBCI2(2.0-ax)*esp_fBCI1(1.0-ay)*i43
	    +esp_fBCI2(1.0+ax)*esp_fBCI2(2.0-ay)*i14
	    +esp_fBCI1(    ax)*esp_fBCI2(2.0-ay)*i24
	    +esp_fBCI1(1.0-ax)*esp_fBCI2(2.0-ay)*i34
	    +esp_fBCI2(2.0-ax)*esp_fBCI2(2.0-ay)*i44;
	int r=Limit(0,(int)floor(d+0.5),255);

	//green
	i11=C2G(c11); i21=C2G(c21); i31=C2G(c31); i41=C2G(c41);
	i12=C2G(c12); i22=C2G(c22); i32=C2G(c32); i42=C2G(c42);
	i13=C2G(c13); i23=C2G(c23); i33=C2G(c33); i43=C2G(c43);
	i14=C2G(c14); i24=C2G(c24); i34=C2G(c34); i44=C2G(c44);
	d =  esp_fBCI2(1.0+ax)*esp_fBCI2(1.0+ay)*i11
		+esp_fBCI1(    ax)*esp_fBCI2(1.0+ay)*i21
		+esp_fBCI1(1.0-ax)*esp_fBCI2(1.0+ay)*i31
		+esp_fBCI2(2.0-ax)*esp_fBCI2(1.0+ay)*i41
	    +esp_fBCI2(1.0+ax)*esp_fBCI1(    ay)*i12
	    +esp_fBCI1(    ax)*esp_fBCI1(    ay)*i22
	    +esp_fBCI1(1.0-ax)*esp_fBCI1(    ay)*i32
	    +esp_fBCI2(2.0-ax)*esp_fBCI1(    ay)*i42
	    +esp_fBCI2(1.0+ax)*esp_fBCI1(1.0-ay)*i13
	    +esp_fBCI1(    ax)*esp_fBCI1(1.0-ay)*i23
	    +esp_fBCI1(1.0-ax)*esp_fBCI1(1.0-ay)*i33
	    +esp_fBCI2(2.0-ax)*esp_fBCI1(1.0-ay)*i43
	    +esp_fBCI2(1.0+ax)*esp_fBCI2(2.0-ay)*i14
	    +esp_fBCI1(    ax)*esp_fBCI2(2.0-ay)*i24
	    +esp_fBCI1(1.0-ax)*esp_fBCI2(2.0-ay)*i34
	    +esp_fBCI2(2.0-ax)*esp_fBCI2(2.0-ay)*i44;
	int g=Limit(0,(int)floor(d+0.5),255);

	//blue
	i11=C2B(c11); i21=C2B(c21); i31=C2B(c31); i41=C2B(c41);
	i12=C2B(c12); i22=C2B(c22); i32=C2B(c32); i42=C2B(c42);
	i13=C2B(c13); i23=C2B(c23); i33=C2B(c33); i43=C2B(c43);
	i14=C2B(c14); i24=C2B(c24); i34=C2B(c34); i44=C2B(c44);
	d =  esp_fBCI2(1.0+ax)*esp_fBCI2(1.0+ay)*i11
		+esp_fBCI1(    ax)*esp_fBCI2(1.0+ay)*i21
		+esp_fBCI1(1.0-ax)*esp_fBCI2(1.0+ay)*i31
		+esp_fBCI2(2.0-ax)*esp_fBCI2(1.0+ay)*i41
	    +esp_fBCI2(1.0+ax)*esp_fBCI1(    ay)*i12
	    +esp_fBCI1(    ax)*esp_fBCI1(    ay)*i22
	    +esp_fBCI1(1.0-ax)*esp_fBCI1(    ay)*i32
	    +esp_fBCI2(2.0-ax)*esp_fBCI1(    ay)*i42
	    +esp_fBCI2(1.0+ax)*esp_fBCI1(1.0-ay)*i13
	    +esp_fBCI1(    ax)*esp_fBCI1(1.0-ay)*i23
	    +esp_fBCI1(1.0-ax)*esp_fBCI1(1.0-ay)*i33
	    +esp_fBCI2(2.0-ax)*esp_fBCI1(1.0-ay)*i43
	    +esp_fBCI2(1.0+ax)*esp_fBCI2(2.0-ay)*i14
	    +esp_fBCI1(    ax)*esp_fBCI2(2.0-ay)*i24
	    +esp_fBCI1(1.0-ax)*esp_fBCI2(2.0-ay)*i34
	    +esp_fBCI2(2.0-ax)*esp_fBCI2(2.0-ay)*i44;
	int b=Limit(0,(int)floor(d+0.5),255);

	return RGB2C(r,g,b);
}

//---時間待ち関数(単位:ミリ秒)---
//(待っている間のStopチェック&メッセージ処理あり)
int ESP_Sleep(int msec)
{
	LARGE_INTEGER esp_li_time0,esp_li_time1;
	long double esp_ld_fpms;	//esp_ld_fpmsをローカル変数にした 20210113 kinya iwamoto
	QueryPerformanceFrequency(&esp_li_freq);
	esp_ld_fpms = (long double)(1000.0 / esp_li_freq.QuadPart);

	QueryPerformanceCounter(&esp_li_time0);
	for(;;){
		QueryPerformanceCounter(&esp_li_time1);
		double esp_d_time = (esp_li_time1.QuadPart - esp_li_time0.QuadPart)*esp_ld_fpms;
		int t = (int)floor(esp_d_time+0.5);
		if(t >= msec) break;
		if(ESP_STOP) return 1;
	}
	return 0;
}

//Bezier（ベジェ）曲線の描画
// x=(1-t)^3 x0 + 3t(1-t)^2 x1 + 3t^2(1-t) x2 + t^3 x3				
// y=(1-t)^3 y0 + 3t(1-t)^2 y1 + 3t^2(1-t) y2 + t 3 y3				
// div:分割数  例:20.0
void ESP_Bezier(int x0,int y0,int x1,int y1,int x2,int y2,int x3,int y3, int div, int c)
{
	double tstep=1.0/(double)div;
	int _x=x0;
	int _y=y0;

	for(double t=tstep; t<=1.00001; t+=tstep){
		double t2=t*t;
		double t3=t2*t;
		double _t=1.-t;
		double _t2=_t*_t;
		double _t3=_t2*_t;
		int x = (int)( _t3*x0 + 3.*t*_t2*x1 + 3.*t2*_t*x2 + t3*x3);
		int y = (int)( _t3*y0 + 3.*t*_t2*y1 + 3.*t2*_t*y2 + t3*y3);
		ESP_Line(_x,_y,x,y,c);
		_x=x;
		_y=y;
	}
}

//Bezier（ベジェ）曲線の描画 XOR
void ESP_BezierXOR(int x0,int y0,int x1,int y1,int x2,int y2,int x3,int y3, int div)
{
	double tstep=1.0/(double)div;
	int _x=x0;
	int _y=y0;

	for(double t=tstep; t<=1.00001; t+=tstep){
		double t2=t*t;
		double t3=t2*t;
		double _t=1.-t;
		double _t2=_t*_t;
		double _t3=_t2*_t;
		int x = (int)( _t3*x0 + 3.*t*_t2*x1 + 3.*t2*_t*x2 + t3*x3);
		int y = (int)( _t3*y0 + 3.*t*_t2*y1 + 3.*t2*_t*y2 + t3*y3);
		ESP_LineXOR(_x,_y,x,y);
		if(t!=tstep) ESP_PsetXOR(_x,_y);
		_x=x;
		_y=y;
	}
}

//ライブラリモードで使うための関数 v8.0
#ifdef ESP_LIBRARY_MODE
//HANDLE esp_hstart;
unsigned __stdcall _esp_start(void *arglist)
{
	esp_hInst = GetModuleHandle(NULL);
	esp_WinMain(esp_hInst, NULL, NULL, 0);

#ifndef _MFC_VER
	//スレッド終了処理
	//非MFCではここにCloseHandleを行ってもエラーは出ないがハンドルの解放は出来ていない。20210113　kinya iwamoto
	//CloseHandle(esp_hstart);	
	//esp_hstart= NULL;
	::_endthreadex(0);
#else
	//20210113　kinya iwamoto
	//CloseHandleを書いておかないとボタンウインドウが表示されない。esp_hInstがうまく制御できていない。releseモードのみ
	//releseモードのみesp_hInstがうまく制御できていない原因はテキストウインドウを生成するときのCreateWindowでesp_hInstが
	//書き換わってします。esp_OpenTextWindow関数の修正箇所を参照。
	//CloseHandleを残してAfxEndThreadで終了するとエラーになる（原因：ハンドルesp_hstartを先に解放してしまうため）

	//スレッド終了処理
	//CloseHandle(esp_hstart);	
	::AfxEndThread(0);			
#endif // !_MFC_VER				

	return 0;
}
//mw_show=0:表示しない 1:表示する
void ESP_Start(int mw_show=0)
{
	if(esp_running) return;
	esp_mw_show= mw_show;
	//MFCではスレッドの開始にAfxBeginThread、スレッド関数の終了にAfxEndThreadを使用する。MFC環境で_beginthreadexを
	//使用するとハンドルを解放できないなどの具合を生じた経験がある。20210113　kinya iwamoto
#ifndef _MFC_VER					
	esp_hstart = (HANDLE)_beginthreadex(NULL, 0, _esp_start, NULL, 0, NULL);
#else
	pRecvThread_esp_start = ::AfxBeginThread(_esp_start, NULL, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
	esp_hstart = pRecvThread_esp_start->m_hThread;
	pRecvThread_esp_start->m_bAutoDelete = FALSE;	// 自動破棄フラグクリア
	pRecvThread_esp_start->ResumeThread();			// サスペンド解除
#endif // !_MFC_VER

	while(!esp_running) Sleep(1);
}
void ESP_Ready(void)
{
}
void ESP_Main(void)
{
}
void ESP_Finish(void)
{
}
#endif

//End of esplib.h
