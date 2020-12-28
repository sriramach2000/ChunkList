#include <iostream>
#include <string>
#include "ChunkList2.h"
using namespace std;

int main()
{

	ChunkList<int> chunk_obj;

	ifstream inFile;       // file containing operations
	ofstream outFile;      // file containing output
	string inFileName;     // input file external name
	string outFileName;    // output file external name
	string outputLabel;
	string command;        // operation to be executed
	int list_item;

	// Prompt for file names, read file names, and prepare files
	cout << "Enter name of input command file; press return." << endl;
	cin >> inFileName;
	inFile.open(inFileName.c_str());

	cout << "Enter name of output file; press return." << endl;
	cin >> outFileName;
	outFile.open(outFileName.c_str());

	cout << "Enter name of test run; press return." << endl;
	cin >> outputLabel;

	outFile << outputLabel << endl;

	if (!inFile)
	{
		cout << "File not found." << endl;
		exit(2);
	}
	inFile >> command;
	while (command != "Quit") {
		// tested append works! 
		if (command == "Append") {
			inFile >> list_item;
			chunk_obj.Append(list_item);
			cout << "Appending" << " " << list_item << " " << "to link list" << endl;
			outFile << "Appending" << " " << list_item << " " << "to link list" << endl;
		}
		// returns correct amount
		// tested check! 
		else if (command == "GetLength") {

			cout << "Total length of list:" << " " << chunk_obj.GetLength() << endl;
			outFile << "Total length of list:" << " " << chunk_obj.GetLength() << endl;
		}
		// tested check! 
		// gives correct number at respective index!
		else if (command == "GetIndex") {
			inFile >> list_item;
			cout << "Item at index" << " " << list_item << " " << "is" << " " << chunk_obj.GetIndex_value(list_item) << endl;
			outFile << "Item at index" << " " << list_item << " " << "is" << " " << chunk_obj.GetIndex_value(list_item) << endl;
		}
		// WORKS!
		else if (command == "Contains")
		{
			inFile >> list_item;
			if (chunk_obj.Contains(list_item) == false) {
				cerr << list_item << " " << "is no longer in list" << endl;
				outFile << list_item << " " << "is no longer in list" << endl;
			}
			else {
				cout << "Item " << " "<< list_item << " " << "exists" << endl;
				outFile << "Item " << " " << list_item << " " << "exists" << endl;
			}

		}
		else if (command == "Print") {
			cout << "printing list" << endl;
			outFile << "printing list" << endl;
			chunk_obj.Print(cout);
			chunk_obj.Print(outFile);

		}
		else if (command == "Remove") {
			inFile >> list_item;
			chunk_obj.Remove(list_item);
			cout << "removing" << " " << list_item << " from link list"<<endl;
			outFile << "removing" << " " << list_item << " from link list" << endl;
		}

		// ask if this is the best way to write it
		// WORKS! (the noob way)
		else if (command == "IsEmpty") {
			// I want to direct whatever the return of isEmpty is to true to make 
			// sure I know that it does not output the wrong cout statement
			if (chunk_obj.IsEmpty() == false) {
				cout << "list has items" << endl;
				outFile << "list has items" << endl;
			}
		}

		inFile >> command;


	}
	return 0;
}
