//------------------------------------------------------------------------
/**
   @file Algorithm.cpp
   @brief
      - ���� ��ǥ �� �̵� �˰��� ����
   
   @details
   -# ���� ������ ��ǥ �ʱ�ȭ �� ���̾�α׿��� START ��ư Ŭ�� �� ó�� ���� ���� ȭ�鿡��
      ���� ������ ���� �˰���� ��ư Ŭ�� �� ���� ������ �̵��ϴ� �˰��� ����
    
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
      - ���� ������ ��ǥ�� �����ϰ� �ʱ�ȭ�ϴ� �Լ�

   @details
      -# ���� ���̾�α׷� ���� ����� �Է� �޾� ����� �ش��ϴ�
		 ũ���� ���� ������ ��ǥ�� �����Ѵ�.

    @param
      -# int nSize : ���� ������ ����� �ǹ�

   @return
       - Index* : ������ ���� ������ ��ǥ�� ��ȯ

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
      - ���� ������ ���� �˰��� ���� 

   @details
      -# START ��ư�� Ŭ���Ǹ� �ʱ�ȭ�� ���� ������ ������ ��������
	     ��Ģ�� ���� ���� �˰��� ����

    @param
      -# Index* pIndex : ���� ���̾�α׷� ���� �Է¹޾� ���� ����� �Ǵ� ���� ������ ��ǥ�� �ǹ�
	  -# int& nGrayIndex :ȸ�� ���� ������ ��ǥ�� �ǹ�
	  -# int nSize : ������ ����� �ǹ�

   @return
       - BOOL : �˰��� ������ ������ ��ȯ

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
	case 0:		//����
		index.x = index.x - 1;
		break;
	case 1:		//����
		index.y = index.y + 1;
		break;
	case 2:		//����
		index.x = index.x + 1;
		break;
	case 3:		//����
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
      - ������ ��ǥ�� ��ȯ�ϴ� �˰��� ����

   @details
      -# ����ڰ� ���� ������ Ŭ������ �� ��Ģ�� ���� �Ǵ��Ͽ� ���� ������
	     �̵� ��Ű�� �˰��� ����

    @param
      -# Index* pIndex : ���� ���̾�α׷� ���� �Է¹޾� ���� ����� �Ǵ� ���� ������ ��ǥ�� �ǹ�
	  -# Index index : �̵� ��ų ���� ������ �ǹ�
	  -# int& nGrayIndex : ȸ�� ���� ������ ��ǥ�� �ǹ�
	  -# int nSize : ���� ������ ��ü ����� �ǹ�

   @return
       - BOOL : ���� ������ �̵� ���θ� ��ȯ

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
      - ������ �ϼ��� Ȯ���ϴ� ���

   @details
      -# ���� �ε��� ���� ������ �˻��Ͽ� �ϼ� ���θ� �����ϴ� ���

    @param
      -# Index* pIndex : ���� ���̾�α׷� ���� �Է¹޾� ���� ����� �Ǵ� ���� ������ ��ǥ�� �ǹ�
	  -# int nSize : ���� ������ ��ü ����� �ǹ�

   @return
       - BOOL : ���� �ϼ� ���θ� ��ȯ

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