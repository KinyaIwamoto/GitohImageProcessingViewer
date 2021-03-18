#include "pch.h"
#include "framework.h"
#include<process.h>
#include <system_error>
#include"EasyLib.h"
#include "Functions.h"


//�t�@�C�����J���_�C�A���OWin32API�̃��b�p�[
BOOL glGetOpenFileName(tstring* FileFullPath, tstring* FileName, tstring InitialDir, const TCHAR* Filter)
{
	//static TCHAR		filefullpath[MAX_PATH];
	TCHAR		filefullpath[MAX_PATH] = _T("\0");		//�k�������i\0�j�ŏ��������Ȃ��ƃ_�C�A���O�̐����Ɏ��s����B
	TCHAR		filename[MAX_PATH];
	static TCHAR		customfilter[MAX_FILTER_NAME];
	const TCHAR* strInitialDir = InitialDir.c_str();
	//const TCHAR*	strFilter = Filter.c_str();
	const TCHAR* strFilter = Filter;
	const TCHAR* strTitle = _T("�t�@�C�����J��");

	static int filterindex = 0;
	OPENFILENAME		ofn;

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	//ofn.hInstance;
	ofn.lpstrFilter = strFilter;
	ofn.lpstrCustomFilter = customfilter;
	ofn.nMaxCustFilter = sizeof(customfilter);
	ofn.nFilterIndex = filterindex;
	ofn.lpstrFile = filefullpath;
	ofn.nMaxFile = sizeof(filefullpath);
	ofn.lpstrFileTitle = filename;
	ofn.nMaxFileTitle = sizeof(filename);
	ofn.lpstrInitialDir = strInitialDir;
	//ofn.lpstrTitle = strTitle;
	ofn.lpstrTitle = strTitle;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_EXPLORER;
	//ofn.nFileOffset;
	//ofn.nFileExtension;
	//ofn.lpstrDefExt;
	//ofn.lCustData;
	//ofn.lpfnHook;
	//ofn.lpTemplateName;
	if (!::GetOpenFileName(&ofn))  return FALSE;
	if (FileFullPath)*FileFullPath = tstring(filefullpath);
	if (FileName)*FileName = tstring(filename);
	return TRUE;
}

//�C���[�W�E�C���h�E�̈ʒu�A�傫���A�\���{���̎Z�o
void ImageWindowPositioning(
	int width,				//�摜�̕�
	int height,				//�摜�̍���
	int dtwidth,			//�f�X�N�g�b�v�̕�
	int bw_y,				//�{�^���E�C���h�E�̏�[
	int* imb_x,			//�C���[�W�E�C���h�E�̍���X���W
	int* imb_y,			//�C���[�W�E�C���h�E�̍���Y���W
	int* zoom_num		//�\���{��
)
{
	const int left_margin = 5;
	const int right_margin = 400;
	const int top_margin = 5;
	const int bottom_margin = 45;
	const int dtcenter_x = (dtwidth - (left_margin + right_margin)) / 2;		//�f�X�N�g�b�v�Z���^��X���W

	*zoom_num = 100;
	int timb_x = dtcenter_x - (width / 2);
	int timb_y = bw_y - (height + (top_margin + bottom_margin));
	if (timb_x < 0 || timb_y < 0)
	{
		int z_num1 = 100;
		int z_num2 = 100;
		if (timb_x < 0) timb_x = left_margin;
		if (timb_y < 0) timb_y = top_margin;

		if (width > dtwidth - (left_margin + right_margin))
		{
			z_num1 = (int)((double)(dtwidth - (left_margin + right_margin)) / (double)width * 100);
		}
		if (height > bw_y - (top_margin + bottom_margin))
		{
			z_num2 = (int)((double)(bw_y - (top_margin + bottom_margin)) / (double)height * 100);
		}
		if (z_num1 < z_num2)
		{
			*zoom_num = z_num1;
			timb_y = (bw_y - height * z_num1 / 100) - (top_margin + bottom_margin);
		}
		else
		{
			*zoom_num = z_num2;
			timb_x = dtcenter_x - width * z_num2 / 100 / 2;
		}
	}
	*imb_x = timb_x;
	*imb_y = timb_y;
}

