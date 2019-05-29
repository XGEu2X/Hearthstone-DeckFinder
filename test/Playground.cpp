#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "General.hpp"

using namespace std;

int main() {
	
	remove_file("web.html", "../data/");
	
	return 0;
}