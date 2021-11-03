#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <QChar>
#include <QString>
#include <QList>

class MathSolver
{
public:
    //!
    //! \brief MathSolver
    //! Constructor.
    //!
    MathSolver();

    //!
    //! \brief isSupported
    //! Checks for supported characters.
    //! Currently: numbers,^,*,/,+,-
    //! \param c
    //! \return bool
    //!
    bool isSupported(QChar c);

    //!
    //! \brief validateExpression
    //! Calls isSupported() on each character in expression
    //! \param expression
    //! \return bool
    //!
    bool validateExpression(QString expression);

    //!
    //! \brief evaluate
    //! Evaluate expression specified. Throws when running into unsupported operator
    //! Parenthese not supported currently.
    //! \param expression
    //! \return QString
    //! \throw std::runtime_error
    //!
    QString evaluate(QString expression);

private:
    QList<QChar> m_supportedOperators;
};

#endif
