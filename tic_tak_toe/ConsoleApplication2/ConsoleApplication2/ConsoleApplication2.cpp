// ConsoleApplication2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "PlayField.h"
using namespace std;


int main()
{
	
	
	for (int Id = 0;Id < 8;Id++)
	{
		PlayField game;

		for (int i = 0; i < 9; i++)
		{
			game.arrayOfNewGame[i] = PlayField::csEmpty;
		}
		PlayField::CellIdx call;
		call.set_id(Id);
		game.makeMove(call);
		PlayField::TreeNode root;
		root.level = 1;
		for (int i = 0;i < 9;i++)
		{
			root.field[i] = game.arrayOfNewGame[i];
		}
		game.toCalculateCombination(root);
		game.print_result();
	}
	system("pause");
	return 0;
}


