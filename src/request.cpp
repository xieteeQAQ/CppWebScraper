#include "../include/request.hpp"

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

int WriteData(std::string readBuffer)
{
    try
    {
        std::ofstream f;
        std::string filename = "receive/receive.txt";

        if (readBuffer[0] == '<')
        {
            // std::cout << "|log| writing the data into file......\n";
            f.open(filename, std::ios::app);
            if (f.is_open())
            {
                f << readBuffer;
                f.close();
                // std::cout << "|log| data has been writen into txt!\n";
            }
            else
            {
                std::cerr << "|error| file opening fail: file opening error!\n";
                return -1;
            }
        }
        else if (readBuffer[0] == '{')
        {
            nlohmann::json json = json.parse(readBuffer);
            // std::cout << "|log| writing the data into file......\n";
            f.open(filename, std::ios::app);
            if (f.is_open())
            {
                f << json << "\n";
                f.close();
                // std::cout << "|log| data has been writen into json!\n";
            }
            else
            {
                std::cerr << "|error| file opening fail: file opening error!\n";
                return -1;
            }
        }

        if (filename.empty())
        {
            std::cerr << "|error| data analyse fail: unkown data type!\n";
            return -1;
        }
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "|error| " << e.what() << '\n';
        return -1;
    }
}

std::string GenerateID(int base, int pid)
{
    std::string id{};
    if (pid < 10)
        id = "0" + std::to_string(base) + "0" + std::to_string(pid);
    else
        id = "0" + std::to_string(base) + std::to_string(pid);
    return id;
}

std::string GenerateURL(CURL *curl, std::string name, std::string id)
{
    std::string url{};
    char *encode_name = curl_easy_escape(curl, name.c_str(), 0);

    url = "https://dgcpzxcz.dgjy.net/nhqc/CardRecharge/Weixin/searchName.html?"
          "person_name=" +
          std::string(encode_name) +
          "&dept_name=" + id;

    return url;
}

int Request(CURL *curl, CURLcode &res, std::string url, std::string &readBuffer, std::vector<Student> &result)
{
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cerr << "|error| curl request fail: " << curl_easy_strerror(res) << "\n";
        return -1;
    }
    else
    {
        // std::cout << "|log| we have got the response!\n";
        if (readBuffer.empty())
            std::cout << "|error| readBuffer empty!\n";
        else if (WriteData(readBuffer) == 0)
        {
            try
            {
                nlohmann::json json = json.parse(readBuffer);
                if (json["state"] == "1")
                {
                    auto rs = json["rs"];
                    for (const auto &item : rs)
                    {
                        Student student(item["personcode"], item["personname"], item["dptlongname"]);
                        result.push_back(student);
                    }
                }
            }
            catch (const std::exception &e)
            {
                // std::cerr << e.what() << '\n';
            }
            // std::cout << "|log| data has been recorded!\n";
        }
        else
        {
            std::cerr << "|error| data recording fail!\n";
            return -1;
        }
    }
    return 0;
}

#include <iostream>
#include <string>

void printProgress(int current, int total)
{
    const int barWidth = 40;

    float progress = (float)current / total;
    int pos = barWidth * progress;
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << progress * 100.0;
    std::string prog = ss.str();

    std::cout << "\r[";

    for (int i = 0; i < barWidth; ++i)
    {
        if (i < pos)
            std::cout << "#";
        else if (i == pos)
            std::cout << ">";
        else
            std::cout << "-";
    }

    std::cout << "] "
              << prog
              << "% ("
              << current << "/"
              << total << ")"
              << std::flush;

    if (current == total)
        std::cout << " done\n";
}

void clear()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
