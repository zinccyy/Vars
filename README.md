# Vars
Simple variable storing in C++.

### Include a file
```c++
#include <Vars.hpp>
```

### Example code
```c++
#include <Vars.hpp>
#include <iostream>
using namespace std;

int main()
{
    vars::Document doc["file.vars"];
    float a = doc["float_variable"];
    cout << a << endl;
    return 0;
}
```
