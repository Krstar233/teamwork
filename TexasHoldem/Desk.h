#pragma once
#include "PokerHeap.h"
/*
	�ƾ֣����棩�ࣺ
		ӵ�й����ƣ����ص���Ϣ��ׯ���ܹ�������ַ�������
*/
class Desk
{
	PokerHeap publicPoker; //������
	int betMount;//������Ͷע 
	int jackPot;//���� 
public:
	Desk();
	~Desk();
	void init(); //��ʼ��
	void publicPokerSort(); //����������
	void publicPokerShow(); //���������
	int getSize();
	int getJackPot(); 
	void addJackPot(int num);
	PokerHeap getpublicPoker();
	PokerHeap& getCard();
	void clearPublicPoker();
};
