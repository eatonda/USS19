#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::string;


int validation(int val)
{
	while (!(cin >> val))
	{
		cout << "Please select a number" << endl;
		cin.clear();
		cin.ignore(100, '\n');
	}
	return val;
}

int main()
{
	int choice = 0;
	int gridSize = 0;
	int shipColor = 0;
	int numOfShips = 0;

	do
	{
		cout << "Please go through each step to set up the game." << endl;
		cout << "1. Grid Size" << endl;
		cout << "2. Ship(s) Color" << endl;
		cout << "3. Number of Ships" << endl;
		cout << "4. Exit" << endl;
		choice = validation(choice);
		

		switch (choice)
		{
		
		case 1:
			cout << "Please select grid size" << endl;
			gridSize = validation(gridSize);
			cout << "Your grid size is " << gridSize << endl;
			break;

		case 2:
			cout << "Please select a color for your ship(s)" << endl;
			cout << "1. Grey" << endl;
			cout << "2. Blue" << endl;
			shipColor = validation(shipColor);
			cout << "You chose the color #" << shipColor << " for your ships" << endl;
			break;

		case 3:
			cout << "Please enter the number of ships you wish to have" << endl;
			numOfShips = validation(numOfShips);
			cout << "Your fleet contains " << numOfShips << " of ships" << endl;
			break;

		case 4:
			cout << "Exit..." << endl;
			return 0;
		}
	}

	while (choice != 4);

}