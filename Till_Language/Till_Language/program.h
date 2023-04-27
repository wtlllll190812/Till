#pragma once

class node 
{
public:
	virtual std::string token_value() const = 0;
	virtual std::string to_string() const = 0;
	virtual ~node() {};

	template<typename T>
	const T* cast() const
	{
		return dynamic_cast<const T*>(this);
	}

	template<typename T>
	T* cast()
	{
		return dynamic_cast<T*>(this);
	}
};

class program: public node
{
};

class statement : public node
{
};

class expression : public node
{
};