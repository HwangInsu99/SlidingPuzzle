#pragma once
class QuadPuzzle
{
public:
	int puzzleNum[4][4];
	int checkNum[16];

	int number;
	int startX;
	int startY;
	bool clear;
	int inversion;
	bool even;

	CImage images[16];

	QuadPuzzle();
	void LoadImage();
	void Draw(CDC& dc);
	void Shuffle();
	BOOL Change(int x, int y);
	void Possible();
	BOOL Check();
};

