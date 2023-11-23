#include <iostream>
#include <fstream>
#include "parser.hpp"

void code_gen(std::vector<struct func> parsed)
{
    std::ofstream file;
    file.open("output.asm");
    file << ".global _start\n.intel_syntax noprefix\n\n_start:\n";
    for(int i = 0; i < parsed.size(); i++)
    {
        file << "\tmov " << "eax, " << parsed[i].return_thing.return_num << std::endl;
        file << "\tmov ebx, eax\n\tmov eax, 1\n\tint 0x80\n";
    }
    file.close();
}