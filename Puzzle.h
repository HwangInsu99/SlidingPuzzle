#pragma once
class Puzzle
{
public:
	int puzzleNum[3][3];
	int checkNum[9];

	int number;
	int startX;
	int startY;
	bool clear;
	int inversion;

	CImage images[9];

	Puzzle();
	void LoadImage();
	void Draw(CDC& dc);
	void Shuffle();
	BOOL Change(int x, int y);
	void Possible();
	BOOL Check();
};

