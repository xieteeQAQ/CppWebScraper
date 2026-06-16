#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <thread>
#include <chrono>
#include <random>
#include <iomanip>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

struct Student
{
    Student(std::string c, std::string n, std::string d)
    {
        code = c;
        name = n;
        dept = d;
    };
    std::string code{};
    std::string name{};
    std::string dept{};
};

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

int WriteData(std::string readBuffer);

std::string GenerateID(int base, int pid);

std::string GenerateURL(CURL *curl, std::string name, std::string id);

int Request(CURL *curl, CURLcode &res, std::string url, std::string &readBuffer, std::vector<Student> &result);

void printProgress(int current, int total);

void clear();