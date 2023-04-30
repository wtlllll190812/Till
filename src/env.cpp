#include "env.h"

Env::Env()
{
    env_var = EnvScopes();
    env_func = FuncMap();
    func_stack = std::stack<std::string>();
    return_value = std::shared_ptr<Object>(new Object());
}

void Env::push_scope(std::map<std::string, std::shared_ptr<Object>> env)
{
    // std::cout << "push_scope" << std::endl;
    env_var.push_back(env);
}

void Env::pop_scope()
{
    // std::cout << "pop_scope" << std::endl;
    env_var.pop_back();
}

void Env::declare_var(std::string &var_name, std::shared_ptr<Object> object)
{
    auto &env = env_var.back();
    env[var_name] = object;
}

std::shared_ptr<Object> Env::find_var(std::string var_name)
{
    for (size_t i = env_var.size() - 1; i >= 0; i--)
    {
        auto &env = env_var[i];
        if (env.find(var_name) != env.end())
        {
            return env[var_name];
        }
    }
}

void Env::declare_func(std::string &func_name, std::vector<std::string> &args, Block &body)
{
    env_func[func_name] = std::shared_ptr<Function>(new Function(args, body));
}

std::shared_ptr<Function> &Env::find_func(std::string &func_name)
{
    func_stack.push(func_name);
    return env_func[func_name];
}

std::shared_ptr<Object> &Env::get_return_val()
{
    return return_value;
}

void Env::set_return_val(std::shared_ptr<Object> obj)
{
    func_stack.pop();
    return_value = obj;
}