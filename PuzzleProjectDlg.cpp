//------------------------------------------------------------------------
/**
   @file PuzzleProjectDlg.cpp
   @brief
      - 퍼즐 게임 제어 기능 구현
   
   @details
      -# 전체적으로 퍼즐 게임을 제어하기 위한 기능들을 구현

   @par History
      - 2020/1/16: Created(sckim)
*/

// PuzzleProjectDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "PuzzleProject.h"
#include "PuzzleProjectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(CPuzzleProjectDlg) //left , top ,right, bottom
	EASYSIZE(IDC_BUTTON1,ES_KEEPSIZE,ES_BORDER,ES_BORDER,ES_KEEPSIZE,0);
	EASYSIZE(IDC_BUTTON2,ES_KEEPSIZE,ES_BORDER,ES_BORDER,ES_KEEPSIZE,0);
	EASYSIZE(IDC_CHECK1,ES_KEEPSIZE,ES_BORDER,ES_BORDER,ES_KEEPSIZE,0);
	EASYSIZE(IDC_EDIT1,ES_KEEPSIZE,ES_KEEPSIZE,ES_BORDER,ES_BORDER,0);
	EASYSIZE(IDC_STATIC,ES_KEEPSIZE,ES_KEEPSIZE,ES_BORDER,ES_BORDER,0);
	EASYSIZE(IDC_STATIC_2,ES_KEEPSIZE,ES_KEEPSIZE,ES_BORDER,ES_BORDER,0);
END_EASYSIZE_MAP
// CPuzzleProjectDlg 대화 상자



CPuzzleProjectDlg::CPuzzleProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPuzzleProjectDlg::IDD, pParent),m_pSplitImg(NULL),m_pIndex(NULL),m_pnID(NULL),m_bIsLoaded(FALSE),m_nSize(0),m_nGrayIndex(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}
CPuzzleProjectDlg::~CPuzzleProjectDlg()
{	
	if(m_pSplitImg)
	{
		delete[] m_pSplitImg;
		m_pSplitImg = NULL;
	}

	if(m_pIndex)
	{
		delete[] m_pIndex;
		m_pIndex=NULL;
	}

	if(m_pnID)
	{
		delete[] m_pnID;
		m_pnID = NULL;
	}
}
void CPuzzleProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPuzzleProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPuzzleProjectDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPuzzleProjectDlg::OnBnClickedButton2)
	ON_COMMAND_RANGE(BTN_ID,BTN_ID+MAX_BUTTON_NUM-1,OnButtonEvent)
	ON_BN_CLICKED(IDC_CHECK1, &CPuzzleProjectDlg::OnBnClickedCheck1)
	ON_COMMAND(ID_MENU_EXIT, &CPuzzleProjectDlg::OnMenuExit)
	ON_COMMAND(ID_GAME_CHANGETHELEVEL, &CPuzzleProjectDlg::OnGameChangethelevel)
	ON_WM_SIZING()
	ON_WM_GETMINMAXINFO()
	ON_WM_CTLCOLOR()
	ON_WM_DRAWITEM()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_ENTERSIZEMOVE()
	ON_WM_EXITSIZEMOVE()
	ON_WM_NCPAINT()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_EXITSIZEMOVE()
END_MESSAGE_MAP()


// CPuzzleProjectDlg 메시지 처리기

