// test.j17.8.19.�ҵ�������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "XXL.h"

int _tmain(int argc, _TCHAR* argv[])
{
	try{

	CXXL* pCA = new CXXL();

	pCA->Start();


	while (true)
	{

		S_POINT first;
		S_POINT second;
		first.h = 0;
		first.x = 0;
		second.h= 0;
		second.x= 0;




		printf("������Ҫ���������ֵĵ�ַx h�����������������:' 0 2  0 3 '\r\n");
		scanf_s("%d%d %d%d",&first.x,&first.h,&second.x,&second.h);


		if(pCA->SwapBlock(first,second))
		{
			printf("�����ɹ�:)\n");
		}
		else
		{
			printf("����ʧ��\n");
		}

	}
			delete(pCA);
	}
	catch(char* s)
	{
		printf("�쳣:%s",s);
		
		getchar();

	}

	


	


	return 0;
}

