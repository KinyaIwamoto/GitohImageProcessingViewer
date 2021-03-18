
// GitohImageProcessingViewer.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CGitohImageProcessingViewerApp:
// このクラスの実装については、GitohImageProcessingViewer.cpp を参照してください
//

class CGitohImageProcessingViewerApp : public CWinApp
{
public:
	CGitohImageProcessingViewerApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()

	//設定の後損策をレジストリーにする
	BOOL m_blSaveSettingsREG;

};

extern CGitohImageProcessingViewerApp theApp;
