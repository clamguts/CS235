#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

void parseStudentName(string name[], int i, string studentName);

void parseStudentScores(int* studentScores[], int num_exams, int i, string line);

void parseNamesAndGrades(string name[], int num_exams, string* studentGrades[], double averages[], int* studentScores[], int i);

void parseExamsAndNumOfGrades(int* numofGrades[], int e, int num_exams, int num_students, string* studentGrades[], const int& NUM_LETTERS);

void calcAvg(int* studentScores[], int num_exams, int num_students, double averages[]);

void memCleanUp(int* studentScores[], string names[], double averages[], int num_students, string* studentGrades[], int num_exams, int* numofGrades[]);

string calcGrade(double average, int score, string grade);

int getIndex(string grade);

void printNamesScores(int* studentScores[], string names[], int num_exams, int num_students, ofstream& out)
{
	out << "Student Scores: " << endl;
	for (int i = 0; i < num_students; ++i)
	{
		out << setw(20) << names[i];
		for (int j = 0; j < num_exams; ++j)
		{
			out << fixed << setprecision(0) << setw(6) << studentScores[i][j] << " ";
		}
		out << endl;
	}
}

void printAverages(double averages[], int num_exams, ofstream& out)
{
	out << "Exam Averages: " << endl;
	for (int i = 0; i < num_exams; ++i)
	{
		out << "    Exam " << i + 1 << " Average = " << setw(6) << fixed << setprecision(1) << averages[i];
		out << endl;
	}
}

void printNamesScoresWithGrade(int* studentScores[], double averages[], string names[], int num_exams, int num_students, string* studentGrades[], ofstream& out)
{
	out << "Student Exam Grades: " << endl;
	for (int i = 0; i < num_students; ++i)
	{
		out << setw(20) << names[i];
		for (int j = 0; j < num_exams; ++j)
		{
			out << fixed << setprecision(0) << setw(6) << studentScores[i][j] << "(" << studentGrades[i][j] << ") ";
		}
		out << endl;
	}
}

void printNumofEachLetter(int num_exams, int* numofGrades[], const int& NUM_LETTERS, ofstream& out)
{
	out << "Exam Grades: " << endl;
	for (int i = 0; i < num_exams; ++i)
	{
		out << "    Exam " << i + 1 << setw(6);
		for (int j = 0; j < NUM_LETTERS; ++j)
		{
			out << setw(6) << numofGrades[i][j];
			if (j == 0)
			{
				out << "(A)";
			}
			else if (j == 1)
			{
				out << "(B)";
			}
			else if (j == 2)
			{
				out << "(C)";
			}
			else if (j == 3)
			{
				out << "(D)";
			}
			else if (j == 4)
			{
				out << "(E)";
			}
		}
		out << endl;
	}
}

const int NUM_LETTERS = 5;

int main(int argc, char* argv[]) 
{

	VS_MEM_CHECK

	if (argc < 3)
	{
		cerr << "Please provide name of input and output files";
		return 1;
	}

	std::cout << "Input file: " << argv[1] << endl;
	ifstream in(argv[1]);
	if (!in)
	{
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}

	std::cout << "Output file: " << argv[2] << endl;
	ofstream out(argv[2]);
	if (!out)
	{
		in.close();
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}

	int num_students;
	int num_exams;
	in >> num_students >> num_exams;
	// Skip the rest of the line
	in.ignore(numeric_limits<int>::max(), '\n');

	string* names = new string[num_students];
	int** studentScores = new int* [num_students];
	
	for (int i = 0; i < num_students; ++i)
	{
		string line;
		getline(in, line);

		parseStudentName(names, i, line);
		parseStudentScores(studentScores, num_exams, i, line);
	}

	printNamesScores(studentScores, names, num_exams, num_students, out);

	double* averages = new double[num_exams];
	calcAvg(studentScores, num_exams, num_students, averages);
	printAverages(averages, num_exams, out);

	string** studentGrades = new string* [num_students];
	for (int i = 0; i < num_students; ++i)
	{
		parseNamesAndGrades(names, num_exams, studentGrades, averages, studentScores, i);
	}
	int** numofEachLetter = new int* [num_exams];
	for (int e = 0; e < num_exams; ++e)
	{
		parseExamsAndNumOfGrades(numofEachLetter, e, num_exams, num_students, studentGrades, NUM_LETTERS);
	}
	
	printNamesScoresWithGrade(studentScores, averages, names, num_exams, num_students, studentGrades, out);

	printNumofEachLetter(num_exams, numofEachLetter, NUM_LETTERS, out);

	memCleanUp(studentScores, names, averages, num_students, studentGrades, num_exams, numofEachLetter);

	return 0;
}

