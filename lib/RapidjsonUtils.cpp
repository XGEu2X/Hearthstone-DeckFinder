#include "RapidjsonUtils.hpp"

rapidjson::Document read_json(const std::string& filename){
    FILE* fp = fopen(filename.c_str(), "r");
    if(fp == 0){
        std::cout << "Where's " << filename << "?" << std::endl;
        return NULL;
    }
    char readBuffer[65536];
    rapidjson::FileReadStream file(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document document;
    document.ParseStream(file);
    fclose(fp);
    return document;
}
void write_json(rapidjson::Document& document, const std::string& filename){
    FILE* fp = fopen(filename.c_str(), "w");
    char writeBuffer[65536];
    rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
    rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
    document.Accept(writer);
    fclose(fp);
}
