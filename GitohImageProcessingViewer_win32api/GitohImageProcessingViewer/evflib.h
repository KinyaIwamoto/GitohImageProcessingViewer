// EVFLIB [Easy Video Frame LIBrary]
//          version 1.2
// Copyright (C) 2016-2018 I.N.  All rights reserved.

// OS: Windows 10
// Compiler: Visual C++ 2015/2017

// 2013/08/13-9/2 ver.1.0 初版
// 2016/05/20 ver.1.1 一部の環境でEVF_Close()時に強制終了する不具合を修正
// 2017/05/30 ver.1.2 Visual C++ 2017対応

#pragma once
#define EVFLIB_H

//#define EVF_DEBUG

#include <dshow.h>
#pragma include_alias( "dxtrans.h", "qedit.h" )
#define __IDxtCompositor_INTERFACE_DEFINED__
#define __IDxtAlphaSetter_INTERFACE_DEFINED__
#define __IDxtJpeg_INTERFACE_DEFINED__
#define __IDxtKey_INTERFACE_DEFINED__
#include "qedit.h"
#pragma comment(lib,"strmiids.lib")

#ifndef EVF_TYPE
	#ifdef _CV_H_
		#define EVF_TYPE MEDIASUBTYPE_RGB24
	#else
		#ifdef __OPENCV_CV_H__
			#define EVF_TYPE MEDIASUBTYPE_RGB24
		#else
			#define EVF_TYPE MEDIASUBTYPE_RGB32
		#endif
	#endif
#endif

#ifdef EVF_DEBUG
	#pragma comment(lib,"quartz.lib")
#endif

//タイムアウト時間(単位:ms)
#define EVF_TIMEOUT_BUFSIZE 5000
#define EVF_TIMEOUT_PAUSE   1000
#define EVF_TIMEOUT_WAIT    1000

#define evf_release(x) {if(x)x->Release();x=0;}

int evf_cominit=0;	//COM初期化フラグ(1なら終了処理を行う)
int evf_init=0;		//EMDLIBを初期化したら1

//構造体の定義
struct evf_struct{
	int init;						//初期化フラグ
	int wx;							//画像の幅
	int wy;							//画像の高さ
	int bit;						//画像のビット数
	char filename[MAX_PATH];		//動画ファイル名
	unsigned char *img;				//バッファの先頭アドレス
	unsigned char *pbuf;			//画像格納アドレス
	volatile long bufsize;			//バッファサイズ
	LONGLONG AvgTimePerFrame;		//平均フレーム時間(100ナノ秒単位)
	LONGLONG MaxTime;				//総動画時間(100ナノ秒単位)
	LONGLONG CurTime;				//現在位置(100ナノ秒単位)
	int frames;						//総フレーム数
	int frame;						//現在のフレーム番号
	IGraphBuilder *pGraphBuilder;
	IBaseFilter *pGrabberF;
	ISampleGrabber *pGrabber;
	IBaseFilter *pVmr9;
	IMediaControl *pMediaControl;
	IMediaSeeking *pMediaSeeking;
	IVideoFrameStep *pVFS;
	volatile int buf_enable;		//バッファ準備完了フラグ
	volatile int wait;				//転送未完了フラグ
	volatile double SampleTime;		//サンプル時刻(秒)
	volatile double _SampleTime;	//１つ前のサンプル時刻(秒)
	int count;
	int count_per_seek;		//Seek１回につき何回BufferCB()が発生するか
	int afterseek;
};

//最大同時オープン数
#ifndef EVF_OPENMAX
	#define EVF_OPENMAX 10	
#endif

//構造体の宣言
evf_struct evf_s[EVF_OPENMAX];

