#include "tokenize.hpp"
#include <iostream>
#include <vector>
#include "parser.hpp"

std::vector<struct func> parsee(std::vector<std::string> tokens)
{
    std::vector<struct func> parsed;
    for(int i = 0; i < tokens.size(); i++)
    {
        if (tokens[i].compare("int") == 0)
        {
            if (tokens[i + 1].compare("main()") == 0)
            {
                struct func function("main", std::vector<std::string>(), "int", kw_return(0));
                parsed.push_back(function);
            }
        }
        if (tokens[i].compare("return") == 0)
        {
            if (tokens[i + 1].contains(";"))
            {
                tokens[i + 1].pop_back();
                struct kw_return kw(atoi(tokens[i + 1].c_str()));
                parsed[0].return_thing = kw;
            }
        }
    }
    return parsed;
}

int main(int argc, char *a[])
{
    if (argc < 2)
    {
        std::cout << "Not enough arguments" << std::endl;
    }
    std::ifstream t(a[1]);
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string b = buffer.str();
    std::vector<std::string> tokens = tokenize(b);
    std::vector<std::string> aaaa;
    std::vector<int> to;

    for(int i = 0; i < tokens.size(); i++)
    {
        std::vector<std::string> temp = tokenize(tokens[i], '\n');
        aaaa.insert(aaaa.end(), temp.begin(), temp.end());
    }
    
    for(int i = 0; i < aaaa.size(); i++)
    {   

        if (isNumber(aaaa[i]))
        {
            to.push_back(T_INT_LIT);
        }
        if (aaaa[i].compare("int") == 0)
        {
            to.push_back(T_INT);
        }
        if(aaaa[i].contains("main"))
        {
            to.push_back(T_MAIN);
        }
        if(aaaa[i].contains("("))
        {
            to.push_back(T_OPEN_PARENTESIS);
        }
        if(aaaa[i].contains(")"))
        {
            to.push_back(T_CLOSE_PARENTESIS);
        }
        if(aaaa[i].contains("{"))
        {
            to.push_back(T_OPEN_BRACES);
        }
        if(aaaa[i].contains("}"))
        {
            to.push_back(T_CLOSE_BRACES);
        }
        if(aaaa[i].contains(";"))
        {
            to.push_back(T_SEMICOLON);
        }
        if(aaaa[i].compare("return") == 0)
        {
            to.push_back(T_RETURN);
        }
    }

    for(int i = 0; i < aaaa.size(); i++)
    {
        std::cout << aaaa[i] << std::endl;
    }

    std::vector<struct func> parsed = parsee(aaaa);

    for(int i = 0; i < parsed.size(); i++)
    {
        std::cout << "FUNCTION: " << parsed[0].name << std::endl;
        std::cout << "   args: "  << "()" << std::endl;
        std::cout << "   return: type: " << parsed[0].return_type << " value: " << parsed[0].return_thing.return_num << std::endl;
    }

}