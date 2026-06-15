#include "../include/request.hpp"

int main()
{
    std::string name{};
    std::cout << "hello world!\n";
    std::cout << "who would you want to find?\n";
    std::cout << "name: ";
    std::cin >> name;
    std::cout << "\n";
    if (name.empty())
        name = "安晟林";

    CURL *curl = curl_easy_init();
    CURLcode res;
    std::string readBuffer{};

    if (curl)
    {
        struct curl_slist *headers = nullptr;
        headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) "
                                             "AppleWebKit/537.36 (KHTML, like Gecko) "
                                             "Chrome/137.0.0.0 Safari/537.36");

        curl_easy_setopt(curl, CURLOPT_URL, "https://www.baidu.com");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        int times = 1;
        std::cout << "| request " << times << " |\n";
        std::cout << "---------------------------------------\n";
        std::cout << "|log| curl has been initialized!\n";
        // curl_easy_setopt();

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            std::cerr << "|error| curl request fail: " << curl_easy_strerror(res) << "\n";
        else
        {
            std::cout << "|log| we have got the response!\n";
            if (WriteData(readBuffer) == 0)
                std::cout << "|log| data has been recorded!\n";
            else
                std::cerr << "|error| data recording fail!\n";
        }
        std::cout << "---------------------------------------\n\n";
        ++times;
    }

    return 0;
}