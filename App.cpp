#include"BinaryTree.h"
#include"BinaryTree.cpp"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<algorithm>
using namespace std;

//Name: Islam Osama Nwishy
//ID#: 900170200
//Assignment 5
//Filename: App.cpp


//PS. I wasn't able to read the script from a .docx file so i changed it to .txt
//So the program will only work properly with files of extention .txt for input
//I tried to find a way online but i couldn't find a solution that wasn't confusing to me.


//Global fstreams
ifstream input;
ofstream output;

//Functions Prototyping
string UpperCase(string x);
void InputFile(BinaryTree<string, int> Tree[], string Script, int& wordcount);
bool ShouldRemove(char c);
string ReadyString();
void Start(BinaryTree<string, int> Tree[], int& wordcount, int State);
int PreRun(BinaryTree<string, int> Tree[], int& wordcount);
void InputOld(BinaryTree <string, int> Tree[]);
void CleanAndAdd(BinaryTree<string, int>Tree[], int& wordcount);
bool Add(BinaryTree<string, int>Tree[], int& wordcount);
string Save(BinaryTree<string, int> Tree[]);
void SearchAndRetrive(BinaryTree<string, int> Tree[]);
void GetWordsofFreq(BinaryTree<string, int>Tree[]);



void main() {
	int WordCount = 0;											//Holds the word Count Entered to the Tree
	BinaryTree<string, int> Tree[26];							//A BinaryTree array of 26 elements (the number of english alphabets)
																//I didn't make slots for the numbers and stored them with the letters


	Start(Tree, WordCount, PreRun(Tree, WordCount));

	//Saving the Data Before Closing the Program
	if (WordCount > 0) {										//If there is Data in the Tree
		cout <<endl<< "If You Don't Want to Save Type 0 (You Will Lose Any Saved Data for the Next Run)";
		string filename = Save(Tree);							//Stores the file name of the save file chosen by the user
		if (filename != "0") {									//if the file is not called 0 then the data were saved
			output.open("RunFile.txt");							//RunFile.txt is a file that stores some data about the last run
			output << 1 << endl;								//1 means some data is saved
			output << filename << endl;							//Save the file name to retrieve it on the next run
			output << WordCount << endl;						//Save the word count to retrieve it on the next run
			output.close();

		}
		else {													//If the user chooses not the save
			output.open("RunFile.txt");
			output << 0;										//0 Means there is no data stored
			output.close();
		}
	}
	else {														//If there is no data in the Tree 
		output.open("RunFile.txt");								
		output << 0;											//0 Means there is no data stored
		output.close();
	}

	

	

}


//Checks the File RunFile.txt before starting the program to find a restore saved data if any
//Returns the state of the run, 0 means Initial Run, 1 Means Cumulative/Query Run
int PreRun(BinaryTree<string, int> Tree[], int& wordcount) {
	input.open("RunFile.txt");
	string in;
	if (input.fail()) {
		cout << "Couldn't find RunFile.txt" << endl;
		return 0;
	}

	getline(input, in, '\n');								//Takes the state of the Last Run 0 = no data stored, 1 = some data stored 
	if (in == "1") {
		string filename; 
		getline(input, filename, '\n');						//Take the save file destination
		getline(input, in, '\n');							//Take the word count
		wordcount = atoi(in.c_str());						//Update the program's word count
		input.close();
		input.open(filename);								//Open the save file
		if (input.fail()) {
			return 0;
		}
		InputOld(Tree);										//Input the saved data
		return 1;
	}
	else {
		input.close();
		return 0;
	}
	
	
}

//Inputs the Old data saved by the last run
void InputOld(BinaryTree <string, int> Tree[]) {
	string Key, Data, dummy;
	
	getline(input, dummy, '\n');							//dummy string to remove the headings
	while (!input.eof()) {
		getline(input, Key, ',');							//take the key
		getline(input, Data, '\n');							//take the data
		Tree[Key[0] % 25].Insert(Key, atoi(Data.c_str()));	//Input them to the Tree
	}
	input.close();
}

