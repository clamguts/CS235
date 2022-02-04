#include "QS.h"
#include<fstream>
#include<iostream>
#include<sstream>
using namespace std;


#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

int main(int argc, char* argv[]) {
	VS_MEM_CHECK

	//Opening files
	ifstream in(argv[1]);
	if (!in)
	{
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	// open argv[2] file or cout for output
	ostream& out = (argc > 2) ? *(new ofstream(argv[2])) : cout;
	if (!out) return 2;

	string line, command, item1, item2, item3;
	QS<int> qsInt = QS<int>();

	while (getline(in, line)) 
	{
			if (line.size() == 0) continue;
			istringstream iss(line);
			iss >> command;

			if (command == "QuickSort") 
			{
				out << endl << line;
				iss >> item1;
				qsInt.newQuicksort(stoi(item1));
				out << " OK";

			}
			else if (command == "AddToArray") 
			{
				out << endl << command << "  ";
				string addPrint = "";
				while (iss >> item1) 
				{
					qsInt.addElement(stoi(item1));
					addPrint += item1;
					addPrint += ",";
				}
				addPrint.pop_back();
				out << addPrint << " OK";
			}
			else if (command == "Capacity") 
			{
				out << endl << line;
				out << " " << qsInt.capacity();
			}
			else if (command == "Clear") 
			{
				out << endl << line;
				qsInt.clear();
				out << " OK";
			}
			else if (command == "Size")
			{
				out << endl << line;
				out << " " << qsInt.size();
			}
			else if (command == "Sort") 
			{
				qsInt.resetStats();
				out << endl << command;
				iss >> item1;
				iss >> item2;
				out << " " << item1 << "," << item2;
				int item = stoi(item2) - 1;
				qsInt.sort(stoi(item1), item);
				out << " OK";	
			}
			else if (command == "SortAll") 
			{
				qsInt.resetStats();
				out << endl << line;
				qsInt.sortAll();
				out << " OK";
			}
			else if (command == "MedianOfThree") 
			{
				out << endl << command;
				iss >> item1;
				iss >> item2;
				out << " " << item1 << "," << item2 << " = " << qsInt.medianOfThree(stoi(item1), stoi(item2));
			}
			else if (command == "Partition") 
			{ 
				out << endl << command;
				iss >> item1;
				iss >> item2;
				iss >> item3;
				out << " " << item1 << "," << item2 << "," << item3 << " = " << qsInt.partition(stoi(item1), stoi(item2), stoi(item3));
			}
			else if (command == "PrintArray")
			{
				out << endl << line;
				out << " " << qsInt;
			}
			else if (command == "Stats")
			{
				out << endl << command << ": ";
				out << qsInt.stats();
			}
	}

	if (&out != &std::cout) delete(&out);
	return 0;
}