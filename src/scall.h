#pragma once
#include "ast.h"

SystemCallMap SystemCallExpression::syscalls = SystemCallMap();

Object test(std::vector<Object> args)
{
    std::cout << "test" << std::endl;
    return Object("100", Object::Int);
}