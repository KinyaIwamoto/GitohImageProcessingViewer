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
BOOL GetOpenFileName(
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
void OpenRTextWindow(int txt_win_num, int txtw_w, int txtw_h, int imb_x, int imb_y, int width, int zoom_num, int margin);

//�J�����p�X���b�h�֐�
unsigned __stdcall  PlayCamera(LPVOID lpParam);
//����t�@�C���p�X���b�h�֐�
unsigned __stdcall  PlayVideo(LPVOID lpParam);

//string�^��wstring�^�ɕϊ�����B
std::wstring string_to_wstring(std::string const& src, UINT CodePage = CP_ACP);

//wstring�^��string�^�ɕϊ�����B
std::string wstring_to_string(std::wstring const& wsrc, UINT CodePage = CP_ACP);

//�f�o�C�X�t�H�[�}�b�g�������Ή�����GUID�l�ɕϊ�����
GUID getStringAsMediaSubtype(tstring typestr);