void parseStudentName(string name[], int i, string studentName)
{
	size_t p = 0;
	size_t q = 0;
	while (!isdigit(studentName[p])) ++p;
	q = p;
	while (!isalpha(studentName[q])) --q;

	name[i] = studentName.substr(0, (q + 1));
}

void parseStudentScores(int* studentScores[], int num_exams, int i, string line)
{
	int* scores = new int[num_exams];
	size_t p = 0;
	while (!isdigit(line[p])) ++p;

	istringstream iss(line.substr(p));
	for (int j = 0; j < num_exams; ++j)
	{
		iss >> scores[j];
	}

	studentScores[i] = scores;
}

void parseNamesAndGrades(string name[], int num_exams, string* studentGrades[], double averages[], int* studentScores[], int i)
{
	string* grades = new string[num_exams];
	string grade = "";
	for (int j = 0; j < num_exams; ++j)
	{
		double average = averages[j];
		int score = studentScores[i][j];
		grade = calcGrade(average, score, grade);
		grades[j] = grade;
	}

	studentGrades[i] = grades;
}

void parseExamsAndNumOfGrades(int* numofGrades[], int e, int num_exams, int num_students, string* studentGrades[], const int& NUM_LETTERS)
{
	int* numLetters = new int[NUM_LETTERS];
	for (int k = 0; k < NUM_LETTERS; ++k)
	{
		numLetters[k] = 0;
	}
	for (int s = 0; s < num_students; ++s)
	{
		string grade = studentGrades[s][e];
			int index = getIndex(grade);
			numLetters[index] += 1;
	}
	numofGrades[e] = numLetters;
}


void calcAvg(int* studentScores[], int num_exams, int num_students, double averages[])
{
	for (int i = 0; i < num_exams; ++i)
	{
		double sum = 0;
		for (int j = 0; j < num_students; ++j)
		{
			sum = sum + studentScores[j][i];
		}

		double average = sum / num_students;
		averages[i] = average;
	}
}
	 

 string calcGrade(double average, int score, string grade)
 {

	 if ((score <= (average + 5)) && (score >= (average - 5)))
	 {
		 grade = "C";

	 }
	 else if ((score < (average + 15)) && (score > (average + 5)))
	 {
		 grade = "B";

	 }
	 else if ((score > (average - 15)) && (score < (average - 5)))
	 {
		 grade = "D";

	 }
	 else if (score >= (average + 15))
	 {
		 grade = "A";

	 }
	 else if (score <= (average - 15))
	 {
		 grade = "E";
	 }

	 return grade;
 }

 int getIndex(string grade)
 {
	 int index = 0;
	 if (grade == "A")
	 {
		 index = 0;
	 }
	 else if (grade == "B")
	 {
		index = 1;
	 }
	 else if (grade == "C")
	 {
		index = 2;
	 }
	 else if (grade == "D")
	 {
		index = 3;
	 }
	 else if (grade == "E")
	 {
		index = 4;
	 }
	 return index;
 }
 

void memCleanUp(int* studentScores[], string names[], double averages[], int num_students, string* studentGrades[], int num_exams, int* numofGrades[])
{
	for (int i = 0; i < num_students; ++i)
	{
		delete[] studentScores[i];
	}
	delete[] studentScores;

	for (int i = 0; i < num_students; ++i)
	{
		delete[] studentGrades[i];
	}
	delete[] studentGrades;

	for (int i = 0; i < num_exams; ++i)
	{
		delete[] numofGrades[i];
	}
	delete[] numofGrades;

	delete[] names;

	delete[] averages;
}


	











	



