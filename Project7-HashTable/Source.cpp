/*
* Ian Fletcher
* CST-201
* 11/17/2022
* This is my own work with help from the slides in class
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//creates a constant int called length and sets it equal to 37
const int LENGTH = 37;
//creates an array of struct node pointers of size LENGTH
struct node* bucket[LENGTH];

//creates node
struct node
{
	string value;
	node* next = NULL;
};

//insert method that takes in a string [O(n)]
void insert(string input)
{
	//creates a new node called newNode
	struct node* newNode = new node;
	//creates int inputVal to store sum of ascii values of characters in input
	int inputVal = 0;
	//runs while i is less than the length of input
	for (int i = 0; i < input.length(); i++)
	{
		//adds ascii value of the current character to the current value of inputVal
		inputVal += int(input[i]);
	}
	//creates int hashed and sets it equal to inputVal mod length (hash equation)
	int hashed = inputVal % LENGTH;
	//sets the value of newNode to input
	newNode->value = input;
	//sets newNode next pointer equal to bucket at index hashed
	newNode->next = bucket[hashed];
	//sets bucket at index hashed equal to newNode
	bucket[hashed] = newNode;
}

//find method that takes in a string [O(n + m)]
bool find(string input)
{
	//creates new node
	struct node* temp = new node;
	//creates int inputVal equal to 0
	int inputVal = 0;
	//runs while i is less than the length of input
	for (int i = 0; i < input.length(); i++)
	{
		//adds ascii value of the current character to the current value of inputVal
		inputVal += int(input[i]);
	}
	//creates int hashed and sets it equal to inputVal mod length (hash equation)
	int hashed = inputVal % LENGTH;
	//sets temp equal to bucket at the index of hashed
	temp = bucket[hashed];
	//checks if bucket at index hashed is NULL and if so returns false
	if (bucket[hashed] == NULL)
	{
		return false;
	}
	//checks if the value at bucket[hashed] equals input and if so returns true
	else if (bucket[hashed]->value == input)
	{
		return true;
	}
	else
	{
		//runs while temp doesn't equal NULL
		while (temp != NULL)
		{
			//checks if the value at temp equals input and if so returns true
			if (temp->value == input)
			{
				return true;
			}
			//sets temp equal to temp->next to iterate through list
			temp = temp->next;
		}
		//return false if everything else if false
		return false;
	}
}

//display method [O(n * m)]
void display()
{
	//creates new node pointer temp
	struct node* temp = new node;
	//creates int result 
	int result;
	//runs while i is less than length
	for (int i = 0; i < LENGTH; i++)
	{
		//sets result equal to i mod LENGTH
		result = i % LENGTH;
		//sets temp equal to bucket at the index of result
		temp = bucket[result];
		cout << i << ": ";
		//runs while temp isn't null
		while (temp != NULL)
		{
			//prints out result
			cout << temp->value << " ";
			//sets temp equal to temp->next to iterate through list
			temp = temp->next;
		}
		cout << "" << endl;
	}
	cout << "" << endl;
}

//main method
int main()
{
	//creates string word for importing from file
	string word;
	//creates string userInput for controlling while loop
	string userInput;
	//opens file as myFile
	ifstream myFile("Text.txt");
	//while there is a line to get, imports the line from myFile to word and inserts value
	while (getline(myFile, word))
	{
		myFile >> word;
		insert(word);
	}
	//displays values
	display();
	//runs while userInput isn't equal to -1
	while (userInput != "-1")
	{
		//prompts the user to enter a value to search for
		cout << "Enter word to search for: ";
		//takes in the input as userInput
		cin >> userInput;
		cout << " " << endl;
		//checks if find given userInput returns true and userInput isn't equal to -1
		//and if so prints out value was found
		if (find(userInput) && userInput != "-1")
		{
			cout << userInput << " was found" << endl;
		}
		//checks if find given userInput returns false and userInput isn't equal to -1
		//and if so prints out value wasn't
		else if(!find(userInput) && userInput != "-1")
		{
			cout << userInput << " was not found." << endl;
		}
	}
	//closes file
	myFile.close();
}