//コールバック関数の定義
class evf_SampleGrabberCB :public ISampleGrabberCB
{
public:
	STDMETHODIMP_(ULONG) AddRef()
	{
		return 2;
	}
	STDMETHODIMP_(ULONG) Release()
	{
		return 1;
	}
	STDMETHODIMP QueryInterface(REFIID riid, void ** ppv)
	{
		if(riid==IID_ISampleGrabberCB || riid==IID_IUnknown){
			*ppv= (void *)static_cast<ISampleGrabberCB*>(this);
			return NOERROR;
		}
		return E_NOINTERFACE;
	}
	STDMETHODIMP SampleCB(double SampleTime, IMediaSample *pSample)
	{
		return S_OK;
	}
	//フレーム毎に呼ばれる関数
	STDMETHODIMP BufferCB(double dblSampleTime, BYTE *pBuffer, long lBufferSize)
	{
		evf_s[i].count++;

		evf_s[i].bufsize= lBufferSize;

		if(evf_s[i].buf_enable){
			int wx= evf_s[i].wx;
			int wy= evf_s[i].wy;
			int byte= lBufferSize/wy;
			//画像の上下を逆にしてコピー
			for(int y=0; y<wy; y++){
				memcpy(evf_s[i].pbuf+(wy-1-y)*byte, pBuffer+y*byte, byte);
			}
		}

		if(evf_s[i].wait) evf_s[i].wait--;

		evf_s[i]._SampleTime= evf_s[i].SampleTime;
		evf_s[i].SampleTime= dblSampleTime;

		return S_OK;
	}
	//コンストラクタ	
	evf_SampleGrabberCB(int num)
	{
		i=num;
		evf_s[i].bufsize=0;
	}
	//デストラクタ
	~evf_SampleGrabberCB()
	{
	}
private:
	int i;
};

evf_SampleGrabberCB *evf_pSampleGrabberCB[EVF_OPENMAX];

//番号iの範囲チェック，初期化済みのチェック
int evf_i_check(int i)
{
	if((unsigned int)i>=EVF_OPENMAX) return 1;
	if(!evf_s[i].init) return 2;
	return 0;
}

void evf_FreeMediaType(AM_MEDIA_TYPE& mt)
{
	if(mt.cbFormat){
		CoTaskMemFree((PVOID)mt.pbFormat);
		mt.cbFormat = 0;
		mt.pbFormat = NULL;
	}
	if(mt.pUnk){
		evf_release(mt.pUnk);
	}
}

void evf_DeleteMediaType(AM_MEDIA_TYPE *pmt)
{
	if(pmt){
        evf_FreeMediaType(*pmt); 
        CoTaskMemFree(pmt);
    }
}

//ピンのタイプがmajortypeかどうか調べる(yes=1)
int evf_checkpintype(IPin *pPin, GUID majortype)
{
	HRESULT hr;
	IEnumMediaTypes *pEmt=0;
	AM_MEDIA_TYPE *pmt=0;
	int found=0;

	hr= pPin->EnumMediaTypes(&pEmt);
	while(pEmt->Next(1,&pmt,0)==S_OK){
		if(pmt->majortype == majortype){
			found=1;
			evf_DeleteMediaType(pmt);
			break;
		}
		evf_DeleteMediaType(pmt);
	}
	evf_release(pEmt);
	
	return found;
}

//フィルタpFilterのピン（PinDirで方向指定）を取得する
// ＜オプション＞
//   majortype:この値がGUID_NULLでなく，該当ピンが複数あったときは，majortypeの条件付きとなる
IPin *evf_GetPin(IBaseFilter *pFilter, PIN_DIRECTION PinDir, GUID majortype=GUID_NULL)
{
	HRESULT hr;

	IEnumPins *pEnum;
	IPin *pPin=0;
	int num=0;

	//ピン数を調べる
	hr= pFilter->EnumPins(&pEnum);
	if(hr!=S_OK) return NULL;
	while(pEnum->Next(1,&pPin,0)==S_OK){
		//方向を調べる
		PIN_DIRECTION PinDirThis;
		pPin->QueryDirection(&PinDirThis);
		if(PinDir==PinDirThis) num++;
		evf_release(pPin);
	}
	evf_release(pEnum);

	hr= pFilter->EnumPins(&pEnum);
	if(hr!=S_OK) return NULL;
	while(pEnum->Next(1,&pPin,0)==S_OK){
		//方向を調べる
		PIN_DIRECTION PinDirThis;
		pPin->QueryDirection(&PinDirThis);
		if(PinDir==PinDirThis){
			if(majortype!=GUID_NULL && num>1){
				//ピンが複数で，タイプ指定があればチェック
				if(evf_checkpintype(pPin,majortype)) break;
			}else{
				break;
			}
        }
		evf_release(pPin);
	}
	evf_release(pEnum);

	return pPin;	//無い場合はNULL
}

