#include "../includes/tester.hpp"

std::string toString(int i)
{
   std::stringstream ss;
   ss << i;
   return ss.str();
}

void printTestName(const std::string& nbLine, std::string name, const std::string& info)
{
    std::cout.width(45);
    name = "\nline " + nbLine + ": " + name;
    if (!info.empty())
        name = name + " " + info + ":";
    std::cout << std::left << name;
    std::cout.width(0);
}

int getTestNumber(int *nb)
{
    static int i = 0;

    if (nb)
        i = *nb;
    else
        return ++i;
    return 0;
}
