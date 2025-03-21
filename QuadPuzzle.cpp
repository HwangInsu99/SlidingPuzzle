#include "pch.h"
#include "QuadPuzzle.h"
QuadPuzzle::QuadPuzzle() {
	number = 0;
	startX = 150;
	startY = 75;
	clear = false;
	inversion = 0;
	even = false;
	srand((unsigned int)time(NULL));

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

void QuadPuzzle::Shuffle() {
	number = 0;

	for (int i = 0; i < 45; i++) {
		int x, y, a, b;

		do {
			x = rand() % 4;
			y = rand() % 4;
			a = rand() % 4;
			b = rand() % 4;
		} while (x == a && y == b);

		int temp = puzzleNum[x][y];
		puzzleNum[x][y] = puzzleNum[a][b];
		puzzleNum[a][b] = temp;
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			checkNum[number] = puzzleNum[i][j];
			if (puzzleNum[i][j] == 15) {
				if (i % 2 == 0)
					even = true;
				else
					even = false;
			}
			number++;
		}
	}
	Possible();
}

void QuadPuzzle::Possible() {
	inversion = 0;

	for (int i = 0; i < 16; i++) {
		for (int j = i; j < 16; j++) {
			if (checkNum[i] > checkNum[j] && checkNum[i] != 15)
				inversion++;
		}
	}

	if (even && inversion % 2 == 0)
		Shuffle();

	else if (!even && inversion % 2 != 0)
		Shuffle();

	else if (inversion == 0)
		Shuffle();

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

BOOL QuadPuzzle::Change(int x, int y) {
	int dx[] = { -1, 1, 0, 0 };
	int dy[] = { 0, 0, -1, 1 };

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx >= 0 && nx < 4 && ny >= 0 && ny < 4) {
			if (puzzleNum[nx][ny] == 15) {
				puzzleNum[nx][ny] = puzzleNum[x][y];
				puzzleNum[x][y] = 15;
				return TRUE;
			}
		}
	}
	return FALSE;
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