#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

std::string readExpression(char *inputFile)
{
    std::string line;
    std::ifstream inf(inputFile);
    std::cout << "Opening file: " << inputFile << std::endl;

    if (inf.is_open())
    {
        while (getline(inf,line)){}
        inf.close();
    }
    else
    {
        std::cout << "[Error] Cannot open " << inputFile << std::endl;
        return "";
    }
    
    remove_if(line.begin(), line.end(), isspace);
    if(any_of(line.begin(), line.end(), isalpha))
    {
        std::cout << "[Error] Invalid Input. Found alpha in input." << std::endl;
        return "";
    }

    return line;
}

int main(int argc, char *argv[])
{
    // Display user mannual if lacking argument
    if(argc < 2) 
    {
        std::cout << "Missing Input. Example:" << std::endl;
        std::cout << "./calculate <input file with expression>" << std::endl;
    }

    // Loops thru input files
    for(int i = 1; i < argc; i++)
    {
        std::string expression = readExpression(argv[i]);

        if(expression == "") continue;

        try
        {
            std::cout << expression << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    
    return 0;
}