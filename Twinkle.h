#pragma once
class Twinkle
{
public:
	int count;
	int x;
	int y;

	CImage images[6];

	Twinkle();
	void LoadImage();
	void Tick();
	void RandomPoint();
	void Draw(CDC& dc);
};

