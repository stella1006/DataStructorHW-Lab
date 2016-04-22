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
	std::cout << "����ָ����Ϊ����" << std::endl;
	call_p_func(&print);
	call_p_func(&print2);
	call_p_function(&printSomething);
	call_p_function(&sayHello);
	call_p_function(sayHello);
	// �����������ĳЩ��������˵��һ���ģ������Ƽ�ʹ��ǰ�ߵ�д����
	// ���������ǳ���Ŀɶ��Ը���һЩ

	std::cout << "����������Ϊ����" << std::endl;
	call_r_func(print);
	call_r_func(print2);

	return 0;
}
