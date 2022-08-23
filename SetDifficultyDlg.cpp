// SetDifficultyDlg.cpp : 구현 파일입니다.
//

//------------------------------------------------------------------------
/**
   @file SetDifficultyDlg.cpp
   @brief
      - 퍼즐 난이도 설정 기능 구현
   
   @details
      -# Edit Box를 통해 퍼즐의 사이즈를 입력받고, 사이즈에 제한을 두는 기능 구현
    
   @par History
      - 2020/1/19: Created(sckim)
*/

#include "stdafx.h"
#include "PuzzleProject.h"
#include "SetDifficultyDlg.h"
#include "afxdialogex.h"


// CSetDifficultyDlg 대화 상자입니다.

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


// CSetDifficultyDlg 메시지 처리기입니다.


/**
   @fn OnBnClickedOk
   @brief
      - 퍼즐 사이즈를 입력받는 기능

   @details
      -# 다이얼로그의 Edit Box로 부터 퍼즐의 사이즈를 입력받는다.

   @param


   @return
    

   @par History
      - 2020/1/19: Created(sckim)
*/

void CSetDifficultyDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	UpdateData(TRUE);
	
	int uSize = _ttoi(m_Edit);
	
	if(uSize < MIN_BUTTON_NUM || uSize > MAX_BUTTON_NUM)
	{
		CString str;
		str.Format(_T("사이즈 제한 범위는 %d이상 %d이하 입니다! 다시 입력하세요."),MIN_BUTTON_NUM,MAX_BUTTON_NUM);
		AfxMessageBox(str);
		
		return;
	}

	CDialogEx::OnOK();
}


void CSetDifficultyDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}