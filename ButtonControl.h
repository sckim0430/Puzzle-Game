//------------------------------------------------------------------------
/**
   @file ButtonControl.h
   @brief
      - ��ư�� �����ϱ� ���� ����
   
   @details
      -# �������� ��ư�� �����ϰ� ����
    
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
      - ��ư ���� Ŭ����
   
   @details
      -# �������� ��ư�� ����
    
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