#include "pch.h"
#include <iostream>
#include "PlayField.h"
#include <vector>
#include <cassert>
#include<cmath>
#include <queue>
#include "TreeNode.h"

PlayField m;
vector<struct TreeNode::tnode> Nqueue;
TreeNode::TreeNode(int Id)
{	    
		tnode root;
		vector<PlayField::CallIdx> arr;
		root.level = 1;
		root.field[Id - 1] = 'x';		
		Nqueue.push_back(root);
		while (Nqueue.size()!=0)
		{
			tnode top=Nqueue.back();			
			arr = m.getEmptyCells(top.field);
			int count = childQty(top);
			Nqueue.pop_back();
            for (int i=0;i<count;i++)
		    {
			    PlayField::CallIdx call = arr.back();
				arr.pop_back();
			    addCild(top, call.get_Id());
		    }			
		}				
};

int TreeNode::childQty(tnode a)
{
	return 9 -a.level;
}
void TreeNode::addCild(tnode a, int callId)
{
	tnode  san;
	san.level = a.level + 1;
	for (int i = 0;i < 9;i++)
	{
		san.field[i]=a.field[i];
	}
	char symbol;
	if (san.level % 2 == 1) symbol = 'x';
	else symbol = 'o';	
	san.field[callId] = symbol;
	PlayField::tipeOfGame tipe=m.checkFieldStatus(san.field);
	if (tipe == PlayField::tipeOfGame::fsNormal)
	{
		Nqueue.push_back(san);		
	}
		
};
TreeNode::~TreeNode()
{
}
