#include "stdafx.h"
#include "XXL.h"
#include <stdlib.h>
#include <time.h>

CXXL::CXXL(void)
	:m_map_x(9),m_map_h(9),_MAP(nullptr),num_Block(6)
{
	Init();
}
CXXL::CXXL(int x/*横*/,int h/*高*/)
	:m_map_x(x),m_map_h(h),_MAP(nullptr),num_Block(6)
{
	Init();
}
CXXL::~CXXL(void)
{
	End();
};

void CXXL::Init()
{
	if (_MAP==nullptr)
	{
		_MAP=new char[m_map_h*m_map_x]();
	}
	else
	{
		throw("Init: _MAP!=nullptr");
	}

	srand(time(0));
}

void CXXL::End()
{
	if (_MAP!=nullptr)
	{
		delete []_MAP;
		_MAP = nullptr;
	}

}


/*没有任何动作return false*/
bool CXXL::CheckAndAddNewBlock()
{
	bool work = false;
	
	for (int i=0;i<m_map_x;++i)
	{
		if (_MAP[i]==t_black)
		{
			work = true;
			char result = rand()%num_Block+1;
			switch (result)
			{
			case 1:
				{
					_MAP[i] = t_1;
					break;
				}
			case 2:
				{
					_MAP[i] = t_2;
					break;
				}
			case 3:
				{
					_MAP[i] = t_3;
					break;
				}
			case 4:
				{
					_MAP[i] = t_4;
					break;
				}
			case 5:
				{
					_MAP[i] = t_5;
					break;
				}
			case 6:
				{
					_MAP[i] = t_6;
					break;
				}
			default:
				throw("意外数");
				break;
			}
		}
	}
	return work;
}

bool CXXL::PhyEngine()
{
	/*重力
	枚举块：从倒数第2排-顺数第一排开始
	下坠

	要能解决下面这种情况,通过一落到底
	***********
	*** *******
	*** *******

	*/
	bool work = false;
	if (m_map_h<3)
	{
		throw("PhyEngine: 地图高度小于3,没法玩");
	}

	/*pai从倒数第二排开始*/
	for (int pai=(m_map_h-1-1)/*排*/,ThisPai/*优化内层速度*/=(pai+1)/*next_pai*/*m_map_x;pai>=0;--pai,ThisPai-=m_map_x)
	{
		for (int lp/*列*/=0;lp<m_map_x;++lp)
		{/*遇到空格一落到底*/

			const int di = m_map_h-1;
			/*next_pai从倒数第二排的下一排开始，即最后一排*/
			for (int next_pai=pai+1,nowOffset/*当前偏移的下一排*/=ThisPai+lp;next_pai<=di;++next_pai,nowOffset+=m_map_x)
			{
				/*用 nowOffset 代替"next_pai*m_map_x+lp"*/
				if (_MAP[nowOffset]==t_black)//下面一格子为空则交互
				{//swap
					work = true;

					_MAP[nowOffset] = _MAP[nowOffset-m_map_x];
					_MAP[nowOffset-m_map_x] = t_black;
				}
				else
				{
					break;
				}
			}//end for
		}// end for
	}//end for

	return work;

}

