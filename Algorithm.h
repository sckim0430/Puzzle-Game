//------------------------------------------------------------------------
/**
   @file Algorithm.h
   @brief
      - ���� �̵� �˰��� ����
   
   @details
      -# ���� ��ǥ �ʱ�ȭ �� ���ų� �̵���Ű�� �˰��� ���� 
    
   @par History
      - 2020/1/21: Created(sckim)
*/

#pragma once
#include<time.h>
#include<stdlib.h>
#include<windows.h>


/**
   @struct  Index
   @brief
      - ���� ������ ��ǥ�� �ǹ��ϴ� ����ü
         
     @param
      -# int x : ���� ������ ���� �ǹ��ϴ� x��ǥ
	  -# int y : ���� ������ ���� �ǹ��ϴ� y��ǥ
        
   @par History
      - 2020/1/21: Created(sckim)
*/
static struct Index
{
	int x;
	int y;

	Index()
	{
		x=-1;
		y=-1;
	}
};

/**
   @class CAlgorithm
   @brief
      - ������ �̵��� �����ϴ� �˰����� ������ Ŭ����
   
   @details
      -# ���� ������ �����ϰ�, ���ų� �̵� ��Ű�� ����� ���
    
   @par History
      - 2020/1/21: Created(sckim)
*/

class CAlgorithm
{
public:
	CAlgorithm();
	~CAlgorithm();

	Index* CreateIndex(int nSize);
	BOOL SuffleObject(Index* pIndex,int& nGrayIndex, int nSize);
	BOOL ChageObject(Index* pIndex, Index index, int& nGrayIndex, int nSize);
	BOOL CheckObject(Index* pIndex,int nSize);
};