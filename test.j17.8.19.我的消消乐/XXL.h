#pragma once

struct S_POINT{
	int x;
	int h;
};

class CXXL
{
public:
	CXXL(void);
	CXXL(int x/*��*/,int h/*��*/);

	~CXXL(void);

public:
	void Start();

private:
	/*��ʼ���洢λ��*/
	void Init();
	/*����*/
	void End();

private:
	/*
	��鲢��������¿����Ϸ�,
	falseû���κζ���
	*/
	bool CheckAndAddNewBlock();
	/*
	��������
	falseû���κζ���
	*/
	bool PhyEngine();
	
	/*falseû���κζ���*/
	bool ��鲢�������Ϲ����ģ��();
	//void ����Block(S_POINT);

	
	int myabs(int x)
	{
		return x>0?x:-x;
	}
	bool ����(S_POINT m_a,S_POINT m_b);

	/*
	�ڲ��ı�ԭ���Ķ����Ļ����ϣ���һ������
	����ɹ���ȥ��ʵ���������޸�

	�����������б�֤�Ϸ����
	*/
	bool _TrySwapBlock(S_POINT,S_POINT);

	/*��ȡ��Χ������*/
	void GetZVWW(S_POINT FACK_P,
		char& a,char& b,
		char& d,char& e,
		char& g,char& f,
		char& h,char& i
		);

	//��ʾ�ص�
	void Display();
public:
	
	bool SwapBlock(S_POINT,S_POINT);

private:
	const int num_Block;
public:
	enum BlockType{t_black=0,t_error=1/*ǽ��*/,t_1=10,t_2,t_3,t_4,t_5,t_6};
private:
	int m_map_x;//��ͼ��
	int m_map_h;//��ͼ��

	char* _MAP;//��ͼ�ڴ�ָ��

};