//�ڑ�����Ă���J�����̏����W�߂�
std::vector<std::vector<RES>> CamInit()
{
	int result = 0;
	int camera_num = 0;
	std::vector<std::vector<RES>> cam_formats;
	result = EWC_Open(0);
	if (result)
	{
		ESP_Printf("�J�������ڑ�����Ă��܂��� %d\n", result);
		//opecap_num = Video;
	}
	else
	{
		camera_num = EWC_GetCamera();
		ESP_Printf("�J���������o����܂���\n");
		ESP_Printf("�J�����ڑ��䐔 %d\n", camera_num);
		EWC_Close(0);
		for (int i = 0; i < camera_num; i++)
		{
			EWC_Open(0, 0, 0, 0, i);
			//cam_name.push_back(EWC_GetDeviceName(i));
			ESP_PrintfU("%d��ځF%s\n", i + 1, EWC_GetDeviceName(0));
			ewc_format f[MAXFORMAT];
			int n = MAXFORMAT;
			result = EWC_GetFormat(i, f, &n);       //�t�H�[�}�b�g�擾
			//ESP_Printf("EWC_GetFormat()=%d n=%d \n", result, n);
			std::vector<RES> cam_format;
			for (int j = 0; j < n; j++) {
				ESP_PrintfU("%d: %dx%d(%d) %I64d %f[fps] %s\n"
					, j, f[j].width, f[j].height, f[j].bit, f[j].AvgTimePerFrame, f[j].fps, f[j].subtype_t);
				RES format;
				format.name = EWC_GetDeviceName(0);
				format.width = f[j].width;
				format.height = f[j].height;
				format.frame = f[j].fps;
				format.format = f[j].subtype_t;
				cam_format.push_back(format);
			}
			EWC_Close(0);
			cam_formats.push_back(cam_format);
		}
	}
	return cam_formats;
}

//���L�������̏�����
HANDLE InitShareMemory(tstring memortname, size_t typesize, LPVOID* lpmemory)
{
	HANDLE hMemory;
	// �}�b�s���O�I�u�W�F�N�g�쐬
	hMemory = ::CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		typesize,		// ���L�������̃T�C�Y
		memortname.c_str()// ���L��������
	);

	if (hMemory == NULL) {
		tstring sbuff = _T("CreateFileMapping�G���[");
		tstring caption = _T("�G���[");
		::MessageBox(NULL, sbuff.c_str(), caption.c_str(), MB_OK);
		return NULL;
	}

	// ���L���������}�b�s���O
	*lpmemory = ::MapViewOfFile(hMemory, FILE_MAP_WRITE, 0, 0, 0);
	if (*lpmemory == NULL) {
		tstring sbuff = _T("MapViewOfFile�G���[");
		tstring caption = _T("�G���[");
		::MessageBox(NULL, sbuff.c_str(), caption.c_str(), MB_OK);
		return NULL;
	}
	return hMemory;
}

//���L���������J��
HANDLE OpenShareMemory(tstring memortname, LPVOID* lpmemory)
{
	HANDLE hMemory;
	// ���L������Open
	hMemory = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, memortname.c_str());
	*lpmemory = ::MapViewOfFile(hMemory, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	return hMemory;
}

//���L�����������
void CloseShareMemory(HANDLE hmemory, LPVOID* lpmemory)
{
	::UnmapViewOfFile(*lpmemory);
	::CloseHandle(hmemory);
}

//�J�����t�H�[�}�b�g�̑I��
RES SelectCameraFormat(const int dtcenter_x, const int bw_y, std::vector<std::vector<RES>> cam_formats, int& use_cam_num)
{
	//int use_cam_num = 0;
	int use_cam_format = 0;
	ESP_OpenTextWindow(0, dtcenter_x - 320, bw_y - 870, 640, 800);
	if (cam_formats.size() > 1)
	{
		for (int i = 0; i < cam_formats.size(); i++)
		{
			ESP_Printf("%d: %s\n", i, cam_formats[i][0].name.c_str());
		}
		while (TRUE)
		{
			ESP_Printf("Select[0-%d]:", cam_formats.size() - 1);
			char str[10];
			ESP_Input(str);         //�J������ԍ��őI��
			use_cam_num = atoi(str);
			if (use_cam_num < cam_formats.size())
			{
				break;
			}
			else
			{
				ESP_Printf("�I�����ꂽ�J�����̕����ԍ��͖����ł��B\n");
			}
		}
	}
	ESP_Printf("�I�����ꂽ�J�����̕����ԍ�: %d\n", use_cam_num);
	ESP_Printf("�I�����ꂽ�J�����̖���: %s\n", cam_formats[use_cam_num][0].name.c_str());
	for (int i = 0; i < cam_formats[use_cam_num].size(); i++)
	{
		ESP_PrintfU("%d: %dx%d %f[fps] %s\n"
			, i, cam_formats[use_cam_num][i].width, cam_formats[use_cam_num][i].height,
			cam_formats[use_cam_num][i].frame, cam_formats[use_cam_num][i].format.c_str());
	}
	while (TRUE)
	{
		ESP_Printf("Select[0-%d]:", cam_formats[use_cam_num].size() - 1);
		char str[10];
		ESP_Input(str);         //�J������ԍ��őI��
		use_cam_format = atoi(str);
		if (use_cam_format < cam_formats[use_cam_num].size())
		{
			break;
		}
		else
		{
			ESP_Printf("�I�����ꂽ�t�H�[�}�b�g�ԍ��͖����ł��B\n");
		}
	}
	ESP_CloseTextWindow(0);
	return cam_formats[use_cam_num][use_cam_format];
}

