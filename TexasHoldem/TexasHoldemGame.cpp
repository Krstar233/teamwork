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
		cout << "�ֵ���ң�" << player->getName() << endl;

		//����֮ǰû����עʱ
		if (lastBetNum == 0) {
			cout << "�����ѡ�� 1.��ע 2.���� 3.���� (���������)��";
			while (cin >> cmd) {
				if (cmd == 1) {
					cout << "��������עֵ: ";
					int bet;
					while (cin >> bet && (bet <= 0 || bet > player->getMoney()))	cout << "��������ȷ��ֵ" << endl;
					player->bet(desk, bet);
					lastBetNum = bet;
					cout << "����ע $" << bet << ", ʣ��ע��$" << player->getMoney() << endl;
					playerBeted.push(player);
					break;
				}
				else if (cmd == 2) {
					playersNeedtoBet.push(player);
					cout << "�����ơ�" << endl;
					break;
				}
				else if (cmd == 3) {
					player->outGame();
					cout << "�����ơ�" << endl;
					break;
				}
				cout << "��������ȷ����ţ�";
			}
			continue;
		}

		//����������ע��
		cout << "�����ѡ�� 1.��ע 2.��ע 3.���� (���������)��";
		while (cin >> cmd) {
			if (cmd == 1) {
				player->followBet(desk, lastBetNum);
				cout << "�Ѹ�ע��" << endl;
				playerBeted.push(player);
				break;
			}
			else if (cmd == 2) {
				int num;
				cout << "�������ע���";
				cin >> num;
				player->addBet(desk, lastBetNum, num);
				lastBetNum += num;
				cout << "�Ѽ�ע��ʣ��ע��$" << player->getMoney() << endl;
				while (!playerBeted.empty()) {
					playersNeedtoBet.push(playerBeted.front());
					playerBeted.pop();
				}
				break;
			}
			else if (cmd == 3) {
				player->outGame();
				cout << "�����ơ�" << endl;
				break;
			}
			cout << "��������ȷ����ţ�";
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
	personNum,��ҵ�����
	*/

	//��ʼ����Ϸ��Ϣ:
	//banker = Banker();
	cout << "����������ǳ�:" << endl;
	for (int i = 0; i < personNum; i++) {
		Player player;
		string name;
		cout << "���" << i + 1 << "��";
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
	cout << "��Ϸ��ʼ" << endl;

	//�����������
	for (int i = 0; i < players.size(); i++)
	{
		players[i].initOut();
		players[i].clearHandCard();
	}

	//��������(�ƾ�)
	desk.init();
	desk.clearPublicPoker();

	//�����ƶ�
	pokerHeap.init();

	//ǿ���´�Сäע
	players[0].bet(desk, 1);
	cout << "��ң�" << players[0].getName() << "����Сäע $1" << endl;
	players[1].bet(desk, 2);
	cout << "��ң�" << players[1].getName() << "���˴�äע $2" << endl;

	//ׯ�Ҹ�ÿ����ҷ���
	banker.licensing(players, pokerHeap);
	cout << "�������." << endl;

	//��ÿ����ҵ���������
	for (int i = 0; i < players.size(); i++) {
		players[i].handCardSort();
	}

	//��һ����ע
	cout << "��һ����ע��" << endl;
	firstRound();

	//ׯ�ҷ�3�Ź�����
	cout << "ׯ�ҷ���3�Ź�����" << endl;
	banker.licensingPublicCard(desk, pokerHeap, 3);

	//�����ƶ�����
	desk.publicPokerSort();
	desk.publicPokerShow();

	//�ڶ�����ע
	cout << "�ڶ�����ע��" << endl;
	otherRound();

	//ׯ�ҷ�1�Ź�����
	cout << "ׯ�ҷ���1�Ź����ƣ�" << endl;
	banker.licensingPublicCard(desk, pokerHeap, 1);

	//�����ƶ�����
	desk.publicPokerSort();
	desk.publicPokerShow();

	//��������ע
	cout << "��������ע��" << endl;
	otherRound();

	//ׯ�ҷ����һ�Ź�����
	cout << "ׯ�ҷ������һ�Ź����ƣ�" << endl;
	banker.licensingPublicCard(desk, pokerHeap, 1);

	//�����ƶ�����
	desk.publicPokerSort();
	desk.publicPokerShow();

	//���һ����ע
	cout << "���һ����ע:" << endl;
	otherRound();

	//���ձ����ж���Ӯ����һ�ý���
	judgeWin();
	
	cout << "������Ϸ����" << endl;
}

void TexasHoldemGame::GameTest(int playerNum)
{
	for (int i = 0; i < playerNum; i++) {
		Player player;
		string name = "���" + to_string(i + 1);
		player.setName(name);
		player.setMoney(10000);
		players.push_back(player);
	}
	desk = Desk();
	while (true) {
		cout << "��Ϸ��ʼ" << endl;

		//�����������
		for (int i = 0; i < players.size(); i++) {
			players[i].clearHandCard();
			players[i].initOut();
		}
		//��������(�ƾ�)
		desk.init();
		desk.clearPublicPoker();

		//�����ƶ�
		pokerHeap.init();

		//ׯ�Ҹ�ÿ����ҷ���
		banker.licensing(players, pokerHeap);
		cout << "�������." << endl;

		//��ÿ����ҵ���������
		for (int i = 0; i < players.size(); i++) {
			players[i].handCardSort();
		}

		//ׯ�ҷ�3�Ź�����
		cout << "ׯ�ҷ���3�Ź�����" << endl;
		banker.licensingPublicCard(desk, pokerHeap, 3);

		//�����ƶ�����
		desk.publicPokerSort();
		desk.publicPokerShow();

		//ׯ�ҷ�1�Ź�����
		cout << "ׯ�ҷ���1�Ź����ƣ�" << endl;
		banker.licensingPublicCard(desk, pokerHeap, 1);

		//�����ƶ�����
		desk.publicPokerSort();
		desk.publicPokerShow();

		//ׯ�ҷ����һ�Ź�����
		cout << "ׯ�ҷ������һ�Ź����ƣ�" << endl;
		banker.licensingPublicCard(desk, pokerHeap, 1);

		//�����ƶ�����
		desk.publicPokerSort();
		desk.publicPokerShow();

		//���ձ����ж���Ӯ����һ�ý���
		judgeWin();

		cout << "������Ϸ����...���������������.." << endl;
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