#ifdef EVF_DEBUG
//エラーメッセージの出力
void disp_err(HRESULT hr)
{
	wchar_t ptext[256];
	char text[256];
	AMGetErrorText(hr,ptext,sizeof(ptext)/sizeof(wchar_t));
	wchar_t2char(ptext,text,sizeof(text));
	ESP_PrintfU("Error:%s\n",text);
}
#endif

//インターフェース，オブジェクト，メモリ解放
void evf_objects_release(int i)
{
	evf_release(evf_s[i].pMediaSeeking);
	evf_release(evf_s[i].pVFS);
	//evf_release(evf_s[i].pMediaControl); //v1.1

	evf_release(evf_s[i].pGraphBuilder);

	if(evf_pSampleGrabberCB[i]){
		delete evf_pSampleGrabberCB[i];
		evf_pSampleGrabberCB[i]=0;
	}

	if(evf_s[i].img){
		delete[] evf_s[i].img;
		evf_s[i].img=0;
	}
}

//State_Pausedを待つ(タイムアウトあり)
int evf_waitpause(int i, DWORD step=1)
{
	OAFilterState fs;
	int t0;

	t0=GetTickCount();
	do{
		Sleep(1);
		if((GetTickCount()-t0)>(EVF_TIMEOUT_PAUSE*step)) return 1;
		evf_s[i].pMediaControl->GetState(EVF_TIMEOUT_PAUSE,&fs);
	}while(fs!=State_Paused);

	return 0;
}

//データ転送完了を待つ
int evf_waitwait(int i)
{
	int t0;

	t0=GetTickCount();
	while(evf_s[i].wait){
		Sleep(1);
		if((GetTickCount()-t0)>EVF_TIMEOUT_WAIT) return 1;
	}

	return 0;
}

//頭出しして，Pausedを待つ
int evf_setzero(int i)
{
	HRESULT hr;
	int r;

	evf_s[i].wait= evf_s[i].count_per_seek;

	LONGLONG pos=0;
	hr= evf_s[i].pMediaSeeking->SetPositions(&pos,AM_SEEKING_AbsolutePositioning,NULL,AM_SEEKING_NoPositioning);
	if(hr!=S_OK) return 1;
	
	r= evf_waitpause(i);
	if(r) return 2;

	r= evf_waitwait(i);
	if(r) return 3;

	evf_s[i].frame=0;
	evf_s[i].afterseek=1;
	return 0;
}

