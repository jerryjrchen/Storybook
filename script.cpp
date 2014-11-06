// ****************************************************
// Assignment #1 - CS202 - script.cpp
// Author: Jerry Chen
// This contains the implementation of the functions
// necessary to create, view, and maintain a script.
// ****************************************************

#include "script.h"

//default constructor for name
name :: name(void)
{
	title = NULL;
}

//constructor for name with title as arg
name :: name(char * title_add)
{
	add_title(title_add);
}

//copy constructor for name
name :: name(const name & in)
{
	add_title(in.title);
}

//destructor for name
name :: ~name(void)
{
	remove_title();
}

//adds in title
void name :: add_title(char * title_add)
{
	//copies the array of char
	title = new char[strlen(title_add) + 1];
	strcpy(title, title_add);
}
//removes title
void name :: remove_title(void)
{
	//deletes the title
	delete [] title;
	title = NULL;
}
//displays title
void name :: disp_title(void)
{
	//if the title exists
	if(title)
		cout << title << endl;
}

//default constructor for paragraph
paragraph :: paragraph(void)
{
	text = NULL;
}

//constructor for paragraph that copies over text
//intialization list for name
paragraph :: paragraph(char * text_add, char * title_add) : name(title_add)
{
	//copies over the information from the arguments
	add_text(text_add);
}

//copy constructor for paragraph
paragraph :: paragraph(const paragraph & in)
{
	add_text(in.text);
}

//destructor for paragraph
paragraph :: ~paragraph(void)
{
	//deallocates memory with the remove function
	remove_text();
}

//displays text
void paragraph :: disp_text(void)
{
	//if text exists
	if(text)
		cout << text << endl;
}

//adds in text
void paragraph :: add_text(char * text_add)
{
	//copies the text over
        text = new char[(strlen(text_add) + 1)];
	strcpy(text, text_add);      
}

//deallocates the text
void paragraph :: remove_text(void)
{
	//deletes the text
	delete [] text;
	text = NULL;
}
