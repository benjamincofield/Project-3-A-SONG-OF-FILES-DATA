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
vector<pair<string, double>> allChronologicalData;


// Struct to store file size, dat
struct FileData {
	vector<pair<string, double>> dataWithTimeStamps;
	vector<pair<string, double>> chronologicalData;
	string fileName;
};

//Global variables to hold file data for input/output
FileData outputData;

//---------------------------------------------------------------------------------------------------------------------------------------//
// Find Any Malforms
bool isMalform(FileData& fileData) {
	ifstream inputFile(fileData.fileName);

	if (!inputFile.is_open()) {
		cout << "File not found. Please try again." << endl;
		return true;
	}

	string line;
	bool hasValidContent = false;

	while (getline(inputFile, line)) {
		// Check for tab character in the line
		if (line.find('\t') == string::npos) {
			cout << "Not an input file. Illegal content/structure detected (missing tab). Please try again." << endl;
			inputFile.close();
			return true; // YES Malform
		}

		stringstream ss(line);
		double number;
		string timestamp;

		// Attempt to parse the value and timestamp from the line
		if (ss >> number && getline(ss, timestamp, '\t')) {
			// If we successfully read a number and a timestamp, we have valid content
			hasValidContent = true;
		} else {
			cout << "Not an input file. Illegal content/structure detected. Please try again." << endl;
			inputFile.close();
			return true; // YES Malform
		}
	}

	inputFile.close();

	if (!hasValidContent) {
		cout << "No valid content found in the file." << endl;
		return true; // Malform if no valid content found
	}

	return false; // NO Malform
}
//---------------------------------------------------------------------------------------------------------------------------------------//
// Sort the data by its timestamp
void sortDataByTimestamp(FileData& fileData) {
	fileData.chronologicalData = fileData.dataWithTimeStamps; // Copy data
	sort(fileData.chronologicalData.begin(), fileData.chronologicalData.end(),
	     [](const pair<string, double>& first, const pair<string, double>& second) {
	         return first.first < second.first; // Sort by timestamp
	     });

	// Add sorted data from this file to the global allChronologicalData
	allChronologicalData.insert(allChronologicalData.end(),
			    fileData.chronologicalData.begin(),
			    fileData.chronologicalData.end());
}

// Display the sorted data by timestamp
void displaySortDataByTimeStamp(const FileData& fileData) {
	cout << "Chronologically sorted list of " << fileData.chronologicalData.size() << " values:\n";
	for (const auto& value : fileData.chronologicalData) {
		cout << value.second << " ";
	}
	cout << endl;
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
			fileData.dataWithTimeStamps.push_back(make_pair(timestamp, value));
			allData.push_back(value);
		}

	}

	// Display list of values read from file
	cout << "The list of " << fileData.dataWithTimeStamps.size() << " values in file " << fileData.fileName << " is: " << endl;
	for (const auto& entry : fileData.dataWithTimeStamps) {
		cout << entry.second << "\t" << entry.first << endl;
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

void displayNumbers(vector<double>& allData, const vector<FileData>& filesData) {
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

	// Display sorted data by timestamps for each file
	cout << "\nThe chronologically sorted list of " << allChronologicalData.size() << " values is:\n";
	for (const auto& value : allChronologicalData) {
		cout << value.second << " ";
	}
	cout << endl << endl;

	// Extract only numeric data from allChronologicalData
	vector<double> chronologicalValues;
	for (const auto& value : allChronologicalData) {
		chronologicalValues.push_back(value.second);
	}

	// Calculate Mean, Median, Mode
	cout << "The mean is " << calculateMean(chronologicalValues) << endl;
	cout << "The median is " << calculateMedian(chronologicalValues) << endl;
	cout << "The mode is " << calculateMode(chronologicalValues) << endl;
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

	// Display sorted data by timestamps for each file
	outStream << "\nThe chronologically sorted list of " << allChronologicalData.size() << " values is:\n";
	for (const auto& value : allChronologicalData) {
		outStream << value.second << " ";
	}
	outStream << endl << endl;

	// Extract only numeric data from allChronologicalData
	vector<double> chronologicalValues;
	for (const auto& value : allChronologicalData) {
		chronologicalValues.push_back(value.second);
	}

	// Calculate Mean, Median, Mode
	outStream << "The mean is " << calculateMean(chronologicalValues) << endl;
	outStream << "The median is " << calculateMedian(chronologicalValues) << endl;
	outStream << "The mode is " << calculateMode(chronologicalValues) << endl;

	cout << "***File " << outputFileName << " has been written to disk ***" << endl
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
		sortDataByTimestamp(fileData);
		filesData.push_back(fileData);
	}

	// Merge Sort & Display The Numbers
	if (!filesData.empty()) {
		mergeSort(allData, 0, allData.size() - 1);
	}

	displayNumbers(allData, filesData);

	cout << "Enter the output filename to save: ";
	string outputFileName;
	cin >> outputFileName;
	writeFile(outputFileName, allData);
}