//�C���[�W�E�C���h�E�E���̃e�L�X�g�E�C���h�E���J��
//void OpenRTextWindow(int txt_win_num, int txtw_w, int txtw_h, int imb_x, int imb_y, int width, int zoom_num, int margin)
//{
//	int txtw_x = imb_x + width * zoom_num / 100 + margin;
//	int txtw_y = imb_y;
//	ESP_OpenTextWindow(txt_win_num, txtw_x, txtw_y, txtw_w, txtw_h);
//}

unsigned __stdcall  PlayCamera(LPVOID lpParam)
{
	HANDLE	hShoriFlag;
	BOOL* lpShoriFlag;
	HANDLE	hStartFlag;
	BOOL* lpStartFlag;
	int counter = 0;
	int cam_logicalnun = ((PARAM*)lpParam)->device_num;
	//RES CamFormat = ((PARAM*)lpParam)->format; //RES�ɑ������ƃ������[���[�N����
	//const int width = CamFormat.width;
	const int width = ((PARAM*)lpParam)->format.width;
	const int height = ((PARAM*)lpParam)->format.height;
	int* img32 = new int[width * width];
	LPBITMAPINFO bmpinf = NULL;
	LPBYTE img24 = glInitDIBImage(width, height);
	LPBYTE camBuffer = new BYTE[EWC_GetBufferSize(cam_logicalnun)];
	glSetBmpInfo(&bmpinf, width, height);

	LARGE_INTEGER	cnt1, cnt2, cnt3;				// ������\�^�C�}�[�p�ϐ�
	LONGLONG	 freq = 0;								// �v���Z�b�T�̏������g���i������\�^�C�}�[�p�ϐ��j
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	QueryPerformanceCounter(&cnt1);

	ESP_Printf("�X���b�h�X�^�[�g\n");
	// ���L������Open
	hStartFlag = OpenShareMemory(_T("STARTFLAG"), (LPVOID*)&lpStartFlag);
	hShoriFlag = OpenShareMemory(_T("SHORIFLAG"), (LPVOID*)&lpShoriFlag);

	LPINT Rimage1 = new int[width * height];;
	LPINT Bimage1 = new int[width * height];;
	LPINT Gimage1 = new int[width * height];;
	LPINT Rimage2 = new int[width * height];;
	LPINT Bimage2 = new int[width * height];;
	LPINT Gimage2 = new int[width * height];;

	for (;;)
	{
		if (!*lpStartFlag)break;
		//ESP_Printf("%d\n", counter++);
		if (EWC_IsCaptured(cam_logicalnun)) {
			//EWC_GetImage(cam_logicalnun, ESP_VramPtr[0]);
			//EWC_GetImage(cam_logicalnun, img32);
			EWC_GetImage(cam_logicalnun, camBuffer);
			glConvertBGRtoDIB(img24, camBuffer, width, height, FALSE);
			if (*lpShoriFlag)
			{
				//�����ɉ摜�����̃R�[�h������
				//�����܂�
			}
			glBitmapFlipVertical(img24, img24, width, height, Rimage1, Gimage1, Bimage1, Rimage2, Gimage2, Bimage2);
			glBmp24ToBmp32(img24, (LPBYTE)img32, width, height);
			ESP_PutWindow(img32, 0, 0, width, height);
			ESP_Update();
			ESP_Locate(0, -1);
			QueryPerformanceCounter(&cnt2);
			double fps = (double)(cnt2.QuadPart - cnt1.QuadPart) / (double)freq * 1000.0;
			cnt1 = cnt2;
			//ESP_Printf("FPS:%.3f", 1.0 / ewc_s[cam_logicalnun].ftime);
			ESP_Printf("FPS:%.3f", fps);
		}
	}
	ESP_PrintfU("�X���b�h�G���h\n");

	if (img32)
	{
		delete[] img32;
		img32 = NULL;
	}

	glDeleteImageData(&img24);
	glDelImageBuffer(&camBuffer);
	delete bmpinf;

	delete[] Rimage1;
	delete[] Gimage1;
	delete[] Bimage1;
	delete[] Rimage2;
	delete[] Gimage2;
	delete[] Bimage2;

	::UnmapViewOfFile(lpStartFlag);
	::CloseHandle(hStartFlag);
	::UnmapViewOfFile(lpShoriFlag);
	::CloseHandle(hShoriFlag);
#ifndef _MFC_VER
	::_endthreadex(0);
#else
	::AfxEndThread(0);
#endif // !_MFC_VER

	return 0;
}

