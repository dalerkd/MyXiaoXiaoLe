#include "stdafx.h"
#include "XXL.h"
#include <stdlib.h>
#include <time.h>

CXXL::CXXL(void)
	:m_map_x(9),m_map_h(9),_MAP(nullptr),num_Block(6)
{
	Init();
}
CXXL::CXXL(int x/*��*/,int h/*��*/)
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


/*û���κζ���return false*/
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
				throw("������");
				break;
			}
		}
	}
	return work;
}

bool CXXL::PhyEngine()
{
	/*����
	ö�ٿ飺�ӵ�����2��-˳����һ�ſ�ʼ
	��׹

	Ҫ�ܽ�������������,ͨ��һ�䵽��
	***********
	*** *******
	*** *******

	*/
	bool work = false;
	if (m_map_h<3)
	{
		throw("PhyEngine: ��ͼ�߶�С��3,û����");
	}

	/*pai�ӵ����ڶ��ſ�ʼ*/
	for (int pai=(m_map_h-1-1)/*��*/,ThisPai/*�Ż��ڲ��ٶ�*/=(pai+1)/*next_pai*/*m_map_x;pai>=0;--pai,ThisPai-=m_map_x)
	{
		for (int lp/*��*/=0;lp<m_map_x;++lp)
		{/*�����ո�һ�䵽��*/

			const int di = m_map_h-1;
			/*next_pai�ӵ����ڶ��ŵ���һ�ſ�ʼ�������һ��*/
			for (int next_pai=pai+1,nowOffset/*��ǰƫ�Ƶ���һ��*/=ThisPai+lp;next_pai<=di;++next_pai,nowOffset+=m_map_x)
			{
				/*�� nowOffset ����"next_pai*m_map_x+lp"*/
				if (_MAP[nowOffset]==t_black)//����һ����Ϊ���򽻻�
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

bool CXXL::��鲢�������Ϲ����ģ��()
{
	/*
	Ҫ�������
	�ܲ�������?
	���ǿ��ԣ�
	ֻ���X�Ĳ��֣���ż�

	x0x0
	0x0x
	x0x0
	0x0x
	*/

	bool work = false;
	for (int hh=0;hh<m_map_h;++hh)
	{
		for (int lp=hh%2;lp<m_map_x;lp+=2)//Ϊ����ɰڶ�,����ͼ
		{

			//char middleValue = _MAP[lp*m_map_x+hh];
			char middleValue = _MAP[hh*m_map_x+lp];


			S_POINT FACK_P;
			FACK_P.x = lp;
			FACK_P.h = hh;

			char m_v = middleValue;//good value
			if (middleValue==t_black||middleValue==t_error)
			{
				throw("���������ֵ��������һ����������û��ִ�������");
			}
			char m_a=0,m_b=0,m_d=0,m_e=0,m_f=0,m_g=0,m_h=0,m_i=0;
			GetZVWW(FACK_P,m_a,m_b,m_d,m_e,m_g,m_f,m_h,m_i);


			/*�ҵ�һ�ֳɹ��������*/
			if (m_b==m_v&&m_a==m_v)
			{
				_MAP[hh*m_map_x+lp] = t_black;
				_MAP[hh*m_map_x+lp-1]=t_black;
				_MAP[hh*m_map_x+lp-2]=t_black;

				work = true;
				goto ����End;
				//break;
			}
			else if(m_b==m_v&&m_d==m_v)
			{
				_MAP[hh*m_map_x+lp] = t_black;
				_MAP[hh*m_map_x+lp-1] = t_black;
				_MAP[hh*m_map_x+lp+1] = t_black;

				work = true;
				goto ����End;
				//break;
			}
			else if(m_d==m_v&&m_e==m_v)
			{
				_MAP[hh*m_map_x+lp] = t_black;
				_MAP[hh*m_map_x+lp+1] = t_black;
				_MAP[hh*m_map_x+lp+2] = t_black;

				work = true;
				goto ����End;
				//break;
			}
			else if(m_g==m_v&&m_f==m_v)
			{
				_MAP[hh*m_map_x+lp] = t_black;
				_MAP[(hh-1)*m_map_x+lp] = t_black;
				_MAP[(hh-2)*m_map_x+lp] = t_black;

				work = true;
				goto ����End;
				//break;
			}
			else if (m_g==m_v&&m_h==m_v)
			{
				_MAP[hh*m_map_x+lp] = t_black;
				_MAP[(hh-1)*m_map_x+lp] = t_black;
				_MAP[(hh+1)*m_map_x+lp] = t_black;

				work = true;
				goto ����End;
				//break;
			}
			else if(m_h==m_v&&m_i==m_v)
			{
				_MAP[hh*m_map_x+lp] = t_black;
				_MAP[(hh+1)*m_map_x+lp] = t_black;
				_MAP[(hh+2)*m_map_x+lp] = t_black;

				work = true;
				goto ����End;
				//break;
			}
			else
			{
				continue;
			}
		}
	}
����End:

	return work;
}

bool CXXL::����(S_POINT m_a,S_POINT m_b)
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

	bool work = false;/*�Ƿ񽻻��ɹ�?*/
	/*

	**f**
	**g**
	abcde
	**h**
	**i**

	��ȡ���ǵ�ֵ
	*/
	S_POINT FACK_P = first;
	char m_v = fack_first;//good value

	char m_a=0,m_b=0,m_d=0,m_e=0,m_f=0,m_g=0,m_h=0,m_i=0;
	GetZVWW(FACK_P,m_a,m_b,m_d,m_e,m_g,m_f,m_h,m_i);

	/*�ҵ�һ�ֳɹ��������*/
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

			/*�ҵ�һ�ֳɹ��������*/
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

��ȡ���ǵ�ֵ
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
step 1: �Ƿ���Ҫ���?
step 2: �Ƿ���׹?

step 3: �Ƿ���Ҫ��?��ǰ�����ȶ��������,��ʼ������
��:goto step 1
����û����Ҫ����ʱ��

�����������߼�:������⣬�������߼��򽻻��ɹ�������ԭ��

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
			if (PhyEngine())//�ж�������Ҫ���¼��
			{
				//Display();
				continue;
			}
			else//��������û�ж������Ѿ��ȶ�
			{
				break;
			}

		}//while end

		if (��鲢�������Ϲ����ģ��())
		{
			//Display();
			continue;
		}
		else//���޿���
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
				throw("Display: ����ַ���ʲô��!");

				break;
			}

		}
		printf("\n");

	}
}

/*
Todo: ����ֻ����Start���������ʱ�򣬲ſ����С�


*/
bool CXXL::SwapBlock(S_POINT m_a,S_POINT m_b)
{
	/*
	���ݵĵ��������
	�����Ϸ����

	*/
	if (m_a.x<0||m_a.h<0||m_b.x<0||m_b.h<0||
		m_a.x>m_map_x-1||m_a.h>m_map_h-1||
		m_b.x>m_map_x-1||m_b.h>m_map_h-1
		)
	{
		throw("Swap: swap���ݳ�����Χ��");
	}

	if (!����(m_a,m_b))
	{
		throw("Swap: �����ٵĵ�");
	}

	/*
	ĳ������ΪX���ԣ���ĳ���ط���ĳ����������ܷ񴥷��¼�?
	*/
	if(!_TrySwapBlock(m_a,m_b))
	{
		return false;
	}
	else
	{
		/*
		�Ѿ��������
		����������
		*/
		Start();
		return true;
	}
}