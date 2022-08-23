//------------------------------------------------------------------------
/**
   @file PuzzleProjectDlg.cpp
   @brief
      - ���� ���� ���� ��� ����
   
   @details
      -# ��ü������ ���� ������ �����ϱ� ���� ��ɵ��� ����

   @par History
      - 2020/1/16: Created(sckim)
*/

// PuzzleProjectDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "PuzzleProject.h"
#include "PuzzleProjectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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
// CPuzzleProjectDlg ��ȭ ����



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


// CPuzzleProjectDlg �޽��� ó����

BOOL CPuzzleProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	
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

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CPuzzleProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);

		CRect rect;
		GetClientRect(rect);

		//�޸� DC�� BITMAP ����
		CDC *pDC = GetDC();
		
		//�޸� DC�� �׸���
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
// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CPuzzleProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/**
   @fn OnButtonEvent
   @brief
      - ��ư Ŭ�� �̺�Ʈ ó��

   @details
      -# Ŭ���� ��ư�� ID�� ��ǥ�� �˻��Ͽ� �̵���Ű�� ���

   @param
      -# UINT ID : Ŭ���� ��ư�� ID

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
      - ��ư Ŭ�� �̺�Ʈ ó��

   @details
      -# �̹��� ������ �ε��ϰ� ���ҵ� �̹����� �� ��ư�� ��ġ�Ͽ�
		 ���� ��� ���¸� ����� ���

   @param
      

   @return
    

   @par History
      - 2020/1/20: Created(sckim)
*/

void CPuzzleProjectDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

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
		//�����Ҵ� ����
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
      - ��ư Ŭ�� �̺�Ʈ ó��

   @details
      -# ������ ���� ���¸� Ȯ���ϰ� �÷��� �߿� ��ư�� �̵��ϰ�,
	     �ð��� �����ϴ� ���

   @param
    

   @return
    

   @par History
      - 2020/1/21: Created(sckim)
*/

void CPuzzleProjectDlg::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_TmControl.IsThreadInIt())
	{
		//���� ����
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
      - ��ư Ŭ�� �̺�Ʈ ó��

   @details
      -# üũ �ڽ� Ŭ�� ���ο� ���� ��Ʈ ��� ���θ� �����Ͽ� ��Ʈ �̹����� ��� ���θ�
		 �����ϴ� ���

   @param
    

   @return
    

   @par History
      - 2020/1/26: Created(sckim)
*/

void CPuzzleProjectDlg::OnBnClickedCheck1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL bIsChecked = IsDlgButtonChecked(IDC_CHECK1);

	if(bIsChecked)		//��Ʈ �̹��� ������ ����
	{
		m_ImgControl.GetHintImage();
	}
	else				//��Ʈ �̹��� ������ �ݱ�
	{
		m_ImgControl.DestroyHintImage();
	}

}

/**
   @fn OnMenuExit
   @brief
      - �޴� �̺�Ʈ ó��

   @details
      -# ���� ���� ���� ���� ���


   @param
    

   @return
    

   @par History
      - 2020/1/27: Created(sckim)
*/

void CPuzzleProjectDlg::OnMenuExit()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	
	AfxMessageBox(_T("Exit the game"));

	exit(1);
}

/**
   @fn OnGameChangethelevel
   @brief
      - �޴� �̺�Ʈ ó��

   @details
      -# ���� ����� �����ϴ� ���


   @param
    

   @return
    

   @par History
      - 2020/1/27: Created(sckim)
*/

void CPuzzleProjectDlg::OnGameChangethelevel()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

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

		//�����Ҵ� ����
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
      - ���̾�α� â ������ ����

   @details
      -# ���̾�α� â�� �ִ� �� �ּ� ������ ������ �δ� ���


   @param
      - MINMAXINFO* lpMMI: ���� ���̾�α��� �ִ� �� �ּ� ������ ����
	  
   @return
    
   @par History
      - 2020/1/28: Created(sckim)
*/

 void CPuzzleProjectDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
   lpMMI->ptMinTrackSize.x = 550;
   lpMMI->ptMinTrackSize.y = 550;
   lpMMI->ptMaxTrackSize.x = 1000;
   lpMMI->ptMaxTrackSize.y = 1000;

   CDialogEx::OnGetMinMaxInfo(lpMMI);
}

 /**
   @fn GetDialogScale_x
   @brief
      - ���̾�α� â ����

   @details
      -# ó�� ���̾�α��� â ���̿� ���� ���̾�α��� â ���� ������ ��ȯ


   @param
     
	  
   @return
	  -# double : ó�� ���̾�α��� â ���̿� ���� ���̾�α��� â ���� ����

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
      - ���̾�α� â ����

   @details
      -# ó�� ���̾�α��� â �ʺ�� ���� ���̾�α��� â �ʺ� ������ ��ȯ


   @param
     
	  
   @return
	  -# double : ó�� ���̾�α��� â �ʺ�� ���� ���̾�α��� â �ʺ� ����

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
      - ���̾�α� ��Ʈ�� �Ӽ� ����

   @details
      -# ���̾�α� ��Ʈ�� ����ȭ �� �� ����


   @param
     -# CDC* pDC: ���� ���̾�α��� DC
	 -# CWnd* pWnd: ���� ������Ʈ�� ������ Ŭ����
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
		 pDC->SetBkMode(TRANSPARENT);		//��� �����ϰ�
	 }
	 else if(nCtlColor == CTLCOLOR_LISTBOX)
	 {
		 pDC->SetBkColor(RGB(255, 255, 255));	//���� ����
	 }
	 else
	 {
		 if(nCtlColor == CTLCOLOR_BTN)
		 {
			 pDC->SetBkMode(TRANSPARENT);		//��� �����ϰ�			 
		 }
	 }

	 pDC->SetTextColor(RGB(255,255,255));
	
	 hbr = (HBRUSH)GetStockObject(NULL_BRUSH);

	 return hbr;
 }


 void CPuzzleProjectDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
 {
	 // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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
	 // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	 return FALSE;
	 //return CDialogEx::OnEraseBkgnd(pDC);
 }

 /**
   @fn OnSize
   @brief
      - ���̾�α� â Ȯ�� ��� �̺�Ʈ ó��

   @details
      -# �⺻ ��Ʈ�ѷ��� �̵� �� ���� ���� ũ�� ���� ���


   @param
     
   @return

   @par History
      - 2020/1/28: Created(sckim)
*/

 void CPuzzleProjectDlg::OnSize(UINT nType, int cx, int cy)
 {
	 CDialogEx::OnSize(nType, cx, cy);

	 // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	 if(m_bIsLoaded)
	 {
		 if(!m_pIndex)
		 {
			 return;
		 }

		 //�����Ҵ� ����
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
