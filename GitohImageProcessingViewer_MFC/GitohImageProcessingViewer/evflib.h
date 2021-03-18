// EVFLIB [Easy Video Frame LIBrary]
//          version 1.2
// Copyright (C) 2016-2018 I.N.  All rights reserved.

// OS: Windows 10
// Compiler: Visual C++ 2015/2017

// 2013/08/13-9/2 ver.1.0 ����
// 2016/05/20 ver.1.1 �ꕔ�̊���EVF_Close()���ɋ����I������s����C��
// 2017/05/30 ver.1.2 Visual C++ 2017�Ή�

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

//�^�C���A�E�g����(�P��:ms)
#define EVF_TIMEOUT_BUFSIZE 5000
#define EVF_TIMEOUT_PAUSE   1000
#define EVF_TIMEOUT_WAIT    1000

#define evf_release(x) {if(x)x->Release();x=0;}

int evf_cominit=0;	//COM�������t���O(1�Ȃ�I���������s��)
int evf_init=0;		//EMDLIB��������������1

//�\���̂̒�`
struct evf_struct{
	int init;						//�������t���O
	int wx;							//�摜�̕�
	int wy;							//�摜�̍���
	int bit;						//�摜�̃r�b�g��
	char filename[MAX_PATH];		//����t�@�C����
	unsigned char *img;				//�o�b�t�@�̐擪�A�h���X
	unsigned char *pbuf;			//�摜�i�[�A�h���X
	volatile long bufsize;			//�o�b�t�@�T�C�Y
	LONGLONG AvgTimePerFrame;		//���σt���[������(100�i�m�b�P��)
	LONGLONG MaxTime;				//�����掞��(100�i�m�b�P��)
	LONGLONG CurTime;				//���݈ʒu(100�i�m�b�P��)
	int frames;						//���t���[����
	int frame;						//���݂̃t���[���ԍ�
	IGraphBuilder *pGraphBuilder;
	IBaseFilter *pGrabberF;
	ISampleGrabber *pGrabber;
	IBaseFilter *pVmr9;
	IMediaControl *pMediaControl;
	IMediaSeeking *pMediaSeeking;
	IVideoFrameStep *pVFS;
	volatile int buf_enable;		//�o�b�t�@���������t���O
	volatile int wait;				//�]���������t���O
	volatile double SampleTime;		//�T���v������(�b)
	volatile double _SampleTime;	//�P�O�̃T���v������(�b)
	int count;
	int count_per_seek;		//Seek�P��ɂ�����BufferCB()���������邩
	int afterseek;
};

//�ő哯���I�[�v����
#ifndef EVF_OPENMAX
	#define EVF_OPENMAX 10	
#endif

//�\���̂̐錾
evf_struct evf_s[EVF_OPENMAX];

//�R�[���o�b�N�֐��̒�`
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
	//�t���[�����ɌĂ΂��֐�
	STDMETHODIMP BufferCB(double dblSampleTime, BYTE *pBuffer, long lBufferSize)
	{
		evf_s[i].count++;

		evf_s[i].bufsize= lBufferSize;

		if(evf_s[i].buf_enable){
			int wx= evf_s[i].wx;
			int wy= evf_s[i].wy;
			int byte= lBufferSize/wy;
			//�摜�̏㉺���t�ɂ��ăR�s�[
			for(int y=0; y<wy; y++){
				memcpy(evf_s[i].pbuf+(wy-1-y)*byte, pBuffer+y*byte, byte);
			}
		}

		if(evf_s[i].wait) evf_s[i].wait--;

		evf_s[i]._SampleTime= evf_s[i].SampleTime;
		evf_s[i].SampleTime= dblSampleTime;

		return S_OK;
	}
	//�R���X�g���N�^	
	evf_SampleGrabberCB(int num)
	{
		i=num;
		evf_s[i].bufsize=0;
	}
	//�f�X�g���N�^
	~evf_SampleGrabberCB()
	{
	}
