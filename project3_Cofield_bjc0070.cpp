// Name: Benjamin Cofield
// Banner_ID: 904218332
// Compile: g++...
// Sources:
// *
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


vector<double> allData;

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
		allData.push_back(value);
	}

	// Display list of values read from file
	cout << "The list of " << fileData.data.size() << " values in file " << fileData.fileName << " is: " << endl;
	for (const double val : fileData.data) {
		cout << val << endl;
	}
	cout << endl;


	inStream.close();

	}


void merge (vector<double>& arr, int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	vector<double> L(n1), R(n2);

	for (int i = 0; i < n1; i++)
		L[i] = arr[left + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[mid + 1 + j];

	int i = 0, j = 0, k = left;

	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k++] = L[i++];
		} else {
			arr[k++] = R[j++];
		}
	}

	while (i < n1) {
		arr[k++] = L[i++];
	}

	while (j < n2) {
		arr[k++] = R[j++];
	}
}

void mergeSort(vector<double>& arr, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
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

	// Merge Sort & Display The Numbers
	if (!filesData.empty()) {
		mergeSort(allData, 0, allData.size() - 1);
	}

	for (const double val : allData) { // Iterate through each object
		cout << val << endl;

	}
	//mergeSort();
	//displayNumbers();
	//writeFile();
}



