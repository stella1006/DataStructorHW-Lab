#include <iostream>

void print(int i)
{
	std::cout << i << std::endl;
}

void print2(int i)
{
	std::cout << i * 2 << std::endl;
}

void printSomething()
{
	std::cout << "Something" << std::endl;
}

void sayHello()
{
	std::cout << "Hello, World!" << std::endl;
}

void call_p_func(void(*func)(int))
{
	func(1);
	func(2);
	func(3);
}

void call_r_func(void(&func)(int))
{
	func(1);
	func(2);
	func(3);
}

void call_p_function(void(*func)())
{
	func();
}

int main()
{
	std::cout << "函数指针作为参数" << std::endl;
	call_p_func(&print);
	call_p_func(&print2);
	call_p_function(&printSomething);
	call_p_function(&sayHello);
	call_p_function(sayHello);
	// 上面两句对于某些编译器来说是一样的，但是推荐使用前者的写法，
	// 这样可以是程序的可读性更好一些

	std::cout << "函数引用作为参数" << std::endl;
	call_r_func(print);
	call_r_func(print2);

	return 0;
}
