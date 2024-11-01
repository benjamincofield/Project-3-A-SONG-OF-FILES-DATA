// Name: Benjamin Cofield
// Banner_ID: 904218332
// Compile: g++...
// Sources:
// *
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;


vector<double> allData;

// Struct to store file size, dat
struct FileData {
	vector<double> data;
	string fileName;
	vector <string> timestamps;
};

//Global variables to hold file data for input/output
FileData input_1, input_2, outputData;

//---------------------------------------------------------------------------------------------------------------------------------------//
// Find Any Malforms
bool isMalform(FileData& fileData) {
	ifstream inputFile(fileData.fileName);

	if (!inputFile.is_open()) {
		cout << "File not found. Please try again." << endl;
		return true;
	}

	// Check for tab character
	string line;
	while (getline(inputFile, line)) {}
	size_t tabPos = line.find('\t');
	if (tabPos == string::npos) {
		cout << "Not an input file. Illegal content/structure detected. Please try again."<< endl;
		inputFile.close();
		return true;
	}
	double number;

	while (getline(inputFile, line)) {
		//Parse each line to double
		try {
			number = stod(line);
		} catch(...) {
			cout << "Not an input file. Illegal content/structure detected. Please try again."<< endl;
			inputFile.close();
			return true; // YES Malform
		}
	}
	inputFile.close();
	return false; // NO Malform

}


//---------------------------------------------------------------------------------------------------------------------------------------//
// Read All Files
void readFile(FileData &fileData) {

	// Check for malformations
	if (isMalform(fileData)) {
		return;
	}

	ifstream inStream;
	// Open file for reading
	inStream.open(fileData.fileName.c_str());

	if (inStream.fail()) {
		cout << "Input file opening failed." << endl;
		return;
	}

	// Read data values from file -> data array
	string line;
	while (getline(inStream, line)) {
		stringstream ss(line);
		string timestamp;
		double value;

		if (ss >> value >> timestamp) {
			fileData.data.push_back(value);
			fileData.timestamps.push_back(timestamp); // Save the timestamp
			allData.push_back(value);
		}
	}

	// Display list of values read from file
	cout << "The list of " << fileData.data.size() << " values in file " << fileData.fileName << " is: " << endl;
	for (int i = 0; i < fileData.data.size(); ++i) {
		cout << fileData.data[i] << "\t" << fileData.timestamps[i] << endl;
	}
	cout << endl;


	inStream.close();

	}

//---------------------------------------------------------------------------------------------------------------------------------------//
// Merge Function
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

//---------------------------------------------------------------------------------------------------------------------------------------//
// Function MergeSort
void mergeSort(vector<double>& arr, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------//
// Calculate the Mean
double calculateMean(vector<double>& arr) {
	double sum = 0.0;
	for (double val : arr) {
		sum += val;
	}
	return (sum / arr.size());
}

//---------------------------------------------------------------------------------------------------------------------------------------//
// Calculate the Median
double calculateMedian(vector<double>& arr) {
	if (arr.empty()) return 0;
	if (arr.size() % 2 == 1) {
		return arr[arr.size() / 2];
	} else {
		return (arr[arr.size() / 2 - 1] + arr[arr.size() / 2]) / 2;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------//
// Calculate the Mode
double calculateMode(vector<double>& arr) {
	unordered_map<double, int> frequency;
	double mode = arr[0];
	int maxFreq = 0;

	// Populate frequency map and find the max frequency
	for (double num : arr) {
		frequency[num]++;
		if (frequency[num] > maxFreq) {
			maxFreq = frequency[num];
			mode = num;
		}
	}

	return mode;
}

void displayNumbers(vector<double>& allData) {
	cout << "*** Summarized Statistics ***" << endl << endl;

	// Display Sorted Values
	cout << "The orderly sorted list of " << allData.size() << " values is: " << endl;

	for (const double val : allData) { // Iterate through each object
		cout << val << " ";
	}
	cout << endl << endl;

	// Calculate Mean, Median, Mode
	cout << "The mean is " << calculateMean(allData) << endl;
	cout << "The median is " << calculateMedian(allData) << endl;
	cout << "The mode is " << calculateMode(allData) << endl;
}



void writeFile(const string &outputFileName, vector<double>& allData) {
	ofstream outStream(outputFileName);

	//Write sorted data
	outStream << "*** Summarized Statistics ***:\n\n"
	<< "The orderly sorted list of " << allData.size() << " is:" << endl;
	for (const double val : allData) {
		outStream << val << " ";
	}
	outStream << endl << endl;

	outStream << "The mean is " << calculateMean(allData) << endl;
	outStream << "The median is " << calculateMedian(allData) << endl;
	outStream << "The mode is " << calculateMode(allData) << endl;

	cout << "File " << outputFileName << " has been written to disk ***" << endl
	<< "*** Goodbye ***";
	outStream.close();
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

	// Merge Sort & Display The Numbers
	if (!filesData.empty()) {
		mergeSort(allData, 0, allData.size() - 1);
	}

	displayNumbers(allData);

	cout << "Enter the output filename to save: ";
	string outputFileName;
	cin >> outputFileName;
	writeFile(outputFileName, allData);
}