//EVF_Open()から呼ばれる
int evf_Open(int i, GUID mstype)
{
	HRESULT hr;
	int flagASF= 0;
	int rtn;
	int t0;
	IVideoWindow *pVidWin= 0;
	IPin *pinSout= 0;
	IPin *pinGin= 0;
	IPin *pinGout= 0;
	IPin *pinRin= 0;
	IMediaFilter *pMediaFilter= 0;
	IBaseFilter *pReader= 0;
	IFileSourceFilter *pSourceF= 0;

	//ファイル名の拡張子を小文字へ変換
	char *name = evf_s[i].filename;
	int len = strlen(name);
	char *ext = name+len-4;
	for(int k=0;k<4;k++){
		*(ext+k) = tolower(*(ext+k));
	}
	if(strstr(ext,".asf") || strstr(ext,".wmv")) flagASF=1;

	//ファイル名をwchar_tへ変換
	wchar_t wFilename[MAX_PATH];
	MultiByteToWideChar(CP_ACP,0,evf_s[i].filename,-1,wFilename, sizeof(wFilename)/sizeof(wchar_t));

	//FilterGraphを生成
	hr= CoCreateInstance(CLSID_FilterGraph,NULL,CLSCTX_INPROC,IID_IGraphBuilder,(LPVOID *)&evf_s[i].pGraphBuilder);
	if(hr!=S_OK) {rtn=3; goto err_open;}

	//MediaFilterの取得
	hr= evf_s[i].pGraphBuilder->QueryInterface(IID_IMediaFilter,(void**)&pMediaFilter);
	if(hr!=S_OK) {rtn=4; goto err_open;}

	//基準クロックを使わない
	hr= pMediaFilter->SetSyncSource(NULL);
	if(hr!=S_OK) {rtn=5; goto err_open;}

	evf_release(pMediaFilter);

	//MediaControlの取得
	hr= evf_s[i].pGraphBuilder->QueryInterface(IID_IMediaControl,(LPVOID *)&evf_s[i].pMediaControl);
	if(hr!=S_OK) {rtn=6; goto err_open;}

	//-------------AsyncReader/WMAsfReaderを生成--------------------
	if(flagASF){
		hr= CoCreateInstance(CLSID_WMAsfReader,0,CLSCTX_INPROC_SERVER,IID_IBaseFilter,(void **)&pReader);
	}else{
		hr= CoCreateInstance(CLSID_AsyncReader,0,CLSCTX_INPROC_SERVER,IID_IBaseFilter,(void**)&pReader);
	}
	if(hr!=S_OK) {rtn=7; goto err_open;}

	hr= pReader->QueryInterface(IID_IFileSourceFilter,(LPVOID *)&pSourceF);
	if(hr!=S_OK) {rtn=8; goto err_open;}
	
	hr= pSourceF->Load(wFilename,NULL);
	if(hr!=S_OK) {rtn=9; goto err_open;}

	hr= evf_s[i].pGraphBuilder->AddFilter(pReader, L"FileSource");
	if(hr!=S_OK) {rtn=10; goto err_open;}
	
	evf_release(pSourceF);
	
	//---------------VMR9を生成---------------
	hr= CoCreateInstance(CLSID_VideoMixingRenderer9, 0, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&evf_s[i].pVmr9);
	if(hr!=S_OK) {rtn=11; goto err_open;}

	//VMR9フィルタをGraphに追加	
	hr= evf_s[i].pGraphBuilder->AddFilter(evf_s[i].pVmr9, L"VMR9");
	if(hr!=S_OK) {rtn=12; goto err_open;}

	//---------- SampleGrabber(Filter)を生成----------------
	hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER,IID_IBaseFilter, (void**)&evf_s[i].pGrabberF);
	if(hr!=S_OK) {rtn=13; goto err_open;}

	//SampleGrabberの取得
	evf_s[i].pGrabberF->QueryInterface(IID_ISampleGrabber, (void**)&evf_s[i].pGrabber);
	if(hr!=S_OK) {rtn=14; goto err_open;}

	AM_MEDIA_TYPE am_media_type;

	//フォーマットを指定
	ZeroMemory(&am_media_type, sizeof(am_media_type));
	am_media_type.majortype= MEDIATYPE_Video;
	am_media_type.subtype= mstype;
	am_media_type.formattype= FORMAT_VideoInfo;
	hr= evf_s[i].pGrabber->SetMediaType(&am_media_type);
	if(hr!=S_OK) {rtn=15; goto err_open;}

	evf_release(evf_s[i].pGrabber);

	//SampleGrabber(Filter)をGraphに追加	
	hr= evf_s[i].pGraphBuilder->AddFilter(evf_s[i].pGrabberF, L"SampleGrabber");
	if(hr!=S_OK) {rtn=16; goto err_open;}

	//--------ピン接続---------
	//ピン取得
	pinSout = evf_GetPin(pReader,            PINDIR_OUTPUT, MEDIATYPE_Video);
	pinGin  = evf_GetPin(evf_s[i].pGrabberF, PINDIR_INPUT );
	pinGout = evf_GetPin(evf_s[i].pGrabberF, PINDIR_OUTPUT);
	pinRin  = evf_GetPin(evf_s[i].pVmr9,     PINDIR_INPUT );

	//ソースとグラバの接続(中間フィルタはおまかせ)
	hr= evf_s[i].pGraphBuilder->Connect(pinSout,pinGin);
	if(hr!=S_OK && hr!=VFW_S_PARTIAL_RENDER){
		#ifdef EVF_DEBUG
		disp_err(hr);
		#endif
		rtn=17; goto err_open;
	}

	//グラバとレンダラの接続(中間フィルタはおまかせ)
	hr= evf_s[i].pGraphBuilder->Connect(pinGout,pinRin);
	if(hr!=S_OK && hr!=VFW_S_PARTIAL_RENDER){
		#ifdef EVF_DEBUG
		disp_err(hr);
		#endif
		rtn=18; goto err_open;
	}

	//ピン解放
	evf_release(pinSout);
	evf_release(pinGin);
	evf_release(pinGout);
	evf_release(pinRin);

	evf_release(pReader);
	evf_release(evf_s[i].pVmr9);

	//ビデオウィンドウを非表示にする
	hr= evf_s[i].pGraphBuilder->QueryInterface(IID_IVideoWindow,(void**)&pVidWin);
	if(hr!=S_OK) {rtn=19; goto err_open;}
	pVidWin->put_AutoShow(OAFALSE);
	evf_release(pVidWin);

	//SampleGrabberの取得
	evf_s[i].pGrabberF->QueryInterface(IID_ISampleGrabber, (void**)&evf_s[i].pGrabber);
	if(hr!=S_OK) {rtn=20; goto err_open;}

	hr= evf_s[i].pGrabber->SetBufferSamples(FALSE);
	if(hr!=S_OK) {rtn=21; goto err_open;}

	hr= evf_s[i].pGrabber->SetOneShot(FALSE);
	if(hr!=S_OK) {rtn=22; goto err_open;}

	//コールバック関数の登録
	evf_pSampleGrabberCB[i]= new evf_SampleGrabberCB(i);
	hr= evf_s[i].pGrabber->SetCallback(evf_pSampleGrabberCB[i],1);
	if(hr!=S_OK) {rtn=23; goto err_open;}

	//Pause状態にして最初のサンプルを待つ
	evf_s[i].pMediaControl->Pause();

	//１回以上サンプルされる(バッファサイズが確定する)まで待機
	t0=GetTickCount();
	do{
		Sleep(1);
		if((GetTickCount()-t0)>EVF_TIMEOUT_BUFSIZE) {rtn=24; goto err_open;}
	}while(evf_s[i].bufsize==0);

	//バッファの確保
	evf_s[i].img = (unsigned char*)new char[evf_s[i].bufsize];	
	if(!evf_s[i].img) {rtn=25; goto err_open;}
	
	evf_s[i].pbuf = evf_s[i].img;

	//バッファ確保完了フラグ
	evf_s[i].buf_enable=1;

	//情報の取得
	hr= evf_s[i].pGrabber->GetConnectedMediaType(&am_media_type);
	if(hr!=S_OK){
		#ifdef EVF_DEBUG
		disp_err(hr);
		#endif
		rtn=26; goto err_open;
	}else{
		//幅，高さ，ビット数，平均フレーム時間の取得
		VIDEOINFOHEADER *pVideoInfoHeader =	(VIDEOINFOHEADER *)am_media_type.pbFormat;
		evf_s[i].wx = pVideoInfoHeader->bmiHeader.biWidth;
		evf_s[i].wy = pVideoInfoHeader->bmiHeader.biHeight;
		evf_s[i].bit= pVideoInfoHeader->bmiHeader.biBitCount;
		evf_s[i].AvgTimePerFrame = pVideoInfoHeader->AvgTimePerFrame;
		evf_FreeMediaType(am_media_type);
	}

	evf_release(evf_s[i].pGrabber);
	evf_release(evf_s[i].pGrabberF);

	//VideoFrameStepの取得
	hr= evf_s[i].pGraphBuilder->QueryInterface(IID_IVideoFrameStep, (LPVOID *)&evf_s[i].pVFS);
	if(hr!=S_OK) {rtn=27; goto err_open;}

	evf_s[i].afterseek=1;

	//MediaSeekingの取得
	hr= evf_s[i].pGraphBuilder->QueryInterface(IID_IMediaSeeking, (void**)&evf_s[i].pMediaSeeking);
	if(hr!=S_OK) {rtn=28; goto err_open;}

	//動画時間の取得(単位:100ns)
	hr= evf_s[i].pMediaSeeking->GetDuration(&evf_s[i].MaxTime);
	if(hr!=S_OK) {rtn=29; goto err_open;}

	//seek後のBufferCB()呼び出し回数の保存（動画ファイルやPC構成によって違うため）
	Sleep(33);
	evf_s[i].count_per_seek= evf_s[i].count;

	//総フレーム数の推定
	if(evf_s[i].AvgTimePerFrame){
		evf_s[i].frames = (int)(evf_s[i].MaxTime / evf_s[i].AvgTimePerFrame);
	}else{
		//AvgTimePerFrame=0でもサンプルタイム間隔から取得できれば設定する
		double period= evf_s[i].SampleTime - evf_s[i]._SampleTime;
		if(period>0.0){
			evf_s[i].AvgTimePerFrame = (LONGLONG)(period * 10000000.);
			evf_s[i].frames = (int)(evf_s[i].MaxTime / evf_s[i].AvgTimePerFrame);
		}
	}

	//頭出し
	evf_setzero(i);

	evf_s[i].init=1;	//初期化完了フラグ
	return 0;

