#pragma once
#include "pch.h"
#include <iostream>
#include "PlayField.h"
#include <vector>
#include <cassert>
#include<cmath>
#include "TreeNode.h"


using namespace std;
class PlayField
{
public:
	int Draw = 0;
	int Cross = 0;
	int Nought = 0;
	enum TipeOf
	{
		csEmpty,
		csCross,
		csNought
	};
	enum tipeOfGame
	{
		fsInvalid,
	    fsNormal ,
	    fsCrossesWin,
	    fsNoughtsWin,
	    fsDraw
	};
	class CallIdx
	{
	public:				
		int get_Id()
		{
			return id;
		};		
		int get_Value()
		{
			return Value;
		};
		void set_Value(char vValue)
		{
			Value = vValue;
		};
		void set_id(int vx)
		{
			id = vx;
		};		
	private:
		int id;	
		char Value;
	};
    char a[9];
	vector<CallIdx> getEmptyCells(char ar[])
	{	
			vector<CallIdx> arr;
			for (int i = 0;i < 9;i++)
			{
				if (ar[i] == '-')
				{
					CallIdx call;
					call.set_id(i);
					call.set_Value('-');
					arr.push_back(call);
				};

			}
			return arr;		
	};
	tipeOfGame checkFieldStatus(char ar[])
	{	
		char  i = check(ar);
		char norm = checkingForCorrectness(ar);
		if (i == 'x')
		{
			Cross++;
			return fsCrossesWin;
		}
		if (i == 'o')
		{
			Nought++;
			return fsNoughtsWin;
		}
		if (getEmptyCells(ar).size() == 0)
		{
			Draw++;
			return fsDraw;
		}
		if (norm == '+') return fsNormal;
		if (norm == '-') return fsInvalid;
	}
	
	void makeMove(CallIdx id)
	{
		assert((a[id.get_Id()] == '-') || (checkFieldStatus(a) == fsNormal));
		a[id.get_Id()] = id.get_Value();
		return_bord();		
	};
	
	
    void return_bord()
	{
		cout << a[0] << "|" << a[1] << "|" << a[2] << endl;
		cout << a[3] << "|" << a[4] << "|" << a[5] << endl;
		cout << a[6] << "|" << a[7] << "|" << a[8] << endl;
	};
	PlayField()
	{
		cout << "Numbers of cells:\n" << endl;
		//Номера клеток для того, чтобы человек знал куда ходить
		cout << "-" << 1 << "-" << '|' << "-" << 2 << "-" << '|' << "-" << 3 << "-" << endl;
		cout << "-" << 4 << "-" << '|' << "-" << 5 << "-" << '|' << "-" << 6 << "-" << endl;
		cout << "-" << 7 << "-" << '|' << "-" << 8 << "-" << '|' << "-" << 9 << "-" << "\n" << endl;		
		for (int i = 0;i < 9;i++)
		{
			a[i] = '-';
		}
		CallIdx call;
		int Id;
		char value;
		cin  >> Id;
		call.set_id(Id - 1);
		call.set_Value('x');
		makeMove(call);
		TreeNode::TreeNode(Id);
		cout << "D=" << Draw << " X=" << Cross << " O=" << Nought << endl;
	};
private:
	char check(char ar[])
	{

		for (int i = 0; i < 3; i++)//Для победы нужны 3 клеточки
		{
			if (ar[i * 3] == ar[i * 3 + 1] && ar[i * 3 + 1] == ar[i * 3 + 2] && ar[i * 3] != '-') //Комбинации для победы вычисляются по
				return ar[i * 3]; //разным формулам, эта - по горизонтали
				//0-1-2, 3-4-5 и 6-7-8
				//нумерация в массиве начинается с 0
			else if (ar[i] == ar[i + 3] && ar[i + 3] == ar[i + 6] && ar[i] != '-') //Вертикальная
				return ar[i]; //0-3-6, 1-4-7 и 2-5-8
			 if (((ar[2] == ar[4] && ar[4] == ar[6]) || (ar[0] == ar[4] && ar[4] == ar[8])) && ar[4] != '-')
				return ar[4]; //И по диагонали: 0-4-8 и 2-4-6	
		}
		return '-'; //Иначе - ничья
	}

	char checkingForCorrectness(char ar[])
	{
		int X=0;
		int O=0;
		for (int i = 0;i < 9;i++)
		{
			if (ar[i] == 'x') X++;
			if (ar[i] == 'o') O++;
			
		}
		if (abs(X - O) > 2) return '-';
		return'+';
	}
};

