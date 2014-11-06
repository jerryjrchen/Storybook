// ****************************************************
// Assignment #1 - CS202 - main.cpp
// Author: Jerry Chen
// This is the main implementation of the script
// editing and viewing program.
// ****************************************************

#include "script.h"
//used for temporary arrays for reading
const int TEMP = 500;
//allows for user choice
char choice(void);

//asks for user choice
char choice(void)
{
	char response;
	//allows user to enter edit mode, viewing mode, or exit
	cout << "Would you like to edit (E), view (V), or quit(Q)?" << endl;
	cin  >> response;
	cin.ignore(100, '\n');
	return toupper(response);
}


int main()
{
	//ask user for size of the story
	int size = -1;
	cout << "How many scenes will the story have?" << endl;
	cin  >> size;
	cin.ignore(100, '\n');
	//creates a script class with the size passed into the constructor
	script story(size);
	//holds the user's decision
	char decision = 'A';
	while(decision != 'Q')
	{
		decision = choice();
		if(decision == 'E')
		{
			//enters editing mode
			story.edit();
		}
		else
			if(decision == 'V')
			{
				//enters viewing mode
				story.view();
			}
	}
	return 0;
}