//Takes the whole text file and prepares it to be inputed to the Tree
//Returns the String ready to be inputed to the tree
string ReadyString() {
	string word, all;
	while (!input.eof())
	{
		getline(input, word, '\n');								//Take line by line
		word.push_back(' ');									//Add Space (instead of the end of line)
		all.append(word);										//Append the line to the string that will store the whole file
	}
	input.close();
	replace_if(all.begin(), all.end(), ShouldRemove,' ');		//Remove any non ascii characters as well as anything that is not
																//alphanumeric or a space or an apostrophe
	return all;
}

//Takes a string and inputs it to the Tree word by word
void InputFile(BinaryTree<string, int> Tree[], string Script, int& wordcount) {
	int alpha = 0; string word, Key;
	istringstream iss(Script);									//input string stream (just makes it easier for me to process the string)
	
		while (iss>>word) {										//input the string word by word (every word is seperated by a space)
			Key = UpperCase(word);
			alpha = (int(Key[0])) % 25;							//alpha is the index of the key in the array (based on the first letter)
																//Every alphabet has a unique index but numbers overlap with them
			if (!Tree[alpha].Insert(Key, 1))					//Insert each word with an occurance of 1
				Tree[alpha].Update(Key, (Tree[alpha].Retrive(Key) + 1));	//if a word already exists update its data by 1
			else
				wordcount++;									//increment wordcount with each unique word added
			
		}
}

//Changes all characters of a string to uppercase (to remove case sensitivity)
string UpperCase(string x) {
	transform(x.begin(), x.end(), x.begin(), ::toupper);
	return x;
}

//Decides which characters are left in the text file (ascii, alphanumeric, spaces and or apostrophes)
bool ShouldRemove(char c) {
	if (isascii(c))
		if (isspace(c)|| isalnum(c)||c=='\'')
			return false;
	return true;
}


//Entry Point of the Program
//Takes the command from the user and calls the appropriate function to process it
void Start(BinaryTree<string, int> Tree[],int& wordcount, int state) {

	int command = 0;						//Holds the choice of the user for a process
	string dummy, FileName;

	cout << "Welcome To the Word Search";

	//In case that this is the Initial Run
	if (state == 0) {						
		while (command != 2) {			//Exit Case for the intital Run State
			cout << endl << endl << "There is No Saved Dictionary\n" << "So You Can:" << endl;
			cout << "\t1- Input a new text file and create a Dictionary of it\n\t2- Exit the program\n\n";
			cout << "Please Enter your Choice [1,2]" << endl;
			cin >> command;
			getline(cin, dummy);		//Dummy to get rid of the (cin) leftovers
			if (cin.fail()) {			//Check if the input does not suite the type int
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				command = 0;
			}


			switch (command)
			{
			case 1:
				if (Add(Tree, wordcount))							//Input a Text file to build a dictionary out of
					command = 2;									//If this process is successful exit the inital state 
				break;
			case 2:													//Exit Case for the program
				return;
			default:
				cout << "Wrong Input! Please Try Again" << endl;

			}
		}
	}

	while (command != 8) { //Exit case

		cout << endl << endl << "You Can:" << endl << endl;
		cout << "\t1- Input a new text file and create a Dictionary of it (This Will Remove Any Exsisting Dictionary)\n\t2- Input a new text file and update the Dictionary";
		cout << "\n\t3- Save the Dictionary to a File\n\t4- Find how many words are there in the Dictionary\n\t";
		cout << "5- Search for the frequancy of a word\n\t6- Search for all words >= a given frequancy\n\t";
		cout << "7- List all words and their frequancies\n\t8- Exit the program\n\n";
		cout << "Please Enter your Choice [1,2,3,4,5,6,7,8]" << endl;
		cin >> command;
		getline(cin, dummy);		//Dummy to get rid of the (cin) leftovers
		if (cin.fail()) {			//Check if the input does not suite the type int
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			command = 0;
		}


		switch (command) {
		case 1:
			CleanAndAdd(Tree, wordcount);						//Delete the Previous Dictionary and start a new one from an given file
			break;
		case 2:
			Add(Tree,wordcount);								//Accumalate the data collected from a file to the existing Dictionary
			break;
		case 3:
			Save(Tree);											//Save the Tree to a File specified by the user
			break;
		case 4:
			cout << endl << "There Are: " << wordcount << " Words in the Dictionary" << endl;	//output word count
			break;
		case 5:
			SearchAndRetrive(Tree);								//Search and Retrieve a given word and its frequancy
			break;
		case 6:
			GetWordsofFreq(Tree);								//Search and Retrieve all words that are <= a given frequancy
			break;
		case 7:
			cout << "Word\t\tFrequancy" << endl;				//Output all the Dictionary to the screen
			for (int i = 0; i < 26; i++)
				Tree[i].Traverse();
			break;
		case 8:													//Exit Case
			break;
		default:
			cout << "Wrong Input! Please Try Again" << endl;
			break;
		}
	}
}


