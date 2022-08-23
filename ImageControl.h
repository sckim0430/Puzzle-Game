//------------------------------------------------------------------------
/**
   @file ImageControl.h
   @brief
      - �̹��� ���� ������ ���� ����
   
   @details
      -# ���� ������ �ǹ��ϴ� �̹����� �ҷ��� �����ϴ� ���
    
   @par History
      - 2020/1/18: Created(sckim)
*/

#pragma once
#include<afxwin.h>
#include<atlimage.h>
#include<afxdlgs.h>
#include <opencv\cv.h>  
#include <opencv\highgui.h> 

//------------------------------------------------------------------------
/**
   @class CImageControl
   @brief
      - �̹����� �����ϴ� Ŭ����
   
   @details
   -# �̹����� �ҷ����� ���� ����� �ش��ϴ� ��ŭ �����ϰ�
      �̹����� �ʺ�� ���̸� ��ȯ�ϴ� ��� ����
    
   @par History
      - 2020/1/18: Created(sckim)
*/

using namespace cv;   
using namespace std;  

class CImageControl
{
private:
	CBitmap m_Bitmap;		//��� �̹���
	CBitmap m_Bmp;
	CImage m_BackImg;
	CImage m_Img;			//���� ���� �̹���
	Mat m_MatImg;			//���� �̹���
	CString m_strPath;
	int m_nHeight;
	int m_nWidth;
	int m_nSize;

private:
	int Mat2CImage(Mat* mat, CImage &img);
	
public:
	CImageControl();
	~CImageControl();
	BOOL LoadImage();
	BOOL GetFilePath();
	BOOL ResizeImg(int nHeight,int nWidth);
	CImage* GetSplitImage(int nHeight,int nWidth,int nSize);
	BOOL GetHintImage();
	BOOL DestroyHintImage();
	BOOL ReNewMatImage();
	void MakeMemBitmap(CDC* pDC,int nWidth,int nHeight);
	CString GetPath();
	void SetPath(CString str);
public:
	int GetHeight();
	int GetWidth();
};