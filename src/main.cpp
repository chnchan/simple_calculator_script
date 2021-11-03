#include <iostream>

#include <QList>
#include <QString>
#include <QFile>
#include <QTextStream>

#include "MathSolver.h"

//! Parse input file into QString and strip all spaces in between characters.
//! Throws if file cannot be opened.
QString readExpression(char *inputFile)
{
    QString input;
    QFile inf(inputFile);

    if(!inf.open(QIODevice::ReadOnly)) {
        throw std::runtime_error("[Error] Cannot open " + std::string(inputFile));
    }

    QTextStream ts(&inf);
    input.append(ts.readAll());
    input.removeIf([](QChar c){ return c.isSpace();});
    return input;
}

int main(int argc, char *argv[])
{
    MathSolver evaluator;

    // Display user manual if lacking argument
    if(argc < 2) 
    {
        std::cout << "[Error] Missing Input. \nExample:" << std::endl;
        std::cout << "./calculate <input file with expression>" << std::endl;
    }

    // Loops thru input files. Assumes only one expression per file.
    for(int i = 1; i < argc; i++)
    {
        try
        {
            QString expression = readExpression(argv[i]);
            evaluator.validateExpression(expression);
            QString result = evaluator.evaluate(expression);
            std::cout << expression.toStdString() + " = " + result.toStdString() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    
    return 0;
}
