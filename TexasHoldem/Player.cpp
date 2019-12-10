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
			desk, 游戏桌面，可向其的奖池加入注
			bet, 当轮游戏中已下最高的注的数目，即所需跟的注数，（若本轮已下注，则加跟到注值为bet的大小)
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
		desk, 游戏桌面，可向其的奖池加入注
		bet, 当轮游戏中已下最高的注的数目，即所需跟的注数，（若本轮已下注，则加跟到注值为bet的大小)
		num, 在最高注bet的基础上加注的数额
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
