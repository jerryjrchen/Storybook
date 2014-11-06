// ****************************************************************
// Assignment #1 - CS202 - plot.cpp
// Author: Jerry Chen
// Implementation of plot elements/graph, paragraph and
// name are in script.cpp
// ****************************************************************

#include "script.h"
//size of temporary array for reading
int TEMP = 1000;
//default constructor for plot
plot :: plot(void)
{
	head = NULL;
}

//constructor for when title and text are passed in
plot :: plot(char * text_add, char * title_add) : paragraph(text_add, title_add)
{
	head = NULL;
}

//copy constructor for plot
plot :: plot(const plot & in)
{
	node * current = in.head;
	node * temp = head;
	while(current)
	{
		temp = new node(*current);
		current = current -> go_next();
		temp = temp -> go_next();
	}
	//last item on list is null
	temp = NULL;
}

//destructor for plot
plot :: ~plot(void)
{
	remove_choices();
}

//add a choice to the adjacency list
void plot :: add_choice(node & add)
{
	//adds the choice to the beginning of the list
	node * temp = head;
	head = new node(add);
	//link up head -> next
	head -> link_next(temp);
}

//view the choices in the adjacency list
void plot :: view_choice(void)
{
	node * temp = head;
	//number of the choice
	int count = 1;
	//iteratively goes through list and displays
	while(temp)
	{
		cout << "Choice #" << count << endl;
		temp -> disp_title();
		temp -> disp_text();
		temp = temp -> go_next();
		++count;
	}
}

//remove the choices in the adjacency list
void plot :: remove_choices(void)
{
	//stops when head is NULL
	while(head)
	{
		node * temp = head -> go_next();
		delete head;
		head = temp;
	}
}

//Figures out the next index to advance to:
//First traverses to the selected item in the adjacency
//list. Then, get the index that the adjacency links to.
int plot :: next_plot(int traversals)
{
	//traversals will be decremented because the choice the user puts
	//in will be 1 to x. However, for the first item, we only
	//want to traverse 0 to x-1 times.
	--traversals;
	//traversal will be done with a temporary pointer
	node * temp = head;
	for(int i = 0; i < traversals; ++i)
	{
		temp = temp -> go_next();
	}
	//returns the plot index that is in the correct choice
	return temp -> get_path();
}

//checks if head is null/ if there is an adjacency list
bool plot :: is_list(void)
{
	if(head)
	{
		return true;
	}
	return false;
}

//default constructor for node
node :: node(void)
{
	next = NULL;
	plot_index = -1;
}

//constructor when the data elements are known and passed
node :: node(char * text_add, char * title_add, int index) : paragraph(text_add, title_add)
{
	plot_index = index;
	next = NULL;
}

//copy constructor for node
node :: node(const node & in) : paragraph(in.text, in.title)
{
	plot_index = in.plot_index;
}

//destructor for node
node :: ~node(void)
{
	plot_index = -1;
	next = NULL;
}

//allows for traversal to the next item 
node * node :: go_next(void)
{
	return next;
}

//links with the next item in a list
void node :: link_next(node * item_to_link)
{
	next = item_to_link;
}

//gets the plot index
int node :: get_path(void)
{
	return plot_index;
}

//the implementation of the script itself

//default constructor for script
script :: script(void)
{
	new_story = true;
	story_size = 0;
}

//constructor with number of plot entries
script :: script(int size)
{
	new_story = true;
	story_size = size;
	//dynamically allocate size of plot
	points = new plot*[size];
	//intialize each element
	for(int i = 0; i < story_size; ++i)
	{
		points[i] = new plot;
	}
}

//copy constructor for script
script :: script(const script & in)
{
	//makes new array of plot points
	points = new plot*[in.story_size];

	//traverses through all indices in "in"
	for(int i = 0; i < in.story_size; ++i)
	{
		//invokes copy constructor for plot
		points[i] = new plot(*in.points[i]);
	}
	
}

//destructor for script
script :: ~script(void)
{
	delete_all();
}

//clears the script
void script :: delete_all(void)
{
	for(int i = 0; i < story_size; ++i)
	{
		delete points[i];
	}
}

