#include<process.h>
#include <system_error>
#include"EasyLib.h"
#include "Functions.h"


//ファイルを開くダイアログWin32APIのラッパー
BOOL GetOpenFileName(tstring* FileFullPath, tstring* FileName, tstring InitialDir, const TCHAR* Filter)
//BOOL GetOpenFileName(tstring* FileFullPath, tstring* FileName, tstring InitialDir, tstring Filter)
{
	//static TCHAR		filefullpath[MAX_PATH];
	TCHAR		filefullpath[MAX_PATH] = _T("\0");		//ヌル文字（\0）で初期化しないとダイアログの生成に失敗する。
	TCHAR		filename[MAX_PATH];
	static TCHAR		customfilter[MAX_FILTER_NAME];
	const TCHAR* strInitialDir = InitialDir.c_str();
	//const TCHAR*	strFilter = Filter.c_str();
	const TCHAR* strFilter = Filter;
	const TCHAR* strTitle = _T("ファイルを開く");

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

//イメージウインドウの位置、大きさ、表示倍率の算出
void ImageWindowPositioning(
	int width,				//画像の幅
	int height,				//画像の高さ
	int dtwidth,			//デスクトップの幅
	int bw_y,				//ボタンウインドウの上端
	int* imb_x,			//イメージウインドウの左上X座標
	int* imb_y,			//イメージウインドウの左上Y座標
	int* zoom_num		//表示倍率
)
{
	const int left_margin = 5;
	const int right_margin = 400;
	const int top_margin = 5;
	const int bottom_margin = 45;
	const int dtcenter_x = (dtwidth - (left_margin + right_margin)) / 2;		//デスクトップセンタのX座標

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

//接続されているカメラの情報を集める
std::vector<std::vector<RES>> CamInit()
{
	int result = 0;
	int camera_num = 0;
	std::vector<std::vector<RES>> cam_formats;
	result = EWC_Open(0);
	if (result)
	{
		ESP_Printf("カメラが接続されていません %d\n", result);
		//opecap_num = Video;
	}
	else
	{
		camera_num = EWC_GetCamera();
		ESP_Printf("カメラが検出されました\n");
		ESP_Printf("カメラ接続台数 %d\n", camera_num);
		EWC_Close(0);
		for (int i = 0; i < camera_num; i++)
		{
			EWC_Open(0, 0, 0, 0, i);
			//cam_name.push_back(EWC_GetDeviceName(i));
			ESP_PrintfU("%d台目：%s\n", i + 1, EWC_GetDeviceName(0));
			ewc_format f[MAXFORMAT];
			int n = MAXFORMAT;
			result = EWC_GetFormat(i, f, &n);       //フォーマット取得
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

//共有メモリの初期化
HANDLE InitShareMemory(tstring memortname, size_t typesize, LPVOID* lpmemory)
{
	HANDLE hMemory;
	// マッピングオブジェクト作成
	hMemory = ::CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		typesize,		// 共有メモリのサイズ
		memortname.c_str()// 共有メモリ名
	);

	if (hMemory == NULL) {
		tstring sbuff = _T("CreateFileMappingエラー");
		tstring caption = _T("エラー");
		::MessageBox(NULL, sbuff.c_str(), caption.c_str(), MB_OK);
		return NULL;
	}

	// 共有メモリをマッピング
	*lpmemory = ::MapViewOfFile(hMemory, FILE_MAP_WRITE, 0, 0, 0);
	if (*lpmemory == NULL) {
		tstring sbuff = _T("MapViewOfFileエラー");
		tstring caption = _T("エラー");
		::MessageBox(NULL, sbuff.c_str(), caption.c_str(), MB_OK);
		return NULL;
	}
	return hMemory;
}

//共有メモリを開く
HANDLE OpenShareMemory(tstring memortname, LPVOID* lpmemory)
{
	HANDLE hMemory;
	// 共有メモリOpen
	hMemory = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, memortname.c_str());
	*lpmemory = ::MapViewOfFile(hMemory, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	return hMemory;
}

//共有メモリを閉じる
void CloseShareMemory(HANDLE hmemory, LPVOID* lpmemory)
{
	::UnmapViewOfFile(*lpmemory);
	::CloseHandle(hmemory);
}

//カメラフォーマットの選択
RES SelectCameraFormat(const int dtcenter_x, const int bw_y, std::vector<std::vector<RES>> cam_formats, int& use_cam_num)
{
	//int use_cam_num = 0;
	int use_cam_format = 0;
	ESP_OpenTextWindow(0, dtcenter_x - 320, bw_y - 550, 640, 480);
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
			ESP_Input(str);         //カメラを番号で選択
			use_cam_num = atoi(str);
			if (use_cam_num < cam_formats.size())
			{
				break;
			}
			else
			{
				ESP_Printf("選択されたカメラの物理番号は無効です。\n");
			}
		}
	}
	ESP_Printf("選択されたカメラの物理番号: %d\n", use_cam_num);
	ESP_Printf("選択されたカメラの名称: %s\n", cam_formats[use_cam_num][0].name.c_str());
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
		ESP_Input(str);         //カメラを番号で選択
		use_cam_format = atoi(str);
		if (use_cam_format < cam_formats[use_cam_num].size())
		{
			break;
		}
		else
		{
			ESP_Printf("選択されたフォーマット番号は無効です。\n");
		}
	}
	ESP_CloseTextWindow(0);
	return cam_formats[use_cam_num][use_cam_format];
}

//イメージウインドウ右側のテキストウインドウを開く
void OpenRTextWindow(int txt_win_num, int txtw_w, int txtw_h, int imb_x, int imb_y, int width, int zoom_num, int margin)
{
	int txtw_x = imb_x + width * zoom_num / 100 + margin;
	int txtw_y = imb_y;
	ESP_OpenTextWindow(txt_win_num, txtw_x, txtw_y, txtw_w, txtw_h);
}

unsigned __stdcall  PlayCamera(LPVOID lpParam)
{
	HANDLE	hShoriFlag;
	BOOL* lpShoriFlag;
	HANDLE	hStartFlag;
	BOOL* lpStartFlag;
	int counter = 0;
	int cam_logicalnun = ((PARAM*)lpParam)->device_num;
	RES CamFormat = ((PARAM*)lpParam)->format;
	const int width = CamFormat.width;
	const int height = CamFormat.height;
	int* img32 = new int[width * width];

	ESP_Printf("スレッドスタート\n");
	// 共有メモリOpen
	hStartFlag = OpenShareMemory(_T("STARTFLAG"), (LPVOID*)&lpStartFlag);
	hShoriFlag = OpenShareMemory(_T("SHORIFLAG"), (LPVOID*)&lpShoriFlag);
	for (;;)
	{
		if (!*lpStartFlag)break;
		//ESP_Printf("%d\n", counter++);
		if (EWC_IsCaptured(cam_logicalnun)) {
			//EWC_GetImage(cam_logicalnun, ESP_VramPtr[0]);
			EWC_GetImage(cam_logicalnun, img32);
			if (*lpShoriFlag)
			{
				//ここに画像処理のコードを書く
				//ここまで
			}
			ESP_PutWindow(img32, 0, 0, width, height);
			ESP_Update();
			ESP_Locate(0, -1);
			ESP_Printf("FPS:%.3f", 1.0 / ewc_s[cam_logicalnun].ftime);
		}
	}
	ESP_PrintfU("スレッドエンド\n");

	if (img32)
	{
		delete[] img32;
		img32 = NULL;
	}

	::UnmapViewOfFile(lpStartFlag);
	::CloseHandle(hStartFlag);
	::UnmapViewOfFile(lpShoriFlag);
	::CloseHandle(hShoriFlag);
	::_endthreadex(0);
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
	RES CamFormat = ((PARAM*)lpParam)->format;
	const int width = CamFormat.width;
	const int height = CamFormat.height;

	ESP_Printf("スレッドスタート\n");
	// 共有メモリOpen
	hStartFlag = OpenShareMemory(_T("STARTFLAG"), (LPVOID*)&lpStartFlag);
	hShoriFlag = OpenShareMemory(_T("SHORIFLAG"), (LPVOID*)&lpShoriFlag);
	hPauseFlag = OpenShareMemory(_T("PAUSEFLAG"), (LPVOID*)&lpPauseFlag);
	SHRAEMEMORY<BOOL>RepeatFlag = OpenShareMemory<BOOL>(_T("REPEATFLG"));

	int* img32 = new int[width * width];

	for (;;) {
		if (!*lpStartFlag)break;
		if (*lpShoriFlag)
		{
			flgFirst = TRUE;
			if (*lpPauseFlag)continue; //「一時停止」ボタンが押された場合
			result = EVF_Next(video_num);
			ESP_Printf("Next:%d f:%d\n", result, EVF_Frame(0));
			if (result)
			{
				if (!*(RepeatFlag.memory))
				{
					ESP_SetButtonBox(StartStop);
				}
				result = EVF_Seek(video_num, 0);
				//break;
			}
			EVF_GetFrame24to32(video_num, img32);
			//ここに画像処理のコードを書く
			//ここまで
			ESP_PutWindow(img32, 0, 0, width, height);
			ESP_Update();
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
					//「停止」ボタンで止めた時に表示が0フレーム目に戻らない場合がある。
					//シークは正常にされている。フレームバッファの画像が更新されない
					//場合があるのではないか。
					//ESP_Update();で更新させても表示が変わらない場合がある。
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

	::UnmapViewOfFile(lpStartFlag);
	::CloseHandle(hStartFlag);
	::UnmapViewOfFile(lpShoriFlag);
	::CloseHandle(hShoriFlag);
	::UnmapViewOfFile(lpPauseFlag);
	::CloseHandle(hPauseFlag);
	CloseShareMemory<BOOL>(RepeatFlag);
	ESP_Printf("スレッドエンド\n");
	::_endthreadex(0);
	return 0;

}

//string型をwstring型に変換する。
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

//wstring型をstring型に変換する。
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

//デバイスフォーマット文字列を対応するGUID値に変換する
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