err_open:
	//エラー終了
	evf_objects_release(i);
	return rtn;
}

//ファイルを開く
int EVF_Open(int i, const char *filename, GUID mstype=EVF_TYPE)
{
	HRESULT hr;

	//範囲チェック
	if((unsigned int)i>=EVF_OPENMAX) return 1;

	//一度だけ.initの初期化
	if(!evf_init){
		for(int j=0;j<EVF_OPENMAX;j++) evf_s[j].init=0;
		evf_init=1;
	}

	//既に開いている？
	if(evf_s[i].init) return 2;

	//COMの初期化
	if(!evf_cominit){
		hr= CoInitializeEx(NULL,COINIT_MULTITHREADED);
		if(hr==S_OK) evf_cominit=1;	//成功したらフラグを立てる
	}

	//構造体の初期化
	ZeroMemory(&evf_s[i],sizeof(evf_struct));

	//ファイル名のコピー
	strcpy_s(evf_s[i].filename,sizeof(evf_s[i].filename),filename);

	//残りの処理
	return evf_Open(i,mstype);
}

//次のフレームへ進める
int EVF_Next(int i, int step=1)
{
	HRESULT hr;
	unsigned int t0;
	int r;

	if(evf_i_check(i)) return 1;

	//Seek直後は１回余分なStep()が必要のよう
	if(evf_s[i].afterseek){
		evf_s[i].afterseek=0;

		hr= evf_s[i].pVFS->Step(1,NULL);
		if(hr!=S_OK) return 2;

		r= evf_waitpause(i);
		if(r) return 3;
	}

	//次のフレームへ
	evf_s[i].wait= 1;
	hr= evf_s[i].pVFS->Step(step,NULL);
	if(hr!=S_OK) return 4;

	//State_Paused待ち，Pauseが来なければ頭出し後，終了判定
	r= evf_waitpause(i,step);
	if(r){
		evf_s[i].pMediaControl->Pause();
		evf_setzero(i);
		return 5;
	}

	//データ転送完了を待つ，データが来なければ頭出し後，終了判定
	t0=GetTickCount();
	while(evf_s[i].wait){
		Sleep(1);
		if((GetTickCount()-t0)>EVF_TIMEOUT_WAIT){
			evf_setzero(i);
			return 5;
		}
	}

	evf_s[i].frame += step;

	return 0;
}