bool CXXL::检查并消除符合规则的模块()
{
	/*
	要检查容易
	能不能提速?
	答案是可以：
	只检查X的部分：奇偶差开

	x0x0
	0x0x
	x0x0
	0x0x
	*/

	bool work = false;
	for (int hh=0;hh<m_map_h;++hh)
	{
		for (int lp=hh%2;lp<m_map_x;lp+=2)//为了造成摆动,看上图
		{

			//char middleValue = _MAP[lp*m_map_x+hh];
			char middleValue = _MAP[hh*m_map_x+lp];


			S_POINT FACK_P;
			FACK_P.x = lp;
			FACK_P.h = hh;

			char m_v = middleValue;//good value
			if (middleValue==t_black||middleValue==t_error)
			{
				throw("真心意外的值啊，是上一步物理引擎没有执行完毕吗");
			}
			char m_a=0,m_b=0,m_d=0,m_e=0,m_f=0,m_g=0,m_h=0,m_i=0;
			GetZVWW(FACK_P,m_a,m_b,m_d,m_e,m_g,m_f,m_h,m_i);


			/*找到一种成功情况即可*/
			if (m_b==m_v&&m_a==m_v)
			{
				_MAP[hh*m_map_x+lp] = t_black;
				_MAP[hh*m_map_x+lp-1]=t_black;
				_MAP[hh*m_map_x+lp-2]=t_black;

				work = true;
				goto 消除End;
				//break;
			}
			else if(m_b==m_v&&m_d==m_v)
			{
				_MAP[hh*m_map_x+lp] = t_black;
				_MAP[hh*m_map_x+lp-1] = t_black;
				_MAP[hh*m_map_x+lp+1] = t_black;

				work = true;
				goto 消除End;
				//break;
			}
			else if(m_d==m_v&&m_e==m_v)
			{
				_MAP[hh*m_map_x+lp] = t_black;
				_MAP[hh*m_map_x+lp+1] = t_black;
				_MAP[hh*m_map_x+lp+2] = t_black;

				work = true;
				goto 消除End;
				//break;
			}
			else if(m_g==m_v&&m_f==m_v)
			{
				_MAP[hh*m_map_x+lp] = t_black;
				_MAP[(hh-1)*m_map_x+lp] = t_black;
				_MAP[(hh-2)*m_map_x+lp] = t_black;

				work = true;
				goto 消除End;
				//break;
			}
			else if (m_g==m_v&&m_h==m_v)
			{
				_MAP[hh*m_map_x+lp] = t_black;
				_MAP[(hh-1)*m_map_x+lp] = t_black;
				_MAP[(hh+1)*m_map_x+lp] = t_black;

				work = true;
				goto 消除End;
				//break;
			}
			else if(m_h==m_v&&m_i==m_v)
			{
				_MAP[hh*m_map_x+lp] = t_black;
				_MAP[(hh+1)*m_map_x+lp] = t_black;
				_MAP[(hh+2)*m_map_x+lp] = t_black;

				work = true;
				goto 消除End;
				//break;
			}
			else
			{
				continue;
			}
		}
	}
消除End:

	return work;
}

