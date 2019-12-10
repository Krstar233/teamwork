#include "Player.h"
#include <iostream>
using namespace std;

Player::Player()
{
	betHasPut = 0;
	money = 0;
	out = false;
}


Player::~Player()
{
}

void Player::bet(Desk& desk, int num)
{
	desk.addJackPot(num);
	this->money -= num;
	this->betHasPut = num;
}

void Player::followBet(Desk& desk, int bet)
{
	/*
		args:
			desk, ��Ϸ���棬������Ľ��ؼ���ע
			bet, ������Ϸ��������ߵ�ע����Ŀ�����������ע����������������ע����Ӹ���עֵΪbet�Ĵ�С)
	*/
	int addNum = bet - betHasPut;
	desk.addJackPot(addNum);
	this->money -= addNum;
	this->betHasPut = bet;
}

void Player::addBet(Desk& desk, int bet, int num)
{
	/*
	args:
		desk, ��Ϸ���棬������Ľ��ؼ���ע
		bet, ������Ϸ��������ߵ�ע����Ŀ�����������ע����������������ע����Ӹ���עֵΪbet�Ĵ�С)
		num, �����עbet�Ļ����ϼ�ע������
	*/
	int addNum = bet - betHasPut + num;
	desk.addJackPot(addNum);
	this->money -= addNum;
	this->betHasPut = bet;
}

void Player::setName(string name)
{
	this->Name = name;
}

string Player::getName()
{
	return this->Name;
}

void Player::setMoney(int money)
{
	this->money = money;
}

int Player::getMoney()
{
	return this->money;
}

void Player::initHandCard()
{
	this->handCard.clear();
}

void Player::initOut()
{
	out = false;
}

void Player::outGame()
{
	out = true;
}

bool Player::isOut()
{
	return out;
}

void Player::initBetHasPut()
{
	betHasPut = 0;
}

void Player::handCardSort()
{
	handCard.sort();
}

void Player::handCardShow()
{
	handCard.show();
}

PokerHeap Player::getHandCard()
{
	return handCard;
}

PokerHeap& Player::getCard()
{
	return handCard;
}
