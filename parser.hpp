#include <iostream>
#include <vector>
#include <variant>

enum tock{ 
    T_INT,
    T_MAIN,
    T_BRACES,
    T_ID,
    T_INT_LIT,
    T_OPEN_PARENTESIS,
    T_SEMICOLON,
    T_CLOSE_PARENTESIS,
    T_RETURN,
    T_OPEN_BRACES,
    T_CLOSE_BRACES
};

struct kw_return
{
    int return_num;
};

struct func
{
    std::string name;
    std::vector<std::string> args;
    std::string return_type;
    struct kw_return return_thing;
};
bool opened = false;