private:
	int i;
};

evf_SampleGrabberCB *evf_pSampleGrabberCB[EVF_OPENMAX];

//�ԍ�i�͈̔̓`�F�b�N�C�������ς݂̃`�F�b�N
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

//�s���̃^�C�v��majortype���ǂ������ׂ�(yes=1)
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

//�t�B���^pFilter�̃s���iPinDir�ŕ����w��j���擾����
// ���I�v�V������
//   majortype:���̒l��GUID_NULL�łȂ��C�Y���s���������������Ƃ��́Cmajortype�̏����t���ƂȂ�
IPin *evf_GetPin(IBaseFilter *pFilter, PIN_DIRECTION PinDir, GUID majortype=GUID_NULL)
{
	HRESULT hr;

	IEnumPins *pEnum;
	IPin *pPin=0;
	int num=0;

	//�s�����𒲂ׂ�
	hr= pFilter->EnumPins(&pEnum);
	if(hr!=S_OK) return NULL;
	while(pEnum->Next(1,&pPin,0)==S_OK){
		//�����𒲂ׂ�
		PIN_DIRECTION PinDirThis;
		pPin->QueryDirection(&PinDirThis);
		if(PinDir==PinDirThis) num++;
		evf_release(pPin);
	}
	evf_release(pEnum);

	hr= pFilter->EnumPins(&pEnum);
	if(hr!=S_OK) return NULL;
	while(pEnum->Next(1,&pPin,0)==S_OK){
		//�����𒲂ׂ�
		PIN_DIRECTION PinDirThis;
		pPin->QueryDirection(&PinDirThis);
		if(PinDir==PinDirThis){
			if(majortype!=GUID_NULL && num>1){
				//�s���������ŁC�^�C�v�w�肪����΃`�F�b�N
				if(evf_checkpintype(pPin,majortype)) break;
			}else{
				break;
			}
        }
		evf_release(pPin);
	}
	evf_release(pEnum);

	return pPin;	//�����ꍇ��NULL
}

#ifdef EVF_DEBUG
//�G���[���b�Z�[�W�̏o��
void disp_err(HRESULT hr)
{
	wchar_t ptext[256];
	char text[256];
	AMGetErrorText(hr,ptext,sizeof(ptext)/sizeof(wchar_t));
	wchar_t2char(ptext,text,sizeof(text));
	ESP_PrintfU("Error:%s\n",text);
}
#endif

//�C���^�[�t�F�[�X�C�I�u�W�F�N�g�C���������
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

//State_Paused��҂�(�^�C���A�E�g����)
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

//�f�[�^�]��������҂�
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

//���o�����āCPaused��҂�
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