unsigned __stdcall  PlayVideo(LPVOID lpParam)
{
	HANDLE	hShoriFlag;
	BOOL* lpShoriFlag;
	HANDLE	hStartFlag;
	BOOL* lpStartFlag;
	HANDLE	hPauseFlag;
	BOOL* lpPauseFlag;
	int result;
	BOOL flgFirst = FALSE;
	int video_num = ((PARAM*)lpParam)->device_num;
	//RES CamFormat = ((PARAM*)lpParam)->format;
	const int width = ((PARAM*)lpParam)->format.width;
	const int height = ((PARAM*)lpParam)->format.height;

	LARGE_INTEGER	cnt1, cnt2, cnt3;				// ������\�^�C�}�[�p�ϐ�
	LONGLONG	 freq = 0;								// �v���Z�b�T�̏������g���i������\�^�C�}�[�p�ϐ��j
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	QueryPerformanceCounter(&cnt1);

	ESP_Printf("�X���b�h�X�^�[�g\n");
	// ���L������Open
	hStartFlag = OpenShareMemory(_T("STARTFLAG"), (LPVOID*)&lpStartFlag);
	hShoriFlag = OpenShareMemory(_T("SHORIFLAG"), (LPVOID*)&lpShoriFlag);
	hPauseFlag = OpenShareMemory(_T("PAUSEFLAG"), (LPVOID*)&lpPauseFlag);
	SHRAEMEMORY<BOOL>RepeatFlag = OpenShareMemory<BOOL>(_T("REPEATFLG"));

	int* img32 = new int[width * width];
	LPBYTE img24 = NULL;
	LPBITMAPINFO bmpinf = NULL;
	glSetBmpInfo(&bmpinf, width, height);
	glInitImageData(&img24, width, height);

	LPINT Rimage1 = new int[width * height];;
	LPINT Bimage1 = new int[width * height];;
	LPINT Gimage1 = new int[width * height];;
	LPINT Rimage2 = new int[width * height];;
	LPINT Bimage2 = new int[width * height];;
	LPINT Gimage2 = new int[width * height];;

	for (;;) {
		if (!*lpStartFlag)break;
		if (*lpShoriFlag)
		{
			flgFirst = TRUE;
			if (*lpPauseFlag)continue; //�u�ꎞ��~�v�{�^���������ꂽ�ꍇ
			result = EVF_Next(video_num);
			ESP_Printf("Next:%d f:%d  ", result, EVF_Frame(0));
			if (result)
			{
				if (!*(RepeatFlag.memory))
				{
					ESP_SetButtonBox(StartStop);
				}
				result = EVF_Seek(video_num, 0);
				//break;
			}
			//EVF_GetFrame24to32(video_num, img32);
			EVF_GetFrame(video_num, img24);
			//�����ɉ摜�����̃R�[�h������
			//glBitmapFlipVertical(img24, img24, width, height, Rimage1, Gimage1, Bimage1, Rimage2, Gimage2, Bimage2);
			//FaceDRAVFanc(img24, img24, bmpinf);
			//glBitmapFlipVertical(img24, img24, width, height, Rimage1, Gimage1, Bimage1, Rimage2, Gimage2, Bimage2);
			//�����܂�
			glBmp24ToBmp32(img24, (LPBYTE)img32, width, height);
			ESP_PutWindow(img32, 0, 0, width, height);
			ESP_Update();
			QueryPerformanceCounter(&cnt2);
			double fps = (double)(cnt2.QuadPart - cnt1.QuadPart) / (double)freq * 1000.0;
			cnt1 = cnt2;
			ESP_Printf("FPS:%.3f\n", fps);
		}
		else
		{
			if (flgFirst)
			{
				flgFirst = FALSE;
				if (*lpPauseFlag)
				{
					ESP_SetButtonBox(PauseRestart);
				}
				for (;;)
				{
					result = EVF_Seek(video_num, 0);
					if (result == 0)break;
					//�u��~�v�{�^���Ŏ~�߂����ɕ\����0�t���[���ڂɖ߂�Ȃ��ꍇ������B
					//�V�[�N�͐���ɂ���Ă���B�t���[���o�b�t�@�̉摜���X�V����Ȃ�
					//�ꍇ������̂ł͂Ȃ����B
					//ESP_Update();�ōX�V�����Ă��\�����ς��Ȃ��ꍇ������B
				}
				EVF_GetFrame24to32(video_num, img32);
				ESP_PutWindow(img32, 0, 0, width, height);
				ESP_Update();
			}
		}
	}

	if (img32)
	{
		delete[] img32;
		img32 = NULL;
	}

	glDeleteImageData(&img24);
	delete bmpinf;

	delete[] Rimage1;
	delete[] Gimage1;
	delete[] Bimage1;
	delete[] Rimage2;
	delete[] Gimage2;
	delete[] Bimage2;

	::UnmapViewOfFile(lpStartFlag);
	::CloseHandle(hStartFlag);
	::UnmapViewOfFile(lpShoriFlag);
	::CloseHandle(hShoriFlag);
	::UnmapViewOfFile(lpPauseFlag);
	::CloseHandle(hPauseFlag);
	CloseShareMemory<BOOL>(RepeatFlag);
	ESP_Printf("�X���b�h�G���h\n");
#ifndef _MFC_VER
	::_endthreadex(0);
#else
	::AfxEndThread(0);
#endif // !_MFC_VER

	return 0;

}

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
//common.h�����gl*.h�g�p���͈ȉ��폜
//string�^��wstring�^�ɕϊ�����B
std::wstring string_to_wstring(std::string const& src, UINT CodePage)
{
	auto const dest_size = ::MultiByteToWideChar(CodePage, 0U, src.data(), -1, nullptr, 0U);
	std::vector<wchar_t> dest(dest_size, L'\0');
	if (::MultiByteToWideChar(CodePage, 0U, src.data(), -1, dest.data(), dest.size()) == 0) {
		throw std::system_error{ static_cast<int>(::GetLastError()), std::system_category() };
	}
	dest.resize(std::char_traits<wchar_t>::length(dest.data()));
	dest.shrink_to_fit();
	return std::wstring(dest.begin(), dest.end());
}