BOOL CPuzzleProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	
	SetWindowTheme(GetDlgItem(IDC_CHECK1)->m_hWnd,_T(""),_T(""));
	
	//Start button disable
	(GetDlgItem(IDC_BUTTON2))->EnableWindow(FALSE);
	
	//Check button disable
	(GetDlgItem(IDC_CHECK1))->EnableWindow(FALSE);

	//Initialize Edit
	SetDlgItemInt(IDC_EDIT1,0);

	//Set Edit Alignment
	CRect r;
	((CEdit *)GetDlgItem(IDC_EDIT1))->GetRect(r);

	r.top += 7;
    r.bottom +=20;

	((CEdit *)GetDlgItem(IDC_EDIT1))->SetRect(r);

	this->GetClientRect(m_rcDlg);
	ScreenToClient(&m_rcDlg);

	INIT_EASYSIZE;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CPuzzleProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CPuzzleProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);

		CRect rect;
		GetClientRect(rect);

		//메모리 DC와 BITMAP 생성
		CDC *pDC = GetDC();
		
		//메모리 DC에 그리기
		m_ImgControl.MakeMemBitmap(pDC,rect.Width(),rect.Height());
		

		GetDlgItem(IDC_STATIC)->RedrawWindow();
		GetDlgItem(IDC_STATIC_2)->RedrawWindow();
		GetDlgItem(IDC_BUTTON1)->RedrawWindow();
		GetDlgItem(IDC_BUTTON2)->RedrawWindow();
		GetDlgItem(IDC_CHECK1)->RedrawWindow();
		GetDlgItem(IDC_EDIT1)->RedrawWindow();
		
		CDialogEx::OnPaint();
	}
}
// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CPuzzleProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/**
   @fn OnButtonEvent
   @brief
      - 버튼 클릭 이벤트 처리

   @details
      -# 클릭된 버튼의 ID와 좌표를 검사하여 이동시키는 기능

   @param
      -# UINT ID : 클릭된 버튼의 ID

   @return
    

   @par History
      - 2020/1/22: Created(sckim)
*/

void CPuzzleProjectDlg::OnButtonEvent(UINT ID)
{
	if(!m_TmControl.IsThreadPlay())
	{
		return;
	}

	Index index;
	
	index.x = (ID - BTN_ID)/(m_nSize);
	index.y = (ID - BTN_ID)%(m_nSize);

	if(m_Algorithm.ChageObject(m_pIndex,index,m_nGrayIndex,m_nSize))
	{
		((CButton*)GetDlgItem(m_pnID[m_nGrayIndex]))
			->SetBitmap((HBITMAP)m_pSplitImg[m_pIndex[m_nGrayIndex].x * m_nSize + m_pIndex[m_nGrayIndex].y]);

		((CButton*)GetDlgItem(m_pnID[index.x*m_nSize + index.y]))
			->SetBitmap((HBITMAP)m_pSplitImg[m_pIndex[index.x*m_nSize+index.y].x * m_nSize + m_pIndex[index.x*m_nSize+index.y].y]);

		m_nGrayIndex = index.x * m_nSize + index.y;

		
		if(m_Algorithm.CheckObject(m_pIndex,m_nSize))
		{
			//Initialize Thread
			m_TmControl.SetPauseState();

			//Initialize Button
			(GetDlgItem(IDC_BUTTON2))->SetWindowText(_T("COMPLETE!"));
			(GetDlgItem(IDC_BUTTON2))->EnableWindow(FALSE);

			//Success Message
			CString strComment;
			int time;

			GetDlgItemText(IDC_EDIT1,strComment);
			time = _ttoi(strComment);
			strComment.Format(_T("You have completed the puzzle. Total game time is %d seconds!"),time);
			AfxMessageBox(strComment);
		}
	}
}

/**
   @fn OnBnClickedButton1
   @brief
      - 버튼 클릭 이벤트 처리

   @details
      -# 이미지 파일을 로드하고 분할된 이미지를 각 버튼에 배치하여
		 시작 대기 상태를 만드는 기능

   @param
      

   @return
    

   @par History
      - 2020/1/20: Created(sckim)
*/

void CPuzzleProjectDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//Get Image Path & Image
	//Get Puzzle Size
	
	int nSize;
	CString str =m_ImgControl.GetPath();

	if(!m_ImgControl.GetFilePath())
	{
		return;
	}
	
	CSetDifficultyDlg CDifficultydlg;

	if(CDifficultydlg.DoModal() == IDOK)
	{
		nSize = _ttoi(CDifficultydlg.m_Edit);
	}
	else
	{
		m_ImgControl.SetPath(str);
		return;
	}

	if(m_bIsLoaded)
	{
		//동적할당 해제
		if(m_pnID)
		{
			for(int i=0;i<m_nSize*m_nSize;i++)
			{
				((CButton*)GetDlgItem(m_pnID[i]))->DestroyWindow();
			}
			
			delete[] m_pnID;
			m_pnID = NULL;
		}

		if(m_pSplitImg)
		{
			delete[] m_pSplitImg;
			m_pSplitImg = NULL;
		}
	
		if(m_pIndex)
		{
			delete[] m_pIndex;
			m_pIndex = NULL;
		}

		if(!m_TmControl.IsThreadInIt())
		{
			//Initialize Thread
			m_TmControl.SetThreadInIt();

			//Initialize Button
			(GetDlgItem(IDC_BUTTON2))->SetWindowText(_T("START"));
			
			//Initialize Edit
			SetDlgItemInt(IDC_EDIT1,0);
		}

		(GetDlgItem(IDC_BUTTON2))->EnableWindow(FALSE);

		//Initialize Button
		if(IsDlgButtonChecked(IDC_CHECK1))
		{
			((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(FALSE);
			m_ImgControl.DestroyHintImage();
		}
		
		(GetDlgItem(IDC_CHECK1))->EnableWindow(FALSE);
	}

	if(!m_ImgControl.LoadImage())
	{
		AfxMessageBox(_T("Wrong Image Type!"));
		return;
	}

	m_nSize = nSize;

	//Resize & Split Image
	m_pSplitImg = m_ImgControl.GetSplitImage(IMAGEROW*this->GetDialogScale_x(),IMAGECOL*this->GetDialogScale_y(),m_nSize);

	//Get Button ID
	m_pnID = m_BtControl.CreateButton((CDialog*)this,IMAGEROW*this->GetDialogScale_x(),IMAGECOL*this->GetDialogScale_y(),m_nSize);

	//Get Image Index
	m_pIndex = m_Algorithm.CreateIndex(m_nSize);	

	//button able
	(GetDlgItem(IDC_BUTTON2))->EnableWindow(TRUE);
	(GetDlgItem(IDC_CHECK1))->EnableWindow(TRUE);

	//Draw Image
	for(int i=0; i<m_nSize*m_nSize;i++)
	{
		((CButton*)GetDlgItem(m_pnID[i]))->SetBitmap((HBITMAP)m_pSplitImg[i]);	
	}

	m_bIsLoaded = TRUE;
}


/**
   @fn OnBnClickedButton2
   @brief
      - 버튼 클릭 이벤트 처리

   @details
      -# 쓰레드 동작 상태를 확인하고 플레이 중에 버튼이 이동하고,
	     시간을 관리하는 기능

   @param
    

   @return
    

   @par History
      - 2020/1/21: Created(sckim)
*/

void CPuzzleProjectDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_TmControl.IsThreadInIt())
	{
		//퍼즐 섞기
		int nCount=0;
		BOOL bIsCreated = FALSE;

		m_nGrayIndex = m_nSize*m_nSize-1;

		do 
		{
			if(m_Algorithm.SuffleObject(m_pIndex,m_nGrayIndex,m_nSize))
			{
				nCount++;
			}
	
		} while ((m_pnID[m_nGrayIndex] != (BTN_ID +m_nSize*m_nSize-1))
					|| m_Algorithm.CheckObject(m_pIndex,m_nSize)
					|| nCount < m_nSize * m_nSize * 100);

		for(int i=0; i<m_nSize*m_nSize;i++)
		{
			((CButton*)GetDlgItem(m_pnID[i]))->SetBitmap((HBITMAP)m_pSplitImg[m_pIndex[i].x * m_nSize + m_pIndex[i].y]);	
		}

		m_TmControl.SetObjectItem(this,IDC_EDIT1);
		m_TmControl.StartThread();

		GetDlgItem(IDC_BUTTON2)->SetWindowText(_T("PAUSE"));
	}
	else
	{
		if(m_TmControl.IsThreadPlay())
		{
			m_TmControl.SetPauseState();

			for(int i=0; i<m_nSize*m_nSize;i++)
			{
				((CButton*)GetDlgItem(m_pnID[i]))->SetBitmap((HBITMAP)m_pSplitImg[i]);	
			}

			GetDlgItem(IDC_BUTTON2)->SetWindowText(_T("RESUME"));
		}
		else if(m_TmControl.IsThreadPause())
		{
			m_TmControl.SetResumeState();

			for(int i=0; i<m_nSize*m_nSize;i++)
			{
				((CButton*)GetDlgItem(m_pnID[i]))->SetBitmap((HBITMAP)m_pSplitImg[m_pIndex[i].x * m_nSize + m_pIndex[i].y]);	
			}

			GetDlgItem(IDC_BUTTON2)->SetWindowText(_T("PAUSE"));
		}
	}

}

