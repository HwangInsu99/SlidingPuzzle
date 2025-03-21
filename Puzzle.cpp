#include "pch.h"
#include "Puzzle.h"

Puzzle::Puzzle() {
	number = 0;
	startX = 150;
	startY = 75;
	clear = false;
	inversion = 0;
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			puzzleNum[i][j] = number;
			checkNum[number] = number;
			number++;
		}
	}

}
void Puzzle::LoadImage() {
	images[0].Load(L"images\\3_1.jpg");
	images[1].Load(L"images\\3_2.jpg");
	images[2].Load(L"images\\3_3.jpg");
	images[3].Load(L"images\\3_4.jpg");
	images[4].Load(L"images\\3_5.jpg");
	images[5].Load(L"images\\3_6.jpg");
	images[6].Load(L"images\\3_7.jpg");
	images[7].Load(L"images\\3_8.jpg");
	images[8].Load(L"images\\3_9.jpg");
}
// 퍼즐을섞어서 배치한다
void Puzzle::Shuffle() {
	
	number = 0;

	for (int i = 0; i < 18; i++) {
		int x, y, a, b;

		do {
			x = rand() % 3;
			y = rand() % 3;
			a = rand() % 3;
			b = rand() % 3;
		} while (x == a && y == b);
		
		int temp = puzzleNum[x][y];
		puzzleNum[x][y] = puzzleNum[a][b];
		puzzleNum[a][b] = temp;
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			checkNum[number] = puzzleNum[i][j];
			number++;
		}
	}
	Possible();
}
//클리어 가능여부 및 완성상태인지 확인 후 다시 다시 섞을지 결정한다
void Puzzle::Possible() {
	inversion = 0;
	
	for (int i = 0; i < 9; i++) {
		for (int j = i; j < 9; j++) {
			if (checkNum[i] > checkNum[j] && checkNum[i] != 8)
				inversion++;
		}
	}
	
	if (inversion % 2 != 0 || inversion == 0)
		Shuffle();
		
}

BOOL Puzzle::Check() {
	inversion = 0;
	number = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			checkNum[number] = puzzleNum[i][j];
			number++;
		}
	}

	for (int i = 0; i < 9; i++) {
		for (int j = i; j < 9; j++) {
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
BOOL Puzzle::Change(int x, int y) {
	// 네 방향 (상, 하, 좌, 우) 이동 방향 정의
	int dx[] = { -1, 1, 0, 0 };
	int dy[] = { 0, 0, -1, 1 };

	// 네 방향을 검사
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		// 배열 범위를 벗어나지 않는지 확인
		if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
			if (puzzleNum[nx][ny] == 8) {
				puzzleNum[nx][ny] = puzzleNum[x][y];
				puzzleNum[x][y] = 8;
				return TRUE;
			}
		}
	}
	return FALSE;
}

void Puzzle::Draw(CDC& dc) {
	int width = 100;
	int height = 100;
	int x = startX;
	int y = startY;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			images[puzzleNum[i][j]].Draw(dc, x, y, width, height);
			x += width;
		}
		x = startX;
		y += height;
	}
}