//wstring�^��string�^�ɕϊ�����B
std::string wstring_to_string(std::wstring const& wsrc, UINT CodePage)
{
	auto const dest_size = ::WideCharToMultiByte(CodePage, 0U, wsrc.data(), -1, nullptr, 0, nullptr, nullptr);
	std::vector<char> dest(dest_size, '\0');
	if (::WideCharToMultiByte(CodePage, 0U, wsrc.data(), -1, dest.data(), (int)dest.size(), nullptr, nullptr) == 0) {
		throw std::system_error{ static_cast<int>(::GetLastError()), std::system_category() };
	}
	dest.resize(std::char_traits<char>::length(dest.data()));
	dest.shrink_to_fit();
	return std::string(dest.begin(), dest.end());
}

//24bit Bitmap�f�[�^�̃T�C�Y��ݒ肷��
void WINAPI glInitImageData(
	LPBYTE * BmpImage,		//Bitmap�f�[�^
	long xsize,					//�摜�̕��T�C�Y
	long ysize						//�摜�̏c�T�C�Y
)
{
	int surplus;
	surplus = 4 - xsize * 3 % 4;
	if (surplus == 4) surplus = 0;

	*BmpImage = new BYTE[xsize * ysize * 3 + surplus * ysize];

}

//24bit DIBImage�f�[�^�̐ݒ肷��
LPBYTE glInitDIBImage(
	long xsize,						//�摜�̕��T�C�Y
	long ysize							//�摜�̏c�T�C�Y
)
{
	LPBYTE DIBImage;		//DIBImage�f�[�^
	int surplus;
	surplus = 4 - xsize * 3 % 4;
	if (surplus == 4) surplus = 0;

	DIBImage = new BYTE[xsize * ysize * 3 + surplus * ysize];

	return DIBImage;

}