/**
   @fn OnBnClickedCheck1
   @brief
      - 버튼 클릭 이벤트 처리

   @details
      -# 체크 박스 클릭 여부에 따라 힌트 사용 여부를 결정하여 힌트 이미지의 출력 여부를
		 결정하는 기능

   @param
    

   @return
    

   @par History
      - 2020/1/26: Created(sckim)
*/

void CPuzzleProjectDlg::OnBnClickedCheck1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL bIsChecked = IsDlgButtonChecked(IDC_CHECK1);

	if(bIsChecked)		//힌트 이미지 윈도우 띄우기
	{
		m_ImgControl.GetHintImage();
	}
	else				//힌트 이미지 윈도우 닫기
	{
		m_ImgControl.DestroyHintImage();
	}

}

/**
   @fn OnMenuExit
   @brief
      - 메뉴 이벤트 처리

   @details
      -# 퍼즐 게임 강제 종료 기능


   @param
    

   @return
    

   @par History
      - 2020/1/27: Created(sckim)
*/

void CPuzzleProjectDlg::OnMenuExit()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	AfxMessageBox(_T("Exit the game"));

	exit(1);
}

/**
   @fn OnGameChangethelevel
   @brief
      - 메뉴 이벤트 처리

   @details
      -# 퍼즐 사이즈를 변경하는 기능


   @param
    

   @return
    

   @par History
      - 2020/1/27: Created(sckim)
*/

