#include <iostream>

using namespace std;

int main()
{
	float x, y;
	cout << "Введите координаты точки (x,y)" << endl; 
	cout << "X -> ";
	cin >> x;
	cout << "Y -> ";
	cin >> y;
	if  ( (x >= -1 && x <= 1) && (y >= -1 && y <= 1) )
		cout << "Точка попала в заштрихованную область" << endl;
	else
		cout << "Точка не попала в заштрихованную область" << endl;
	return 0;
}
