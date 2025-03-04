#include "pch.h"
#include "QuadPuzzle.h"
QuadPuzzle::QuadPuzzle() {
	inputCount = 0;
	number = 0;
	startX = 150;
	startY = 75;
	clear = false;
	inversion = 0;
	even = false;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			puzzleNum[i][j] = number;
			checkNum[number] = number;
			number++;
		}
	}

}
void QuadPuzzle::LoadImage() {
	images[0].Load(L"images\\4_1.jpg");
	images[1].Load(L"images\\4_2.jpg");
	images[2].Load(L"images\\4_3.jpg");
	images[3].Load(L"images\\4_4.jpg");
	images[4].Load(L"images\\4_5.jpg");
	images[5].Load(L"images\\4_6.jpg");
	images[6].Load(L"images\\4_7.jpg");
	images[7].Load(L"images\\4_8.jpg");
	images[8].Load(L"images\\4_9.jpg");
	images[9].Load(L"images\\4_10.jpg");
	images[10].Load(L"images\\4_11.jpg");
	images[11].Load(L"images\\4_12.jpg");
	images[12].Load(L"images\\4_13.jpg");
	images[13].Load(L"images\\4_14.jpg");
	images[14].Load(L"images\\4_15.jpg");
	images[15].Load(L"images\\4_16.jpg");
}
// 퍼즐을섞어서 배치한다
void QuadPuzzle::Shuffle() {
	srand((unsigned int)time(NULL));
	number = 0;

	for (int i = 0; i < 45; i++) {
		int x = rand() % 4;
		int y = rand() % 4;
		int a = rand() % 4;
		int b = rand() % 4;

		int temp = puzzleNum[x][y];
		puzzleNum[x][y] = puzzleNum[a][b];
		puzzleNum[a][b] = temp;
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			checkNum[number] = puzzleNum[i][j];
			if (puzzleNum[i][j] == 15) {
				if (i % 2 == 0)
					even = false;
				else
					even = true;
			}
			number++;
		}
	}
	Possible();
}
//클리어 가능여부 및 완성상태인지 확인 후 다시 다시 섞을지 결정한다
void QuadPuzzle::Possible() {
	inversion = 0;

	for (int i = 0; i < 16; i++) {
		for (int j = i; j < 16; j++) {
			if (checkNum[i] > checkNum[j] && checkNum[i] != 15)
				inversion++;
		}
	}

	if (even && inversion % 2 != 0)
	{
		Shuffle();
	}
	else if (!even && inversion % 2 == 0 && inversion == 0)
	{
		Shuffle();
	}

}

BOOL QuadPuzzle::Check() {
	inversion = 0;
	number = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			checkNum[number] = puzzleNum[i][j];
			number++;
		}
	}

	for (int i = 0; i < 16; i++) {
		for (int j = i; j < 16; j++) {
			if (checkNum[i] > checkNum[j])
				inversion++;
		}
	}

	if (inversion == 0)
		return TRUE;
	else
		return FALSE;
}
//마우스 클릭좌표에 이동가능한 퍼즐이 있는지 확인 후 이동
BOOL QuadPuzzle::Change(int x, int y) {
	if (x == 0) {
		if (puzzleNum[x + 1][y] == 15) {
			puzzleNum[x + 1][y] = puzzleNum[x][y];
			puzzleNum[x][y] = 15;
			return TRUE;
		}
		else if (puzzleNum[x][y + 1] == 15 && y != 3) {
			puzzleNum[x][y + 1] = puzzleNum[x][y];
			puzzleNum[x][y] = 15;
			return TRUE;
		}
		else if (puzzleNum[x][y - 1] == 15 && y != 0) {
			puzzleNum[x][y - 1] = puzzleNum[x][y];
			puzzleNum[x][y] = 15;
			return TRUE;
		}
		else
			return FALSE;
	}
	else if (x == 1) {
		if (puzzleNum[x - 1][y] == 15) {
			puzzleNum[x - 1][y] = puzzleNum[x][y];
			puzzleNum[x][y] = 15;
			return TRUE;
		}
		else if (puzzleNum[x + 1][y] == 15) {
			puzzleNum[x + 1][y] = puzzleNum[x][y];
			puzzleNum[x][y] = 15;
			return TRUE;
		}
		else if (puzzleNum[x][y + 1] == 15 && y != 3) {
			puzzleNum[x][y + 1] = puzzleNum[x][y];
			puzzleNum[x][y] = 15;
			return TRUE;
		}
		else if (puzzleNum[x][y - 1] == 15 && y != 0) {
			puzzleNum[x][y - 1] = puzzleNum[x][y];
			puzzleNum[x][y] = 15;
			return TRUE;
		}
		else
			return FALSE;
	}
	else if (x == 2) {
		if (puzzleNum[x - 1][y] == 15) {
			puzzleNum[x - 1][y] = puzzleNum[x][y];
			puzzleNum[x][y] = 15;
			return TRUE;
		}
		else if (puzzleNum[x + 1][y] == 15) {
			puzzleNum[x + 1][y] = puzzleNum[x][y];
			puzzleNum[x][y] = 15;
			return TRUE;
		}
		else if (puzzleNum[x][y + 1] == 15 && y != 3) {
			puzzleNum[x][y + 1] = puzzleNum[x][y];
			puzzleNum[x][y] = 15;
			return TRUE;
		}
		else if (puzzleNum[x][y - 1] == 15 && y != 0) {
			puzzleNum[x][y - 1] = puzzleNum[x][y];
			puzzleNum[x][y] = 15;
			return TRUE;
		}
		else
			return FALSE;
	}
	else{
		if (puzzleNum[x - 1][y] == 15) {
			puzzleNum[x - 1][y] = puzzleNum[x][y];
			puzzleNum[x][y] = 15;
			return TRUE;
		}
		else if (puzzleNum[x][y + 1] == 15 && y != 3) {
			puzzleNum[x][y + 1] = puzzleNum[x][y];
			puzzleNum[x][y] = 15;
			return TRUE;
		}
		else if (puzzleNum[x][y - 1] == 15 && y != 0) {
			puzzleNum[x][y - 1] = puzzleNum[x][y];
			puzzleNum[x][y] = 15;
			return TRUE;
		}
		else
			return FALSE;
	}
}

void QuadPuzzle::Draw(CDC& dc) {
	int width = 75;
	int height = 75;
	int x = startX;
	int y = startY;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			images[puzzleNum[i][j]].Draw(dc, x, y, width, height);
			x += width;
		}
		x = startX;
		y += height;
	}
}