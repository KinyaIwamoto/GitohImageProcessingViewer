#pragma once
#include <dshow.h>
#include "qedit.h"

#ifndef EWC_NCAMMAX
#define EWC_NCAMMAX 10	//�J�����̍ő�F����v2.2
#endif

#ifndef EWC_BUF_NUM
#define EWC_BUF_NUM	 1	//�����O�o�b�t�@���i1�ȏ�̐����jv2.6
#endif

#define EWC_VPAMPMAX	10
#define EWC_CAMCTLMAX	7
#define EWC_ITEMMAX		(EWC_VPAMPMAX+EWC_CAMCTLMAX)

//�\���̂̒�`
struct ewc_struct {
	int wx;					//�摜�̕�
	int wy;					//�摜�̍���
	double fps;				//�t���[�����[�g�i�����w��l�j
	int device;				//�����f�o�C�X�ԍ��i�����w��l�j
	int devn;				//���蓖�Ă�ꂽ�����f�o�C�X�ԍ�v2.2
	char* pdname;			//FriendlyName��r�pv2.2
	char dname[256];		//�擾����FriendlyName v2.2
	GUID mstype;			//�o�͉摜�̃t�H�[�}�b�g
	char mstype_t[80];		//mstype�ɑΉ����镶����v2.3
	GUID dev_mstype;		//�f�o�C�X�o�̓s���̃t�H�[�}�b�gv2.3
	char dev_mstype_t[80];	//dev_mstype�ɑΉ����镶����v2.3
	volatile int init;
	volatile int stop;
	volatile int errcode;
	int* pbuf;				//�摜�̕ۑ���
	int* buffer;			//�����Ŋm�ۂ����t���[���o�b�t�@
	volatile long bufsize;	//����ꂽ�摜�f�[�^�̃o�C�g��
	volatile double ftime;	//�t���[������(s)�̎����l�i�ŐV�l�j
	volatile int w_count;	//write�����J�E���^�lv2.6
	volatile int r_count;	//read�����J�E���^�lv2.6
	volatile int buffer_r;	//�o�b�t�@�̑I��(read)v2.6
	volatile int buffer_w;	//�o�b�t�@�̑I��(write)v2.6
	volatile double buf_stime[EWC_BUF_NUM];	//�e�o�b�t�@�̃T���v������(s)v2.6
	volatile int buf_count[EWC_BUF_NUM];	//�e�o�b�t�@�̃J�E���^�lv2.6
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

//�t�H�[�}�b�g�i�[�̂��߂̍\����v2.3
struct ewc_format {
	int width;
	int height;
	int bit;
	REFERENCE_TIME AvgTimePerFrame;
	double fps;
	GUID subtype;
	char subtype_t[80];	//subtype�ɑΉ����镶����v2.3
};

extern GUID ewc_type;
extern GUID ewc_device_type;
extern ewc_struct ewc_s[EWC_NCAMMAX];

int EWC_Open(int num, int wx = 0, int wy = 0, double fps = 0, int device = -1, GUID mstype = ewc_type, GUID dev_mstype = ewc_device_type);
int EWC_Close(int num);
int EWC_GetCamera(void);
char* EWC_GetDeviceName(int num);
int EWC_GetFormat(int devn, ewc_format* fmt, int* nmax);

// �V�����摜�������������ǂ��� v2.6
// num:�J�����ԍ�  buffer_r:�ǂݏo�������O�o�b�t�@�̔ԍ�(0�`)
// �߂�l: �O����s�ȍ~�ɓ��������摜�����i������:0, �ʏ�:1, �R�}�����������2�ȏ�j
int EWC_IsCaptured(int num, int* buffer_r = NULL);

//�J����(�ԍ�:num)�̉摜�擾 v2.6
// num:�J�����ԍ�  buffer:�摜�f�[�^���i�[����A�h���X�@count:�t���[���ԍ��@stime:�擾����(�b)
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
//�e�L�X�g�E�B���h�E���J�� v8.2
int esp_OpenTextWindow(int i, int x0, int y0, int wx, int wy);
void esp_RequestOpenTextWindow(int i, int x0, int y0, int wx, int wy);

//�e�L�X�g�E�B���h�E�ɂ����ĕ�������͂��s�� 7.0
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
extern volatile int esp_i;			//���ݑI������Ă���C���[�W�E�B���h�E
#define ESP_Update() (ESP_Update_(esp_i))
#endif // !ESP_Update
int ESP_Update_(int i);

void ESP_Locate(int cx, int cy);
//�{�^���̉����ꂽ�񐔂� 1 �ɂ���
void ESP_SetButtonBox(int i);

//���̃t���[���֐i�߂�
int EVF_Next(int i, int step = 1);
//���݂̃t���[���ԍ�
int EVF_Frame(int i);
//�w��t���[���܂ŃV�[�N
int EVF_Seek(int i, int frame);
//�摜���摜�ϊ�(24�r�b�g->32�r�b�g)���Ȃ��烁�����֊i�[
int EVF_GetFrame24to32(int i, int* dst);
