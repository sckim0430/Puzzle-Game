//------------------------------------------------------------------------
/**
   @file SetDifficultyDlg.h
   @brief
      - ���� ���̵� ���� ����
   
   @details
      -# ���� ���� ����� �Է��Ͽ� ���̵��� �����ϴ� ���� 
    
   @par History
      - 2020/1/19: Created(sckim)
*/

#pragma once
#define MAX_BUTTON_NUM 100
#define MIN_BUTTON_NUM 2

// CSetDifficultyDlg ��ȭ �����Դϴ�.

//------------------------------------------------------------------------
/**
   @class CSetDifficultyDlg
   @brief
      - ���� ���̵��� ���� ���̾�α� Ŭ����
   
   @details
	  -# ���� ������ ����� �����ϴ� ���̾�α� ����
    
   @par History
      - 2020/1/19: Created(sckim)
*/

class CSetDifficultyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetDifficultyDlg)

	BOOL m_StateEdit;

public:
	CSetDifficultyDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSetDifficultyDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_Edit;
};
