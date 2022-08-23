//------------------------------------------------------------------------
/**
   @file ImageControl.cpp
   @brief
      - 이미지 관리 기능 구현 파일
   
   @details
      -# 퍼즐 조각에 해당하는 이미지를 불러오거나 분할하여
		 반환하는 기능을 구현
    
   @par History
      - 2020/1/18: Created(sckim)
*/

#include"ImageControl.h"

CImageControl::CImageControl()
	:m_nHeight(0),m_nWidth(0),m_nSize(0),m_strPath(_T(""))
{
	m_BackImg.Load(_T("C:\\sckim\\Project\\Puzzle Project\\resource\\rc.bmp"));
	m_Bmp.Attach(m_BackImg.Detach());
}

CImageControl::~CImageControl()
{
}

/**
   @fn GetFilePath
   @brief
      - 이미지 파일의 경로를 불러오는 기능

   @details
      -# 파일 선택 다이얼로그로 부터 해당 이미지 파일의 경로를 불러와
		 저장하는 함수

   @param


   @return
       - BOOL : 파일 경로를 불러왔는지에 대한 여부

   @par History
      - 2020/1/18: Created(sckim)
*/

BOOL CImageControl::GetFilePath()
{
	BOOL bIsSelect = FALSE;
	TCHAR szFilter[] = _T("Image (*.BMP) | *.BMP|");

	CFileDialog dlg(TRUE, _T("bmp"), NULL, OFN_HIDEREADONLY,szFilter);

	//파일 경로 불러 오기 및 성공 여부
	if(dlg.DoModal()==IDOK)
	{
		bIsSelect = TRUE;
		m_strPath = dlg.GetPathName();
	}
	else
	{
		bIsSelect = FALSE;
	}

	return bIsSelect;
}

/**
   @fn LoadImage
   @brief
      - 이미지를 저장

   @details
      -# 이미지의 파일 경로로 부터 읽어와서 저장하는 기능

   @param


   @return
       - BOOL : 이미지 불러오기 성공 여부 반환

   @par History
      - 2020/1/18: Created(sckim)
*/
BOOL CImageControl::LoadImage()
{
	BOOL bIsLoaded = FALSE;

	//파일 경로 불러오기 및 성공 여부
	
	CT2CA pszConvertedAnsiString(m_strPath); 
	std::string str(pszConvertedAnsiString); 

	//이미지 로드 & 이미지 존재 여부 및 로드 성공 여부
	if(!m_Img.IsNull())
	{
		m_Img.Destroy();
	}
	
	if(!(m_Img.Load(m_strPath)))
	{
		m_nHeight = m_Img.GetHeight();
		m_nWidth = m_Img.GetWidth();

		m_MatImg = imread(str,IMREAD_COLOR);

		bIsLoaded=TRUE;
	}
	
	return bIsLoaded;
}

/**
   @fn Mat2CImage
   @brief
      - 이미지 자료형 변환

   @details
      -# Mat 형식의 이미지로 부터 CImage 형식으로 변환

   @param
	 -# Mat* mat : 변환 대상이 되는 Mat 형식의 이미지 파일
	 -# CImage &img : 변환된 대상이 되는 CImage 형식의 이미지 파일

   @return
       - int : 이미지 불러오기 성공 여부 반환

   @par History
      - 2020/1/18: Created(sckim)
*/

int CImageControl::Mat2CImage(Mat* mat, CImage &img)//		//Mat에서 CImage로 변환 함수
{										
	if(!mat || mat->empty())								
	{
		return -1;
	}

	int nBPP = mat->channels()*8;
	img.Create(mat->cols,mat->rows,nBPP);

	if(nBPP == 8)
	{
		static RGBQUAD pRGB[256];

		for(int i=0;i<256;i++)
		{
			pRGB[i].rgbBlue = pRGB[i].rgbGreen = pRGB[i].rgbRed =i;
		}

		img.SetColorTable(0,256,pRGB);
	}
	
	uchar* psrc = mat->data;
	uchar* pdst = (uchar*)img.GetBits();
	int imgPitch = img.GetPitch();

	for(int y=0;y<mat->rows; y++)
	{
		memcpy(pdst,psrc,mat->cols*mat->channels());
		psrc += mat->step;
		pdst += imgPitch;
	}
	
	return 0;
}

/**
   @fn ResizeImg
   @brief
      - 이미지의 사이즈 변경

   @details
      -# 원본 이미지로 부터 해당 사이즈의 이미지로 변경

   @param
     -# int nHeight : 변환할 원본 이미지의 높이
	 -# int nWidth : 변환할 원본 이미지의 너비
	

   @return
      - BOOL : 이미지 리사이징 유무를 반환

   @par History
      - 2020/1/27: Created(sckim)
*/

BOOL CImageControl::ResizeImg(int nHeight,int nWidth)
{
	BOOL bIsResized = FALSE;

	if(!m_Img)
	{
		return bIsResized;
	}
	else
	{
		bIsResized = TRUE;
	}
	
	resize(m_MatImg,m_MatImg,Size(nWidth,nHeight),0,0,CV_INTER_NN );

	return bIsResized;
}

/**
   @fn GetSplitImage
   @brief
      - 분할된 이미지를 생성

   @details
      -# 원본 이미지로 부터 해당 사이즈의 크기 만큼 분할한 이미지를
		 생성하는 기능

   @param
     -# int nHeight : 변환할 원본 이미지의 높이
	 -# int nWidth : 변환할 원본 이미지의 너비
	 -# int nSize : 분할할 이미지의 갯수를 의미
	

   @return
       - CImage* : 분할된 이미지들을 반환

   @par History
      - 2020/1/18: Created(sckim)
*/

