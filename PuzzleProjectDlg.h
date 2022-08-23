//------------------------------------------------------------------------
/**
   @file PuzzleProjectDlg.h
   @brief
      - 메인 다이얼로그 헤더파일
   
   @details
      -# 퍼즐 게임을 전체적으로 제어하는 헤더파일
    
   @par History
      - 2020/1/16: Created(sckim)
*/


// PuzzleProjectDlg.h : 헤더 파일
//
#pragma once
#include<afxwin.h>
#include"ImageControl.h"
#include"ButtonControl.h"
#include "afxdialogex.h"
#include"SetDifficultyDlg.h"
#include"TimeControl.h"
#include"Algorithm.h"
#include<iostream>

#define IMAGEROW 300
#define IMAGECOL 300

//------------------------------------------------------------------------
/**
   @class CPuzzleProjectDlg
   @brief
      - 퍼즐 게임 제어 클래스
   
   @details
	  -# 전체적으로 퍼즐 게임을 제어하는 기능
    
   @par History
      - 2020/1/16: Created(sckim)
*/

// CPuzzleProjectDlg 대화 상자
class CPuzzleProjectDlg : public CDialogEx
{
	DECLARE_EASYSIZE

private:
	int m_nSize;
	BOOL m_bIsLoaded;
	CRect m_rcDlg;
private:
	CImage* m_pSplitImg;
	int *m_pnID;
	Index* m_pIndex;
	int m_nGrayIndex;
	
private:
	CImageControl  m_ImgControl;
	CButtonControl m_BtControl;
	CTimeControl m_TmControl;
	CAlgorithm m_Algorithm;

// 생성입니다.
public:
	CPuzzleProjectDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	~CPuzzleProjectDlg();
	double GetDialogScale_x();
	double GetDialogScale_y();
// 대화 상자 데이터입니다.
	enum { IDD = IDD_PUZZLEPROJECT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnButtonEvent(UINT ID);
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnMenuExit();
	afx_msg void OnGameChangethelevel();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
