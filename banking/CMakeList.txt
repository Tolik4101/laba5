cmake_minimum_required(VERSION 3.4)
project(sborka)
add_library(bank STATIC
	Account.cpp
	Account.h
	Transaction.cpp
	Transaction.h)
set_target_properties(bank PROPERTIES
	CXX_STANDART 11
	CXX_STANDART_REQUIRED ON)