//BITMAPINFO�̐ݒ�
void WINAPI glSetBmpInfo(
	LPBITMAPINFO * bmpinfo,			//BITMAPINFO
	long xsize,						//�摜�̕��T�C�Y
	long ysize,						//�摜�̏c�T�C�Y
	long bitcount					//1�s�N�Z��������̃r�b�g���B���̒l��0,1,4,8,16,24,32�̂����ꂩ�̒l�����B
)
{
	int imagesize;

	if (bitcount == 24) {
		int surplus = 4 - xsize * 3 % 4;
		if (surplus == 4) surplus = 0;
		imagesize = xsize * ysize * 3 + surplus * ysize;
	}
	else if (bitcount == 32) {
		imagesize = xsize * ysize * 4;
	}
	else if (bitcount == 8) {
		imagesize = xsize * ysize;
	}

	if (*bmpinfo) delete[] * bmpinfo;
	if (bitcount >= 16) {
		*bmpinfo = (LPBITMAPINFO)new char[sizeof(BITMAPINFO)];
	}
	else {
		*bmpinfo = (LPBITMAPINFO)new char[sizeof(BITMAPINFOHEADER) + (1 << bitcount) * sizeof(RGBQUAD)];
	}

	(*bmpinfo)->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	(*bmpinfo)->bmiHeader.biWidth = xsize;
	(*bmpinfo)->bmiHeader.biHeight = ysize;
	(*bmpinfo)->bmiHeader.biPlanes = 1;
	(*bmpinfo)->bmiHeader.biBitCount = (WORD)bitcount;
	(*bmpinfo)->bmiHeader.biCompression = BI_RGB;
	(*bmpinfo)->bmiHeader.biSizeImage = imagesize;
	(*bmpinfo)->bmiHeader.biXPelsPerMeter = 0;
	(*bmpinfo)->bmiHeader.biYPelsPerMeter = 0;
	(*bmpinfo)->bmiHeader.biClrUsed = 0;
	(*bmpinfo)->bmiHeader.biClrImportant = 0;

	//RGB�J���[�p���b�g�̏�����(8bit,1bit�̏ꍇ)
	if (bitcount < 16 && bitcount > 0) {
		unsigned char* bmtinfo_ofs;
		bmtinfo_ofs = (unsigned char*)bmpinfo;
		RGBQUAD* SI_rgb = (RGBQUAD*)&bmtinfo_ofs[sizeof(BITMAPINFOHEADER)];
		int rr;
		int rrr;
		if (bitcount == 8)rrr = 256;
		else rrr = 2;
		for (rr = 0; rr < rrr; rr++) {
			SI_rgb[rr].rgbBlue = rr;
			SI_rgb[rr].rgbGreen = rr;
			SI_rgb[rr].rgbRed = rr;
			SI_rgb[rr].rgbReserved = 0;
		}
	}
}

//BGR�`���̉摜��DIB�֕ϊ�����
void glConvertBGRtoDIB(
	LPBYTE lpbyDib,
	LPBYTE lpbyBgr,
	const int width,
	const int height,
	const bool mode
)
{
	int surplus = 4 - width * 3 % 4;
	if (surplus == 4) surplus = 0;
	const int nDstLine = width * 3 + surplus;
	const int nSrcLine = width * 3;

	for (int i = 0; i < height; i++) {
		LPBYTE pDst = lpbyDib + nDstLine * i;
		LPBYTE pSrc;
		if (mode)
			pSrc = lpbyBgr + nSrcLine * i;
		else
			pSrc = lpbyBgr + nSrcLine * (height - 1 - i);

		memcpy(pDst, pSrc, sizeof(BYTE) * nSrcLine);

	}
}

// �C���[�W�f�[�^�o�b�t�@�̉��
void glDelImageBuffer(
	LPBYTE* CameraImage
)
{
	if (*CameraImage != NULL) {
		delete[] * CameraImage;
		*CameraImage = NULL;
	}
}

//�z��f�[�^��j������B
template<class T>
void WINAPI DleteArray(
	T** ArrayData				//�z��f�[�^
)
{
	if (*ArrayData) delete[] * ArrayData;
	*ArrayData = NULL;
}

//Bitmap�f�[�^��j������
void WINAPI glDeleteImageData(
	LPBYTE * BmpImage		//Bitmap�f�[�^
)
{
	DleteArray<BYTE>(BmpImage);
}

//RBG�Ɨ���int image[X][Y]�`�����̂�����24Bit Bitmap�f�[�^�`���ɕϊ�
static void WINAPI glChgRGBArrToBmpImage(
	LPINT r_image_in,				//int image[X][Y]�`���̃f�[�^(R)
	LPINT g_image_in,				//int image[X][Y]�`���̃f�[�^(G)
	LPINT b_image_in,				//int image[X][Y]�`���̃f�[�^(B)
	LPBYTE image_out,		//24Bit Bitmap�f�[�^�`��
	long width,					//�摜�̕��T�C�Y
	long height					//�摜�̏c�T�C�Y
)
{
	long i, j, k;
	long p1, p2, p3;
	int surplus;
	//unsigned char buf;
	surplus = 4 - width * 3 % 4;
	if (surplus == 4) surplus = 0;

	for (i = 0; i < height; i++) {
		p1 = height - i - 1;
		for (j = 0; j < width; j++) {
			p2 = height * j + p1;
			p3 = 3 * (width * i + j) + i * surplus;
			*(image_out + p3) = (unsigned char)*(b_image_in + p2);
			*(image_out + p3 + 1) = (unsigned char)*(g_image_in + p2);
			*(image_out + p3 + 2) = (unsigned char)*(r_image_in + p2);

			if (surplus != 0 && j == height - 1) {
				for (k = 0; k < surplus; k++)
					*(image_out + p3 + 2 + k + 1) = 0;
			}
		}
	}
}


