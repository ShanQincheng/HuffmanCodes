// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <string>

typedef struct HuffmanNode
{
	char key;
	int weight;

	struct HuffmanNode * leftChild;
	struct HuffmanNode * rightChild;
}HuffmanNode;

typedef struct HuffmanCode
{
	char key;
	std::string huffmanCode;
}HuffmanCode;

bool compareWeight(const HuffmanNode &a, const HuffmanNode &b); // compare function for STL sort and sort by weight from low to high
bool compareCharacter(const HuffmanCode &a, const HuffmanCode &b); // compare function for STL sort and sort by character from low to high 

using namespace std;


// TODO: reference additional headers your program requires here