//指定フレームまでシーク
int EVF_Seek(int i, int frame)
{
	HRESULT hr;
	int t0;

	if(evf_i_check(i)) return 1;

	//指定フレームへ
	LONGLONG pos;
	pos = evf_s[i].AvgTimePerFrame * (LONGLONG)frame;
	
	evf_s[i].wait= evf_s[i].count_per_seek;

	hr= evf_s[i].pMediaSeeking->SetPositions(&pos,AM_SEEKING_AbsolutePositioning,NULL,AM_SEEKING_NoPositioning);
	if(hr!=S_OK) return 2;

	evf_s[i].afterseek= 1;

	//State_Paused待ちと再生終了判定
	OAFilterState fs;
	do{
		hr= evf_s[i].pMediaSeeking->GetCurrentPosition(&pos);
		if(hr==S_OK){
			//現在位置が取得できたら，その値で終了判定
			evf_s[i].CurTime = pos;
			if(pos>=evf_s[i].MaxTime){
				evf_s[i].pMediaControl->Pause();
				evf_setzero(i);
				return 5;
			}
		}else{
			//取得できなければ，フレーム番号で終了判定
			if((evf_s[i].frame+1)>=evf_s[i].frames){
				evf_s[i].pMediaControl->Pause();
				evf_setzero(i);
				return 5;
			}
		}
		evf_s[i].pMediaControl->GetState(EVF_TIMEOUT_PAUSE,&fs);
	}while(fs!=State_Paused);

	//データ転送完了を待つ，データが来なければ終了判定
	t0=GetTickCount();
	while(evf_s[i].wait){
		Sleep(1);
		if((GetTickCount()-t0)>EVF_TIMEOUT_WAIT){
			evf_setzero(i);
			return 5;
		}
	}
	
	evf_s[i].frame = frame;

	return 0;
}

