#include "pch.h"
#include "Twinkle.h"

Twinkle::Twinkle()
{
	count = 0;
	x = 0;
	y = 0;
}

void Twinkle::LoadImage()
{
	images[0].Load(L"images\\1.png");
	images[1].Load(L"images\\2.png");
	images[2].Load(L"images\\3.png");
	images[3].Load(L"images\\4.png");
	images[4].Load(L"images\\5.png");
	images[5].Load(L"images\\6.png");
}

void Twinkle::Tick()
{
	count++;
}

void Twinkle::RandomPoint()
{
	srand((unsigned int)time(NULL));

	x = rand() % 160 + 200;
	y = rand() % 160 + 125;
}

void Twinkle::Draw(CDC& dc)
{
	images[count].Draw(dc, x, y, 40, 40);
}
