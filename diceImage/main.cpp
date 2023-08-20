#include "olcConsoleGameEngine.h"
#include "imageManager.h"
#include <algorithm>

#define _CRT_SECURE_NO_WARNINGS


class diceImage : public olcConsoleGameEngine
{
public:
	diceImage() {};

	virtual bool OnUserCreate()
	{

		return true;
	}

	bool OnUserUpdate(float fElapsedTime)
	{
		imageValues = imageManager();
		int posY = 0;
		int posX = 0;

		for (int startY = 5; startY < (m_nScreenHeight - 5); startY += 10)
		{
			for (int startX = 5; startX < (m_nScreenWidth - 5); startX += 10)
			{
				int dotNum = imageValues[posY * 18 + posX];
				DrawDie(dotNum, startX, startY, (startX + 10), (startY + 10));
				posX++;
			}
			posX = 0;
			posY++;
		}
		return true;
	}


public:
	void FillDots(int dotNum, short xSegment, short ySegment, short rectEdgeX, short rectEdgeY)
	{
		dotNum = std::clamp(dotNum, 1, 6);

		//General algorithm: FillDots fills a white circle at the start of the rectangles edge plus an offset

		if (dotNum == 1)
		{
			//Draw Middle
			FillCircle((rectEdgeX + xSegment + (short)(xSegment / 2)), (rectEdgeY + ySegment + (short)(ySegment / 2)), (short)(xSegment / 3));
		}
		else if (dotNum == 2)
		{
			//Draw Top Right
			FillCircle((rectEdgeX + (xSegment * 2) + (short)(xSegment / 2)), (rectEdgeY + (short)(ySegment / 2)), (short)(xSegment / 3));
			//Draw Bottom Left
			FillCircle((rectEdgeX + (short)(xSegment / 2)), (rectEdgeY + (ySegment * 2) + (short)(ySegment / 2)), (short)(xSegment / 3));
		}
		else if (dotNum == 3)
		{
			//Draw Top Right
			FillCircle((rectEdgeX + (xSegment * 2) + (short)(xSegment / 2)), (rectEdgeY + (short)(ySegment / 2)), (short)(xSegment / 3));
			//Draw Middle
			FillCircle((rectEdgeX + xSegment + (short)(xSegment / 2)), (rectEdgeY + ySegment + (short)(ySegment / 2)), (short)(xSegment / 3));
			//Draw Bottom Left
			FillCircle((rectEdgeX + (short)(xSegment / 2)), (rectEdgeY + (ySegment * 2) + (short)(ySegment / 2)), (short)(xSegment / 3));
		}
		else if (dotNum == 4)
		{
			//Draw Top Left
			FillCircle((rectEdgeX + (short)(xSegment / 2)), (rectEdgeY + (short)(ySegment / 2)), (short)(xSegment / 3));
			//Draw Top Right
			FillCircle((rectEdgeX + (xSegment * 2) + (short)(xSegment / 2)), (rectEdgeY + (short)(ySegment / 2)), (short)(xSegment / 3));
			//Draw Bottom Left
			FillCircle((rectEdgeX + (short)(xSegment / 2)), (rectEdgeY + (ySegment * 2) + (short)(ySegment / 2)), (short)(xSegment / 3));
			//Draw Bottom Right
			FillCircle((rectEdgeX + (xSegment * 2) + (short)(xSegment / 2)), (rectEdgeY + (ySegment * 2) + (short)(ySegment / 2)), (short)(xSegment / 3));
		}
		else if (dotNum == 5)
		{
			//Draw Top Left
			FillCircle((rectEdgeX + (short)(xSegment / 2)), (rectEdgeY + (short)(ySegment / 2)), (short)(xSegment / 3));
			//Draw Top Right
			FillCircle((rectEdgeX + (xSegment * 2) + (short)(xSegment / 2)), (rectEdgeY + (short)(ySegment / 2)), (short)(xSegment / 3));
			//Draw Middle
			FillCircle((rectEdgeX + xSegment + (short)(xSegment / 2)), (rectEdgeY + ySegment + (short)(ySegment / 2)), (short)(xSegment / 3));
			//Draw Bottom Left
			FillCircle((rectEdgeX + (short)(xSegment / 2)), (rectEdgeY + (ySegment * 2) + (short)(ySegment / 2)), (short)(xSegment / 3));
			//Draw Bottom Right
			FillCircle((rectEdgeX + (xSegment * 2) + (short)(xSegment / 2)), (rectEdgeY + (ySegment * 2) + (short)(ySegment / 2)), (short)(xSegment / 3));
		}
		else if (dotNum == 6)
		{
			//Draw Top Left
			FillCircle((rectEdgeX + (short)(xSegment / 2)), (rectEdgeY + (short)(ySegment / 2)), (short)(xSegment / 3));
			//Draw Top Right
			FillCircle((rectEdgeX + (xSegment * 2) + (short)(xSegment / 2)), (rectEdgeY + (short)(ySegment / 2)), (short)(xSegment / 3));
			//Draw Middle Left
			FillCircle((rectEdgeX + (short)(xSegment / 2)), (rectEdgeY + ySegment + (short)(ySegment / 2)), (short)(xSegment / 3));
			//Draw Middle Right
			FillCircle((rectEdgeX + (xSegment * 2) + (short)(xSegment / 2)), (rectEdgeY + ySegment + (short)(ySegment / 2)), (short)(xSegment / 3));
			//Draw Bottom Left
			FillCircle((rectEdgeX + (short)(xSegment / 2)), (rectEdgeY + (ySegment * 2) + (short)(ySegment / 2)), (short)(xSegment / 3));
			//Draw Bottom Right
			FillCircle((rectEdgeX + (xSegment * 2) + (short)(xSegment / 2)), (rectEdgeY + (ySegment * 2) + (short)(ySegment / 2)), (short)(xSegment / 3));
		}
	}

	void DrawRect(int x1, int y1, int x2, int y2)
	{
		short xDiff = x2 - x1;
		short yDiff = y2 - y1;
		//Top Right Down Left drawing pattern
		DrawLine(x1, y1, (x1 + xDiff), y1);
		DrawLine((x1 + xDiff), y1, x2, y2);
		DrawLine(x2, y2, x1, (y1 + yDiff));
		DrawLine(x1, (y1 + yDiff), x1, y1);
	}

	//x1,y1 is the top left point, x2,y2 is the bottom right point
	void DrawDie(int dotNum, int x1, int y1, int x2, int y2)
	{
		short xDiff = x2 - x1;
		short yDiff = y2 - y1;
		short xSegment = (xDiff + 0.5) / 3;
		short ySegment = (yDiff + 0.5) / 3;
		DrawRect(x1, y1, x2, y2);
		Fill(x1, y1, x2, y2, 0x2588, 0x000C);
		FillDots(dotNum, xSegment, ySegment, x1, y1);
	}

protected:
	std::vector<int> imageValues;
	
};


int main()
{	
	//imageManager();

	if (1)
	{
		diceImage diceImage;
		diceImage.ConstructConsole(190, 100, 8, 8);
		diceImage.Start();
	}
	

	return 0;
}