#include "tokenize.hpp"
#include <iostream>
#include <vector>
#include "parser.hpp"


int main(int argc, char *a[])
{
    std::ifstream t("main.c");
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string b = buffer.str();
    std::vector<std::string> tokens = tokenize(b);
    std::vector<std::string> aaaa;
    std::vector<struct token> to;

    for(int i = 0; i < tokens.size(); i++)
    {
        std::vector<std::string> temp = tokenize(tokens[i], '\n');
        aaaa.insert(aaaa.end(), temp.begin(), temp.end());
    }
    
    for(int i = 0; i < aaaa.size(); i++)
    {   
        if (isNumber(aaaa[i]))
        {
            if (aaaa.size() > 1 && isdigit(aaaa[i].back()) == 0)
            {
                if (aaaa[i].back() == ';')
                {
                    aaaa[i].pop_back();
                    to.push_back(token(T_INT_LIT, aaaa[i]));
                    to.push_back(token(T_SEMICOLON, ";"));
                }
            }
            else
                to.push_back(token(T_INT_LIT, aaaa[i]));
        }
        if (aaaa[i].compare("int") == 0)
        {
            to.push_back(token(T_INT, aaaa[i]));
        }
        if(aaaa[i].contains("main"))
        {
            to.push_back(token(T_MAIN, "main"));
        }
        if(aaaa[i].contains("("))
        {
            to.push_back(token(T_OPEN_PARENTESIS, "("));
        }
        if(aaaa[i].contains(")"))
        {
            to.push_back(token(T_CLOSE_PARENTESIS, ")"));
        }
        if(aaaa[i].contains("{"))
        {
            to.push_back(token(T_OPEN_BRACES, "{"));
        }
        if(aaaa[i].contains("}"))
        {
            to.push_back(token(T_CLOSE_BRACES, "}"));
        }
        if(aaaa[i].contains(";"))
        {
            to.push_back(token(T_SEMICOLON, ";"));
        }
        if(aaaa[i].contains("return"))
        {
            to.push_back(token(T_RETURN, "return"));
        }
        if (aaaa[i].contains("char"))
        {
            to.push_back(token(T_CHAR, "char"));
            to.push_back(token(T_VAR_NAME, aaaa[i+1]));
        }
    }

    /*
    for(int i = 0; i < to.size(); i++)
    {
        std::cout << to[i].code << std::endl;
    }*/

    std::vector<struct func> parsed = parsee(to);

    for(int i = 0; i < parsed.size(); i++)
    {
        std::cout << "FUNCTION: " << parsed[0].name << std::endl;
        std::cout << "   args: "  << "(" << parsed[0].args[0].value << ")" << std::endl;
        std::cout << "   return: type: " << parsed[0].return_type << " value: " << parsed[0].return_thing.return_num << std::endl;
    }
}