//EVF_Open()����Ă΂��
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

	//�t�@�C�����̊g���q���������֕ϊ�
	char *name = evf_s[i].filename;
	int len = strlen(name);
	char *ext = name+len-4;
	for(int k=0;k<4;k++){
		*(ext+k) = tolower(*(ext+k));
	}
	if(strstr(ext,".asf") || strstr(ext,".wmv")) flagASF=1;

	//�t�@�C������wchar_t�֕ϊ�
	wchar_t wFilename[MAX_PATH];
	MultiByteToWideChar(CP_ACP,0,evf_s[i].filename,-1,wFilename, sizeof(wFilename)/sizeof(wchar_t));

	//FilterGraph�𐶐�
	hr= CoCreateInstance(CLSID_FilterGraph,NULL,CLSCTX_INPROC,IID_IGraphBuilder,(LPVOID *)&evf_s[i].pGraphBuilder);
	if(hr!=S_OK) {rtn=3; goto err_open;}

	//MediaFilter�̎擾
	hr= evf_s[i].pGraphBuilder->QueryInterface(IID_IMediaFilter,(void**)&pMediaFilter);
	if(hr!=S_OK) {rtn=4; goto err_open;}

	//��N���b�N���g��Ȃ�
	hr= pMediaFilter->SetSyncSource(NULL);
	if(hr!=S_OK) {rtn=5; goto err_open;}

	evf_release(pMediaFilter);

	//MediaControl�̎擾
	hr= evf_s[i].pGraphBuilder->QueryInterface(IID_IMediaControl,(LPVOID *)&evf_s[i].pMediaControl);
	if(hr!=S_OK) {rtn=6; goto err_open;}

	//-------------AsyncReader/WMAsfReader�𐶐�--------------------
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
	
	//---------------VMR9�𐶐�---------------
	hr= CoCreateInstance(CLSID_VideoMixingRenderer9, 0, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&evf_s[i].pVmr9);
	if(hr!=S_OK) {rtn=11; goto err_open;}

	//VMR9�t�B���^��Graph�ɒǉ�	
	hr= evf_s[i].pGraphBuilder->AddFilter(evf_s[i].pVmr9, L"VMR9");
	if(hr!=S_OK) {rtn=12; goto err_open;}

	//---------- SampleGrabber(Filter)�𐶐�----------------
	hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER,IID_IBaseFilter, (void**)&evf_s[i].pGrabberF);
	if(hr!=S_OK) {rtn=13; goto err_open;}

	//SampleGrabber�̎擾
	evf_s[i].pGrabberF->QueryInterface(IID_ISampleGrabber, (void**)&evf_s[i].pGrabber);
	if(hr!=S_OK) {rtn=14; goto err_open;}

	AM_MEDIA_TYPE am_media_type;

	//�t�H�[�}�b�g���w��
	ZeroMemory(&am_media_type, sizeof(am_media_type));
	am_media_type.majortype= MEDIATYPE_Video;
	am_media_type.subtype= mstype;
	am_media_type.formattype= FORMAT_VideoInfo;
	hr= evf_s[i].pGrabber->SetMediaType(&am_media_type);
	if(hr!=S_OK) {rtn=15; goto err_open;}

	evf_release(evf_s[i].pGrabber);

	//SampleGrabber(Filter)��Graph�ɒǉ�	
	hr= evf_s[i].pGraphBuilder->AddFilter(evf_s[i].pGrabberF, L"SampleGrabber");
	if(hr!=S_OK) {rtn=16; goto err_open;}

	//--------�s���ڑ�---------
	//�s���擾
	pinSout = evf_GetPin(pReader,            PINDIR_OUTPUT, MEDIATYPE_Video);
	pinGin  = evf_GetPin(evf_s[i].pGrabberF, PINDIR_INPUT );
	pinGout = evf_GetPin(evf_s[i].pGrabberF, PINDIR_OUTPUT);
	pinRin  = evf_GetPin(evf_s[i].pVmr9,     PINDIR_INPUT );

	//�\�[�X�ƃO���o�̐ڑ�(���ԃt�B���^�͂��܂���)
	hr= evf_s[i].pGraphBuilder->Connect(pinSout,pinGin);
	if(hr!=S_OK && hr!=VFW_S_PARTIAL_RENDER){
		#ifdef EVF_DEBUG
		disp_err(hr);
		#endif
		rtn=17; goto err_open;
	}

	//�O���o�ƃ����_���̐ڑ�(���ԃt�B���^�͂��܂���)
	hr= evf_s[i].pGraphBuilder->Connect(pinGout,pinRin);
	if(hr!=S_OK && hr!=VFW_S_PARTIAL_RENDER){
		#ifdef EVF_DEBUG
		disp_err(hr);
		#endif
		rtn=18; goto err_open;
	}

	//�s�����
	evf_release(pinSout);
	evf_release(pinGin);
	evf_release(pinGout);
	evf_release(pinRin);

	evf_release(pReader);
	evf_release(evf_s[i].pVmr9);

	//�r�f�I�E�B���h�E���\���ɂ���
	hr= evf_s[i].pGraphBuilder->QueryInterface(IID_IVideoWindow,(void**)&pVidWin);
	if(hr!=S_OK) {rtn=19; goto err_open;}
	pVidWin->put_AutoShow(OAFALSE);
	evf_release(pVidWin);

	//SampleGrabber�̎擾
	evf_s[i].pGrabberF->QueryInterface(IID_ISampleGrabber, (void**)&evf_s[i].pGrabber);
	if(hr!=S_OK) {rtn=20; goto err_open;}

	hr= evf_s[i].pGrabber->SetBufferSamples(FALSE);
	if(hr!=S_OK) {rtn=21; goto err_open;}

	hr= evf_s[i].pGrabber->SetOneShot(FALSE);
	if(hr!=S_OK) {rtn=22; goto err_open;}

	//�R�[���o�b�N�֐��̓o�^
	evf_pSampleGrabberCB[i]= new evf_SampleGrabberCB(i);
	hr= evf_s[i].pGrabber->SetCallback(evf_pSampleGrabberCB[i],1);
	if(hr!=S_OK) {rtn=23; goto err_open;}

	//Pause��Ԃɂ��čŏ��̃T���v����҂�
	evf_s[i].pMediaControl->Pause();

	//�P��ȏ�T���v�������(�o�b�t�@�T�C�Y���m�肷��)�܂őҋ@
	t0=GetTickCount();
	do{
		Sleep(1);
		if((GetTickCount()-t0)>EVF_TIMEOUT_BUFSIZE) {rtn=24; goto err_open;}
	}while(evf_s[i].bufsize==0);

	//�o�b�t�@�̊m��
	evf_s[i].img = (unsigned char*)new char[evf_s[i].bufsize];	
	if(!evf_s[i].img) {rtn=25; goto err_open;}
	
	evf_s[i].pbuf = evf_s[i].img;

	//�o�b�t�@�m�ۊ����t���O
	evf_s[i].buf_enable=1;

	//���̎擾
	hr= evf_s[i].pGrabber->GetConnectedMediaType(&am_media_type);
	if(hr!=S_OK){
		#ifdef EVF_DEBUG
		disp_err(hr);
		#endif
		rtn=26; goto err_open;
	}else{
		//���C�����C�r�b�g���C���σt���[�����Ԃ̎擾
		VIDEOINFOHEADER *pVideoInfoHeader =	(VIDEOINFOHEADER *)am_media_type.pbFormat;
		evf_s[i].wx = pVideoInfoHeader->bmiHeader.biWidth;
		evf_s[i].wy = pVideoInfoHeader->bmiHeader.biHeight;
		evf_s[i].bit= pVideoInfoHeader->bmiHeader.biBitCount;
		evf_s[i].AvgTimePerFrame = pVideoInfoHeader->AvgTimePerFrame;
		evf_FreeMediaType(am_media_type);
	}

	evf_release(evf_s[i].pGrabber);
	evf_release(evf_s[i].pGrabberF);

	//VideoFrameStep�̎擾
	hr= evf_s[i].pGraphBuilder->QueryInterface(IID_IVideoFrameStep, (LPVOID *)&evf_s[i].pVFS);
	if(hr!=S_OK) {rtn=27; goto err_open;}

	evf_s[i].afterseek=1;

	//MediaSeeking�̎擾
	hr= evf_s[i].pGraphBuilder->QueryInterface(IID_IMediaSeeking, (void**)&evf_s[i].pMediaSeeking);
	if(hr!=S_OK) {rtn=28; goto err_open;}

	//���掞�Ԃ̎擾(�P��:100ns)
	hr= evf_s[i].pMediaSeeking->GetDuration(&evf_s[i].MaxTime);
	if(hr!=S_OK) {rtn=29; goto err_open;}

	//seek���BufferCB()�Ăяo���񐔂̕ۑ��i����t�@�C����PC�\���ɂ���ĈႤ���߁j
	Sleep(33);
	evf_s[i].count_per_seek= evf_s[i].count;

	//���t���[�����̐���
	if(evf_s[i].AvgTimePerFrame){
		evf_s[i].frames = (int)(evf_s[i].MaxTime / evf_s[i].AvgTimePerFrame);
	}else{
		//AvgTimePerFrame=0�ł��T���v���^�C���Ԋu����擾�ł���ΐݒ肷��
		double period= evf_s[i].SampleTime - evf_s[i]._SampleTime;
		if(period>0.0){
			evf_s[i].AvgTimePerFrame = (LONGLONG)(period * 10000000.);
			evf_s[i].frames = (int)(evf_s[i].MaxTime / evf_s[i].AvgTimePerFrame);
		}
	}

	//���o��
	evf_setzero(i);

	evf_s[i].init=1;	//�����������t���O
	return 0;