//画像をメモリへ格納 (形式(24or32)そのまま)
int EVF_GetFrame(int i, void *dst)
{
	if(evf_i_check(i)) return 1;
	//画像データのコピー
	memcpy(dst, evf_s[i].img, evf_s[i].bufsize);
	return 0;
}

//画像を画像変換(24ビット->32ビット)しながらメモリへ格納
int EVF_GetFrame24to32(int i, int *dst)
{
	if(evf_i_check(i)) return 1;

	unsigned char R,G,B;
	int wx=evf_s[i].wx;
	int wy=evf_s[i].wy;
	int *p;
	unsigned char *src=evf_s[i].img;
	int byte= evf_s[i].bufsize/wy;
	unsigned char *s;

	for(int y=0;y<wy;y++){
		s = src;
		p = dst + wx*y;
		for(int x=0;x<wx;x++){
			B = *(s+0);
			G = *(s+1);
			R = *(s+2);
			*p++ = (R<<16) | (G<<8) | B;
			s+=3;
		}
		src += byte;
	}
	return 0;
}

//ファイルを閉じる
int EVF_Close(int i)
{
	if(evf_i_check(i)) return 1;

	evf_objects_release(i);
	Sleep(1);	//これがないとXPでおちる

	evf_s[i].init=0;

	int c=0;
	for(int j=0;j<EVF_OPENMAX;j++){
		if(evf_s[j].init) c++;
	}

	//COMの解除 (すべて閉じたら ＆ COMの初期化をしていたら)
	if(c==0 && evf_cominit){
		CoUninitialize();
		evf_cominit=0;
	}
	return 0;
}

//総フレーム数(frame)
int EVF_Frames(int i)
{
	if(evf_i_check(i)) return 0;
	return evf_s[i].frames;
}

//現在のフレーム番号
int EVF_Frame(int i)
{
	if(evf_i_check(i)) return 0;
	return evf_s[i].frame;
}

//平均フレーム時間(単位:100ナノ秒)
LONGLONG EVF_AvgTime(int i)
{
	if(evf_i_check(i)) return 0;
	return evf_s[i].AvgTimePerFrame;
}

//動画時間(単位:100ナノ秒)
LONGLONG EVF_MaxTime(int i)
{
	if(evf_i_check(i)) return 0;
	return evf_s[i].MaxTime;
}

//現在位置(単位:100ナノ秒)
LONGLONG EVF_CurTime(int i)
{
	if(evf_i_check(i)) return 0;
	return evf_s[i].CurTime;
}

//フレームレート(fps)
double EVF_FrameRate(int i)
{
	if(evf_i_check(i)) return 0;
	if(evf_s[i].AvgTimePerFrame){
		return 10000000./(double)evf_s[i].AvgTimePerFrame;
	}else{
		return 0.0;
	}
}

//横サイズ(pixel)
int EVF_WX(int i)
{
	if(evf_i_check(i)) return 0;
	return evf_s[i].wx;
}

//縦サイズ(pixel)
int EVF_WY(int i)
{
	if(evf_i_check(i)) return 0;
	return evf_s[i].wy;
}

//ビット数(bit)
int EVF_Bit(int i)
{
	if(evf_i_check(i)) return 0;
	return evf_s[i].bit;
}

//バッファサイズ(byte)
int EVF_BufferSize(int i)
{
	if(evf_i_check(i)) return 0;
	return evf_s[i].bufsize;
}

//バッファアドレスの変更
int EVF_SetBuffer(int i, void *buffer)
{
	if(evf_i_check(i)) return 1;
	evf_s[i].pbuf= (unsigned char *)buffer;
	return 0;
}
