
// GitohImageProcessingViewerDlg.h : ヘッダー ファイル
//

#pragma once


// CGitohImageProcessingViewerDlg ダイアログ
class CGitohImageProcessingViewerDlg : public CDialogEx
{
// コンストラクション
public:
	CGitohImageProcessingViewerDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GITOHIMAGEPROCESSINGVIEWER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);//追加
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_visible;

public:
	void ChangeShowFlag() { m_visible = TRUE; };
};
