// Name: Benjamin Cofield
// Banner_ID: 904218332
// Compile: g++...
// Sources:
// *
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;



// Struct to store file size, dat
struct FileData {
	vector<double> data;
	string fileName;
};

//Global variables to hold file data for input/output
FileData input_1, input_2, outputData;


//----- FUNCTIONS ----//
void readFile(FileData &fileData) {

	ifstream inStream;
	// Open file for reading
	inStream.open(fileData.fileName.c_str());

	if (inStream.fail()) {
		cout << "Input file opening failed." << endl;
		return;
	}

	// Read data values from file -> data array
	double value;
	while (inStream >> value) {
		fileData.data.push_back(value);
	}

	// Display list of values read from file
	cout << "The list of " << fileData.data.size() << " values in file " << fileData.fileName << " is: " << endl;
	for (const double val : fileData.data) {
		cout << val << endl;
	}
	cout << endl;


	inStream.close();

	}




void mergeSort() {
	return;
}

void displayNumbers() {
	return;
}

void writeFile() {
	return;
}


//----- MAIN ----//
int main () {
	int numOfFiles;
	vector<FileData> filesData;

	cout << "*** Welcome to Ben's Data Analyzer ***" << endl;

	// Prompt user of # of files to read
	cout << "Enter the number of files to read: ";
	cin >> numOfFiles;
	cin.ignore();

	for (int i = 1; i <= numOfFiles; i++) {
		FileData fileData;
		cout << "Enter the filename for file " << i << ": ";

		cin >> fileData.fileName;
		if (fileData.fileName == "quit") {
			break;
		}
		readFile(fileData);
		filesData.push_back(fileData);
	}


	//readFile(input_1);
	//readFile(input_2);
	//mergeSort();
	//displayNumbers();
	//writeFile();
}


/*
for (const FileData &fileData : filesData) { // Iterate through each object
for (const double val : fileData.data) { //access data vector of each object
cout << val << endl;
}

}