#ifndef __VARS_DOCUMENT_HPP__
#define __VARS_DOCUMENT_HPP__

#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <Variable.hpp>

namespace vars
{
    class Document
    {
    public:
        Document();
        Document(const char*);
        bool LoadFile(const char*);
        Var& operator[](const char* name)
        {
            for(auto& var : variables)
                if(strcmp(name, var.GetName()) == 0) 
                    return var;
            return variables[0]; // for now
        }
        ~Document();
        
    private:
        
        enum TokenType
        {

            VariableName,
            DollarSign,
            Int,
            Float,
            String,
            Bool,
            Colon,
            Comma,
            SemiColon, 
            LBracket,
            RBracket,
            Null,
            Unknown

        };

        struct Token
        {

            std::string Value;
            TokenType Type;

        };

        bool IsFloat(std::string& s)
        {
            bool HasADot = false;
            for(int i = 0; i < s.size(); i++)
            {
                if((s[i] < '0' || s[i] > '9') && s[i] != '.')
                    return false;
                if(s[i] == '.') {
                    HasADot = true;
                    break;
                }
            }
            return HasADot;
        }

        bool IsInt(std::string& s)
        {
            for(int i = 0; i < s.size(); i++)
                if(s[i] < '0' || s[i] > '9')
                    return false;
            return true;
        }

        TokenType GetTokenType(char c)
        {
            switch(c)
            {
                case ':':
                    return Colon;
                    break;
                case ';':
                    return SemiColon;
                    break;
                case ',':
                    return Comma;
                    break;
                case '[':
                    return LBracket;
                    break;
                case ']':
                    return RBracket;
                    break;
                case '$':
                    return DollarSign;
                    break;
            }
        }

        TokenType GetTokenType(std::string& s)
        {
            if(s == "null" || s == "NULL" || s == "Null")
                return Null;
            else if(s == "true" || s == "false")
                return Bool;
            else if(IsFloat(s))
                return Float;
            else if(IsInt(s))
                return Int;
            return VariableName;
        }

        void Parse();
        void Tokenize(std::string& line);
        bool IsBreakPoint(char c)
        {
            return (c == ':' || c == '[' || c == ']' || c == ',' || c == ';' || c == '$' || c == ' ');
        }

        std::vector<Token> tokens;
        std::vector<Var> variables;
    };
}

#endif