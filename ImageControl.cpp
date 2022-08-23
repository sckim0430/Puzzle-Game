//------------------------------------------------------------------------
/**
   @file ImageControl.cpp
   @brief
      - �̹��� ���� ��� ���� ����
   
   @details
      -# ���� ������ �ش��ϴ� �̹����� �ҷ����ų� �����Ͽ�
		 ��ȯ�ϴ� ����� ����
    
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
      - �̹��� ������ ��θ� �ҷ����� ���

   @details
      -# ���� ���� ���̾�α׷� ���� �ش� �̹��� ������ ��θ� �ҷ���
		 �����ϴ� �Լ�

   @param


   @return
       - BOOL : ���� ��θ� �ҷ��Դ����� ���� ����

   @par History
      - 2020/1/18: Created(sckim)
*/

BOOL CImageControl::GetFilePath()
{
	BOOL bIsSelect = FALSE;
	TCHAR szFilter[] = _T("Image (*.BMP) | *.BMP|");

	CFileDialog dlg(TRUE, _T("bmp"), NULL, OFN_HIDEREADONLY,szFilter);

	//���� ��� �ҷ� ���� �� ���� ����
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
      - �̹����� ����

   @details
      -# �̹����� ���� ��η� ���� �о�ͼ� �����ϴ� ���

   @param


   @return
       - BOOL : �̹��� �ҷ����� ���� ���� ��ȯ

   @par History
      - 2020/1/18: Created(sckim)
*/
BOOL CImageControl::LoadImage()
{
	BOOL bIsLoaded = FALSE;

	//���� ��� �ҷ����� �� ���� ����
	
	CT2CA pszConvertedAnsiString(m_strPath); 
	std::string str(pszConvertedAnsiString); 

	//�̹��� �ε� & �̹��� ���� ���� �� �ε� ���� ����
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
      - �̹��� �ڷ��� ��ȯ

   @details
      -# Mat ������ �̹����� ���� CImage �������� ��ȯ

   @param
	 -# Mat* mat : ��ȯ ����� �Ǵ� Mat ������ �̹��� ����
	 -# CImage &img : ��ȯ�� ����� �Ǵ� CImage ������ �̹��� ����

   @return
       - int : �̹��� �ҷ����� ���� ���� ��ȯ

   @par History
      - 2020/1/18: Created(sckim)
*/

int CImageControl::Mat2CImage(Mat* mat, CImage &img)//		//Mat���� CImage�� ��ȯ �Լ�
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
      - �̹����� ������ ����

   @details
      -# ���� �̹����� ���� �ش� �������� �̹����� ����

   @param
     -# int nHeight : ��ȯ�� ���� �̹����� ����
	 -# int nWidth : ��ȯ�� ���� �̹����� �ʺ�
	

   @return
      - BOOL : �̹��� ������¡ ������ ��ȯ

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
      - ���ҵ� �̹����� ����

   @details
      -# ���� �̹����� ���� �ش� �������� ũ�� ��ŭ ������ �̹�����
		 �����ϴ� ���

   @param
     -# int nHeight : ��ȯ�� ���� �̹����� ����
	 -# int nWidth : ��ȯ�� ���� �̹����� �ʺ�
	 -# int nSize : ������ �̹����� ������ �ǹ�
	

   @return
       - CImage* : ���ҵ� �̹������� ��ȯ

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
      - �̹��� ������ ��ȯ

   @details
      -# ���� �̹����� ���̸� ��ȯ

   @param
	 

   @return
       - int : ���� �̹����� ���̸� ��ȯ

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
      - �̹��� ������ ��ȯ

   @details
      -# ���� �̹����� �ʺ� ��ȯ

   @param
	 

   @return
       - int : ���� �̹����� �ʺ� ��ȯ

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
      - �̹��� â ��ȯ

   @details
      -# ��Ʈ�� �ǹ��ϴ� ���� �̹��� ������ ���

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
      - �̹��� â ����

   @details
      -# ��Ʈ�� �ǹ��ϴ� ���� �̹��� ������ ����

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
      - Mat �̹��� ����

   @details
      -# Mat �̹����� �����Ͽ� ������ ȭ���� �����ϴ� ���

   @param
	 

   @return
      -# BOOL : �̹��� ���� ���θ� ��ȯ

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
      - ���� ���۸� ���

   @details
      -# �̸� Bitmap�� �׸��� �׷��ִ� ���

   @param
	 -# CDialog* pDlg : �׸��� �׸� ����� ��ġ

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

	//�޸� DC �� BITMAP�� ���� DC�� ���� ��ġ
	MemDC.CreateCompatibleDC(pDC);

	pOldBitmap = MemDC.SelectObject(&m_Bmp);

	//�޸� DC�� ���� DC�� ����
	pDC->BitBlt(0,0,nWidth,nHeight,&MemDC,0,0,SRCCOPY);

	//���� �޸� DC �� BITMAP ����
	MemDC.SelectObject(pOldBitmap);
	MemDC.DeleteDC();
}
*/

void CImageControl::MakeMemBitmap(CDC* pDC,int nWidth,int nHeight)
{
	CDC MemDC;
	BITMAP bmp_info;
	CBitmap* pOldBitmap;

	//�޸� DC �� BITMAP�� ���� DC�� ���� ��ġ
	m_Bmp.GetBitmap(&bmp_info);
	
	MemDC.CreateCompatibleDC(pDC);
	pOldBitmap=MemDC.SelectObject(&m_Bmp);
	
	//�޸� DC�� ���� DC�� ����
	pDC->StretchBlt(0,0,nWidth,nHeight,&MemDC,
		0,0,bmp_info.bmWidth,bmp_info.bmHeight,SRCCOPY);

	//���� �޸� DC �� BITMAP ����
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