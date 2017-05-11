// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "concurrency\concurrency.h"
#include "utility\utility.h"
#include <cstdlib>
#include <iostream>
#include <Windows.h>


using namespace le::concurrency;
using namespace le::utility;

namespace
{
	int test_case = 0;
}
inline std::ostream& green(std::ostream &s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout,
		FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	return s;
}
inline std::ostream& white(std::ostream &s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout,
		FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	return s;
}

#define LOG_TEST		do{std::clog<<green<<	\
						"test_case: #"<<test_case<<" pass!"<<std::endl<<std::endl<<	\
						white;	\
						}while(0);

#define LE_TEST_BEGIN	{{	\
						++test_case;

#define LE_TEST_END		}	\
						LOG_TEST	\
						}

void f()
{
	std::cout << "void f() running..." << std::endl;
}

int main()
{
	LE_TEST_BEGIN
		auto_thread t;
	LE_TEST_END

		LE_TEST_BEGIN
		auto_thread t(auto_thread::run_stat::RS_JOIN, f);
	LE_TEST_END

		LE_TEST_BEGIN
		int i = 0;
	auto_thread t(auto_thread::run_stat::RS_JOIN,
		[&i]()
	{
		Sleep(3000);
		std::cout << "In thread to join." << std::endl;
	}
	);
	t.explicit_join();
	std::cout << "This shoule print after thread join." << std::endl;
	LE_TEST_END

		LE_TEST_BEGIN
		auto_thread t(auto_thread::run_stat::RS_JOIN, f);
	t.explicit_join();
	try { t.explicit_join(); }
	catch (std::system_error const &se)
	{
		std::cerr << "Error code: " << se.code() << ", meaning " << se.what() << std::endl;
	}
	LE_TEST_END

		LE_TEST_BEGIN
		//since the thread has been detached, the color and the text is not right
		//just let it do what it wants
		auto_thread t1(auto_thread::run_stat::RS_DETACH, f);
	auto_thread t2(std::move(t1));
	LE_TEST_END

		system("pause");
	return 0;
}