#include "Desk.h"


Desk::Desk()
{
	betMount = jackPot = 0;
}


Desk::~Desk()
{
}

void Desk::init()
{
	this->betMount = 0;
	this->jackPot = 0;
	this->publicPoker.clear();
}

void Desk::publicPokerSort()
{
	publicPoker.sort();
}

void Desk::publicPokerShow()
{
	publicPoker.show();
}

int Desk::getSize(){
	return publicPoker.getSize();
}

int Desk::getJackPot(){
	return jackPot;
}

void Desk::addJackPot(int num) {
	this->jackPot += num;
}

PokerHeap Desk::getpublicPoker()
{
	return publicPoker;
}

PokerHeap& Desk::getCard()
{
	return publicPoker;
}
