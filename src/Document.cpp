#include <Document.hpp>
#include <iostream>
#include <fstream>

vars::Document::Document()
{

}

vars::Document::Document(const char* filename)
{
    if(!LoadFile(filename))
        exit(-1);
}

bool vars::Document::LoadFile(const char* filename)
{
    std::ifstream file(filename);
    if(!file.is_open())
    {
        std::cout << "Unable to open file." << std::endl;
        return false;
    }
    std::string line;
    while(std::getline(file, line))
        Tokenize(line);
    file.close();
    Parse();
    return true;
}

void vars::Document::Parse()
{
    vars::Var var;
    for(int i = 0; i < tokens.size(); i++)
    {
        if(tokens[i].Type == TokenType::Colon) {
            var.SetName(tokens[i-1].Value.c_str());
            // std::cout << tokens[i-1].Value << " :: " << tokens[i-1].Type << ", " << tokens[i+1].Value << " :: " << tokens[i+1].Type << std::endl;  
            if(tokens[i+1].Type != LBracket) // single values
            {
                switch(tokens[i+1].Type)
                {
                    case TokenType::Int:
                        var.SetValue(std::stoi(tokens[i+1].Value));
                        break;
                    case TokenType::Float:
                        var.SetValue(std::stof(tokens[i+1].Value));
                        break;
                    case TokenType::Bool:
                        if(tokens[i].Value == "true") var.SetValue(true);
                        else var.SetValue(false);
                        break;
                    case TokenType::String:
                        var.SetValue(tokens[i+1].Value.substr(1,tokens[i+1].Value.size() - 2).c_str());
                        break;
                }
                variables.push_back(var);
            }
        }
    }

    /*for(auto& v : variables)
    {
        std::cout << v.GetName() << " :: ";
        switch(v.GetType())
        {
            case VariableType::Int:
                std::cout << (int)v;
                break;
            case VariableType::Float:
                std::cout << (float)v;
                break;
            case VariableType::Bool:
                std::cout << (bool)v;
                break;
            case VariableType::String:
                std::cout << (char*)v;
                break;
        }
        std::cout << std::endl;
    } --> outputting variables */
}

void vars::Document::Tokenize(std::string& line)
{
    bool writingString = false;
    int i, prev = 0, cnt = 0;
    Token tok;
    std::string token;

    for(i = 0; i < line.size(); i++, cnt++)
    {
        if(IsBreakPoint(line[i]) && !writingString)
        {
            token = line.substr(prev,cnt);
            if(line[i] == ' ')
            {
                if(token != "")
                {
                    tok.Type = GetTokenType(token);
                    tok.Value = line.substr(prev,cnt);
                    tokens.push_back(tok);
                    //std::cout << "[ " << line.substr(prev,cnt) << " ]" << std::endl;
                }  
            }
            else
            {
                if(token != "")
                {
                    tok.Type = GetTokenType(token);
                    tok.Value = line.substr(prev,cnt);
                    tokens.push_back(tok);
                    //std::cout << "[ " << line.substr(prev,cnt) << " ]" << std::endl;
                }
                    
                //std::cout << "[ " << line.substr(prev,cnt) << " ]" << std::endl;
                tok.Type = GetTokenType(line[i]);
                tok.Value = std::string(1, line[i]);
                tokens.push_back(tok);
                //std::cout << "Token: " << line[i] << std::endl;
            }
            prev = i + 1;
            cnt = -1;
        }
        else if(line[i] == '\"')
        {
            if(writingString)
            {
                tok.Type = String;
                tok.Value = line.substr(prev,cnt);
                tokens.push_back(tok);
                /*if(line.substr(prev,cnt) == "")
                    //std::cout << "EMPTY" << std::endl;
                else //std::cout << "[ " << line.substr(prev,cnt) << " ]" << std::endl;*/
                writingString = false;
                prev = i+1;
                cnt = -1;
            }
            else {
                ++cnt;
                writingString = true;
            }
        }
    }
}


vars::Document::~Document()
{
    /*
    for(auto& item: tokens)
    {
        std::cout << "Token: " << std::endl;
        std::cout << "\t - type:  " << item.Type << std::endl;
        std::cout << "\t - value: " << item.Value << std::endl;
    }
    */
}