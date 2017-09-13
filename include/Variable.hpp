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

        VariableType GetType()
        { return VarType; }

        operator int() const { return *((int*)Value); }
        operator float() const { return *((float*)Value); }
        operator bool() const { return *((bool*)Value); }
        operator char*() const { return (char*)Value; }

        Var operator[](int a)
        {
            /*for(int i = 0; i < sizeof((int*)Value) / sizeof(int); i++)
            {
                std::cout << *((int*)Value + i) << std::endl;
            }*/
            std::vector<int>* vec = static_cast<std::vector<int>*>(Value);
            Var var(Name, vec->at(a));
            return var;
        }

        /*Var GetValue()
        {
            Var v;
            v.SetName(Name);
            switch(VarType)
            {
                case Int:
                    v.SetValue(*((int*)Value));
                    break;
                case Float:
                    v.SetValue(*((float*)Value));
                    break;
                case Bool:
                    v.SetValue(*((bool*)Value));
                    break;
                case String:
                    v.SetValue((char*)Value);
                    break;
                case IntArray:
                    
                    v.SetValue(vec);
                    break;
            }
            return v; 
        }*/

        ~Var();
    private:
        char* Name;
        void* Value;
        VariableType VarType;
    };
}

#endif