bool CXXL::相临(S_POINT m_a,S_POINT m_b)
{
	if (myabs(m_a.x-m_b.x)==1)
	{
		if (myabs(m_a.h-m_b.h)!=0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else if(myabs(m_a.x-m_b.x)==0)
	{
		if (myabs(m_a.h-m_b.h)!=1)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

bool CXXL::_TrySwapBlock(S_POINT first,S_POINT second)
{
	char firstValue =_MAP[first.h*m_map_x+first.x];
	char secondValue=_MAP[second.h*m_map_x+second.x];

	char fack_first = secondValue;
	char fack_second= firstValue;

	bool work = false;/*是否交互成功?*/
	/*

	**f**
	**g**
	abcde
	**h**
	**i**

	获取他们的值
	*/
	S_POINT FACK_P = first;
	char m_v = fack_first;//good value

	char m_a=0,m_b=0,m_d=0,m_e=0,m_f=0,m_g=0,m_h=0,m_i=0;
	GetZVWW(FACK_P,m_a,m_b,m_d,m_e,m_g,m_f,m_h,m_i);

	/*找到一种成功情况即可*/
	if ((m_b==m_v&&m_a==m_v)||(m_b==m_v&&m_d==m_v)||
		(m_d==m_v&&m_e==m_v)||(m_g==m_v&&m_f==m_v)||
		(m_g==m_v&&m_h==m_v)||(m_h==m_v&&m_i==m_v)
		)
	{
		work = true;
		char temp = _MAP[first.h*m_map_x+first.x];
		_MAP[first.h*m_map_x+first.x] = _MAP[second.h*m_map_x+second.x];
		_MAP[second.h*m_map_x+second.x] = temp;
	}
	else
	{
		/*S_POINT*/ FACK_P = second;
		/*char*/ m_v = fack_second;//good value
		{
			m_a=0,m_b=0,m_d=0,m_e=0,m_f=0,m_g=0,m_h=0,m_i=0;
			GetZVWW(FACK_P,m_a,m_b,m_d,m_e,m_g,m_f,m_h,m_i);

			/*找到一种成功情况即可*/
			if ((m_b==m_v&&m_a==m_v)||(m_b==m_v&&m_d==m_v)||
				(m_d==m_v&&m_e==m_v)||(m_g==m_v&&m_f==m_v)||
				(m_h==m_v&&m_i==m_v)
				)
			{
				work = true;
				char temp = _MAP[first.h*m_map_x+first.x];
				_MAP[first.h*m_map_x+first.x] = _MAP[second.h*m_map_x+second.x];
				_MAP[second.h*m_map_x+second.x] = temp;
			}
			else
			{
				work = false;
			}

		}


	}

	return work;
}


/*

**f**
**g**
abcde
**h**
**i**

获取他们的值
*/
void CXXL::GetZVWW(S_POINT FACK_P, char& m_a,char& m_b, char& m_d,char& m_e, char& m_g,char& m_f, char& m_h,char& m_i)
{
	if (FACK_P.x>0)
	{
		m_b = _MAP[FACK_P.h*m_map_x+FACK_P.x-1];
		if (FACK_P.x>1)
		{
			m_a = _MAP[FACK_P.h*m_map_x+FACK_P.x-2];
		}
		else
		{
			m_a = t_error;
		}
	}
	else
	{
		m_b = t_error;
		m_a = t_error;
	}

	if (FACK_P.x<m_map_x-1)
	{
		m_d = _MAP[FACK_P.h*m_map_x+FACK_P.x+1];
		if (FACK_P.x<m_map_x-2)
		{
			m_e = _MAP[FACK_P.h*m_map_x+FACK_P.x-2];
		}
		else
		{
			m_e = t_error;
		}
	}
	else
	{
		m_d = t_error;
		m_e = t_error;
	}

	if (FACK_P.h>0)
	{
		m_g = _MAP[(FACK_P.h-1)*m_map_x+FACK_P.x];
		if (FACK_P.h>1)
		{
			m_f = _MAP[(FACK_P.h-2)*m_map_x+FACK_P.x];
		}
		else
		{
			m_f = t_error;
		}
	}
	else
	{
		m_g = t_error;
		m_f = t_error;
	}

	if (FACK_P.h<m_map_h-1)
	{
		m_h = _MAP[(FACK_P.h+1)*m_map_x+FACK_P.x];
		if (FACK_P.h<m_map_h-2)
		{
			m_i = _MAP[(FACK_P.h+2)*m_map_x+FACK_P.x];
		}
		else
		{
			m_i = t_error;
		}
	}
	else
	{
		m_h = t_error;
		m_i = t_error;
	}

}

/*
step 1: 是否需要填充?
step 2: 是否下坠?

step 3: 是否需要消?当前两者稳定的情况下,开始触发。
消:goto step 1
至到没有需要消的时候。

交互触发消逻辑:单独检测，构成消逻辑则交换成功，否则复原。

*/
void CXXL::Start()
{
	Display();
	for(;;)
	{

		while(true)
		{
			if(CheckAndAddNewBlock())
			{
				//Display();
			}
			if (PhyEngine())//有动作则需要重新检查
			{
				//Display();
				continue;
			}
			else//物理引擎没有动作：已经稳定
			{
				break;
			}

		}//while end

		if (检查并消除符合规则的模块())
		{
			//Display();
			continue;
		}
		else//消无可消
		{
			Display();
			break;
		}
	}//for end


}

void CXXL::Display()
{
	//[m_map_h*m_map_x];
	system("cls");
	printf("X012345678\n");
	for (int h=0;h<m_map_h;++h)
	{
		printf("%d",h);
		for (int x=0;x<m_map_x;++x)
		{
			char it = _MAP[h*m_map_x+x];
			switch (it)
			{
			case t_black:
				printf("%c",0x0);
				break;
			case t_1:
				printf("%c",0x1);
				break;
			case t_2:
				printf("%c",0x2);
				break;
			case t_3:
				printf("%c",0x3);
				break;
			case t_4:
				printf("%c",0x4);
				break;
			case t_5:
				printf("%c",0x5);
				break;
			case t_6:
				printf("%c",0x6);
				break;
			default:
				printf("Bad error:0x%x",it);
				throw("Display: 这个字符是什么鬼!");

				break;
			}

		}
		printf("\n");

	}
}

/*
Todo: 警告只有在Start引擎结束的时候，才可运行。


*/
bool CXXL::SwapBlock(S_POINT m_a,S_POINT m_b)
{
	/*
	操纵的点必须相临
	其他合法检查

	*/
	if (m_a.x<0||m_a.h<0||m_b.x<0||m_b.h<0||
		m_a.x>m_map_x-1||m_a.h>m_map_h-1||
		m_b.x>m_map_x-1||m_b.h>m_map_h-1
		)
	{
		throw("Swap: swap内容超过范围啦");
	}

	if (!相临(m_a,m_b))
	{
		throw("Swap: 不相临的点");
	}

	/*
	某点设置为X测试：在某个地方用某数据替代，能否触发事件?
	*/
	if(!_TrySwapBlock(m_a,m_b))
	{
		return false;
	}
	else
	{
		/*
		已经交互完成
		启动引擎们
		*/
		Start();
		return true;
	}
}