#pragma once
#include <tchar.h>
#include <vector>
#include <string>

#ifndef tstring
typedef std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> > tstring;
#endif // !tstring


#define MAXFORMAT 100   //�擾���̏��

//	�J�����t�H�[�}�b�g��ۑ�����N���X
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

//�t�@�C�����J���_�C�A���OWin32API�̃��b�p�[
BOOL glGetOpenFileName(
	tstring* FileFullPath, 
	tstring* FileName, 
	tstring InitialDir, 
	const TCHAR* Filter
);

//�C���[�W�E�C���h�E�̈ʒu�A�傫���A�\���{���̎Z�o
void ImageWindowPositioning(
	int width,				//�摜�̕�
	int height,				//�摜�̍���
	int dtwidth,			//�f�X�N�g�b�v�̕�
	int bw_y,				//�{�^���E�C���h�E�̏�[
	int* imb_x,			//�C���[�W�E�C���h�E�̍���X���W
	int* imb_y,			//�C���[�W�E�C���h�E�̍���Y���W
	int* zoom_num		//�\���{��
);

//�ڑ�����Ă���J�����̏����W�߂�
std::vector<std::vector<RES>> CamInit();

//���L�������̏�����
HANDLE InitShareMemory(tstring memortname, size_t typesize, LPVOID* lpmemory);

template<typename T>
SHRAEMEMORY<T> InitShareMemory(tstring memortname)
{
	SHRAEMEMORY<T> memory;
	memory.handle = InitShareMemory(memortname, sizeof(T), (LPVOID*)&(memory.memory));
	return memory;
}

//���L���������J��
HANDLE OpenShareMemory(tstring memortname, LPVOID* lpmemory);

template<typename T>
SHRAEMEMORY<T> OpenShareMemory(tstring memortname)
{
	SHRAEMEMORY<T> memory;
	memory.handle = OpenShareMemory(memortname, (LPVOID*)&(memory.memory));
	return memory;
}

//���L�����������
void CloseShareMemory(HANDLE hmemory, LPVOID* lpmemory);

template<typename T>
void CloseShareMemory(SHRAEMEMORY<T>memory)
{
	CloseShareMemory(memory.handle, (LPVOID*)&(memory.memory));
}

//�J�����t�H�[�}�b�g�̑I��
RES SelectCameraFormat(const int dtcenter_x, const int bw_y, std::vector<std::vector<RES>> cam_formats, int& use_cam_num);

//�C���[�W�E�C���h�E�E���̃e�L�X�g�E�C���h�E���J��
//MFC�ł�inline�֐��ɂ��Ȃ��ƃe�L�X�g�E�C���h�E��j�����鎞�ɃG���[�ɂȂ�B
//void OpenRTextWindow(int txt_win_num, int txtw_w, int txtw_h, int imb_x, int imb_y, int width, int zoom_num, int margin);
inline void OpenRTextWindow(int txt_win_num, int txtw_w, int txtw_h, int imb_x, int imb_y, int width, int zoom_num, int margin)
{
	int txtw_x = imb_x + width * zoom_num / 100 + margin;
	int txtw_y = imb_y;
	ESP_OpenTextWindow(txt_win_num, txtw_x, txtw_y, txtw_w, txtw_h);
}

//�J�����p�X���b�h�֐�
unsigned __stdcall  PlayCamera(LPVOID lpParam);
//����t�@�C���p�X���b�h�֐�
unsigned __stdcall  PlayVideo(LPVOID lpParam);

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
//common.h�����gl*.h�g�p���͈ȉ��폜
//string�^��wstring�^�ɕϊ�����B
std::wstring string_to_wstring(std::string const& src, UINT CodePage = CP_ACP);

//wstring�^��string�^�ɕϊ�����B
std::string wstring_to_string(std::wstring const& wsrc, UINT CodePage = CP_ACP);

//24bit Bitmap�f�[�^�̃T�C�Y��ݒ肷��
void WINAPI glInitImageData(
	LPBYTE* BmpImage,		//Bitmap�f�[�^
	long xsize,					//�摜�̕��T�C�Y
	long ysize						//�摜�̏c�T�C�Y
);

//24bit Bitmap�f�[�^�̃T�C�Y��ݒ肷��
LPBYTE glInitDIBImage(
	long xsize,					//�摜�̕��T�C�Y
	long ysize					//�摜�̏c�T�C�Y
);

//BITMAPINFO�̐ݒ�
void WINAPI glSetBmpInfo(
	LPBITMAPINFO* bmpinfo,	//BITMAPINFO
	long xsize,			//�摜�̕��T�C�Y
	long ysize,			//�摜�̏c�T�C�Y
	long bitcount = 24		//1�s�N�Z��������̃r�b�g���B���̒l��0,1,4,8,16,24,32�̂����ꂩ�̒l�����B
);

//BGR�`���̉摜��DIB�֕ϊ�����
void glConvertBGRtoDIB(LPBYTE lpbyDib,
	LPBYTE lpbyBgr,
	const int width,
	const int height,
	const bool mode = TRUE
);

// �C���[�W�f�[�^�o�b�t�@�̉��
void glDelImageBuffer(
	LPBYTE* CameraImage
);

//Bitmap�f�[�^�̃T�C�Y��j������
void WINAPI glDeleteImageData(
	LPBYTE* BmpImage		//Bitmap�f�[�^
);

//24bit Bitmap�f�[�^���㉺���]����
 void WINAPI glBitmapFlipVertical(
	LPBYTE BmpImage24_in,	//���r�b�g�}�b�v�f�[�^
	LPBYTE BmpImage24_out,	//�㉺���]��̃r�b�g�}�b�v�f�[�^
	long width,				//���摜�̕��T�C�Y
	long height,				//���摜�̏c�T�C�Y
	int* buf1Rimage = NULL,		//��Ɨp�摜�o�b�t�@
	int* buf1Gimage = NULL,		//��Ɨp�摜�o�b�t�@
	int* buf1Bimage = NULL,		//��Ɨp�摜�o�b�t�@
	int* buf2Rimage = NULL,		//��Ɨp�摜�o�b�t�@
	int* buf2Gimage = NULL,		//��Ɨp�摜�o�b�t�@
	int* buf2Bimage = NULL		//��Ɨp�摜�o�b�t�@
);

 //24Bit Bitmap�f�[�^�`����32Bit Bitmap�f�[�^�`���ɕϊ�
void WINAPI glBmp24ToBmp32(
	 LPBYTE BmpImage24_in,			//24Bit Bitmap�`���̃f�[�^
	 LPBYTE BmpImage32_out,		//32Bit Bitmap�f�[�^�`��
	 long width,					//�摜�̕��T�C�Y
	 long height					//�摜�̏c�T�C�Y
 );

//�f�o�C�X�t�H�[�}�b�g�������Ή�����GUID�l�ɕϊ�����
GUID getStringAsMediaSubtype(tstring typestr);

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/