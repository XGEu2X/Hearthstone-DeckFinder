#pragma once

#include <iostream>
#include <vector>
#include <string>

class Base64String
{
public:
	//Constructors
	Base64String():string("====") {}
	Base64String(const std::string& s);
	Base64String(const std::vector<uint8_t>& Numbers);
	//methods
	inline std::vector<uint8_t> get_list_of_decimals() const{ return Decimals; }
	inline std::string get_string() const{ return string; }
	inline bool is_void() const{ return string == "===="; }
	inline bool has_error() const { return error; }
	inline std::string get_error_message()const { return error_message; }
private:
	//variables
	std::string string;
	std::vector<uint8_t> Decimals;
	bool error;
	std::string error_message;
};

uint8_t ctod(char c);
char dtoc(uint8_t n);
