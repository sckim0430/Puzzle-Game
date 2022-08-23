//------------------------------------------------------------------------
/**
   @file ButtonControl.cpp
   @brief
      - 버튼 관리 기능 구현
   
   @details
      -# 동적으로 버튼을 생성하고 버튼 설정을 조작하는 기능 구현
    
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
      - 동적으로 버튼을 생성하는 기능

   @details
      -# 외부로 입력받은 버튼의 크기와 갯수를 해당 다이얼로그에 
		 생성하는 기능

    @param
      -# CDialog* dlg : 버튼을 생성할 다이얼로그의 주소 
	  -# int Height : 버튼의 높이를 의미
	  -# int Width : 버튼의 너비를 의미
	  -# int nSize : 생성할 버튼의 갯수를 의미

   @return
       - int* : 생성된 버튼들의 ID를 반환

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