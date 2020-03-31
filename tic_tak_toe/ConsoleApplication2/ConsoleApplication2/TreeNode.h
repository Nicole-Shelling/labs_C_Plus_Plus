#pragma once
#include "pch.h"
#include <iostream>
#include "PlayField.h"
#include <vector>
#include <queue>
#include <cassert>
#include<cmath>
#include "TreeNode.h"

using namespace std;
class TreeNode
{
public:
	struct tnode 
	{
		char field[9] = {'-','-','-','-','-','-','-','-','-'};
		int level;
		vector< tnode> children;		
		
	};		
	void addCild(tnode a, int callId);
	TreeNode(int Id);	
	~TreeNode();
private:
	int childQty(tnode a);	
};

