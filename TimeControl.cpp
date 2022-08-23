//------------------------------------------------------------------------
/**
   @file TimeControl.cpp
   @brief
      - ���� ���� �ð��� ���� ��� ����
   
   @details
      -# ������ �Լ��� �̿��Ͽ� ��� ���̾�α��� Edit�� �ð��� ����ϰ�
	     ����

   @par History
      - 2020/1/20: Created(sckim)
*/

#include"TimeControl.h"

CTimeControl::CTimeControl()
{
	m_time.TPauseTime = 0;
	m_time.TResumeTime = 0;
	m_time.TStartTime = 0;
	
	m_EThreadStatus = EThreadStatus::THREAD_INITAL;
	m_pThread=NULL;
}

CTimeControl::~CTimeControl()
{
	if(m_pThread)
	{
		delete[] m_pThread;
		m_pThread = NULL;
	}
}


/**
   @fn SetObjectItem
   @brief
      - ���̾�α׿� ��Ʈ�ѷ��� ID�� �Է¹޴´�.

   @details
      -# �ð��� ����� ���̾�α׿� ��µ� �ش� ��Ʈ���� ���̵� �Է¹޴� ���

   @param
      -# CDialog* pDlg : �ð��� ����� ���̾�α��� �ּ�
	  -# int n_ID : �ð��� ��µ� ��Ʈ���� ���̵�

   @return
    

   @par History
      - 2020/1/20: Created(sckim)
*/

void CTimeControl::SetObjectItem(CDialog* pDlg,int n_ID)
{
	m_pDlg = pDlg;
	m_nID = n_ID;

	return;
}

/**
   @fn StartThread
   @brief
      - �ð� �����带 �����ϴ� ���

   @details
      -# �ð��� �����ϴ� �����带 ���۽�Ű�� ���

   @param
     

   @return
    

   @par History
      - 2020/1/20: Created(sckim)
*/

void CTimeControl::StartThread()
{
	m_time.TStartTime = clock();

	m_EThreadStatus = EThreadStatus::THREAD_PLAY;
	m_pThread = AfxBeginThread(ThreadFunction,this);
	m_pThread->m_bAutoDelete = FALSE;

	return;
}

/**
   @fn SetPauseState
   @brief
      - �������� ���¸� �����ϴ� ���

   @details
      -# �÷��� ���¿��� �����带 ������Ű�� ���

   @param
     

   @return
    

   @par History
      - 2020/1/20: Created(sckim)
*/

void CTimeControl::SetPauseState()
{
	m_time.TPauseTime += clock();
	m_EThreadStatus = EThreadStatus::THREAD_PAUSE;
	m_pThread->SuspendThread();

	return;
}

/**
   @fn SetResumeState
   @brief
      - �������� ���¸� �����ϴ� ���

   @details
      -# ���� ���¿��� �����带 �ٽ� �����Ű�� ��� 

   @param
     

   @return
    

   @par History
      - 2020/1/20: Created(sckim)
*/

void CTimeControl::SetResumeState()
{
	m_time.TResumeTime += clock();
	m_EThreadStatus = EThreadStatus::THREAD_PLAY;
	m_pThread->ResumeThread();

	return;
}

/**
   @fn IsThreadInIt
   @brief
      - �������� ���¸� Ȯ���ϴ� ���

   @details
      -# �����尡 �ʱ� �������� Ȯ���ϴ� ���

   @param
     

   @return
    

   @par History
      - 2020/1/20: Created(sckim)
*/

BOOL CTimeControl::IsThreadInIt()
{
	if(m_EThreadStatus == EThreadStatus::THREAD_INITAL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/**
   @fn IsThreadPlay
   @brief
      - �������� ���¸� Ȯ���ϴ� ���

   @details
      -# �����尡 ���� �������� Ȯ���ϴ� ���

   @param
     

   @return
    

   @par History
      - 2020/1/20: Created(sckim)
*/

BOOL CTimeControl::IsThreadPlay()
{
	if(m_EThreadStatus == EThreadStatus::THREAD_PLAY)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/**
   @fn IsThreadPause
   @brief
      - �������� ���¸� Ȯ���ϴ� ���

   @details
      -# �����尡 ���� �������� Ȯ���ϴ� ���

   @param
     

   @return
    

   @par History
      - 2020/1/20: Created(sckim)
*/

BOOL CTimeControl::IsThreadPause()
{
	if(m_EThreadStatus == EThreadStatus::THREAD_PAUSE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/**
   @fn ThreadFunction
   @brief
      - ������ �Լ�

   @details
      -# �����尡 ���� �����϶� ���������� Edit Box�� �ð��� ����ϴ� ���


   @param
      -# LPVOID __mothod : ������ �Լ��� �����ϴ� Ŭ������ �ּ�

   @return
    

   @par History
      - 2020/1/20: Created(sckim)
*/

UINT CTimeControl::ThreadFunction(LPVOID __mothod)
{
	CTimeControl *pDlg = (CTimeControl*)__mothod;

	while(pDlg->m_EThreadStatus == EThreadStatus::THREAD_PLAY)
	{
		CRect rc;
		(pDlg->m_pDlg)->GetDlgItem(pDlg->m_nID)->GetWindowRect(&rc);
		(pDlg->m_pDlg)->ScreenToClient(&rc);
		(pDlg->m_pDlg)->InvalidateRect(rc);
		(pDlg->m_pDlg)->SetDlgItemInt(pDlg->m_nID,(int)(clock() - pDlg->m_time.TStartTime - (pDlg->m_time.TResumeTime - pDlg->m_time.TPauseTime))/CLOCKS_PER_SEC);		
		Sleep(150);
	}

	return 0;
}

/**
   @fn SetThreadInIt
   @brief
      - �������� ���¸� �����ϴ� ���

   @details
      -# ������ �� �ð��� �ʱ�ȭ ���·� �����ϴ� ���


   @param
     

   @return
    

   @par History
      - 2020/1/23: Created(sckim)
*/

void CTimeControl::SetThreadInIt()
{
	if(m_pThread)
	{
		m_pThread->SuspendThread();

		DWORD dwResult;
		::GetExitCodeThread(m_pThread->m_hThread,&dwResult);

		if(m_pThread)
		{
			delete[] m_pThread;
			m_pThread = NULL;
		}

		m_EThreadStatus = EThreadStatus::THREAD_INITAL;

		m_time.TStartTime = m_time.TPauseTime = m_time.TResumeTime =0;
	}
	else
	{
		AfxMessageBox(_T("Thread Not Start!!"));
	}

	return;
}