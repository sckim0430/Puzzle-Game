// DifficlutyDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "PuzzleProject.h"
#include "DifficultyDlg.h"
#include "afxdialogex.h"


// CDifficlutyDlg ��ȭ �����Դϴ�.

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


// CDifficlutyDlg �޽��� ó�����Դϴ�.


void CDifficultyDlg::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CDialog::OnOK();
}


void CDifficultyDlg::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
		CDialog::OnCancel();
}
