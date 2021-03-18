
// GitohImageProcessingViewer.cpp : アプリケーションのクラス動作を定義します。
//

#include "pch.h"
#include "framework.h"
#include "GitohImageProcessingViewer.h"
#include "GitohImageProcessingViewerDlg.h"
#include<iostream>
#include<cmath>
//#include <string>

#define ESP_LIBRARY_MODE
#include "esplib.h"
#include "evflib.h"
#include "ewclib.h"
#include "Functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGitohImageProcessingViewerApp

BEGIN_MESSAGE_MAP(CGitohImageProcessingViewerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CGitohImageProcessingViewerApp の構築

CGitohImageProcessingViewerApp::CGitohImageProcessingViewerApp()
{
	// 再起動マネージャーをサポートします
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
	m_blSaveSettingsREG = TRUE;

}


// 唯一の CGitohImageProcessingViewerApp オブジェクト

CGitohImageProcessingViewerApp theApp;


// CGitohImageProcessingViewerApp の初期化

BOOL CGitohImageProcessingViewerApp::InitInstance()
{
	// アプリケーション マニフェストが visual スタイルを有効にするために、
	// ComCtl32.dll Version 6 以降の使用を指定する場合は、
	// Windows XP に InitCommonControlsEx() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// アプリケーションで使用するすべてのコモン コントロール クラスを含めるには、
	// これを設定します。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ダイアログにシェル ツリー ビューまたはシェル リスト ビュー コントロールが
	// 含まれている場合にシェル マネージャーを作成します。
	CShellManager *pShellManager = new CShellManager;

	// MFC コントロールでテーマを有効にするために、"Windows ネイティブ" のビジュアル マネージャーをアクティブ化
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 標準初期化
	// これらの機能を使わずに最終的な実行可能ファイルの
	// サイズを縮小したい場合は、以下から不要な初期化
	// ルーチンを削除してください。
	if (m_blSaveSettingsREG)
	{
		// 設定が格納されているレジストリ キーを変更します。
		// TODO: 会社名または組織名などの適切な文字列に
		// この文字列を変更してください。
		SetRegistryKey(_T("Gitoh"));
	}
	else
	{
		// iniファイル設定（EXEがあるフォルダの、EXEファイル名の拡張子がiniなものになるように）
		if (m_pszProfileName)
		{
			free((void*)m_pszProfileName);
		}
		TCHAR	szModulePathName[MAX_PATH];
		::GetModuleFileName(AfxGetInstanceHandle(), szModulePathName, MAX_PATH);	// DLLでも使えるようにAfxGetInstanceHandle()を使っている。
		TCHAR	szIniPathName[_MAX_PATH];
		TCHAR	drive[_MAX_DRIVE];
		TCHAR	dir[_MAX_DIR];
		TCHAR	fname[_MAX_FNAME];
		TCHAR	ext[_MAX_EXT];
		_tsplitpath_s(szModulePathName, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);
		_tmakepath_s(szIniPathName, _MAX_PATH, drive, dir, fname, _T("ini"));
		m_pszProfileName = _tcsdup(szIniPathName);
		if (!m_pszProfileName)
		{
			AfxMessageBox(_T("メモリ不足エラー"));
			return FALSE;
		}
	}


	//CGitohImageProcessingViewerDlg dlg;
	//m_pMainWnd = &dlg;
	//dlg.DoModal();
	CGitohImageProcessingViewerDlg* dlg = new CGitohImageProcessingViewerDlg();
	m_pMainWnd = dlg;
	//dlg.Create(IDD_GITOHIMAGEPROCESSINGVIEWER_DIALOG);
	dlg->ShowWindow(SW_HIDE);
	//dlg.RunModalLoop(MLF_NOKICKIDLE);


	//ここから必要な処理を書く
		//アプリケーションの初期化
	ESP_Start();
	const int button_width = 140;
	const int button_height = 40;
	const int button_x = 7;
	const int button_y = 1;
	const int bb_width = button_width * button_x;
	const int bb_height = button_height * button_y;
	RECT dtrect;
	HWND hDeskWnd = ::GetDesktopWindow();	 //この関数でデスクトップのハンドルを取得
	::GetWindowRect(hDeskWnd, &dtrect);			//デスクトップのハンドルからその(画面の)大きさを取得
	const int dtwidth = dtrect.right - dtrect.left;
	const int dtheight = dtrect.bottom - dtrect.top;
	const int dtcenter_x = dtwidth / 2;
	const int dtcenter_y = dtheight / 2;

	//ボタンウインドウの生成と設定
	const int bw_x = dtcenter_x - bb_width / 2;
	const int bw_y = dtheight - (bb_height + 120);

	int result = 0;
	int camera_num = 0;
	tstring mes;
	int opecap_num = Camera;
	int openclosecap_num = 0;
	int startstopcap_num = 0;
	int pauserestartcap_num = 0;
	int repeatcap_num = 0;
	RES CamFormat;

	ESP_OpenTextWindow(0, 5, 5, 640, 480);
	std::vector<std::vector<RES>> cam_formats = CamInit();
	if (cam_formats.size() == 0)
	{
		opecap_num = Video;
	}
	else
	{
		camera_num = cam_formats.size();
	}

	ESP_CloseTextWindow(0);
	ESP_OpenButtonBox(bw_x, bw_y, button_x, button_y);
	ESP_ResizeButtonBox(bb_width, bb_height);
	std::vector<std::string>buttton_ope_caption = { "USBカメラ","動画ファイル","静止画" };
	std::vector<std::string>buttton_OpenClose_caption = { "開く","閉じる" };
	std::vector<std::string>buttton_StartStop_caption = { "開始","停止" };
	std::vector<std::string>buttton_PauseRestart_caption = { "一時停止","再開" };
	std::vector<std::string>buttton_Repeat_caption = { "リピートオフ","リピートオン" };
	ESP_SetButtonBoxTitle(Ope, buttton_ope_caption[opecap_num].c_str());
	ESP_SetButtonBoxTitle(OpenClose, buttton_OpenClose_caption[openclosecap_num].c_str());
	ESP_SetButtonBoxTitle(StartStop, buttton_StartStop_caption[startstopcap_num].c_str());
	ESP_SetButtonBoxTitle(PauseRestart, buttton_PauseRestart_caption[pauserestartcap_num].c_str());
	ESP_SetButtonBoxTitle(Repeat, buttton_Repeat_caption[repeatcap_num].c_str());
	ESP_SetButtonBoxTitle(Setting, "設定");
	ESP_SetButtonBoxTitle(Exit, "終了");

	BOOL flgOpen = FALSE;
	BOOL flgStart = FALSE;
	BOOL flgPause = FALSE;
	BOOL flgRepeat = FALSE;
	int width = 0;
	int height = 0;
	int bit = 0;
	double fps = 0.0;
	int img_win_num = 0;
	int txt_win_num = 0;
	int video_num = 0;
	int cam_logicalnun = 0;
	int imb_x = 0;
	int imb_y = 0;
	int txtw_x = 0;
	int txtw_y = 0;
	int txtw_w = 350;
	int txtw_h = 300;
	int txt_lmargin = 25;
	int zoom_num = 100;
	LPINT img32 = NULL;
	//int use_cam_num = 0;
	//int use_cam_format = 0;

	//スレッド関連
	HANDLE hThread = NULL;
#ifdef _MFC_VER
	CWinThread* pRecvThread = NULL;				//スレッドのオブジェクト
#endif // _MFC_VER
	UINT dwThreadID;						// Thread ID
	HANDLE hStartFlag;					//開始フラグ用共有メモリへのハンドル
	BOOL* lpStartFlag;						//開始フラグ用共有メモリ
	HANDLE hShoriFlag;					//処理フラグ用共有メモリへのハンドル
	BOOL* lpShoriFlag;					//処理フラグ用共有メモリ
	HANDLE hPauseFlag;					//処理フラグ用共有メモリへのハンドル
	BOOL* lpPauseFlag;					//処理フラグ用共有メモリ
	DWORD dwExitCode = 0;
	PARAM param;

	hStartFlag = InitShareMemory(_T("STARTFLAG"), sizeof(BOOL), (LPVOID*)&lpStartFlag);
	hShoriFlag = InitShareMemory(_T("SHORIFLAG"), sizeof(BOOL), (LPVOID*)&lpShoriFlag);
	hPauseFlag = InitShareMemory(_T("PAUSEFLAG"), sizeof(BOOL), (LPVOID*)&lpPauseFlag);
	SHRAEMEMORY<BOOL> RepeatFlag = InitShareMemory<BOOL>(_T("REPEATFLG"));
	if (!hShoriFlag || !hStartFlag || !hPauseFlag || !RepeatFlag.handle)
	{
		tstring sbuff = _T("共有メモリが確保出来ません");
		tstring caption = _T("エラー");
		::MessageBox(NULL, sbuff.c_str(), caption.c_str(), MB_OK);
		return FALSE;
	}
	*lpStartFlag = FALSE;
	*lpShoriFlag = FALSE;
	*lpPauseFlag = FALSE;
	*(RepeatFlag.memory) = FALSE;

	dlg->ChangeShowFlag();

	do
	{
		if (ESP_STOP)break;

		if (ESP_GetButtonBox(Ope) > 0)
		{
			if (!flgOpen)
			{
				if (opecap_num >= buttton_ope_caption.size() - 1)opecap_num = Before;
				if (camera_num == 0 && opecap_num == Before)opecap_num = Camera;
				ESP_SetButtonBoxTitle(Ope, buttton_ope_caption[++opecap_num].c_str());
			}
		}
		if (ESP_GetButtonBox(OpenClose) > 0)
		{
			if (!flgStart)
			{
				if (!flgOpen)						//「開く」ボタンが押されたとき
				{
					tstring FileFullPath;
					tstring FileName;
					tstring strInitialDir = _T("");
					std::string filepath;
					std::string filename;
					const TCHAR* strFilterVideo = _T("Video files (*.avi  *.mp4)\0*.avi;*.mp4\0");
					//tstring strFilterVideo = _T("Video files (*.avi  *.mp4)\0*.av;*.mp4\0");
					//tstringでは正常にフィルタの値が渡せない
					const TCHAR* strFilterPict = _T("Image files (*.bmp  *.jpg *.png)\0*.bmp;*.jpg;*.png\0");
					//tstring strFilterPict = _T("Image files (*.bmp  *.jpg *.png)\0*.bmp;*.jpg;*.png\0");

					switch (opecap_num)
					{
					case Camera:
					{
						int use_cam_num = 0;
						CamFormat = SelectCameraFormat(dtcenter_x, bw_y, cam_formats, use_cam_num/*, use_cam_format*/);
						//CamFormat = param.format;
						//int use_cam_num = param.device_num;
						width = CamFormat.width;
						height = CamFormat.height;
						fps = CamFormat.frame;
#ifdef _UNICODE
						tstring camfomat = string_to_wstring(CamFormat.format);
#else
						tstring camfomat = CamFormat.format;
#endif // _UNICODE
						ImageWindowPositioning(width, height, dtwidth, bw_y, &imb_x, &imb_y, &zoom_num);
						result = ESP_CreateImage(img_win_num, filename.c_str(), imb_x, imb_y, width, height, zoom_num);
						OpenRTextWindow(txt_win_num, txtw_w, txtw_h, imb_x, imb_y, width, zoom_num, 25);
						result = EWC_Open(cam_logicalnun, width, height, fps, use_cam_num, MEDIASUBTYPE_RGB24, getStringAsMediaSubtype(camfomat));
						//result = EWC_Open(cam_logicalnun, width, height, fps, use_cam_num);
						if (result)
						{
							tstring sbuff = _T("カメラ接続に失敗しました\nカメラを確認してください");
							tstring caption = _T("エラー");
							::MessageBox(NULL, sbuff.c_str(), caption.c_str(), MB_OK);
							continue;
						}
						else
						{
							ESP_Printf("カメラ名：%s\n", EWC_GetDeviceName(cam_logicalnun));
							ESP_Printf("画像幅： %d 画像高さ：%d\n", width, height);
							ESP_Printf("フレームレイト：%f\n", fps);
							ESP_Printf("映像フォーマット：%s\n", EWC_GetDeviceSubtype(cam_logicalnun));
							ESP_Printf("画像フォーマット：%s\n", EWC_GetSubtype(cam_logicalnun));
						}
						*lpStartFlag = TRUE;
						param.device_num = cam_logicalnun;
						param.format = CamFormat;
#ifndef _MFC_VER
						hThread = (HANDLE)::_beginthreadex(NULL, 0, PlayCamera, (LPVOID)&param, 0, &dwThreadID);
#else
						pRecvThread = ::AfxBeginThread(PlayCamera, (LPVOID)&param, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
						hThread = pRecvThread->m_hThread;
						dwThreadID = pRecvThread->m_nThreadID;
						pRecvThread->m_bAutoDelete = FALSE;	// 自動破棄フラグクリア
						pRecvThread->ResumeThread();			// サスペンド解除
#endif // !_MFC_VER

						break;
					}
					case Video:
						strInitialDir = _T("D:\\Users\\kinya\\Videos");
						if (!glGetOpenFileName(&FileFullPath, &FileName, strInitialDir, strFilterVideo))continue;
						filepath = wstring_to_string(FileFullPath);
						filename = wstring_to_string(FileName);
						result = EVF_Open(video_num, filepath.c_str(), MEDIASUBTYPE_RGB24);
						if (result)
						{
							tstring sbuff = FileName + _T("が開けません");
							tstring caption = _T("エラー");
							::MessageBox(NULL, sbuff.c_str(), caption.c_str(), MB_OK);
							continue;
						}
						width = EVF_WX(video_num);
						height = EVF_WY(video_num);
						CamFormat.name = filepath;
						CamFormat.width = width;
						CamFormat.height = height;
						CamFormat.frame = EVF_FrameRate(video_num);
						CamFormat.format = "";
						if (img32) delete[] img32;
						img32 = new int[width * height];
						ImageWindowPositioning(width, height, dtwidth, bw_y, &imb_x, &imb_y, &zoom_num);
						result = ESP_CreateImage(img_win_num, filename.c_str(), imb_x, imb_y, width, height, zoom_num);
						result = EVF_GetFrame24to32(video_num, img32);
						ESP_PutWindow(img32, 0, 0, width, height);
						ESP_Update();
						OpenRTextWindow(txt_win_num, txtw_w, txtw_h, imb_x, imb_y, width, zoom_num, 25);
						ESP_Printf("カメラ名：%s\n", CamFormat.name.c_str());
						ESP_Printf("画像幅： %d 画像高さ：%d\n", width, height);
						ESP_Printf("フレームレイト：%f\n", CamFormat.frame);
						*lpStartFlag = TRUE;
						param.device_num = video_num;
						param.format = CamFormat;
#ifndef _MFC_VER
						hThread = (HANDLE)::_beginthreadex(NULL, 0, PlayVideo, (LPVOID)&param, 0, &dwThreadID);
#else
						pRecvThread = ::AfxBeginThread(PlayVideo, (LPVOID)&param, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
						hThread = pRecvThread->m_hThread;
						dwThreadID = pRecvThread->m_nThreadID;
						pRecvThread->m_bAutoDelete = FALSE;	// 自動破棄フラグクリア
						pRecvThread->ResumeThread();			// サスペンド解除
#endif // !_MFC_VER
						
						break;
					case image:
						strInitialDir = _T("D:\\Users\\kinya\\Pictures");
						if (!glGetOpenFileName(&FileFullPath, &FileName, strInitialDir, strFilterPict))continue;
						filepath = wstring_to_string(FileFullPath);
						ESP_GetImageInfo(filepath.c_str(), &width, &height, &bit);
						ImageWindowPositioning(width, height, dtwidth, bw_y, &imb_x, &imb_y, &zoom_num);
						ESP_ImageOpen(filepath.c_str(), imb_x, imb_y, zoom_num, &img_win_num, &width, &height);
						OpenRTextWindow(txt_win_num, txtw_w, txtw_h, imb_x, imb_y, width, zoom_num, 25);
						break;
					default:
						break;
					}
					flgOpen = TRUE;
				}
				else								//「閉じる」ボタンが押されたとき
				{
					switch (opecap_num)
					{
					case Camera:
						*lpStartFlag = FALSE;
						// スレッドの終了待ち
						::WaitForSingleObject(hThread, INFINITE);
						//if (::WaitForSingleObject(hThread, 2000) == WAIT_TIMEOUT)
						//{
						//	// スレッド強制停止
						//	// (絶対に停止するなら WaitForSingleObjectで INFINITE も可）
						//	::TerminateThread(hThread, 0xffffffff);
						//	::AfxMessageBox(_T("スレッド強制停止"));
						//}
						// スレッドの終了コードを取得
						::GetExitCodeThread(hThread, &dwExitCode);
						//{
						//	std::wstring tbuf = std::wstring(L"スレッド終了コード = ") + std::to_wstring(dwExitCode)+ std::wstring(L"\n");
						//	OutputDebugString(tbuf.c_str());
						//}
#ifndef _MFC_VER
						// スレッドハンドルの解放
						::CloseHandle(hThread);
						hThread=NULL
#else
						//スレッドオブジェクトの解放
						if(pRecvThread) delete pRecvThread;
						pRecvThread = NULL;
#endif // !_MFC_VER
						EWC_Close(cam_logicalnun);
						break;
					case Video:
						*lpStartFlag = FALSE;
						// スレッドの終了待ち
						::WaitForSingleObject(hThread, INFINITE);
						// スレッドの終了コードを取得
						::GetExitCodeThread(hThread, &dwExitCode);
#ifndef _MFC_VER
						// スレッドハンドルの解放
						::CloseHandle(hThread);
						hThread = NULL
#else
						//スレッドオブジェクトの解放
						if (pRecvThread) delete pRecvThread;
						pRecvThread = NULL;
#endif // !_MFC_VER
						result = EVF_Close(video_num);
						if (img32)
						{
							delete[] img32;
							img32 = NULL;
						}
						//リピートオンの状態をリピートオフに戻す
						if (flgRepeat)
						{
							flgRepeat = FALSE;
							*(RepeatFlag.memory) = FALSE;
							repeatcap_num = 0;
							ESP_SetButtonBoxTitle(Repeat, buttton_Repeat_caption[repeatcap_num].c_str());
						}
						break;
					case image:
						break;
					default:
						break;
					}
					ESP_CloseTextWindow(txt_win_num);
					ESP_DestroyImage(img_win_num);
					flgOpen = FALSE;
				}
				if (openclosecap_num >= buttton_OpenClose_caption.size() - 1)openclosecap_num = -1;
				ESP_SetButtonBoxTitle(OpenClose, buttton_OpenClose_caption[++openclosecap_num].c_str());
			}
		}
		if (ESP_GetButtonBox(StartStop) > 0)
		{
			if (flgOpen)
			{
				if (!flgStart)						//「開始」ボタンが押されたとき
				{
					int* img32 = new int[width * width];
					//LPBYTE img24 = NULL;
					//LPBITMAPINFO bmpinf = NULL;
					//glSetBmpInfo(&bmpinf, width, height);
					//glInitImageData(&img24, width, height);
					//LPINT Rimage1 = new int[width * height];;
					//LPINT Bimage1 = new int[width * height];;
					//LPINT Gimage1 = new int[width * height];;
					//LPINT Rimage2 = new int[width * height];;
					//LPINT Bimage2 = new int[width * height];;
					//LPINT Gimage2 = new int[width * height];;
					switch (opecap_num)
					{
					case Camera:
						flgStart = TRUE;
						*lpShoriFlag = TRUE;
						break;
					case Video:
						flgStart = TRUE;
						*lpShoriFlag = TRUE;
						break;
					case image:
						ESP_GetWindow(img32, 0, 0, width, height);
						//ここに画像処理のコードを書く
						//glBmp32ToBmp24((LPBYTE)img32, img24, width, height);
						//glBitmapFlipVertical(img24, img24, width, height, Rimage1, Gimage1, Bimage1, Rimage2, Gimage2, Bimage2);
						//FaceDRAVFanc(img24, img24, bmpinf);
						//glBitmapFlipVertical(img24, img24, width, height, Rimage1, Gimage1, Bimage1, Rimage2, Gimage2, Bimage2);
						//glBmp24ToBmp32(img24, (LPBYTE)img32, width, height);
						//ここまで
						ESP_PutWindow(img32, 0, 0, width, height);
						ESP_Update();
						flgStart = FALSE;
						break;
					default:
						break;
					}
					if (img32)
					{
						delete[] img32;
						img32 = NULL;
					}
					//glDeleteImageData(&img24);
					//delete bmpinf;
					//delete[] Rimage1;
					//delete[] Gimage1;
					//delete[] Bimage1;
					//delete[] Rimage2;
					//delete[] Gimage2;
					//delete[] Bimage2;
				}
				else									//「停止」ボタンが押されたとき
				{
					switch (opecap_num)
					{
					case Camera:
						*lpShoriFlag = FALSE;
						break;
					case Video:
						*lpShoriFlag = FALSE;
						break;
					case image:
						break;
					default:
						break;
					}
					flgStart = FALSE;
				}
				if (opecap_num != image)
				{
					if (startstopcap_num >= buttton_StartStop_caption.size() - 1)startstopcap_num = -1;
					ESP_SetButtonBoxTitle(StartStop, buttton_StartStop_caption[++startstopcap_num].c_str());
				}
			}
		}

		if (ESP_GetButtonBox(PauseRestart) > 0)
		{
			if (flgOpen)
			{
				if (!flgPause)	//「一時停止」ボタンが押されたとき
				{
					switch (opecap_num)
					{
					case Camera:
						break;
					case Video:
						*lpPauseFlag = TRUE;
						flgPause = TRUE;
						break;
					case image:
						break;
					default:
						break;
					}
				}
				else	//「再開」ボタンが押されたとき
				{
					switch (opecap_num)
					{
					case Camera:
						break;
					case Video:
						*lpPauseFlag = FALSE;
						flgPause = FALSE;
						break;
					case image:
						break;
					default:
						break;
					}
				}
				if (opecap_num == Video)
				{
					if (pauserestartcap_num >= buttton_PauseRestart_caption.size() - 1)pauserestartcap_num = -1;
					ESP_SetButtonBoxTitle(PauseRestart, buttton_PauseRestart_caption[++pauserestartcap_num].c_str());
				}
			}
		}

		if (ESP_GetButtonBox(Repeat) > 0)
		{
			if (flgOpen)
			{
				if (!flgRepeat)		//「リピートオフ」ボタンが押された
				{
					if (opecap_num == Video)
					{
						flgRepeat = TRUE;
						*(RepeatFlag.memory) = TRUE;
					}
				}
				else					//「リピートオン」ボタンが押された
				{
					if (opecap_num == Video)
					{
						flgRepeat = FALSE;
						*(RepeatFlag.memory) = FALSE;
					}
				}
				if (opecap_num == Video)
				{
					if (repeatcap_num >= buttton_Repeat_caption.size() - 1)repeatcap_num = -1;
					ESP_SetButtonBoxTitle(Repeat, buttton_Repeat_caption[++repeatcap_num].c_str());
				}
			}
		}
		if (ESP_GetButtonBox(Setting) > 0)
		{
			//INT_PTR nResponse = dlg.DoModal();
			INT_PTR nResponse = IDOK;
			dlg->ShowWindow(SW_SHOW);

			if (nResponse == IDOK)
			{
				// TODO: ダイアログが <OK> で消された時のコードを
				//  記述してください。
			}
			else if (nResponse == IDCANCEL)
			{
				// TODO: ダイアログが <キャンセル> で消された時のコードを
				//  記述してください。
			}
			else if (nResponse == -1)
			{
				TRACE(traceAppMsg, 0, "警告: ダイアログの作成に失敗しました。アプリケーションは予期せずに終了します。\n");
				TRACE(traceAppMsg, 0, "警告: ダイアログで MFC コントロールを使用している場合、#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS を指定できません。\n");
			}
		}

		if (ESP_GetButtonBox(Exit) > 0)		//「終了」ボタンが押された
		{
			if (flgOpen)
			{
				switch (opecap_num)
				{
				case Camera:
					*lpStartFlag = FALSE;
					// スレッドの終了待ち
					::WaitForSingleObject(hThread, INFINITE);
					// スレッドの終了コードを取得
					::GetExitCodeThread(hThread, &dwExitCode);
#ifndef _MFC_VER
					// スレッドハンドルの解放
					::CloseHandle(hThread);
					hThread = NULL
#else
					//スレッドオブジェクトの解放
					if (pRecvThread) delete pRecvThread;
					pRecvThread = NULL;
#endif // !_MFC_VER
					EWC_Close(cam_logicalnun);
					break;
				case Video:
					*lpStartFlag = FALSE;
					// スレッドの終了待ち
					::WaitForSingleObject(hThread, INFINITE);
					// スレッドの終了コードを取得
					::GetExitCodeThread(hThread, &dwExitCode);
#ifndef _MFC_VER
					// スレッドハンドルの解放
					::CloseHandle(hThread);
					hThread = NULL
#else
					//スレッドオブジェクトの解放
					if (pRecvThread) delete pRecvThread;
					pRecvThread = NULL;
#endif // !_MFC_VER
					if (img32)
					{
						delete[] img32;
						img32 = NULL;
					}
					//リピートオンの状態をリピートオフに戻す
					if (flgRepeat)
					{
						flgRepeat = FALSE;
						*(RepeatFlag.memory) = FALSE;
						repeatcap_num = 0;
						ESP_SetButtonBoxTitle(Repeat, buttton_Repeat_caption[repeatcap_num].c_str());
					}
					break;
				case image:
					break;
				default:
					break;
				}
				ESP_DestroyImage(img_win_num);
				ESP_CloseTextWindow(txt_win_num);
				flgOpen = FALSE;
			}
			// 共有メモリの後始末
			if (lpStartFlag)
			{
				::UnmapViewOfFile(lpStartFlag);			// 共有メモリのclose
				::CloseHandle(hStartFlag);					// 共有メモリの削除
			}
			if (lpShoriFlag)
			{
				::UnmapViewOfFile(lpShoriFlag);		// 共有メモリのclose
				::CloseHandle(hShoriFlag);				// 共有メモリの削除
			}
			CloseShareMemory(hPauseFlag, (LPVOID*)&lpPauseFlag);
			CloseShareMemory<BOOL>(RepeatFlag);
			ESP_CloseButtonBox();

			//ESP_Exit();
			break;
		}
	} while (true);

	ESP_Exit();

	// 上で作成されたシェル マネージャーを削除します。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

	delete dlg;		//ダイアログボックスの削除

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// ダイアログは閉じられました。アプリケーションのメッセージ ポンプを開始しないで
	//  アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}

