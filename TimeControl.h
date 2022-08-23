//------------------------------------------------------------------------
/**
   @file TimeControl.h
   @brief
      - ���� ���� �ð��� �����ϴ� ����
   
   @details
      -# ������ �Լ��� ���� ���� ������ ���� �� �ð��� ��Ʈ���ϴ� ��� ����
    
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
      - ���� �ð��� �����ϴ� Ŭ����
   
   @details
	  -# �������� ���� ��� ���� ���� �ð��� ����
    
   @par History
      - 2020/1/20: Created(sckim)
*/

class CTimeControl
{
private:
/**
   @struct  CTime
   @brief
      - ���� ������ �� ���� ������ �����ϴ� ����ü
         
     @param
      -# time_t TStartTime : ���� ���� �ð��� ����
      -# time_t TPauseTime : �Ͻ� ������ ������ �ð��� ����
	  -# time_t TResumeTime : ����۵� ������ �ð��� ����
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
      - ������ ���¸� �����Ѵ�.
         
   @param
      -# THREAD_INITAL : ������ ���� ��� ���¸� �ǹ�
	  -# THREAD_PLAY : ������ ���� ���¸� �ǹ�
	  -# THREAD_PAUSE : ������ �Ͻ� ������ �ǹ�
        
   @par History
      - 2020/1/20: Created(sckim)
*/
	enum class EThreadStatus
	{
		THREAD_INITAL,		//�ʱ� ����
		THREAD_PLAY,		//���� ����
		THREAD_PAUSE		//�Ͻ� ����
	};

private:
	CTime m_time;
	EThreadStatus m_EThreadStatus;
	CWinThread *m_pThread;
	CDialog* m_pDlg;		//�����带 ���۽�Ű���� �����ϴ� ���̾�α�
	int m_nID;				//������ ������ �����ϴ� ���̾�α׿� ����� ��ġ�� ID

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