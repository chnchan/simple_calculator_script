#include <algorithm>
#include <cmath>
#include <iostream>

#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "MathSolver.h"

MathSolver::MathSolver()
{
    m_supportedOperators = {'^', '*', '/', '+', '-'};
}

QString MathSolver::evaluate(QString expression)
{
    QString result = expression;

    foreach(QChar symbol, m_supportedOperators)
    {
        // Regex Explainations:
        //  ?<left>         - is a tag that QRegularExpression supports to make retrieving more readible
        //  (^-|\\D-)?      - checks if left operand is negative (if starting with '-' or have another operator in front of '-' (ex. 1+-2))
        //              ^           - start with
        //              ^-          - start with '-' (ex. -1 + 3)
        //              |           - OR
        //              \\D         - not digit
        //              ?           - zero or one
        // \\d+(\\.\\d+)?   - gets left operant
        //              \\d         - digit
        //              +           - one or more
        //              \\.         - dot (needs to be escaped hence the '//')
        //              (\\.\\d+)?  - checks for decimal
        // \\ symbol        - symbol needs to be escaped (ex. \\^, \\*, \\/, \\+, \\-)
        // right side regex is essentially the left side but simpler for the negative checks.
        QRegularExpression re("(?<left>(^-|\\D-)?\\d+(\\.\\d+)?)\\" + QString(symbol) + "(?<right>-?\\d+(\\.\\d+)?)");
        QRegularExpressionMatch match = re.match(result);

        while(match.hasMatch())
        {
            QString matchingStr = match.captured(0);
            QString leftStr = match.captured("left");
            QString rightStr = match.captured("right");
//            std::cout << "match - " + matchingStr.toStdString() << std::endl;

            double left = leftStr.toDouble();
            double right = rightStr.toDouble();
            double value;

            switch(symbol.unicode())
            {
            case '^':
                value = pow(left,right);
                break;
            case '*':
                value = left * right;
                break;
            case '/':
                value = left / right;
                break;
            case '+':
                value = left + right;
                break;
            case '-':
                value = left - right;
                break;
            default:
                throw std::runtime_error("[Error] Found operator not supported.");
            }

//            std::cout << "before - " + result.toStdString() << std::endl;
            result.remove(matchingStr);
            result.insert(match.capturedStart(0), QString::number(value, 'f', 10));
//            std::cout << "after - " + result.toStdString() << std::endl;
            match = re.match(result);
        }
    }

    return result;
}

bool MathSolver::isBalanced(QString expression)
{
    int numOpeningParenthese = 0;

    foreach(QChar c, expression)
    {
        if(c == '(') numOpeningParenthese++;
        if(c == ')') numOpeningParenthese--;
    }

    return numOpeningParenthese == 0;
}

bool MathSolver::isSupported(QChar c)
{
    QList<QChar> supportedChar = {'.', '(', ')'};
    return c.isNumber() || supportedChar.contains(c) || m_supportedOperators.contains(c);
}

QString MathSolver::solve(QString expression)
{
    if(!isBalanced(expression))
    {
        throw std::runtime_error("[Error] Unbalanced parenthese: " + expression.toStdString());
    }

    QString result = expression;
    QRegularExpression re("\\(.*\\)");
    QRegularExpressionMatch match = re.match(result);

    while(match.hasMatch())
    {
        QString matchingStr = match.captured(0);
//        std::cout << "match - " + matchingStr.toStdString() << std::endl;

        int closingIndex = expression.indexOf(')');
        int openingIndex = expression.first(closingIndex).lastIndexOf('(');
        QString subexpression = expression.mid(openingIndex + 1, closingIndex - openingIndex - 1);

//        std::cout << "before - " + result.toStdString() << std::endl;
        result.remove(matchingStr);
        result.insert(match.capturedStart(0),evaluate(subexpression));
//        std::cout << "after - " + result.toStdString() << std::endl;
        match = re.match(result);
    }

    return evaluate(result);
}

bool MathSolver::validateExpression(QString expression)
{
    bool result = true;
    foreach(QChar c, expression)
    {
        result = result && isSupported(c);
    }
    return result;
}

