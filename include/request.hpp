#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <thread>
#include <chrono>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

int WriteData(std::string readBuffer);

void Request(CURL *curl, CURLcode &res, std::string &readBuffer, std::string &name, std::string &dept_name);