//24Bit Bitmap�f�[�^�`����RBG�Ɨ���int image[X][Y]�`���ɕϊ�
static void WINAPI glChgBmpImageToRBGArr(
	LPBYTE image_in,		//24Bit Bitmap�f�[�^�`��
	LPINT r_image_out,				//int image[X][Y]�`���̃f�[�^(R)
	LPINT g_image_out,				//int image[X][Y]�`���̃f�[�^(G)
	LPINT b_image_out,				//int image[X][Y]�`���̃f�[�^(B)
	long width,					//�摜�̕��T�C�Y
	long height					//�摜�̏c�T�C�Y
)
{
	long i, j;
	long p1, p2, p3;
	int surplus;
	surplus = 4 - width * 3 % 4;
	if (surplus == 4) surplus = 0;

	for (i = 0; i < height; i++) {
		p1 = height - i - 1;
		for (j = 0; j < width; j++) {
			p2 = height * j + p1;
			p3 = 3 * (width * i + j) + i * surplus;
			*(b_image_out + p2) = (int)*(image_in + p3);
			*(g_image_out + p2) = (int)*(image_in + p3 + 1);
			*(r_image_out + p2) = (int)*(image_in + p3 + 2);
		}
	}
}

//�摜���㉺���]����
static void WINAPI grImageFlipVertical(
	LPINT imageXY_in,							//���摜���i�[����z��int image[X][Y]�`��
	LPINT imageXY_out,							//�T�C�Y�ύX��摜���i�[����z��int image[X][Y]�`
	long width,									//�摜�̕��T�C�Y
	long height									//�摜�̏c�T�C�Y
)
{
	LPINT image_buf;
	long x, y;

	if (imageXY_in == imageXY_out) {
		if ((image_buf = (int*)malloc(sizeof(int) * width * height)) == NULL) return;

	}
	else {
		image_buf = imageXY_out;
	}

	for (x = 0; x < width; x++)
		for (y = 0; y < height; y++) {
			*(image_buf + x * height + (height - y - 1)) = *(imageXY_in + x * height + y);
		}

	if (imageXY_in == imageXY_out) {
		memcpy(imageXY_out, image_buf, sizeof(int) * width * height);
		free(image_buf);
	}
}

//24bit Bitmap�f�[�^���㉺���]����
void WINAPI glBitmapFlipVertical(
	LPBYTE BmpImage24_in,		//���r�b�g�}�b�v�f�[�^
	LPBYTE BmpImage24_out,		//�㉺���]��̃r�b�g�}�b�v�f�[�^
	long width,					//���摜�̕��T�C�Y
	long height,					//���摜�̏c�T�C�Y
	int* buf1Rimage,			//��Ɨp�摜�o�b�t�@
	int* buf1Gimage,			//��Ɨp�摜�o�b�t�@
	int* buf1Bimage,			//��Ɨp�摜�o�b�t�@
	int* buf2Rimage,			//��Ɨp�摜�o�b�t�@
	int* buf2Gimage,			//��Ɨp�摜�o�b�t�@
	int* buf2Bimage				//��Ɨp�摜�o�b�t�@
)
{
	LPINT Rimage1;
	LPINT Bimage1;
	LPINT Gimage1;
	LPINT Rimage2;
	LPINT Bimage2;
	LPINT Gimage2;

	if (buf1Rimage) Rimage1 = buf1Rimage;
	else Rimage1 = new int[width * height];
	if (buf1Gimage) Gimage1 = buf1Gimage;
	else Gimage1 = new int[width * height];
	if (buf1Bimage) Bimage1 = buf1Bimage;
	else Bimage1 = new int[width * height];

	if (buf2Rimage) Rimage2 = buf2Rimage;
	else Rimage2 = new int[width * height];
	if (buf2Gimage) Gimage2 = buf2Gimage;
	else Gimage2 = new int[width * height];
	if (buf2Bimage) Bimage2 = buf2Bimage;
	else Bimage2 = new int[width * height];

	LPBYTE image_buf;
	int surplus;
	surplus = 4 - width * 3 % 4;
	if (surplus == 4) surplus = 0;

	if (BmpImage24_in == BmpImage24_out) {
		if ((image_buf = (LPBYTE)malloc(sizeof(BYTE) * (width * height * 3 + height * surplus))) == NULL) return;

	}
	else {
		image_buf = BmpImage24_out;
	}
	glChgBmpImageToRBGArr(BmpImage24_in, Rimage1, Gimage1, Bimage1, width, height);
	grImageFlipVertical(Rimage1, Rimage2, width, height);
	grImageFlipVertical(Gimage1, Gimage2, width, height);
	grImageFlipVertical(Bimage1, Bimage2, width, height);
	glChgRGBArrToBmpImage(Rimage2, Gimage2, Bimage2, image_buf, width, height);

	if (BmpImage24_in == BmpImage24_out) {
		memcpy(BmpImage24_out, image_buf, sizeof(BYTE) * (width * height * 3 + height * surplus));
		free(image_buf);
	}

	if (!buf1Rimage)	delete[] Rimage1;
	if (!buf1Gimage)	delete[] Gimage1;
	if (!buf1Bimage) delete[] Bimage1;

	if (!buf2Rimage) delete[] Rimage2;
	if (!buf2Gimage) delete[] Gimage2;
	if (!buf2Bimage) delete[] Bimage2;
}

