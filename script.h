// **************************************************************
// Assignment #1 - CS202 - script.h
// Author: Jerry Chen
// This is the header file for the script; it will include
// information necessary to building a "create your own
// adventure" type script.
// **************************************************************

#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

//object "name" acts as a title, specifically for the paragraph class. All paragraphs are names (titles) and text.
class name
{
	public:
	//default constructor
	name(void);
	//constructor for name that takes in a title as an argument
	name(char * title_add);
	//copy constructor for name
	name(const name & in);
	//destructor for name
	~name(void);
	//adds in text
	void add_title(char * title_add);
	//remove the text
	void remove_title(void);
	//displays the title
	void disp_title(void);

	protected:
	//the acutal title of the item
	char * title;
};

//object "paragraph" is a text object
//it can read in text, store text, delete text, and
//display text.
class paragraph : public name
{
	public:
	//default constructor for paragraph
	paragraph(void);
	//constructor for paragraph that takes in text
	//and name as an argument
	paragraph(char * text_add, char * title_add);
	//copy constructor for paragraph
	paragraph(const paragraph & in);
	//destructor for the paragraph
	~paragraph(void);
	//adds in text
	void add_text(char * text_add);
	//removes text
	void remove_text(void);
	//displays text
	void disp_text(void);
	
	protected:
	//stores the text itself
	char * text;
};

//The node (decisions) will give the user choices of plot points to choose from
//and will be part of the adjacency list.
class node : public paragraph
{
        public:
        //default constructor for node
        node(void);
        //constructor when title and text are passed in as well as index
        node(char * text_add, char * title_add, int index);
        //copy constructor for node
        node(const node & in);
        //default destructor for node
        ~node(void);
        //traverse to the next item
        node * go_next(void);
	//link up with the next item
	void link_next(node * item_to_link);
	//wrapper-ish function to get the plot index
	int get_path(void);
        protected:
        //the index of the plot point that the node (decision)
        //points to
        int plot_index;
        //next decision possible
        node * next;
};



//The plot points have a title and text in addition to a marking
//so it will inherit the paragraph class
class plot : public paragraph
{
	public:
	//default constructor for plot
	plot(void);
	//constructor when title and text are passed in
	plot(char * text_add, char * title_add);
	//copy constructor for plot
	plot(const plot & in);
	//destructor for plot
	~plot(void);
	//add choices
	void add_choice(node & add);
	//view (and choose) choices
	void view_choice(void);
	//remove choices
	void remove_choices(void);
	//figures out the next index to advance to
	int next_plot(int traversals);
	//checks if head is null
	bool is_list(void);
	protected:
	//adjacency list of decisions
	node * head;

};

//the script itself is a graph, where the indexes are plot
//points and the adjancency list is a list of decisions
class script
{
	public:
	//default constructor for script
	script(void);
	//constructor for script that takes in the total size of the plot
	script(int size);
	//copy constructor for script
	script(const script & in);
	//default destructor for script
	~script(void);
	//clears the script
	void delete_all(void);
	//editing mode
	void edit(void);
	//viewing mode
	void view(void);
	//gets the user's choice for editing
	char edit_choice(void);
	
	protected:
	//array of plot pointers, creates plot points
	//first index, 0,  will be the introduction
	plot ** points;
	//number of plot entries
	int story_size;
	//new story?
	bool new_story;
};

