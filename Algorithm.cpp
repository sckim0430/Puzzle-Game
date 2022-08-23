//------------------------------------------------------------------------
/**
   @file Algorithm.cpp
   @brief
      - 퍼즐 좌표 및 이동 알고리즘 구현
   
   @details
   -# 퍼즐 조각의 좌표 초기화 및 다이얼로그에서 START 버튼 클릭 시 처음 퍼즐 정답 화면에서
      퍼즐 조각을 섞는 알고리즘과 버튼 클릭 시 퍼즐 조각이 이동하는 알고리즘 구현
    
   @par History
      - 2020/1/21: Created(sckim)
*/

#include"Algorithm.h"

CAlgorithm::CAlgorithm()
{
	srand(time(NULL));
}

CAlgorithm::~CAlgorithm()
{
}

/**
   @fn CreateIndex
   @brief
      - 퍼즐 조각의 좌표를 생성하고 초기화하는 함수

   @details
      -# 메인 다이얼로그로 부터 사이즈를 입력 받아 사이즈에 해당하는
		 크기의 퍼즐 조각의 좌표를 생성한다.

    @param
      -# int nSize : 퍼즐 조각의 사이즈를 의미

   @return
       - Index* : 생성된 퍼즐 조각의 좌표를 반환

   @par History
      - 2020/1/21: Created(sckim)
*/
Index* CAlgorithm::CreateIndex(int nSize)
{
	Index* pIndex;

	pIndex = new Index[nSize * nSize];

	for(int x=0;x<nSize;x++)
	{
		for(int y=0;y<nSize;y++)
		{
			pIndex[x*nSize+y].x =x;
			pIndex[x*nSize+y].y =y;
		}
	}

	return pIndex;
}

/**
   @fn SuffleObject
   @brief
      - 퍼즐 조각을 섞는 알고리즘 구현 

   @details
      -# START 버튼이 클릭되면 초기화된 퍼즐 조각을 임의의 방향으로
	     규칙에 의해 섞는 알고리즘 구현

    @param
      -# Index* pIndex : 메인 다이얼로그로 부터 입력받아 섞을 대상이 되는 퍼즐 조각의 좌표를 의미
	  -# int& nGrayIndex :회색 퍼즐 조각의 좌표를 의미
	  -# int nSize : 퍼즐의 사이즈를 의미

   @return
       - BOOL : 알고리즘 실행의 유무를 반환

   @par History
      - 2020/01/21: Created(sckim)
*/
BOOL CAlgorithm::SuffleObject(Index* pIndex, int& nGrayIndex, int nSize)
{
	int	nRandom = rand()%4;
	Index index;
	BOOL bIsShuffled = FALSE;
	
	if(!pIndex || nGrayIndex < 0 || nGrayIndex >= nSize*nSize)
	{
		return bIsShuffled;
	}

	index.x = nGrayIndex/nSize;
	index.y = nGrayIndex%nSize;

	switch(nRandom)
	{
	case 0:		//상향
		index.x = index.x - 1;
		break;
	case 1:		//우향
		index.y = index.y + 1;
		break;
	case 2:		//하향
		index.x = index.x + 1;
		break;
	case 3:		//좌향
		index.y = index.y-1;
		break;
	default:
		break;
	}
	
	if(index.x>=0 && index.x < nSize && index.y>=0 && index.y < nSize)
	{
		Index temp;
		
		temp = pIndex[nGrayIndex];
		pIndex[nGrayIndex] = pIndex[index.x*nSize+index.y];
		pIndex[index.x*nSize+index.y] = temp;

		nGrayIndex = index.x*nSize+index.y;
		
		bIsShuffled= TRUE;
	}
	
	return bIsShuffled;
}

/**
   @fn ChangeObject
   @brief
      - 퍼즐의 좌표를 교환하는 알고리즘 구현

   @details
      -# 사용자가 퍼즐 조각을 클릭했을 때 규칙에 의해 판단하여 퍼즐 조각을
	     이동 시키는 알고리즘 구현

    @param
      -# Index* pIndex : 메인 다이얼로그로 부터 입력받아 섞을 대상이 되는 퍼즐 조각의 좌표를 의미
	  -# Index index : 이동 시킬 퍼즐 조각을 의미
	  -# int& nGrayIndex : 회색 퍼즐 조각의 좌표를 의미
	  -# int nSize : 퍼즐 조각의 전체 사이즈를 의미

   @return
       - BOOL : 퍼즐 조각의 이동 여부를 반환

   @par History
      - 2020/01/21: Created(sckim)
*/
BOOL CAlgorithm::ChageObject(Index* pIndex, Index index, int& nGrayIndex, int nSize)
{
	BOOL bIsChanged = FALSE;
	
	if(!pIndex || nGrayIndex < 0 || nGrayIndex >= nSize*nSize)
	{
		return bIsChanged;
	}

	if(abs(nGrayIndex/nSize - index.x)+ 
		abs(nGrayIndex%nSize - index.y) == 1)
	{
		Index temp;

		temp = pIndex[nGrayIndex];
		pIndex[nGrayIndex] = pIndex[index.x *nSize+index.y];
		pIndex[index.x *nSize+index.y] = temp;

		bIsChanged = TRUE;

		return bIsChanged;
	}

	return bIsChanged;
}

/**
   @fn CheckObject
   @brief
      - 퍼즐의 완성을 확인하는 기능

   @details
      -# 퍼즐 인덱스 내의 순서를 검사하여 완성 여부를 판정하는 기능

    @param
      -# Index* pIndex : 메인 다이얼로그로 부터 입력받아 섞을 대상이 되는 퍼즐 조각의 좌표를 의미
	  -# int nSize : 퍼즐 조각의 전체 사이즈를 의미

   @return
       - BOOL : 퍼즐 완성 여부를 반환

   @par History
      - 2020/01/23: Created(sckim)
*/

BOOL CAlgorithm::CheckObject(Index* pIndex,int nSize)
{
	BOOL bIsCompleted = FALSE;
	
	for(int x=0;x<nSize;x++)
	{
		for(int y=0;y<nSize;y++)
		{
			int nX = pIndex[x*nSize+y].x;
			int nY = pIndex[x*nSize+y].y;

			if((nX*nSize+nY) != (x*nSize+y))
			{
				return bIsCompleted;
			}
		}
	}

	bIsCompleted=TRUE;

	return bIsCompleted;
}