//24Bit Bitmap�f�[�^�`����32Bit Bitmap�f�[�^�`���ɕϊ�
void WINAPI glBmp24ToBmp32(
	LPBYTE image_in,		//24Bit Bitmap�`���̃f�[�^
	LPBYTE image_out,		//32Bit Bitmap�`���̃f�[�^
	long width,					//�摜�̕��T�C�Y
	long height					//�摜�̏c�T�C�Y
)
{
	long i, j;
	int surplus;
	surplus = 4 - width * 3 % 4;
	if (surplus == 4) surplus = 0;

	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			*(image_out + 4 * (width * i + j)) = *(image_in + 3 * (width * i + j) + i * surplus);
			*(image_out + 4 * (width * i + j) + 1) = *(image_in + 3 * (width * i + j) + i * surplus + 1);
			*(image_out + 4 * (width * i + j) + 2) = *(image_in + 3 * (width * i + j) + i * surplus + 2);
			*(image_out + 4 * (width * i + j) + 3) = 0;
		}
	}
}

//�f�o�C�X�t�H�[�}�b�g�������Ή�����GUID�l�ɕϊ�����
GUID getStringAsMediaSubtype(tstring typestr)
{

	GUID tmpMS;
	if (typestr == _T("RGB24"))tmpMS = MEDIASUBTYPE_RGB24;
	else if (typestr == _T("RGB32"))tmpMS = MEDIASUBTYPE_RGB32;
	else if (typestr == _T("RGB555"))tmpMS = MEDIASUBTYPE_RGB555;
	else if (typestr == _T("RGB565"))tmpMS = MEDIASUBTYPE_RGB565;
	else if (typestr == _T("YUY2"))tmpMS = MEDIASUBTYPE_YUY2;
	else if (typestr == _T("YVYU"))tmpMS = MEDIASUBTYPE_YVYU;
	else if (typestr == _T("YUYV"))tmpMS = MEDIASUBTYPE_YUYV;
	else if (typestr == _T("IYUV"))tmpMS = MEDIASUBTYPE_IYUV;
	else if (typestr == _T("UYVY"))tmpMS = MEDIASUBTYPE_UYVY;
	else if (typestr == _T("YV12"))tmpMS = MEDIASUBTYPE_YV12;
	else if (typestr == _T("YVU9"))tmpMS = MEDIASUBTYPE_YVU9;
	else if (typestr == _T("Y411"))tmpMS = MEDIASUBTYPE_Y411;
	else if (typestr == _T("Y41P"))tmpMS = MEDIASUBTYPE_Y41P;
	else if (typestr == _T("Y211"))tmpMS = MEDIASUBTYPE_Y211;
	else if (typestr == _T("AYUV"))tmpMS = MEDIASUBTYPE_AYUV;
	//else if (typestr == _T("Y800"))tmpMS = MEDIASUBTYPE_Y800;
	//else if (typestr == _T("Y8"))tmpMS = MEDIASUBTYPE_Y8;
	//else if (typestr == _T("GREY"))tmpMS = MEDIASUBTYPE_GREY;
	else if (typestr == _T("MJPG"))tmpMS = MEDIASUBTYPE_MJPG;
	else tmpMS = MEDIASUBTYPE_RGB24;

	return tmpMS;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