void CPuzzleProjectDlg::OnGameChangethelevel()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	if(m_bIsLoaded)
	{
		int nSize;
		CSetDifficultyDlg CDifficultydlg;

		if(CDifficultydlg.DoModal() == IDOK)
		{
			nSize = _ttoi(CDifficultydlg.m_Edit);
		}
		else
		{
			return;
		}

		//동적할당 해제
		if(m_pnID)
		{
			for(int i=0;i<m_nSize*m_nSize;i++)
			{
				((CButton*)GetDlgItem(m_pnID[i]))->DestroyWindow();
			}
			
			delete[] m_pnID;
			m_pnID = NULL;
		}

		if(m_pSplitImg)
		{
			delete[] m_pSplitImg;
			m_pSplitImg = NULL;
		}
	
		if(m_pIndex)
		{
			delete[] m_pIndex;
			m_pIndex = NULL;
		}

		if(!m_TmControl.IsThreadInIt())
		{
			//Initialize Thread
			m_TmControl.SetThreadInIt();

			//Initialize Button
			(GetDlgItem(IDC_BUTTON2))->SetWindowText(_T("START"));
			
			//Initialize Edit
			SetDlgItemInt(IDC_EDIT1,0);
		}

		(GetDlgItem(IDC_BUTTON2))->EnableWindow(FALSE);

		//Initialize Button
		if(IsDlgButtonChecked(IDC_CHECK1))
		{
			((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(FALSE);
			m_ImgControl.DestroyHintImage();
		}
		
		(GetDlgItem(IDC_CHECK1))->EnableWindow(FALSE);

		m_nSize = nSize;

	//Split Image
	m_pSplitImg = m_ImgControl.GetSplitImage(this->GetDialogScale_x()*IMAGEROW,this->GetDialogScale_y()*IMAGECOL,m_nSize);

	//Get Button ID
	m_pnID = m_BtControl.CreateButton((CDialog*)this,this->GetDialogScale_x()*IMAGEROW,this->GetDialogScale_y()*IMAGECOL,m_nSize);

	//Get Image Index
	m_pIndex = m_Algorithm.CreateIndex(m_nSize);

	//button able
	(GetDlgItem(IDC_BUTTON2))->EnableWindow(TRUE);
	(GetDlgItem(IDC_CHECK1))->EnableWindow(TRUE);

	//Draw Image
	for(int i=0; i<m_nSize*m_nSize;i++)
	{
		((CButton*)GetDlgItem(m_pnID[i]))->SetBitmap((HBITMAP)m_pSplitImg[i]);	
	}
	}
	else
	{
		AfxMessageBox(_T("No image loaded!"));
	}
}


/**
   @fn OnGetMinMaxInfo
   @brief
      - 다이얼로그 창 사이즈 제한

   @details
      -# 다이얼로그 창의 최대 및 최소 사이즈 제한을 두는 기능


   @param
      - MINMAXINFO* lpMMI: 현재 다이얼로그의 최대 및 최소 정보를 저장
	  
   @return
    
   @par History
      - 2020/1/28: Created(sckim)
*/

 void CPuzzleProjectDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
   // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
   lpMMI->ptMinTrackSize.x = 550;
   lpMMI->ptMinTrackSize.y = 550;
   lpMMI->ptMaxTrackSize.x = 1000;
   lpMMI->ptMaxTrackSize.y = 1000;

   CDialogEx::OnGetMinMaxInfo(lpMMI);
}

 /**
   @fn GetDialogScale_x
   @brief
      - 다이얼로그 창 비율

   @details
      -# 처음 다이얼로그의 창 높이와 현재 다이얼로그의 창 높이 비율을 반환


   @param
     
	  
   @return
	  -# double : 처음 다이얼로그의 창 높이와 현재 다이얼로그의 창 높이 비율

   @par History
      - 2020/1/28: Created(sckim)
*/

 double CPuzzleProjectDlg::GetDialogScale_x()
 {
	 CRect rcDlg;
	 double dblDlgScale_Height;

	 GetClientRect(&rcDlg);
	 ScreenToClient(&rcDlg);
	 
	 dblDlgScale_Height = (double)(rcDlg.Height())/(m_rcDlg.Height());
	 
	 return dblDlgScale_Height;
 }

 /**
   @fn GetDialogScale_y
   @brief
      - 다이얼로그 창 비율

   @details
      -# 처음 다이얼로그의 창 너비와 현재 다이얼로그의 창 너비 비율을 반환


   @param
     
	  
   @return
	  -# double : 처음 다이얼로그의 창 너비와 현재 다이얼로그의 창 너비 비율

   @par History
      - 2020/1/28: Created(sckim)
*/

 double CPuzzleProjectDlg::GetDialogScale_y()
 {
	 CRect rcDlg;
	 double dblDlgScale_Width;

	 GetClientRect(&rcDlg);
	 ScreenToClient(&rcDlg);

	 dblDlgScale_Width = (double)(rcDlg.Width())/(m_rcDlg.Width());

	 return dblDlgScale_Width;
 }

 /**
   @fn OnCtlColor
   @brief
      - 다이얼로그 컨트롤 속성 변경

   @details
      -# 다이얼로그 컨트롤 투명화 및 색 변경


   @param
     -# CDC* pDC: 현재 다이얼로그의 DC
	 -# CWnd* pWnd: 현재 프로젝트의 윈도우 클래스
	 -# UINT nCtlColor
	  
   @return
	  -# HBRUSH

   @par History
      - 2020/1/29: Created(sckim)
*/


 HBRUSH CPuzzleProjectDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
 {
	 CBrush brh;

	 HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	 brh.CreateSolidBrush(RGB(255,255,255));

	 if((nCtlColor == CTLCOLOR_STATIC) || (nCtlColor == CTLCOLOR_EDIT))
	 {
		 pDC->SetBkMode(TRANSPARENT);		//배경 투명하게
	 }
	 else if(nCtlColor == CTLCOLOR_LISTBOX)
	 {
		 pDC->SetBkColor(RGB(255, 255, 255));	//배경색 변경
	 }
	 else
	 {
		 if(nCtlColor == CTLCOLOR_BTN)
		 {
			 pDC->SetBkMode(TRANSPARENT);		//배경 투명하게			 
		 }
	 }

	 pDC->SetTextColor(RGB(255,255,255));
	
	 hbr = (HBRUSH)GetStockObject(NULL_BRUSH);

	 return hbr;
 }


 void CPuzzleProjectDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
 {
	 // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	 if(nIDCtl==IDC_BUTTON1 || nIDCtl == IDC_BUTTON2)
	 {
		 CDC dc;
		 RECT rect;
		 dc.Attach(lpDrawItemStruct ->hDC);   // Get the Button DC to CDC

		 rect = lpDrawItemStruct->rcItem;     //Store the Button rect to our local rect.
		 dc.Draw3dRect(&rect,RGB(255,255,255),RGB(0,0,0));
		 dc.FillSolidRect(&rect,RGB(0,0,0));//Here you can define the required color to appear on the Button.

		 UINT state=lpDrawItemStruct->itemState;  //This defines the state of the Push button either pressed or not.
		 if((state & ODS_SELECTED))
			 dc.DrawEdge(&rect,EDGE_SUNKEN,BF_RECT);
		 else
			 dc.DrawEdge(&rect,EDGE_RAISED,BF_RECT);

		 dc.SetBkColor(RGB(100,100,255));   //Setting the Text Background color
		 dc.SetTextColor(RGB(255,255,255));     //Setting the Text Color

		 TCHAR buffer[MAX_PATH];           //To store the Caption of the button.
		 ZeroMemory(buffer,MAX_PATH );     //Intializing the buffer to zero
		 ::GetWindowText(lpDrawItemStruct->hwndItem,buffer,MAX_PATH); //Get the Caption of Button Window

		 dc.DrawText(buffer,&rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);//Redraw the  Caption of Button Window
		 dc.Detach();  // Detach the Button DC
	 }

	 CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
 }


 BOOL CPuzzleProjectDlg::OnEraseBkgnd(CDC* pDC)
 {
	 // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	 return FALSE;
	 //return CDialogEx::OnEraseBkgnd(pDC);
 }

 /**
   @fn OnSize
   @brief
      - 다이얼로그 창 확대 축소 이벤트 처리

   @details
      -# 기본 컨트롤러의 이동 및 퍼즐 조각 크기 변경 기능


   @param
     
   @return

   @par History
      - 2020/1/28: Created(sckim)
*/

 void CPuzzleProjectDlg::OnSize(UINT nType, int cx, int cy)
 {
	 CDialogEx::OnSize(nType, cx, cy);

	 // TODO: 여기에 메시지 처리기 코드를 추가합니다.

	 if(m_bIsLoaded)
	 {
		 if(!m_pIndex)
		 {
			 return;
		 }

		 //동적할당 해제
		 if(m_pnID)
		 {
			 for(int i=0;i<m_nSize*m_nSize;i++)
			 {
				 ((CButton*)GetDlgItem(m_pnID[i]))->DestroyWindow();
			 }

			 delete[] m_pnID;
			 m_pnID = NULL;
		 }

		 if(m_pSplitImg)
		 {
			 delete[] m_pSplitImg;
			 m_pSplitImg = NULL;
		 }		   


		 //Split Image
		 m_ImgControl.ReNewMatImage();
		 m_pSplitImg = m_ImgControl.GetSplitImage(IMAGEROW*this->GetDialogScale_x(),IMAGECOL*this->GetDialogScale_y(),m_nSize);

		 //Get Button ID
		 m_pnID = m_BtControl.CreateButton((CDialog*)this,IMAGEROW*this->GetDialogScale_x(),IMAGECOL*this->GetDialogScale_y(),m_nSize);

		 //Draw Image
		 if(m_TmControl.IsThreadPlay())
		 {
			for(int i=0; i<m_nSize*m_nSize;i++)
			{
				 ((CButton*)GetDlgItem(m_pnID[i]))->SetBitmap((HBITMAP)m_pSplitImg[m_pIndex[i].x * m_nSize + m_pIndex[i].y]);	
			}
		 }
		 else
		 {
			 for(int i=0; i<m_nSize*m_nSize;i++)
			 {
				 ((CButton*)GetDlgItem(m_pnID[i]))->SetBitmap((HBITMAP)m_pSplitImg[i]);	
			 }
		 }
	 }

	 UPDATE_EASYSIZE;
 }
