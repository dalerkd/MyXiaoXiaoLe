#pragma once

struct S_POINT{
	int x;
	int h;
};

class CXXL
{
public:
	CXXL(void);
	CXXL(int x/*横*/,int h/*高*/);

	~CXXL(void);

public:
	void Start();

private:
	/*初始化存储位置*/
	void Init();
	/*销毁*/
	void End();

private:
	/*
	检查并按需添加新块在上方,
	false没有任何动作
	*/
	bool CheckAndAddNewBlock();
	/*
	物理引擎
	false没有任何动作
	*/
	bool PhyEngine();
	
	/*false没有任何动作*/
	bool 检查并消除符合规则的模块();
	//void 消除Block(S_POINT);

	
	int myabs(int x)
	{
		return x>0?x:-x;
	}
	bool 相临(S_POINT m_a,S_POINT m_b);

	/*
	在不改变原来的东西的基础上，做一个测试
	如果成功就去真实的完成这个修改

	！调用者自行保证合法检查
	*/
	bool _TrySwapBlock(S_POINT,S_POINT);

	/*获取周围的数据*/
	void GetZVWW(S_POINT FACK_P,
		char& a,char& b,
		char& d,char& e,
		char& g,char& f,
		char& h,char& i
		);

	//显示回调
	void Display();
public:
	
	bool SwapBlock(S_POINT,S_POINT);

private:
	const int num_Block;
public:
	enum BlockType{t_black=0,t_error=1/*墙壁*/,t_1=10,t_2,t_3,t_4,t_5,t_6};
private:
	int m_map_x;//地图宽
	int m_map_h;//地图高

	char* _MAP;//地图内存指针

};

