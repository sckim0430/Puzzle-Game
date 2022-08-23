//------------------------------------------------------------------------
/**
   @file TimeControl.h
   @brief
      - 퍼즐 게임 시간을 관리하는 파일
   
   @details
      -# 쓰레드 함수를 통해 퍼즐 게임의 동작 및 시간을 컨트롤하는 기능 구현
    
   @par History
      - 2020/1/20: Created(sckim)
*/

#pragma once
#include<time.h>
#include<afxwin.h>

//------------------------------------------------------------------------
/**
   @class CTimeControl
   @brief
      - 게임 시간을 관리하는 클래스
   
   @details
	  -# 쓰레드의 동작 제어를 통해 게임 시간을 제어
    
   @par History
      - 2020/1/20: Created(sckim)
*/

class CTimeControl
{
private:
/**
   @struct  CTime
   @brief
      - 퍼즐 게임의 각 동작 시점을 저장하는 구조체
         
     @param
      -# time_t TStartTime : 게임 시작 시간을 저장
      -# time_t TPauseTime : 일시 정지된 시점의 시간을 저장
	  -# time_t TResumeTime : 재시작된 시점의 시간을 저장
   @par History
      - 2020/1/20: Created(sckim)
*/
	struct CTime
	{
		time_t TStartTime;
		time_t TPauseTime;
		time_t TResumeTime;
	};

/**
   @enum EThreadStatus
   @brief
      - 게임의 상태를 저장한다.
         
   @param
      -# THREAD_INITAL : 게임의 시작 대기 상태를 의미
	  -# THREAD_PLAY : 게임의 실행 상태를 의미
	  -# THREAD_PAUSE : 게임의 일시 정지를 의미
        
   @par History
      - 2020/1/20: Created(sckim)
*/
	enum class EThreadStatus
	{
		THREAD_INITAL,		//초기 상태
		THREAD_PLAY,		//실행 상태
		THREAD_PAUSE		//일시 중지
	};

private:
	CTime m_time;
	EThreadStatus m_EThreadStatus;
	CWinThread *m_pThread;
	CDialog* m_pDlg;		//쓰레드를 동작시키도록 지시하는 다이얼로그
	int m_nID;				//쓰레드 동작을 지시하는 다이얼로그에 출력할 장치의 ID

private:
	static UINT ThreadFunction(LPVOID _mothod);

public:
	CTimeControl();
	~CTimeControl();
	BOOL IsThreadInIt();
	BOOL IsThreadPlay();
	BOOL IsThreadPause();
	void SetObjectItem(CDialog* pDlg,int n_ID);
	void StartThread();
	void SetPauseState();
	void SetResumeState();
	void SetThreadInIt();
};