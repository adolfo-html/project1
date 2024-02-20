#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// Adolfo Chavez - Operating Systems Assignment 1

// Step 1: Declare global variables / constructor methods

// Declaring register variable OUTSIDE of the scanInst function so that it doesn't get declared/set to 0 every time I call it
int r[10] = {0};
string ram[1000];

// count is initially 0, then increments with every instruction process
int count = 0;

void printRegisters(int *r);

string getValue(int n)
{
	if (n > 9)
	{
		if (n > 99)
		{
			return to_string(n);
		} else {
			return "0" + to_string(n);
		}
	} else {
		return "00" + to_string(n);
	}
}


// scanInst is for verifying valid input, then executing the right functions based on the instruction.
int scanInst(string input)
{

// Step 3: Preprocessing stuff (making sure input is good)

	// Collect the first 3 characters of the input.
	char inst[3] = {input[0], input[1], input[2]};

	// Make sure there are no letters.

	// For all 3 chars...
	for (int i = 0; i < 3; i++)
	{
		// Check if char is a number. Most frustrating part.
		bool ugh = inst[i] == '0' || inst[i] == '1' || inst[i] == '2' || inst[i] == '3' || inst[i] == '4' || inst[i] == '5' || inst[i] == '6' || inst[i] == '7' || inst[i] == '8' || inst[i] == '9';
		if (!ugh)
		{
			cout << "+ + + + SYNTAX ERROR + + + +\n";

			// This needs to be here or it will cause a buffer overflow. Don't know why.
			return 0;
		}
	}

	// Exit program if instruction is 100.
	if (inst[0] == '1' && inst[1] == '0' && inst[2] == '0')
	{
		cout << "+ Process exiting ...\n";
		printRegisters(r);
		count++;
		return 0;
	}

// Preprocessing done! Now figure out what operation to do.

// Change operands (second and third numbers) into int variable type, for math
	int d = inst[1] - '0';
	int n = inst[2] - '0';

	// Determine operation from 1st character.
	// Execute corresponding operation.
	// You know what I might not even need a designated function for all of these things cause they're so dang simple. So let's not complicate things

	switch (inst[0])
	{
		case '0':
			if (n != 0)
				cout << "Register " << d << ": " << getValue(d) << "\n";
			break;
		case '1':
			cout << "+ + + NO OPERATION DEFINED + + +\n";
			break;
		case '2':
			r[d] = n;
			cout << "+ Process complete\n";
			break;
		case '3':
			r[d] = r[d] * n;
			cout << "+ Process complete\n";
			break;
		case '4':
			r[d] += n;
			cout << "+ Process complete\n";
			break;
		case '5':
			r[d] = r[n];
			cout << "+ Process complete\n";
			break;
		case '6':
			r[d] = r[d] * r[n];
			cout << "+ Process complete\n";
			break;
		case '7':
			r[d] = r[d] + r[n];
			cout << "+ Process complete\n";
			break;
		case '8':
			r[d] = r[n];
			break;
		case '9':
			
			break;
	}

	// Increase count every time an instruction is processed
	count++;

	return 0;
}

// Step 2: Processing functions
// REMBER: You might not even NEED to have a designated function for all of these things.

// To indicate that the variable you're passing to a function is an array, you have to put the * symbol before the variable name. I don't know.
void printRegisters(int *r)
{
	for (int i = 0; i < 10; i++)
		cout << "Register " << i << ": " << getValue(r[i]) << "\n";
}

// REMINDER: int will be at the bottom of the program just to make sure C++ doesn't want me to declare any more functions before it

int main()
{
// Step 0: Make interface for input collection
	cout << "+ +  WELCOME  + +\n\n\n";
	cout << "-- Description --\n";
	cout << "Input the name of the text file you want to execute.\n";
	cout << "Every entry must be a 3 digit number to execute instructions.\n";
	cout << "They also have to be on their own line of text.\n";
	cout << "1st number determines what command you will use.\n";
	cout << "2nd number is the register you will affect.\n";
	cout << "3rd number is the value you operate with.\n\n";

// The input has to be a string. This is because if you type a 0 as the first number...
// The int variable removes it. You have to detect '0' instructions too.
// So you can't check if it's from 100 to 999. Sigh.


// IMPORTANT: I need to implement the instructions in RAM thing.
// So I need to get the instructions from the text file and sequentially set them in the RAM array.
// I plan on doing this by getting the instructions as an INT instead of a string.
// So, to optimize a little, I'm going to try to change the initial string myText to an int at first.
// This can be problematic but I'm not sure. Because I don't know if the getline function will accept an int value.

// Looks like that didn't work

// Now I'm gonna try getting it as a string, then I'll convert the string to an int later for operation.
// That works

// HOW TO READ DATA FROM A FILE! :)

	// Designated string variable for each instruction
	string myText;

	// Designated string for file name
	string fileName;

	// Get name of file to read instructions from
	cout << "# FILENAME: ";
	cin >> fileName;

	// Remember to set the ifstream object AFTER you have a value for fileName...
	ifstream file(fileName);
	ifstream file1(fileName);

	// The getline function will collect text line by line. Two parameters: your file, and the text variable the output is going to.
	// This while loop is cool because it makes it so the program goes through all the lines/instructions, and stops when there are no more lines. Nice
	
	// Collecting instructions in RAM
	int instCount = 0;
	while (getline(file, myText))
	{
		ram[instCount] = myText;
		instCount++;
	}
	// WORKS!

// So here it's getting all the instructions and setting it to its sequential ram position.
// Afterwards the next getline function (below) doesn't read anything, so let me try setting the ifstream object again.

//	ifstream file(fileName); The object was previously declared! So I have to make a new "file" filename, I guess. I'll just make two up above and be done with it...
	
	while (getline(file1, myText))
	{
		cout << "+ Executing instruction " << myText << " ... \n";
		scanInst(myText);
	}

	// Notify if no instructions executed
	cout << "\nNumber of instructions executed: " << count << "\n";
	if (count == 0)
		cout << "Since 0 instructions were executed, check if you got the file name right\n";

	return 0;
}
