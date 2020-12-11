#pragma once

#include <iostream>

//https://stackoverflow.com/questions/2020184/preincrement-faster-than-postincrement-in-c-true-if-yes-why-is-it#:~:text=actually%20%2D%20it%20depends.,the%20value%20before%20the%20increment.

int preIncrementValue(int& i)
{
	i += 1;
	return i;
}

int postIncrementValue(int& i)
{
	int iCopy = i;
	i += 1;
	return iCopy;
}