// DifficlutyDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "PuzzleProject.h"
#include "DifficultyDlg.h"
#include "afxdialogex.h"


// CDifficlutyDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDifficultyDlg, CDialogEx)

CDifficultyDlg::CDifficultyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDifficultyDlg::IDD, pParent)
	, m_Edit(0)
{

}

CDifficultyDlg::~CDifficultyDlg()
{
}

void CDifficultyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDifficultyDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CDifficultyDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDifficultyDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CDifficlutyDlg 메시지 처리기입니다.


void CDifficultyDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CDialog::OnOK();
}


void CDifficultyDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		CDialog::OnCancel();
}
