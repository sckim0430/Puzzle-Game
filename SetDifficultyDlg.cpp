// SetDifficultyDlg.cpp : ���� �����Դϴ�.
//

//------------------------------------------------------------------------
/**
   @file SetDifficultyDlg.cpp
   @brief
      - ���� ���̵� ���� ��� ����
   
   @details
      -# Edit Box�� ���� ������ ����� �Է¹ް�, ����� ������ �δ� ��� ����
    
   @par History
      - 2020/1/19: Created(sckim)
*/

#include "stdafx.h"
#include "PuzzleProject.h"
#include "SetDifficultyDlg.h"
#include "afxdialogex.h"


// CSetDifficultyDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSetDifficultyDlg, CDialogEx)

CSetDifficultyDlg::CSetDifficultyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetDifficultyDlg::IDD, pParent)
	, m_Edit(_T("5"))
{
	m_StateEdit = FALSE;
}

CSetDifficultyDlg::~CSetDifficultyDlg()
{
}

void CSetDifficultyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Edit);
}


BEGIN_MESSAGE_MAP(CSetDifficultyDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetDifficultyDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSetDifficultyDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSetDifficultyDlg �޽��� ó�����Դϴ�.


/**
   @fn OnBnClickedOk
   @brief
      - ���� ����� �Է¹޴� ���

   @details
      -# ���̾�α��� Edit Box�� ���� ������ ����� �Է¹޴´�.

   @param


   @return
    

   @par History
      - 2020/1/19: Created(sckim)
*/

void CSetDifficultyDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	UpdateData(TRUE);
	
	int uSize = _ttoi(m_Edit);
	
	if(uSize < MIN_BUTTON_NUM || uSize > MAX_BUTTON_NUM)
	{
		CString str;
		str.Format(_T("������ ���� ������ %d�̻� %d���� �Դϴ�! �ٽ� �Է��ϼ���."),MIN_BUTTON_NUM,MAX_BUTTON_NUM);
		AfxMessageBox(str);
		
		return;
	}

	CDialogEx::OnOK();
}


void CSetDifficultyDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}