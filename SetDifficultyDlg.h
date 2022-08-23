//------------------------------------------------------------------------
/**
   @file SetDifficultyDlg.h
   @brief
      - 퍼즐 난이도 관련 파일
   
   @details
      -# 퍼즐 조각 사이즈를 입력하여 난이도를 설정하는 파일 
    
   @par History
      - 2020/1/19: Created(sckim)
*/

#pragma once
#define MAX_BUTTON_NUM 100
#define MIN_BUTTON_NUM 2

// CSetDifficultyDlg 대화 상자입니다.

//------------------------------------------------------------------------
/**
   @class CSetDifficultyDlg
   @brief
      - 퍼즐 난이도를 설정 다이얼로그 클래스
   
   @details
	  -# 퍼즐 조각의 사이즈를 설정하는 다이얼로그 정의
    
   @par History
      - 2020/1/19: Created(sckim)
*/

class CSetDifficultyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetDifficultyDlg)

	BOOL m_StateEdit;

public:
	CSetDifficultyDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSetDifficultyDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_Edit;
};