err_open:
	//�G���[�I��
	evf_objects_release(i);
	return rtn;
}

//�t�@�C�����J��
int EVF_Open(int i, const char *filename, GUID mstype=EVF_TYPE)
{
	HRESULT hr;

	//�͈̓`�F�b�N
	if((unsigned int)i>=EVF_OPENMAX) return 1;

	//��x����.init�̏�����
	if(!evf_init){
		for(int j=0;j<EVF_OPENMAX;j++) evf_s[j].init=0;
		evf_init=1;
	}

	//���ɊJ���Ă���H
	if(evf_s[i].init) return 2;

	//COM�̏�����
	if(!evf_cominit){
		hr= CoInitializeEx(NULL,COINIT_MULTITHREADED);
		if(hr==S_OK) evf_cominit=1;	//����������t���O�𗧂Ă�
	}

	//�\���̂̏�����
	ZeroMemory(&evf_s[i],sizeof(evf_struct));

	//�t�@�C�����̃R�s�[
	strcpy_s(evf_s[i].filename,sizeof(evf_s[i].filename),filename);

	//�c��̏���
	return evf_Open(i,mstype);
}

//���̃t���[���֐i�߂�
int EVF_Next(int i, int step=1)
{
	HRESULT hr;
	unsigned int t0;
	int r;

	if(evf_i_check(i)) return 1;

	//Seek����͂P��]����Step()���K�v�̂悤
	if(evf_s[i].afterseek){
		evf_s[i].afterseek=0;

		hr= evf_s[i].pVFS->Step(1,NULL);
		if(hr!=S_OK) return 2;

		r= evf_waitpause(i);
		if(r) return 3;
	}

	//���̃t���[����
	evf_s[i].wait= 1;
	hr= evf_s[i].pVFS->Step(step,NULL);
	if(hr!=S_OK) return 4;

	//State_Paused�҂��CPause�����Ȃ���Γ��o����C�I������
	r= evf_waitpause(i,step);
	if(r){
		evf_s[i].pMediaControl->Pause();
		evf_setzero(i);
		return 5;
	}

	//�f�[�^�]��������҂C�f�[�^�����Ȃ���Γ��o����C�I������
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

//�w��t���[���܂ŃV�[�N
int EVF_Seek(int i, int frame)
{
	HRESULT hr;
	int t0;

	if(evf_i_check(i)) return 1;

	//�w��t���[����
	LONGLONG pos;
	pos = evf_s[i].AvgTimePerFrame * (LONGLONG)frame;
	
	evf_s[i].wait= evf_s[i].count_per_seek;

	hr= evf_s[i].pMediaSeeking->SetPositions(&pos,AM_SEEKING_AbsolutePositioning,NULL,AM_SEEKING_NoPositioning);
	if(hr!=S_OK) return 2;

	evf_s[i].afterseek= 1;

	//State_Paused�҂��ƍĐ��I������
	OAFilterState fs;
	do{
		hr= evf_s[i].pMediaSeeking->GetCurrentPosition(&pos);
		if(hr==S_OK){
			//���݈ʒu���擾�ł�����C���̒l�ŏI������
			evf_s[i].CurTime = pos;
			if(pos>=evf_s[i].MaxTime){
				evf_s[i].pMediaControl->Pause();
				evf_setzero(i);
				return 5;
			}
		}else{
			//�擾�ł��Ȃ���΁C�t���[���ԍ��ŏI������
			if((evf_s[i].frame+1)>=evf_s[i].frames){
				evf_s[i].pMediaControl->Pause();
				evf_setzero(i);
				return 5;
			}
		}
		evf_s[i].pMediaControl->GetState(EVF_TIMEOUT_PAUSE,&fs);
	}while(fs!=State_Paused);

	//�f�[�^�]��������҂C�f�[�^�����Ȃ���ΏI������
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

//�摜���������֊i�[ (�`��(24or32)���̂܂�)
int EVF_GetFrame(int i, void *dst)
{
	if(evf_i_check(i)) return 1;
	//�摜�f�[�^�̃R�s�[
	memcpy(dst, evf_s[i].img, evf_s[i].bufsize);
	return 0;
}

//�摜���摜�ϊ�(24�r�b�g->32�r�b�g)���Ȃ��烁�����֊i�[
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

//�t�@�C�������
int EVF_Close(int i)
{
	if(evf_i_check(i)) return 1;

	evf_objects_release(i);
	Sleep(1);	//���ꂪ�Ȃ���XP�ł�����

	evf_s[i].init=0;

	int c=0;
	for(int j=0;j<EVF_OPENMAX;j++){
		if(evf_s[j].init) c++;
	}

	//COM�̉��� (���ׂĕ����� �� COM�̏����������Ă�����)
	if(c==0 && evf_cominit){
		CoUninitialize();
		evf_cominit=0;
	}
	return 0;
}

//���t���[����(frame)
int EVF_Frames(int i)
{
	if(evf_i_check(i)) return 0;
	return evf_s[i].frames;
}

//���݂̃t���[���ԍ�
int EVF_Frame(int i)
{
	if(evf_i_check(i)) return 0;
	return evf_s[i].frame;
}

//���σt���[������(�P��:100�i�m�b)
LONGLONG EVF_AvgTime(int i)
{
	if(evf_i_check(i)) return 0;
	return evf_s[i].AvgTimePerFrame;
}

//���掞��(�P��:100�i�m�b)
LONGLONG EVF_MaxTime(int i)
{
	if(evf_i_check(i)) return 0;
	return evf_s[i].MaxTime;
}

//���݈ʒu(�P��:100�i�m�b)
LONGLONG EVF_CurTime(int i)
{
	if(evf_i_check(i)) return 0;
	return evf_s[i].CurTime;
}

//�t���[�����[�g(fps)
double EVF_FrameRate(int i)
{
	if(evf_i_check(i)) return 0;
	if(evf_s[i].AvgTimePerFrame){
		return 10000000./(double)evf_s[i].AvgTimePerFrame;
	}else{
		return 0.0;
	}
}

//���T�C�Y(pixel)
int EVF_WX(int i)
{
	if(evf_i_check(i)) return 0;
	return evf_s[i].wx;
}

//�c�T�C�Y(pixel)
int EVF_WY(int i)
{
	if(evf_i_check(i)) return 0;
	return evf_s[i].wy;
}

//�r�b�g��(bit)
int EVF_Bit(int i)
{
	if(evf_i_check(i)) return 0;
	return evf_s[i].bit;
}

//�o�b�t�@�T�C�Y(byte)
int EVF_BufferSize(int i)
{
	if(evf_i_check(i)) return 0;
	return evf_s[i].bufsize;
}

//�o�b�t�@�A�h���X�̕ύX
int EVF_SetBuffer(int i, void *buffer)
{
	if(evf_i_check(i)) return 1;
	evf_s[i].pbuf= (unsigned char *)buffer;
	return 0;
}
