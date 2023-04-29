#include "ast.h"

DeclareExpression::DeclareExpression(Object ident, Expression &expr) : ident(ident), expr(expr)
{
}

std::string DeclareExpression::toString()
{
    return "Let" + ident.value + "=" + expr.toString() + ";";
}

std::string IfExpression::toString()
{
    return "If" + expr.toString() + block1.toString() + block2.toString();
}