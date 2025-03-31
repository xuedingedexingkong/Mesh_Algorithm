#include<memory>
#include<iostream>
#include <memory>

void f(std::shared_ptr<int>& p)
{
	std::cout << p.use_count();
}

int main()
{
	std::shared_ptr<int>p = std::make_shared<int>(42);
	f(p);
}