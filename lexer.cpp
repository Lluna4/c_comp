#include "tokenize.hpp"
#include <iostream>
#include <vector>
#include "code_gen.hpp"

bool var_name = false;
bool show_lexer = false;
bool show_parser = false;

std::string containsprotectedchar(std::string str)
{
    char search = str.back();
    std::string prot = "{()};";
    if (prot.find(search) != std::string::npos)
    {
        str.pop_back();
        return str;
    }
    return str;
}

int main(int argc, char *a[])
{
    if (argc < 2)
    {
        std::cout << "Not enough arguments" << std::endl;
    }
    if (argc > 2)
    {
        for (int i = 1; i < argc; i++)
        {
            if (strcmp(a[i], "-l") == 0)
            {
                show_lexer = true;
            }
            else if (strcmp(a[i], "-p") == 0)
            {
                show_parser = true;
            }
        }
    }
    std::ifstream t(a[1]);
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
            if (var_name == true)
            {
                std::cout << "ERROR: Number as an argument name";
                exit(1);
            }
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
        if (var_name == true)
        {
            if (aaaa[i].size() == 1)
            {
                if (isalnum(aaaa[i][0]) == 0)
                {
                    std::cout << "ERROR: The variable name is not alphanumeric" << std::endl;
                    exit(1);
                }
            }
            std::string ret = containsprotectedchar(aaaa[i]);
            to.push_back(token(T_VAR_NAME, ret));
            var_name = false;
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
            var_name = true;
        }
        
    }

    if (show_lexer)
    {
        for(int i = 0; i < to.size(); i++)
        {
            std::cout << to[i].code << std::endl;
        }
    }

    std::vector<struct func> parsed = parsee(to);

    if (show_parser)
    {
        for(int i = 0; i < parsed.size(); i++)
        {
            std::cout << "FUNCTION: " << parsed[0].name << std::endl;
            std::cout << "   args: "  << "(" << parsed[0].args[0].value << ")" << std::endl;
            std::cout << "   return: type: " << parsed[0].return_type << " value: " << parsed[0].return_thing.return_num << std::endl;
        }
    }
    code_gen(parsed);
    system("as output.asm -o input.o");
    system("gcc -o a.out input.o -nostdlib -static");
    system("rm input.o");
}