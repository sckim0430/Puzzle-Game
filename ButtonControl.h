//------------------------------------------------------------------------
/**
   @file ButtonControl.h
   @brief
      - 버튼을 관리하기 위한 파일
   
   @details
      -# 동적으로 버튼을 생성하고 관리
    
   @par History
      - 2020/1/17: Created(sckim)
*/

#pragma once
#include<afxwin.h>
#include<afx.h>
#include<Uxtheme.h>

#define BTN_ID   10000

//------------------------------------------------------------------------
/**
   @class CButtonControl
   @brief
      - 버튼 생성 클래스
   
   @details
      -# 동적으로 버튼을 생성
    
   @par History
      - 2020/1/17: Created(sckim)
*/

class CButtonControl
{
public:
	int* CreateButton(CDialog* dlg, int Height,int Width, int nSize);
	
	CButtonControl();
	~CButtonControl();
};