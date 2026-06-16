#include "../include/request.hpp"

int main()
{
    std::string name{};
    while (name != "q" && name != "Q")
    {
        clear();
        std::cout << ">>> coded by C++\n\n";
        std::cout << "hello world!\n";
        std::cout << "who would you want to find? (press \"q\" or \"Q\" to exit)\n";
        std::cout << "name: ";
        std::cin >> name;
        if (name.empty())
            name = "李可";
        else if (name == "q" || name == "Q")
            break;
        std::cout << "\nit will take about half a minute\n\n";

        CURL *curl = curl_easy_init();
        CURLcode res;
        std::string readBuffer{};

        if (curl)
        {
            // header config
            struct curl_slist *headers = nullptr;
            headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) "
                                                 "AppleWebKit/537.36 (KHTML, like Gecko) "
                                                 "Chrome/137.0.0.0 Safari/537.36");
            headers = curl_slist_append(headers, "Accept: application/json, text/javascript, */*; q=0.01");
            headers = curl_slist_append(headers, "X-Requested-With: XMLHttpRequest");

            // curl config
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_COOKIE, "PHPSESSID=rshmo3qj21jvek24ko2pv141t5");
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3L);
            // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
            curl_easy_setopt(curl, CURLOPT_REFERER, "https://dgcpzxcz.dgjy.net/nhqc/index.php/CardRecharge/Weixin/index?code=001Uma0w3ETce73K3O3w3VvsWW2Uma0p&state=STATE");
            // curl_easy_setopt();
            // std::cout << "|log| curl has been initialized!\n";

            // ready for request
            int fail_count = 0;
            std::string id{};
            std::string url{};
            std::vector<Student> result{};
            std::mt19937 generator;
            std::uniform_int_distribution<int> dist(100, 400);
            for (int base = 122; base <= 124; ++base)
            {
                int max_class = base == 122 ? 32 : 36;
                if (base == 122)
                    std::cout << "finding in 2023...\n";
                else if (base == 123)
                    std::cout << "\nfinding in 2024...\n";
                else if (base == 124)
                    std::cout << "\nfinding in 2025...\n";
                for (int pid = 1; pid <= max_class; ++pid)
                {
                    readBuffer.clear();
                    id = GenerateID(base, pid);
                    url = GenerateURL(curl, name, id);
                a:
                    if (Request(curl, res, url, readBuffer, result) == -1)
                    {
                        ++fail_count;
                        std::cout << "trying request again...\n";
                        std::this_thread::sleep_for(std::chrono::milliseconds(dist(generator)));
                        goto a;
                    }
                    if (fail_count > 3)
                    {
                        std::cerr << "|error| too many fail!\n";
                        return -1;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(dist(generator)));
                    printProgress(pid, max_class);
                }
            }
            // std::cout << "|log| all requests done!";
            if (result.empty())
                std::cout << "there is no such person\n";
            else
            {
                std::cout << "\n\nSuccessfully found: \n";
                for (int i = 0; i < result.size(); ++i)
                {
                    std::cout << "code: " << result[i].code << " | "
                              << "name: " << result[i].name << " | "
                              << "dept: " << result[i].dept << "\n";
                }
                std::cout << "\n";
            }
        }
        std::cout << "press \"q\" or \"Q\" to exit, else continue: ";
        std::cin >> name;
    }

    return 0;
}