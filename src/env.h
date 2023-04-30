#pragma once
#include <memory>
#include <map>
#include <stack>
#include "object.h"

class Block;
struct Function
{
    Block &body;
    std::vector<std::string> &args;
    Function(std::vector<std::string> &args, Block &body)
        : args(args), body(body){};
    Function(Function &func) : args(func.args), body(func.body) {}
    ~Function(){};
};

typedef std::map<std::string, std::shared_ptr<Object>> Scope;
typedef std::vector<Scope> EnvScopes;
typedef std::map<std::string, std::shared_ptr<Function>> FuncMap;
typedef std::vector<std::pair<std::string, std::shared_ptr<Object>>> args_vec;

class Env
{
public:
private:
    EnvScopes env_var;
    FuncMap env_func;
    std::stack<std::string> func_stack;
    std::shared_ptr<Object> return_value;

public:
    Env();
    void push_scope(std::map<std::string, std::shared_ptr<Object>> env);
    void pop_scope();
    void declare_var(std::string &var_name, std::shared_ptr<Object> object);
    std::shared_ptr<Object> find_var(std::string var_name);
    void declare_func(std::string &func_name, std::vector<std::string> &args, Block &body);
    std::shared_ptr<Function> &find_func(std::string &func_name);
    std::shared_ptr<Object> &get_return_val();
    void set_return_val(std::shared_ptr<Object> obj);
};
