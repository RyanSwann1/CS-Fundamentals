#pragma once

#include <string>
#include <vector>

//r-value reference
void f(std::string&& t)
{

}

//universal reference
template <typename T>
void f(T&& t)
{

}

void f()
{
	//r-value reference
	std::string a;
	std::string&& b = std::move(a);
	
	//Universal reference
	std::string c;
	auto&& d = c;
}

void f()
{
	//Not universal reference due to T already being deduced
	std::vector<std::string> strings;
	strings.push_back({}); //T&& 


}

void f()
{

}