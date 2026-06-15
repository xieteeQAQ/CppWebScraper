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
        std::string filename{};
        if (readBuffer[0] == '<')
        {
            filename = "receive/receive.txt";
            std::cout << "|log| writing the data into file......\n";
            f.open(filename, std::ios::out);
            if (f.is_open())
            {
                f << readBuffer;
                f.close();
            }
            else
            {
                std::cerr << "|error| file opening fail: file opening error!\n";
                return -1;
            }
        }
        else if (readBuffer[0] == '{')
        {   
            filename = "receive/receive.json";
            nlohmann::json json = json.parse(readBuffer);
            std::cout << "|log| writing the data into file......\n";
            f.open(filename, std::ios::out);
            if (f.is_open())
            {
                f << json;
                f.close();
            }
            else
            {
                std::cerr << "|error| file opening fail: file opening error!\n";
                return -1;
            }
        }
        else
            filename = "receive/receive.txt";
        if (filename.empty())
        {
            std::cerr << "|error| data analyse fail: unkown data type!\n";
            return -1;
        }
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << "|error| " << e.what() << '\n';
        return -1;
    }
}