CImage* CImageControl::GetSplitImage(int nHeight,int nWidth,int nSize)
{
	m_nSize = nSize;	
	
	if(!ResizeImg(nHeight,nWidth) || (!m_Img))
	{
		return NULL;
	}

	CImage* pSplitImg;

	pSplitImg = new CImage[m_nSize * m_nSize];
	
	for(int x=0;x<m_nSize;x++)
	{
		for(int y=0;y<m_nSize;y++)
		{
			Mat subImage;

			if(x==m_nSize-1 && y==m_nSize-1)
			{
				subImage = Scalar(127);

				Mat2CImage(&subImage,pSplitImg[x*m_nSize+y]);

				continue;
			}                                

			int nSplitWidth = nWidth / m_nSize;
			int nSplitHeight = nHeight / m_nSize;

			Rect rect(y*(nSplitWidth),x*(nSplitHeight),nSplitWidth,nSplitHeight);	

			subImage = m_MatImg(rect);	

			Mat2CImage(&subImage,pSplitImg[x*m_nSize+y]);		
		}
	}	
	return pSplitImg;
}

/**
   @fn GetHeight
   @brief
      - 이미지 정보를 반환

   @details
      -# 원본 이미지의 높이를 반환

   @param
	 

   @return
       - int : 원본 이미지의 높이를 반환

   @par History
      - 2020/1/18: Created(sckim)
*/

int CImageControl::GetHeight()
{
	return this->m_nHeight;
}

/**
   @fn GetWidth
   @brief
      - 이미지 정보를 반환

   @details
      -# 원본 이미지의 너비를 반환

   @param
	 

   @return
       - int : 원본 이미지의 너비를 반환

   @par History
      - 2020/1/18: Created(sckim)
*/

int CImageControl::GetWidth()
{
	return this->m_nWidth;
}

/**
   @fn GetHintImage
   @brief
      - 이미지 창 반환

   @details
      -# 힌트를 의미하는 원본 이미지 윈도우 출력

   @param
	 

   @return
      

   @par History
      - 2020/1/26: Created(sckim)
*/

BOOL CImageControl::GetHintImage()
{
	BOOL bIsGetHint = FALSE;

	imshow("Hint Image",m_MatImg);
	bIsGetHint = TRUE;

	return bIsGetHint;
}

/**
   @fn DistroyHintImage
   @brief
      - 이미지 창 제거

   @details
      -# 힌트를 의미하는 원본 이미지 윈도우 제거

   @param
	 

   @return
      

   @par History
      - 2020/1/26: Created(sckim)
*/

BOOL CImageControl::DestroyHintImage()
{
	BOOL bIsDistroyHint = FALSE;

	destroyAllWindows();

	bIsDistroyHint = TRUE;

	return bIsDistroyHint;
}

/**
   @fn ReNewMatImage
   @brief
      - Mat 이미지 갱신

   @details
      -# Mat 이미지를 갱신하여 퍼즐의 화질을 유지하는 기능

   @param
	 

   @return
      -# BOOL : 이미지 갱신 여부를 반환

   @par History
      - 2020/1/28: Created(sckim)
*/

BOOL CImageControl::ReNewMatImage()
{
	BOOL bIsReNewed = FALSE;

	if(m_Img.IsNull())
	{
		return bIsReNewed;
	}
	
	CT2CA pszConvertedAnsiString(m_strPath); 
	std::string str(pszConvertedAnsiString); 

	m_MatImg = imread(str,IMREAD_COLOR);

	bIsReNewed = TRUE;

	return bIsReNewed;
}

/**
   @fn MakeMemBitmap
   @brief
      - 더블 버퍼링 기능

   @details
      -# 미리 Bitmap에 그림을 그려주는 기능

   @param
	 -# CDialog* pDlg : 그림을 그릴 대상의 위치

   @return
      -#

   @par History
      - 2020/1/29: Created(sckim)
*/

/*
void CImageControl::MakeMemBitmap(CDC* pDC,int nWidth,int nHeight)
{
	CDC MemDC;
	CBitmap* pOldBitmap;

	//메모리 DC 및 BITMAP과 현재 DC의 설정 일치
	MemDC.CreateCompatibleDC(pDC);

	pOldBitmap = MemDC.SelectObject(&m_Bmp);

	//메모리 DC를 현재 DC에 복사
	pDC->BitBlt(0,0,nWidth,nHeight,&MemDC,0,0,SRCCOPY);

	//사용된 메모리 DC 및 BITMAP 삭제
	MemDC.SelectObject(pOldBitmap);
	MemDC.DeleteDC();
}
*/

void CImageControl::MakeMemBitmap(CDC* pDC,int nWidth,int nHeight)
{
	CDC MemDC;
	BITMAP bmp_info;
	CBitmap* pOldBitmap;

	//메모리 DC 및 BITMAP과 현재 DC의 설정 일치
	m_Bmp.GetBitmap(&bmp_info);
	
	MemDC.CreateCompatibleDC(pDC);
	pOldBitmap=MemDC.SelectObject(&m_Bmp);
	
	//메모리 DC를 현재 DC에 복사
	pDC->StretchBlt(0,0,nWidth,nHeight,&MemDC,
		0,0,bmp_info.bmWidth,bmp_info.bmHeight,SRCCOPY);

	//사용된 메모리 DC 및 BITMAP 삭제
	MemDC.SelectObject(pOldBitmap);
	MemDC.DeleteDC();
}

CString CImageControl::GetPath()
{
	return m_strPath;
}

void CImageControl::SetPath(CString str)
{
	m_strPath = str;
	return;
}