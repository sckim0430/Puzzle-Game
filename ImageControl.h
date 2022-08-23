//------------------------------------------------------------------------
/**
   @file ImageControl.h
   @brief
      - 이미지 관련 정보를 관리 파일
   
   @details
      -# 퍼즐 조각을 의미하는 이미지를 불러와 관리하는 기능
    
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
      - 이미지를 관리하는 클래스
   
   @details
   -# 이미지를 불러오고 퍼즐 사이즈에 해당하는 만큼 분할하고
      이미지의 너비와 높이를 반환하는 기능 구현
    
   @par History
      - 2020/1/18: Created(sckim)
*/

using namespace cv;   
using namespace std;  

class CImageControl
{
private:
	CBitmap m_Bitmap;		//배경 이미지
	CBitmap m_Bmp;
	CImage m_BackImg;
	CImage m_Img;			//원본 퍼즐 이미지
	Mat m_MatImg;			//퍼즐 이미지
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