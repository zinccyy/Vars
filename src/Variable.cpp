#include <Variable.hpp>
#include <iostream>
#include <cstring>

vars::Var::Var(): Name(nullptr), Value(nullptr), VarType(Undef)
{

}

vars::Var::Var(const Var& var)
{
    Name = nullptr;
    Value = nullptr;
    VarType = Undef;
    SetName(var.Name);
    switch(var.VarType)
    {
        case Int:
            SetValue((int)var);
            break;
        case Float:
            SetValue((float)var);
            break;
        case Bool:
            SetValue((bool)var);
            break;
        case String:
            SetValue((char*)var);
            break;
        case IntArray:
        {
            std::vector<int>* vec = static_cast<std::vector<int>*>(var.Value);
            SetValue(*vec);
            break;
        }
        case FloatArray:
        {
            std::vector<float>* vec = static_cast<std::vector<float>*>(var.Value);
            SetValue(*vec);
            break;
        }
    }
}

vars::Var::Var(const char* n, int v)
{
    Name = nullptr;
    Value = nullptr;
    VarType = Undef;
    SetName(n);
    SetValue(v);
}

vars::Var::Var(const char* n, float v)
{
    Name = nullptr;
    Value = nullptr;
    VarType = Undef;
    SetName(n);
    SetValue(v);
}
vars::Var::Var(const char* n, bool v)
{
    Name = nullptr;
    Value = nullptr;
    VarType = Undef;
    SetName(n);
    SetValue(v);
}

vars::Var::Var(const char* n, const char* v)
{
    Name = nullptr;
    Value = nullptr;
    VarType = Undef;
    SetName(n);
    SetValue(v);
}

void vars::Var::SetName(const char* name)
{
    if(Name == nullptr)
    {
        Name = new char[strlen(name)+1];
        strcpy(Name, name);
        // all good and sets the Name right -> checked 15 times
    }
    else
    {
        delete[] Name;
        switch(VarType)
        {
            case Undef:
    
                break;
            case Int:
                if(Value != nullptr)
                    delete (int*)Value;
                break;
            case Float:
                if(Value != nullptr)
                    delete (float*)Value;
                break;
            case Bool:
                if(Value != nullptr)
                    delete (bool*)Value;
                break;
            case String:
                if(Value != nullptr)
                    delete[] (char*)Value;
                break;
        }
        Value = nullptr;
        Name = new char[strlen(name)+1];
        strcpy(Name, name);
    }
}

char* vars::Var::GetName() { 
    return (char*)Name; 
}
 
void vars::Var::SetValue(int a)
{
    if(Value == nullptr)
    {
        Value = new int;
        *((int*)Value) = a;
        VarType = VariableType::Int;
    }
    else
        if(VarType == VariableType::Int) 
            *((int*)Value) = a;
}

void vars::Var::SetValue(float a)
{
    if(Value == nullptr)
    {
        Value = new float;
        *((float*)Value) = a;
        VarType = VariableType::Float;
    }
    else
        if(VarType == VariableType::Float) 
            *((float*)Value) = a;
}

void vars::Var::SetValue(bool a)
{
    if(Value == nullptr)
    {
        Value = new bool;
        *((bool*)Value) = a;
        VarType = VariableType::Bool;
    }
    else
        if(VarType == VariableType::Bool) 
            *((bool*)Value) = a;
}

void vars::Var::SetValue(const char* a)
{
    if(Value == nullptr)
    {
        Value = new char[strlen(a)+1];
        strcpy((char*)Value, a);
        VarType = VariableType::String;
    }
    else
        if(VarType == VariableType::String) {
            delete[] (char*)Value;
            Value = new char[strlen(a)+1];
            strcpy((char*)Value, a);
        }
}

void vars::Var::SetValue(std::vector<int>& arr)
{
    if(Value == nullptr)
    {
        Value = static_cast<void*> (new std::vector<int>(arr));
        VarType = IntArray;
    }   
    else
        if(VarType == VariableType::IntArray) 
        {
            delete[] (std::vector<int>*)Value;
            Value = new std::vector<int>(arr);
        }
}

void vars::Var::SetValue(std::vector<float>& arr)
{
    if(Value == nullptr)
    {
        Value = static_cast<void*> (new std::vector<float>(arr));
        VarType = FloatArray;
    }   
    else
        if(VarType == VariableType::FloatArray) 
        {
            delete[] (std::vector<float>*)Value;
            Value = new std::vector<float>(arr);
        }
}

vars::Var::~Var()
{
    if(Name != nullptr) 
        delete[] (char*)Name;
    switch(VarType)
    {
        case Undef:

            break;
        case Int:
            if(Value != nullptr)
                delete (int*)Value;
            break;
        case Float:
            if(Value != nullptr)
                delete (float*)Value;
            break;
        case Bool:
            if(Value != nullptr)
                delete (bool*)Value;
            break;
        case String:
            if(Value != nullptr)
                delete[] (char*)Value;
            break;
        case IntArray:
            if(Value != nullptr)
                delete[] (int*)Value;
            break;
        case FloatArray:
            if(Value != nullptr)
                delete[] (float*)Value;
            break;
    }
    Value = nullptr;
    Name = nullptr;
}