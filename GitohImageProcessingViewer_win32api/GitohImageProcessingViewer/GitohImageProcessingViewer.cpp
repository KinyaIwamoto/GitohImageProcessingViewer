#define ESP_HIDE_MAINWINDOW
#include "esplib.h"
#include "evflib.h"
#include "ewclib.h"
#include <vector>
#include <string>
#include "Functions.h"

void ESP_Ready(void)
{
	ESP_START = 1;
}

void ESP_Main(void)
{
	//�A�v���P�[�V�����̏�����
	const int button_width = 120;
	const int button_height = 40;
	const int button_x = 6;
	const int button_y = 1;
	const int bb_width = button_width * button_x;
	const int bb_height = button_height * button_y;
	RECT dtrect;
	HWND hDeskWnd = ::GetDesktopWindow();	 //���̊֐��Ńf�X�N�g�b�v�̃n���h�����擾
	::GetWindowRect(hDeskWnd, &dtrect);			//�f�X�N�g�b�v�̃n���h�����炻��(��ʂ�)�傫�����擾
	const int dtwidth = dtrect.right - dtrect.left;
	const int dtheight = dtrect.bottom - dtrect.top;
	const int dtcenter_x = dtwidth / 2;
	const int dtcenter_y = dtheight / 2;

	//�{�^���E�C���h�E�̐����Ɛݒ�
	const int bw_x = dtcenter_x - bb_width / 2;
	const int bw_y = dtheight - (bb_height + 100);

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
	std::vector<std::string>buttton_ope_caption = { "USB�J����","����t�@�C��","�Î~��" };
	std::vector<std::string>buttton_OpenClose_caption = { "�J��","����" };
	std::vector<std::string>buttton_StartStop_caption = { "�J�n","��~" };
	std::vector<std::string>buttton_PauseRestart_caption = { "�ꎞ��~","�ĊJ" };
	std::vector<std::string>buttton_Repeat_caption = { "���s�[�g�I�t","���s�[�g�I��" };
	ESP_SetButtonBoxTitle(Ope, buttton_ope_caption[opecap_num].c_str());
	ESP_SetButtonBoxTitle(OpenClose, buttton_OpenClose_caption[openclosecap_num].c_str());
	ESP_SetButtonBoxTitle(StartStop, buttton_StartStop_caption[startstopcap_num].c_str());
	ESP_SetButtonBoxTitle(PauseRestart, buttton_PauseRestart_caption[pauserestartcap_num].c_str());
	ESP_SetButtonBoxTitle(Repeat, buttton_Repeat_caption[repeatcap_num].c_str());
	ESP_SetButtonBoxTitle(Exit, "�I��");

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

	//�X���b�h�֘A
	HANDLE hThread = NULL;
	UINT dwThreadID;						// Thread ID
	HANDLE hStartFlag;					//�J�n�t���O�p���L�������ւ̃n���h��
	BOOL* lpStartFlag;						//�J�n�t���O�p���L������
	HANDLE hShoriFlag;					//�����t���O�p���L�������ւ̃n���h��
	BOOL* lpShoriFlag;					//�����t���O�p���L������
	HANDLE hPauseFlag;					//�����t���O�p���L�������ւ̃n���h��
	BOOL* lpPauseFlag;					//�����t���O�p���L������
	DWORD dwExitCode = 0;
	PARAM param;

	hStartFlag = InitShareMemory(_T("STARTFLAG"), sizeof(BOOL), (LPVOID*)&lpStartFlag);
	hShoriFlag = InitShareMemory(_T("SHORIFLAG"), sizeof(BOOL), (LPVOID*)&lpShoriFlag);
	hPauseFlag = InitShareMemory(_T("PAUSEFLAG"), sizeof(BOOL), (LPVOID*)&lpPauseFlag);
	SHRAEMEMORY<BOOL> RepeatFlag = InitShareMemory<BOOL>(_T("REPEATFLG"));
	if (!hShoriFlag || !hStartFlag || !hPauseFlag || !RepeatFlag.handle)
	{
		tstring sbuff = _T("���L���������m�ۏo���܂���");
		tstring caption = _T("�G���[");
		::MessageBox(NULL, sbuff.c_str(), caption.c_str(), MB_OK);
		return;
	}
	*lpStartFlag = FALSE;
	*lpShoriFlag = FALSE;
	*lpPauseFlag = FALSE;
	*(RepeatFlag.memory) = FALSE;

	for (;;)
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
				if (!flgOpen)						//�u�J���v�{�^���������ꂽ�Ƃ�
				{
					tstring FileFullPath;
					tstring FileName;
					tstring strInitialDir = _T("");
					std::string filepath;
					std::string filename;
					const TCHAR* strFilterVideo = _T("Video files (*.avi  *.mp4)\0*.avi;*.mp4\0");
					//tstring strFilterVideo = _T("Video files (*.avi  *.mp4)\0*.av;*.mp4\0");
					//tstring�ł͐���Ƀt�B���^�̒l���n���Ȃ�
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
							result = EWC_Open(cam_logicalnun, width, height, fps, use_cam_num, MEDIASUBTYPE_RGB32, getStringAsMediaSubtype(camfomat));
							if (result)
							{
								tstring sbuff = _T("�J�����ڑ��Ɏ��s���܂���\n�J�������m�F���Ă�������");
								tstring caption = _T("�G���[");
								::MessageBox(NULL, sbuff.c_str(), caption.c_str(), MB_OK);
								continue;
							}
							else
							{
								ESP_Printf("�J�������F%s\n", EWC_GetDeviceName(cam_logicalnun));
								ESP_Printf("�摜���F %d �摜�����F%d\n", width, height);
								ESP_Printf("�t���[�����C�g�F%f\n", fps);
								ESP_Printf("�f���t�H�[�}�b�g�F%s\n", EWC_GetDeviceSubtype(cam_logicalnun));
								ESP_Printf("�摜�t�H�[�}�b�g�F%s\n", EWC_GetSubtype(cam_logicalnun));
							}
							*lpStartFlag = TRUE;
							param.device_num = cam_logicalnun;
							param.format = CamFormat;
							hThread = (HANDLE)::_beginthreadex(NULL, 0, PlayCamera, (LPVOID)&param, 0, &dwThreadID);
							break;
						}
					case Video:
						strInitialDir = _T("D:\\Users\\kinya\\Videos");
						if (!GetOpenFileName(&FileFullPath, &FileName, strInitialDir, strFilterVideo))continue;
						filepath = wstring_to_string(FileFullPath);
						filename = wstring_to_string(FileName);
						result = EVF_Open(video_num, filepath.c_str(), MEDIASUBTYPE_RGB24);
						if (result)
						{
							tstring sbuff = FileName + _T("���J���܂���");
							tstring caption = _T("�G���[");
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
						*lpStartFlag = TRUE;
						param.device_num = video_num;
						param.format = CamFormat;
						hThread = (HANDLE)::_beginthreadex(NULL, 0, PlayVideo, (LPVOID)&param, 0, &dwThreadID);
						break;
					case image:
						strInitialDir = _T("D:\\Users\\kinya\\Pictures");
						if (!GetOpenFileName(&FileFullPath, &FileName, strInitialDir, strFilterPict))continue;
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
				else								//�u����v�{�^���������ꂽ�Ƃ�
				{
					switch (opecap_num)
					{
					case Camera:
						*lpStartFlag = FALSE;
						// �X���b�h�̏I���҂�
						::WaitForSingleObject(hThread, INFINITE);
						// �X���b�h�̏I���R�[�h���擾
						::GetExitCodeThread(hThread, &dwExitCode);
						// �X���b�h�n���h���̉��
						::CloseHandle(hThread);
						EWC_Close(cam_logicalnun);
						break;
					case Video:
						*lpStartFlag = FALSE;
						::WaitForSingleObject(hThread, INFINITE);
						// �X���b�h�̏I���R�[�h���擾
						::GetExitCodeThread(hThread, &dwExitCode);
						// �X���b�h�n���h���̉��
						::CloseHandle(hThread);
						result = EVF_Close(video_num);
						if (img32)
						{
							delete[] img32;
							img32 = NULL;
						}
						//���s�[�g�I���̏�Ԃ����s�[�g�I�t�ɖ߂�
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
				if (openclosecap_num >= buttton_OpenClose_caption.size() - 1)openclosecap_num = -1;
				ESP_SetButtonBoxTitle(OpenClose, buttton_OpenClose_caption[++openclosecap_num].c_str());
			}
		}
		if (ESP_GetButtonBox(StartStop) > 0)
		{
			if (flgOpen)
			{
				if (!flgStart)						//�u�J�n�v�{�^���������ꂽ�Ƃ�
				{
					int* img32 = new int[width * width];
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
						//�����ɉ摜�����̃R�[�h������
						//�����܂�
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
				}
				else									//�u��~�v�{�^���������ꂽ�Ƃ�
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
				if (!flgPause)	//�u�ꎞ��~�v�{�^���������ꂽ�Ƃ�
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
				else	//�u�ĊJ�v�{�^���������ꂽ�Ƃ�
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
				if (!flgRepeat)		//�u���s�[�g�I�t�v�{�^���������ꂽ
				{
					if (opecap_num == Video)
					{
						flgRepeat = TRUE;
						*(RepeatFlag.memory) = TRUE;
					}
				}
				else					//�u���s�[�g�I���v�{�^���������ꂽ
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

		if (ESP_GetButtonBox(Exit) > 0)
		{
			// ���L�������̌�n��
			if (lpStartFlag) 
			{
				::UnmapViewOfFile(lpStartFlag);			// ���L��������close
				::CloseHandle(hStartFlag);					// ���L�������̍폜
			}
			if (lpShoriFlag)
			{
				::UnmapViewOfFile(lpShoriFlag);		// ���L��������close
				::CloseHandle(hShoriFlag);				// ���L�������̍폜
			}
			CloseShareMemory(hPauseFlag, (LPVOID*)&lpPauseFlag);
			CloseShareMemory<BOOL>(RepeatFlag);

			ESP_Exit();
		}
	}
}

void ESP_Finish(void)
{
}