//editing mode
void script :: edit(void)
{
	if (new_story == true) {
		new_story = false;
		char temp[TEMP];
		//read in the intro
		cout << "Now reading in the introduction" << endl;
		cout << "(This will be index 1)" << endl;
		cout << "Enter in the title:" << endl;
		cin.get(temp, TEMP, '\n');
		cin.ignore(TEMP, '\n');
		points[0] = new plot(temp, temp);
		//points[0] -> add_title(temp);
		cout << "Enter in the text:" << endl;
		cin.get(temp, TEMP, '\n');
		cin.ignore(TEMP, '\n');
		points[0]->add_text(temp);
	}
	//now done reading the intro
	char decision = 'A';
	//user chooses to add scene/decision or remove scene or check scenes
	while(decision != 'Q')
	{
		decision = edit_choice();
		if(decision == 'A')
		{
			//the index user wants to add to
			int index;
			//temporary array for reading
			char temp[TEMP];
			cout << "What index to add to? " << "1 to " << story_size << endl;
			cin  >> index;
			cin.ignore(100, '\n');
			//decrement index (conversion)
			--index;
			//read in the story information
			cout << "Enter in the title:" << endl;
			cin.get(temp, TEMP, '\n');
			cin.ignore(TEMP, '\n');
        		points[index] = new plot(temp, temp);
			points[index] -> add_title(temp);
        		cout << "Enter in the text:" << endl;
        		cin.get(temp, TEMP, '\n');
        		cin.ignore(TEMP, '\n');
        		points[index] -> add_text(temp);
        
		}
		if(decision == 'C')
		{
			//add a choice to a scene
			//the index user wants to add a choice to
			int index;
			//the index the choice will lead to
			int index_lead;
			//temporary arrays for reading
			char temp[TEMP];
			char temp2[TEMP];
			cout << "What index to add a choice to?" << "1 to " << story_size << endl;
			cin  >> index;
			cin.ignore(100, '\n');
			//decrement index (so 1 become 0, etc.)
			--index;
			//read in the choice information
			cout << "Enter the title: " << endl;
			cin.get(temp, TEMP, '\n');
			cin.ignore(TEMP, '\n');
			cout << "Enter the text: " << endl;
			cin.get(temp2, TEMP, '\n');
			cin.ignore(TEMP, '\n');
			cout << "What index will this choice lead to? " << endl;
			cin  >> index_lead;
			cin.ignore(100, '\n');
			//creates a node to store the info
			node to_add(temp2, temp, index_lead);
			//adds the node to the adjacency list
			points[index] -> add_choice(to_add);	
		}
		if(decision == 'R')
		{
			//removes scenes
			delete_all();
		}
		if(decision == 'S')
		{
			//check scenes
			//traverses all plot points and displays them
			//and the adjacency list
			for(int i = 0; i < story_size; ++i)
			{
				if(points[i])
				{
					cout << "Index: " << i + 1 << endl;
					points[i] -> disp_title();
					points[i] -> disp_text();
					cout << "Choices: " << endl;
					points[i] -> view_choice();
				}
			}
		} 
	}
}

//viewing mode
void script :: view(void)
{
	//displays the intro first
	//temp used to hold the next index to go to
	int index = 0;
	//while choices existed, aka not an ending
	while(points[index] -> is_list())
	{
		//holds user choice for the adjacency list
		int choice;
		//show the title
		points[index] -> disp_title();
		points[index] -> disp_text();
		//show the choices
		cout << "Choices: " << endl;
		points[index] -> view_choice();
		cout << "Select choice: " << endl;
		cin  >> choice;
		cin.ignore(100, '\n');
		//figure out the next index, choice will
		//be the number of traversals
		index =  points[index] -> next_plot(choice);
		//decrement index so it is the correct "array" index
		--index;
	}
	//displays one last time because the ending will not have an adjacency list
	points[index] -> disp_title();
	points[index] -> disp_text();
}

//gets the user's choice for editing
char script :: edit_choice(void)
{
	char choice;
	cout << "Add another scene (A), add a choice to a scene (C), remove all scenes (R), check scenes (S), or exit (Q) ?" << endl;
	cin  >> choice;
	cin.ignore(100, '\n');
	return toupper(choice);
}
