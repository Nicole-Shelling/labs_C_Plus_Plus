#pragma once
#include "PlayField.h"
#include <vector>

class PlayField
{
public:
	
	enum CellState
	{
	    csEmpty,
		csCross,
		csNought
	};
	enum fieldState
	{
		fsInvalid,
	    fsNormal ,
	    fsCrossesWin,
	    fsNoughtsWin,
	    fsDraw
	};
	class TreeNode
	{
	public:
		PlayField::CellState field[9];
		int level;
	};

	class CellIdx
	{
	public:				
		int get_Id()
		{
			return id;
		};				
		void set_id(int vx)
		{
			id = vx;
		};		
	private:
		int id;	//������� � ������� �������������� ������		
	};
	

    CellState arrayOfNewGame[9]; //������ ��� �������� ���� � ������ ���� � ����� ������� ����
	std::vector <CellIdx> getEmptyCells(PlayField::CellState ar[]); //������ ������� ���������� ��� ��������, ������� �������� ������� ������ TreeNode	
	fieldState checkFieldStatus(PlayField::CellState ar[]);
	void makeMove(CellIdx id);	
	void print_bord();	
	void print_result();	
	void create_and_addCild(TreeNode a, int callId);
	void toCalculateCombination(TreeNode a);
private:
	int Draw = 0;
	int Cross = 0;
	int Nought = 0; //C�������, �� ������ �� ������ ��� ��������� ����
	std::vector< TreeNode> Nqueue;
	PlayField::CellState check(PlayField::CellState ar[]);
	bool checkingForCorrectness(PlayField::CellState ar[]);
};

