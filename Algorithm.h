//------------------------------------------------------------------------
/**
   @file Algorithm.h
   @brief
      - 퍼즐 이동 알고리즘 정의
   
   @details
      -# 퍼즐 좌표 초기화 및 섞거나 이동시키는 알고리즘 정의 
    
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
      - 퍼즐 조각의 좌표를 의미하는 구조체
         
     @param
      -# int x : 퍼즐 조각의 행을 의미하는 x좌표
	  -# int y : 퍼즐 조각의 열을 의미하는 y좌표
        
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
      - 퍼즐의 이동을 결정하는 알고리즘을 구현한 클래스
   
   @details
      -# 퍼즐 조각을 생성하고, 섞거나 이동 시키는 기능을 담당
    
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