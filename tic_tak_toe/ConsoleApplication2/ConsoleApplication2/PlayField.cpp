#include "pch.h"
#include "PlayField.h"
#include<vector>
#include<string>
#include<iostream>
#include<cassert>
using namespace std;


vector <PlayField::CellIdx> PlayField::getEmptyCells(PlayField::CellState ar[])
{
	vector<PlayField::CellIdx> arr;
	for (int i = 0;i < 9;i++)
	{
		if (ar[i] == PlayField::csEmpty)
		{
			PlayField::CellIdx call;
			call.set_id(i);			
			arr.push_back(call);			
		};

	}
	return arr;	
}
void PlayField::print_result()
{
	cout << "D=" << Draw << " X=" << Cross << " O=" << Nought << endl; //Вывод результатов хода на экран
}
	
PlayField::fieldState PlayField::checkFieldStatus(PlayField::CellState ar[])
{
	PlayField::CellState i = check(ar);
	bool isNormal = checkingForCorrectness(ar);
	if (i == PlayField::csCross)
	{
		Cross++;
		return fsCrossesWin;
	}
	if (i == PlayField::csNought)
	{
		Nought++;
		return fsNoughtsWin;
	}
	if (getEmptyCells(ar).size() == 0)
	{
		Draw++;		
		return fsDraw;
	}
	if (isNormal)  return fsNormal;
	else return fsInvalid;
}
void PlayField::makeMove(CellIdx id)
{
	assert((arrayOfNewGame[id.get_Id()] == PlayField::csEmpty) || (checkFieldStatus(arrayOfNewGame) == fsNormal));
	arrayOfNewGame[id.get_Id()] = PlayField::csCross;
	print_bord();
}
void PlayField::print_bord()
{
	cout << arrayOfNewGame[0] << "|" << arrayOfNewGame[1] << "|" << arrayOfNewGame[2] << endl;
	cout << arrayOfNewGame[3] << "|" << arrayOfNewGame[4] << "|" << arrayOfNewGame[5] << endl;
	cout << arrayOfNewGame[6] << "|" << arrayOfNewGame[7] << "|" << arrayOfNewGame[8] << endl;
}

PlayField::CellState PlayField::check(PlayField::CellState ar[])
{
	for (int i = 0; i < 3; i++)//Для победы нужны 3 клеточки
	{
		if (ar[i * 3] == ar[i * 3 + 1] && ar[i * 3 + 1] == ar[i * 3 + 2] && ar[i * 3] != PlayField::csEmpty) //Комбинации для победы вычисляются по
			return ar[i * 3]; //разным формулам, эта - по горизонтали
			//0-1-2, 3-4-5 и 6-7-8
			//нумерация в массиве начинается с 0
		else if (ar[i] == ar[i + 3] && ar[i + 3] == ar[i + 6] && ar[i] != PlayField::csEmpty) //Вертикальная
			return ar[i]; //0-3-6, 1-4-7 и 2-5-8
		if (((ar[2] == ar[4] && ar[4] == ar[6]) || (ar[0] == ar[4] && ar[4] == ar[8])) && ar[4] != PlayField::csEmpty)
			return ar[4]; //И по диагонали: 0-4-8 и 2-4-6	
	}
	return PlayField:: csEmpty; //Иначе - ничья
}
void PlayField::toCalculateCombination(TreeNode root)
{
	vector<CellIdx> arr;
	Nqueue.push_back(root);
	while (Nqueue.size() != 0)
	{
		TreeNode top = Nqueue.back();
		arr = getEmptyCells(top.field);
		int count = arr.size();
		Nqueue.pop_back();
		for (int i = 0;i < count;i++)
		{
			PlayField::CellIdx call = arr.back();
			arr.pop_back();
			create_and_addCild(top, call.get_Id()); // если в данном методе я буду только добавлять, основной метод будет очень перегружен
		}
	}
}

void PlayField::create_and_addCild(TreeNode a, int callId)
{
	TreeNode san;
	san.level = a.level + 1;
	for (int i = 0;i < 9;i++)
	{
		san.field[i] = a.field[i];
	}
	PlayField::CellState state;
	if (san.level % 2 == 1) state = PlayField::csCross;
	else state = PlayField::csNought;
	san.field[callId] = state;
	PlayField::fieldState tipe =checkFieldStatus(san.field);
	if (tipe == PlayField::fieldState::fsNormal)
	{
		Nqueue.push_back(san);
	}
}
bool  PlayField::checkingForCorrectness(PlayField::CellState ar[])
{
	int X = 0;
	int O = 0;
	for (int i = 0;i < 9;i++)
	{
		if (ar[i] == PlayField::csCross) X++;
		if (ar[i] == PlayField::csNought) O++;

	}
	if (X - O <= 1) return true;
	return false;
}

//PlayField::~PlayField()
//{
//}

