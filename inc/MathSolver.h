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
    //! \brief validateExpression
    //! Calls isSupported() on each character in expression
    //! \param expression
    //! \return bool
    //!
    bool validateExpression(QString expression);

    //!
    //! \brief solve
    //! Evaluate expression specified. Looks for parenthesses without parenthesses in it
    //! and call evaluate() to solve the sub-expression first. When no parenthesses are left,
    //! call evaluate() on the remaining expression.
    //! \param expression
    //! \return QString
    //!
    QString solve(QString expression);

private:
    //!
    //! \brief isBalanced
    //! Checks if expression have balanced parentheses
    //! \param expression
    //! \return bool
    //!
    bool isBalanced(QString expression);

    //!
    //! \brief isSupported
    //! Checks for supported characters.
    //! Currently: numbers,decimal,^,*,/,+,-,(,)
    //! \param c
    //! \return bool
    //!
    bool isSupported(QChar c);

    //!
    //! \brief evaluate
    //! Evaluate expression specified. Throws when running into unsupported operator.
    //! \param expression
    //! \return QString
    //! \throw std::runtime_error
    //!
    QString evaluate(QString expression);

    QList<QChar> m_supportedOperators;
};

#endif
