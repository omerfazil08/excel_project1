#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip> // for setw
#include <algorithm> // for max
using namespace std;
struct StudentRecord {
public:
	StudentRecord(
		string goup,
		string quetion,
		int id,
		string Ignore
	) {
		group = goup;
		question = quetion;
		studentId = id;
		ignore = Ignore;
	}
	string group;
	string question;
	int studentId;
	string ignore;
};
void WholeText(const string& outputFileName, const vector<StudentRecord>&
	students) {
	ofstream outputFile(outputFileName);
	if (!outputFile.is_open()) {
		cerr << "Error creating output file: " << outputFileName << endl;
		return;
	}
	map<int, map<string, vector<string>>> studentData; // Store data for each student
		for (const auto& student : students) {

			studentData[student.studentId][student.group].push_back(student.question);
		}
	// Write the header line
	outputFile << left << setw(10) << "Student list" << ";" << left << setw(20) <<
		"GroupName" << ";" << left << "QuestionsAnswered\n";
	// Write each student's information
	for (const auto& studentDataItem : studentData) {
		int studentId = studentDataItem.first;
		const auto& groups = studentDataItem.second;
		for (const auto& groupData : groups) {
			const string& group = groupData.first;
			const vector<string>& questions = groupData.second;
			outputFile << left << setw(10) << studentId << ";" << left << group <<
				";" << left;
			for (size_t i = 0; i < questions.size(); ++i) {
				outputFile << questions[i];
				if (i < questions.size() - 1) {
					outputFile << ",";
				}
			}
			outputFile << "\n";
		}
	}
	outputFile.close();
}
int main() {
	ifstream inputFile;
	inputFile.open("C:\\Users\\omer-\\Desktop\\ders\\COMA 1.1\\EE101\\lanet\\file_list.csv");
	string line = "";
	vector<StudentRecord> students;
	while (getline(inputFile, line)) {
		stringstream inputString(line);
		string group;
		string question;
		int studentId;
		string ignore;
		string tempString;
		getline(inputString, group, '_');
		getline(inputString, question, '_');
		getline(inputString, tempString, '_');
		studentId = atoi(tempString.c_str());
		getline(inputString, ignore, '.');
		StudentRecord student(group, question, studentId, ignore);
		students.push_back(student);
		line = "";
	}
	WholeText("C:\\Users\\omer-\\Desktop\\ders\\COMA 1.1\\EE101\\lanet\\output.csv", students);
	return 0;
}
