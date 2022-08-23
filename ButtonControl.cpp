//------------------------------------------------------------------------
/**
   @file ButtonControl.cpp
   @brief
      - ��ư ���� ��� ����
   
   @details
      -# �������� ��ư�� �����ϰ� ��ư ������ �����ϴ� ��� ����
    
   @par History
      - 2020/1/17: Created(sckim)
*/
#pragma once
#include"ButtonControl.h"

CButtonControl::CButtonControl()
{
}

CButtonControl::~CButtonControl()
{
}

/**
   @fn CreateButton
   @brief
      - �������� ��ư�� �����ϴ� ���

   @details
      -# �ܺη� �Է¹��� ��ư�� ũ��� ������ �ش� ���̾�α׿� 
		 �����ϴ� ���

    @param
      -# CDialog* dlg : ��ư�� ������ ���̾�α��� �ּ� 
	  -# int Height : ��ư�� ���̸� �ǹ�
	  -# int Width : ��ư�� �ʺ� �ǹ�
	  -# int nSize : ������ ��ư�� ������ �ǹ�

   @return
       - int* : ������ ��ư���� ID�� ��ȯ

   @par History
      - 2020/1/17: Created(sckim)
*/

int* CButtonControl::CreateButton(CDialog* dlg, int Height,int Width, int nSize)
{
	BOOL bIsCreated = FALSE;
	
	int* pnID;
	CButton* pBt;

	pnID = new int[nSize*nSize];
	pBt = new CButton[nSize*nSize];

	CRect rc;
	POINT ptTopLeft;

	dlg->GetWindowRect(rc);
	dlg->ScreenToClient(&rc);

	int nButtonHeight=Height/nSize;
	int nButtonWidth=Width/nSize;

	int nStart_x = (rc.bottom-rc.top-Height)/2 + rc.top;
	int nStart_y = (rc.right-rc.left-Width)/2 + rc.left;
	
	
	for(int x=0;x<nSize;x++)
	{
		for(int y=0;y<nSize;y++)
		{
			if (dlg != nullptr)
			{
				
			//	pBt[x*nSize + y].Create(_T(""), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_BITMAP,CRect(y*(nButtonWidth),
			//		(x*(nButtonHeight)),((nButtonWidth)+y*(nButtonWidth)),(nButtonHeight)+(nButtonHeight)*x),dlg,BTN_ID+x*nSize + y);
				

				pBt[x*nSize + y].Create(_T(""), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_BITMAP,CRect(nStart_y + y*(nButtonWidth),
					(nStart_x+ x*(nButtonHeight)),(nStart_y+ (nButtonWidth)+y*(nButtonWidth)),nStart_x+(nButtonHeight)+(nButtonHeight)*x),dlg,BTN_ID+x*nSize + y);
				
			}
			
			SetWindowTheme(GetDlgItem(dlg->m_hWnd,pBt[x*nSize + y].GetDlgCtrlID()), _T(""), _T(""));

			pnID[x*nSize+y] = pBt[x*nSize + y].GetDlgCtrlID();
		}
	}

	return pnID;
}