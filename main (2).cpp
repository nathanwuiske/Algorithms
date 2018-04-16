#include <stdio.h>
#include <iostream>
#include <Windows.h>

using namespace std;

bool setCoordinate(int x, int y)
{
	COORD c = {x,y};
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

struct pos
{
	int x;
	int y;
};

int calcArea(pos rectBTop1, pos rectBBot1, pos rectATop1, pos rectABot1){

    int width = min(rectABot1.x, rectBBot1.x) - max(rectATop1.x, rectBTop1.x);
    int height = min(rectABot1.y, rectBBot1.y) - max(rectATop1.y, rectBTop1.y);
    int area = width * height;
    cout<<"Area of overlap = "<<area<<endl;
}


void draw(int x, int y, int width, int height)
{
	setCoordinate(x,y);
	cout << char(201); //ASCII 201 - upper left corner
	for(int i = 1; i < width; i++)
    {
        cout << char(205); //ASCII 205 -  horizontal line
    }
	cout<<char(187); //ASCII 187 - upper right corner
	setCoordinate(x, height + y);
	cout << char(200); //ASCII 200 - lower left corner
	for(int i = 1; i < width; i++)
    {
        cout<<char(205); //ASCII 205 -  horizontal line
    }
	cout << char(188); //ASCII 188 - lower right corner
	for(int i = y + 1; i < height + y; i++)
	{
		setCoordinate(x, i);
		cout << char(186); //ASCII 186 - vertical line
		setCoordinate(x + width, i);
		cout << char(186); //ASCII 186 - vertical line
	}
	setCoordinate(0,0);
}

bool checkOverlap(pos rectBTop, pos rectBBot, pos rectATop, pos rectABot)
{
    if ((rectATop.x <= rectBTop.x && rectBBot.x <= rectABot.x) &&(rectATop.y >= rectBTop.y && rectBBot.y >= rectABot.y))
	{
        calcArea(rectBTop, rectBBot, rectATop, rectABot);
		return true;
	}
else if ((rectBTop.x<= rectATop.x && rectABot.x <= rectBBot.x) &&(rectBTop.y >= rectATop.y && rectABot.y >= rectBBot.y))
	{
	    calcArea(rectBTop, rectBBot, rectATop, rectABot);
		return true;
	}
	else
	{
		return false;
	}
}
int main()
{
	pos rectATop,rectBTop,rectABot,rectBBot;
	int width, height, width1, height1;
	cout<<"Enter pos X for RectA Top: ";
	cin>>rectATop.x;
	cout<<"Enter pos Y for RectA Top: ";
	cin>>rectATop.y;

	cout<<"Enter pos X for RectA Bot: ";
	cin>>rectABot.x;
	cout<<"Enter pos Y for RectA Bot: ";
	cin>>rectABot.y;

	cout<<"Enter pos X for RectB Top: ";
	cin>>rectBTop.x;
	cout<<"Enter pos Y for RectB Top: ";
	cin>>rectBTop.y;

	cout<<"Enter pos X for RectB Bot: ";
	cin>>rectBBot.x;
	cout<<"Enter pos Y for RectB Bot: ";
	cin>>rectBBot.y;

	cout<<"Enter width for RectA: ";
	cin>>width;
	cout<<"Enter height for RectA: ";
	cin>>height;

	cout<<"Enter width for RectB: ";
	cin>>width1;
	cout<<"Enter height for RectB: ";
	cin>>height1;
    system("cls");

	draw(rectATop.x, rectATop.y, width, height);
	draw(rectBTop.x, rectBTop.y, width1, height1);

    if (checkOverlap(rectBTop,rectBBot,rectATop,rectABot))
	{
		printf("The two rectangles are overlapped\n");
	}
	else
	{
		printf("The two rectangles are NOT overlapped\n");
	}
	int wait;
	cin>>wait;
}
