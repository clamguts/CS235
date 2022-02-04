#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "Header.h"
using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif


int main(int argc, char* argv[])
{
    VS_MEM_CHECK

    if (argc < 3) {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);
    if (!in) {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    if (!out) {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
        return 3;
    }

    LinkedList<string> linked_list;

    // process input strings
    for (string line; getline(in, line);)
    {
        string item1, item2;
        if (line.size() == 0)
        {
            continue;
        }
        out << endl << line;
        istringstream iss(line);
        iss >> item1;
        if (item1 == "Insert")
        {
            while (iss >> item2)
            {
                linked_list.push_front(item2);
            }
        }  

        else if (item1 == "PrintList")
        {
            iss >> item2;

            if (linked_list.empty())
            {
                out << "Empty!";
            }
            else
            {
                out << " " << linked_list.toString();
            } 
        }
        
        else if (item1 == "Clear")
        {
            iss >> item2;

                linked_list.clear();

                if (linked_list.empty())
                {
                    out << " OK";
                }    
        }
    }

        return 0;
}

   

/* try {
    stuff here;
    another case;
    basket case;
    etc;
}
catch {
    more stuff here;
} 

swtich(x)
case a:
x= y
case b:
case c:

*/