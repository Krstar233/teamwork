#include <iostream>
#include <string>

#include "TexasHoldemGame.h"
#include "PokerHeap.h"
using namespace std;

void printStartVeiw();
void game();
void pokerheapTest();
void gameTest();

int main() {

	//game();

	gameTest();

	//pokerheapTest();
}


void printStartVeiw() {
	cout << "*****欢迎来到德州扑克******" << endl;
	cout << "      是否开始游戏？" << endl;
	cout << "          (Y/N)" << endl;
	cout << "**************************" << endl;
}
void game() {
	TexasHoldemGame game; //德州扑克游戏对象
	string cmd; //输入的对德州扑克游戏操作的命令
	int n; //参与玩家的人数

	printStartVeiw();
	cin >> cmd;

	if (cmd == "Y" || cmd == "y") {
		cout << "请输入玩家个数：";
		cin >> n;
		game.start(n);
	}
	while (cmd == "Y" || cmd == "y") {
		cout << "继续游戏？(Y/N):" << endl;
		cin >> cmd;
		if (cmd == "Y" || cmd == "y") {
			game.continueGame();
		}
		else
			break;
	}
	cout << "游戏结束！" << endl;
	game.endGame();
}

void pokerheapTest()
{
	PokerHeap pok;
	pok.init();
	pok.show();
	cout << "合计：" << pok.getSize() << "张" << endl;
	cout << "======================================" << endl;
	pok.upset();
	pok.show();
	cout << "合计：" << pok.getSize() << "张" << endl;
	cout << "======================================" << endl;
	pok.sort();
	pok.show();
	cout << "合计：" << pok.getSize() << "张" << endl;

	Poker poker1("黑桃", "J");
	Poker poker2("红桃", "Q");
	if (poker1 < poker2) {
		poker1.show(); cout << " < "; poker2.show(); cout << endl;
	}
}

void gameTest()
{
	TexasHoldemGame game;
	game.GameTest(5);
}
