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
        String
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

        VariableType GetType()
        { return VarType; }

        operator int() const { return *((int*)Value); }
        operator float() const { return *((float*)Value); }
        operator bool() const { return *((bool*)Value); }
        operator char*() const { return (char*)Value; }

        Var GetValue()
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
            }
            return v; 
        }

        ~Var();
    private:
        char* Name;
        void* Value;
        VariableType VarType;
    };
}

#endif
