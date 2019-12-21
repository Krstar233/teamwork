#include "TexasHoldemGame.h"
#include <iostream>
#include <string>
using namespace std;

void TexasHoldemGame::round(queue<Player*> &playersNeedtoBet)
{
	int lastBetNum = 0;
	queue<Player*> playerBeted;
	while (!playersNeedtoBet.empty()) {
		int cmd;
		Player *player = playersNeedtoBet.front(); playersNeedtoBet.pop();
		cout << "轮到玩家：" << player->getName() << endl;

		//本轮之前没人下注时
		if (lastBetNum == 0) {
			cout << "你可以选择 1.下注 2.让牌 3.弃牌 (请输入序号)：";
			while (cin >> cmd) {
				if (cmd == 1) {
					cout << "请输入下注值: ";
					int bet;
					while (cin >> bet && (bet <= 0 || bet > player->getMoney()))	cout << "请输入正确的值" << endl;
					player->bet(desk, bet);
					lastBetNum = bet;
					cout << "已下注 $" << bet << ", 剩余注：$" << player->getMoney() << endl;
					playerBeted.push(player);
					break;
				}
				else if (cmd == 2) {
					playersNeedtoBet.push(player);
					cout << "已让牌。" << endl;
					break;
				}
				else if (cmd == 3) {
					player->outGame();
					cout << "已弃牌。" << endl;
					break;
				}
				cout << "请输入正确的序号：";
			}
			continue;
		}

		//本轮有人下注后
		cout << "你可以选择 1.跟注 2.加注 3.弃牌 (请输入序号)：";
		while (cin >> cmd) {
			if (cmd == 1) {
				player->followBet(desk, lastBetNum);
				cout << "已跟注。" << endl;
				playerBeted.push(player);
				break;
			}
			else if (cmd == 2) {
				int num;
				cout << "请输入加注数额：";
				cin >> num;
				player->addBet(desk, lastBetNum, num);
				lastBetNum += num;
				cout << "已加注，剩余注：$" << player->getMoney() << endl;
				while (!playerBeted.empty()) {
					playersNeedtoBet.push(playerBeted.front());
					playerBeted.pop();
				}
				break;
			}
			else if (cmd == 3) {
				player->outGame();
				cout << "已弃牌。" << endl;
				break;
			}
			cout << "请输入正确的序号：";
		}
	}
}

void TexasHoldemGame::firstRound()
{
	queue<Player*> q;
	for (int i = 0; i < players.size(); i++) {
		int k = (i + 2) % players.size();
		players[k].initBetHasPut();
		q.push(&players[k]);
	}
	round(q);
}

void TexasHoldemGame::otherRound()
{
	queue<Player*> q;
	for (int i = 0; i < players.size(); i++) {
		if (!players[i].isOut()) {
			players[i].initBetHasPut();
			q.push(&players[i]);
		}
	}
	round(q);
}

void TexasHoldemGame::judgeWin()
{
	banker.distributeReward(players, desk);
}

TexasHoldemGame::TexasHoldemGame()
{
}

void TexasHoldemGame::start(int personNum)
{
	/*
	args:
	personNum,玩家的人数
	*/

	//初始化游戏信息:
	//banker = Banker();
	cout << "请输入玩家昵称:" << endl;
	for (int i = 0; i < personNum; i++) {
		Player player;
		string name;
		cout << "玩家" << i + 1 << "：";
		cin >> name;
		player.setName(name);
		player.setMoney(10000);
		players.push_back(player);
	}
	desk = Desk();
	continueGame();
}
void TexasHoldemGame::continueGame()
{
	cout << "游戏开始" << endl;

	//重置弃牌玩家
	for (int i = 0; i < players.size(); i++)
	{
		players[i].initOut();
		players[i].clearHandCard();
	}

	//重载桌面(牌局)
	desk.init();
	desk.clearPublicPoker();

	//重置牌堆
	pokerHeap.init();

	//强制下大小盲注
	players[0].bet(desk, 1);
	cout << "玩家：" << players[0].getName() << "下了小盲注 $1" << endl;
	players[1].bet(desk, 2);
	cout << "玩家：" << players[1].getName() << "下了大盲注 $2" << endl;

	//庄家给每名玩家发牌
	banker.licensing(players, pokerHeap);
	cout << "发牌完毕." << endl;

	//把每名玩家的手牌排序
	for (int i = 0; i < players.size(); i++) {
		players[i].handCardSort();
	}

	//第一轮下注
	cout << "第一轮下注：" << endl;
	firstRound();

	//庄家发3张公共牌
	cout << "庄家发了3张公共牌" << endl;
	banker.licensingPublicCard(desk, pokerHeap, 3);

	//公共牌堆排序
	desk.publicPokerSort();
	desk.publicPokerShow();

	//第二轮下注
	cout << "第二轮下注：" << endl;
	otherRound();

	//庄家发1张公共牌
	cout << "庄家发了1张公共牌：" << endl;
	banker.licensingPublicCard(desk, pokerHeap, 1);

	//公共牌堆排序
	desk.publicPokerSort();
	desk.publicPokerShow();

	//第三轮下注
	cout << "第三轮下注：" << endl;
	otherRound();

	//庄家发最后一张公共牌
	cout << "庄家发了最后一张公共牌：" << endl;
	banker.licensingPublicCard(desk, pokerHeap, 1);

	//公共牌堆排序
	desk.publicPokerSort();
	desk.publicPokerShow();

	//最后一轮下注
	cout << "最后一轮下注:" << endl;
	otherRound();

	//最终比牌判断输赢，玩家获得奖池
	judgeWin();
	
	cout << "本回游戏结束" << endl;
}

void TexasHoldemGame::GameTest(int playerNum)
{
	for (int i = 0; i < playerNum; i++) {
		Player player;
		string name = "玩家" + to_string(i + 1);
		player.setName(name);
		player.setMoney(10000);
		players.push_back(player);
	}
	desk = Desk();
	while (true) {
		cout << "游戏开始" << endl;

		//重置弃牌玩家
		for (int i = 0; i < players.size(); i++) {
			players[i].clearHandCard();
			players[i].initOut();
		}
		//重载桌面(牌局)
		desk.init();
		desk.clearPublicPoker();

		//重置牌堆
		pokerHeap.init();

		//庄家给每名玩家发牌
		banker.licensing(players, pokerHeap);
		cout << "发牌完毕." << endl;

		//把每名玩家的手牌排序
		for (int i = 0; i < players.size(); i++) {
			players[i].handCardSort();
		}

		//庄家发3张公共牌
		cout << "庄家发了3张公共牌" << endl;
		banker.licensingPublicCard(desk, pokerHeap, 3);

		//公共牌堆排序
		desk.publicPokerSort();
		desk.publicPokerShow();

		//庄家发1张公共牌
		cout << "庄家发了1张公共牌：" << endl;
		banker.licensingPublicCard(desk, pokerHeap, 1);

		//公共牌堆排序
		desk.publicPokerSort();
		desk.publicPokerShow();

		//庄家发最后一张公共牌
		cout << "庄家发了最后一张公共牌：" << endl;
		banker.licensingPublicCard(desk, pokerHeap, 1);

		//公共牌堆排序
		desk.publicPokerSort();
		desk.publicPokerShow();

		//最终比牌判断输赢，玩家获得奖池
		judgeWin();

		cout << "本回游戏结束...按任意键继续测试.." << endl;
		getchar();
		for (int i = 0; i < 25; i++)
			cout << "-";
		cout << endl;
	}
}

void TexasHoldemGame::endGame()
{
}

TexasHoldemGame::~TexasHoldemGame()
{
}
