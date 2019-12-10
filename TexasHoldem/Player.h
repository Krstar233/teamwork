#pragma once
#include "Desk.h"
#include "PokerHeap.h"
#include <string>
using namespace std;
/*
	玩家类：
		拥有手牌，能够下注，跟注，加注，让牌，弃牌
*/
class Player
{
	
	int betHasPut; //在一轮下注中，已经下的注的数目
	int money; //玩家拥有的注的数目
	bool out;
	PokerHeap handCard; //玩家手牌
	string Name;

public:
	Player();
	~Player();

	//下注
	void bet(Desk &desk, int num);

	//跟注
	void followBet(Desk &desk, int bet);

	//加注
	void addBet(Desk &desk, int bet, int num);

	//设置玩家名字
	void setName(string name);

	//获取玩家名字
	string getName();

	void setMoney(int money);

	//获取自己剩余的注(钱)
	int getMoney();

	void initHandCard();

	//重置out
	void initOut();

	//弃牌(退出当局游戏)
	void outGame();

	//返回是否以及弃牌
	bool isOut();

	//重置betHasPut
	void initBetHasPut();

	//将手中的牌排序
	void handCardSort();

	//将手牌展示（输出到控制台）
	void handCardShow();

	//返回手牌
	PokerHeap getHandCard();

	//返回手牌的引用
	PokerHeap& getCard();
};

