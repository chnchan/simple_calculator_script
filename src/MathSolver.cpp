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

bool MathSolver::isSupported(QChar c)
{
    return c.isNumber() || c == '.' || m_supportedOperators.contains(c);
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

QString MathSolver::evaluate(QString expression)
{
    QString result = expression;

    foreach(QChar symbol, m_supportedOperators)
    {
        QRegularExpression re("(?<left>\\d+(\\.\\d+)?)\\" + QString(symbol) + "(?<right>\\d+(\\.\\d+)?)");
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

            result.remove(matchingStr);
            result.insert(match.capturedStart(0), QString::number(value, 'f', 10));
//            std::cout << "result - " + result.toStdString() << std::endl;
            match = re.match(result);
        }
    }

    return result;
}

