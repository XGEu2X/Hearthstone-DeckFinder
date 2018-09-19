#pragma once

#include "Rapidjson/document.h"
#include "Rapidjson/filereadstream.h"
#include "Rapidjson/writer.h"
#include "Rapidjson/stringbuffer.h"
#include "Rapidjson/filewritestream.h"

#include <iostream>
#include <string>

//makes a rapidjson object based in json file
rapidjson::Document read_json(const std::string& filename);
//writes a json file based in a rapidjson object
void write_json(rapidjson::Document& document,const std::string& filename);
