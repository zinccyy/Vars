#ifndef __VARIABLE_HPP
#define __VARIABLE_HPP

#include <cstring>
#include <iostream>
#include <vector>

namespace vars {

    enum VariableType
    {
        Undef,
        Int,
        Float,
        Bool,
        String,

        IntArray,
        FloatArray,
        BoolArray,
        StringArray
    };

    class Var
    {
    public:
        Var();
        Var(const Var&);
        Var(const char*, int);
        Var(const char*, float);
        Var(const char*, bool);
        Var(const char*, const char*);

        void SetName(const char*);
        char* GetName();

        void SetValue(int);
        void SetValue(float);
        void SetValue(bool);
        void SetValue(const char*);

        //arrays

        void SetValue(std::vector<int>&);
        void SetValue(std::vector<float>&);
        void SetValue(std::vector<bool>&);
        void SetValue(std::vector<std::string>&);

        VariableType GetType()
        { return VarType; }

        operator int() const { return *((int*)Value); }
        operator float() const { return *((float*)Value); }
        operator bool() const { return *((bool*)Value); }
        operator char*() const { return (char*)Value; }

        Var operator[](int a)
        {
            Var var;
            var.SetName(Name);
            switch(VarType)
            {
                case IntArray:
                {
                    std::vector<int>* vec = static_cast<std::vector<int>*>(Value);
                    var.SetValue(vec->at(a));
                    break;
                }
                case FloatArray:
                {
                    std::vector<float>* vec = static_cast<std::vector<float>*>(Value);
                    var.SetValue(vec->at(a));
                    break;
                }
                case BoolArray:
                {
                    std::vector<bool>* vec = static_cast<std::vector<bool>*>(Value);
                    var.SetValue(vec->at(a));
                    break;
                }
                case StringArray:
                {
                    std::vector<std::string>* vec = static_cast<std::vector<std::string>*>(Value);
                    var.SetValue(vec->at(a).c_str());
                    break;
                }
            }
            return var;
        }
        ~Var();

    private:

        char* Name;
        void* Value;
        VariableType VarType;
    };
}

#endif