//Deletes the Current Dictionary, if any, and Creates a new one using a given Text file
void CleanAndAdd(BinaryTree<string, int>Tree[], int&wordcount) {
	string FileName;

	cout << "Please Enter the New Text File Destination" << endl;
	getline(cin, FileName);
	input.open(FileName);									//Take the file's name
	if (input.fail()) {										//Only Delete if you can open the file
		input.close();
		cout << "Error! Couldn't Open the File Please Try Again" << endl;
		return;
	}

	cout << endl << "Deleting the Original Tree ..." << endl;
	for (int i = 0; i < 26; i++)							//Delete the old Dictionary
		Tree[i].DeleteTree();

	cout << "Done!" << endl << "Reading and Creating the new Dictionary ..." << endl;
	wordcount = 0;
	InputFile(Tree, ReadyString(),wordcount);				//Input the new one
	cout << "Done!" << endl;
	
	
}


//Adds a new Tree and Accumalates its data to the original dictionary, if any.
bool Add(BinaryTree<string,int>Tree[], int&wordcount) {
	string FileName;
	cout <<endl <<"Please Enter the New Text File Destination" << endl;
	getline(cin, FileName);											//Take the file's name
	input.open(FileName);

	if (input.fail()) {
		input.close();
		cout << "Error! Couldn't Open the File. Please Try Again" << endl;
		return false;
	}

	cout << endl << "Reading the Text File and Adding it to the Dictionary ..." << endl;
	InputFile(Tree, ReadyString(),wordcount);						//Add the text to the Tree
	cout << "Done!" << endl;
	return true;

	
}

//Saves the Dictionary to a given file
//0 means you do not want to save
string Save(BinaryTree<string, int> Tree[]) {
	string FileName;
	cout <<endl <<"Please Enter a Save File Destination" << endl;
	getline(cin, FileName);											//Take the file's name

	if (FileName == "0")
	{
		output.close();
		cout << "Error! Couldn't Open the File. Please Try Again" << endl;
		return FileName;
	}

	output.open(FileName);
	if (output.fail()) {
		output.close();
		cout << "Error! Couldn't Open the File. Please Try Again" << endl;
		return FileName;
	}

	cout << endl << "Outputing the Values to the file ..." << endl;

	output << "Word,Frequancy";
	for (int i = 0; i < 26; i++)									//Save
		Tree[i].Traverse(output);							//Traverse to a file

	cout << "Done!" << endl;
	output.close();
	return FileName;
}

//Searches and Retrives the frequancy of a given word
void SearchAndRetrive(BinaryTree<string, int> Tree[]) {
	string word, dummy;
	cout << endl << "Please Enter a Word to Search" << endl;
	cin >> word;				//Takes the word
	getline(cin, dummy);		//Dummy to get rid of the (cin) leftovers

	int Freq = Tree[int(toupper(word[0])) % 25].Retrive(UpperCase(word));		//Retrives the word
	if (Freq != NULL)															//If you found it output the word and its frequancy
		cout << endl << "The Frequancy for the word " << word << " is " << Freq << endl;
	else
		cout << "Could not find the word" << endl;								//word does not exist
}


//Searches for Words >= a certain Frequancy
void GetWordsofFreq(BinaryTree<string, int>Tree[]) {
	int freq = 0; string dummy;
	cout << endl << "Please Enter a Frequancy" << endl;
	cin >> freq;				//Takes in the frequancy
	getline(cin, dummy);		//Dummy to get rid of the (cin) leftovers
	if (cin.fail()) {			//Check if the input does not suite the type int
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		freq = 0;
	}
	
	if (freq <= 0) {			//if the inputed frequancy is less than or equal to 0 then no words exist
		cout << "Can't find words with frequancy <= 0" << endl;
		return;
	}

	cout << endl;
	for (int i = 0; i < 26; i++)	//Find and Output words under a certain frequancy in each alphabet
		Tree[i].ReverseRetrive(freq);
}