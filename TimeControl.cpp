//------------------------------------------------------------------------
/**
   @file TimeControl.cpp
   @brief
      - 퍼즐 게임 시간을 관리 기능 구현
   
   @details
      -# 쓰레드 함수를 이용하여 대상 다이얼로그의 Edit에 시간을 출력하고
	     관리

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
      - 다이얼로그와 컨트롤러의 ID를 입력받는다.

   @details
      -# 시간을 출력할 다이얼로그와 출력될 해당 컨트롤의 아이디를 입력받는 기능

   @param
      -# CDialog* pDlg : 시간을 출력할 다이얼로그의 주소
	  -# int n_ID : 시간이 출력될 컨트롤의 아이디

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
      - 시간 쓰레드를 시작하는 기능

   @details
      -# 시간을 관리하는 쓰레드를 동작시키는 기능

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
      - 쓰레드의 상태를 지정하는 기능

   @details
      -# 플레이 상태에서 쓰레드를 중지시키는 기능

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
      - 쓰레드의 상태를 지정하는 기능

   @details
      -# 정지 상태에서 쓰레드를 다시 실행시키는 기능 

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
      - 쓰레드의 상태를 확인하는 기능

   @details
      -# 쓰레드가 초기 상태인지 확인하는 기능

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
      - 쓰레드의 상태를 확인하는 기능

   @details
      -# 쓰레드가 실행 상태인지 확인하는 기능

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
      - 쓰레드의 상태를 확인하는 기능

   @details
      -# 쓰레드가 정지 상태인지 확인하는 기능

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
      - 쓰레드 함수

   @details
      -# 쓰레드가 실행 상태일때 지속적으로 Edit Box에 시간을 출력하는 기능


   @param
      -# LPVOID __mothod : 쓰레드 함수를 제어하는 클래스의 주소

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
      - 쓰레드의 상태를 변경하는 기능

   @details
      -# 쓰레드 및 시간을 초기화 상태로 변경하는 기능


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