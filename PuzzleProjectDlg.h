//------------------------------------------------------------------------
/**
   @file PuzzleProjectDlg.h
   @brief
      - ���� ���̾�α� �������
   
   @details
      -# ���� ������ ��ü������ �����ϴ� �������
    
   @par History
      - 2020/1/16: Created(sckim)
*/


// PuzzleProjectDlg.h : ��� ����
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
      - ���� ���� ���� Ŭ����
   
   @details
	  -# ��ü������ ���� ������ �����ϴ� ���
    
   @par History
      - 2020/1/16: Created(sckim)
*/

// CPuzzleProjectDlg ��ȭ ����
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

// �����Դϴ�.
public:
	CPuzzleProjectDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	~CPuzzleProjectDlg();
	double GetDialogScale_x();
	double GetDialogScale_y();
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PUZZLEPROJECT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
