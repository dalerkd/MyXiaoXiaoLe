// test.j17.8.19.我的消消乐.cpp : 定义控制台应用程序的入口点。
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




		printf("输入你要交换消消乐的地址x h横坐标和纵坐标例如:' 0 2  0 3 '\r\n");
		scanf_s("%d%d %d%d",&first.x,&first.h,&second.x,&second.h);


		if(pCA->SwapBlock(first,second))
		{
			printf("消除成功:)\n");
		}
		else
		{
			printf("消除失败\n");
		}

	}
			delete(pCA);
	}
	catch(char* s)
	{
		printf("异常:%s",s);
		
		getchar();

	}

	


	


	return 0;
}

