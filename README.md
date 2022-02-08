## Lua integration class

## Overview

This set of classes (library) enables easy integration of the Lua programming lanuage into
your C++ code. This software uses Lua C API.

This class use the Lua 5.1 but it can be changed to work with other Lua version with small efffort.

## Setup

Before starting, you have to setup proper Lua enviormnt on you machine. In that purpose,
you can follow some Lua 5.1 installation guide on the internet.

If compilig the test, pay attention to Lua C PAI paths in the Makefile. If your path deffers,
please change the path.

## How to use

This chapter shortly explains how to use the library.

### Initialization

Contrutctor will create the class instance, create Lua stack and setup debug mode. Constructor argument is boolean, you can use the macro like on the example below.

`
Lua my_luavar(DEBUG_MODE_OFF);
`

### Registration

In order to determinate Lua file or Lua function, it is needed to register the file/function. Library needs a lot of information to execute a file/function and pass/return all arguments. That is why function/file static information are provided on the file/function registration. To register a file /function, you will provide the name and the list of input/output argument types.
Library currently supports follwing argument types:

- INT = 1,
- FLOAT = 2,
- DOUBLE = 3,
- STRING = 4,
- BOOLEAN = 5

Enummeated just like above in the enum `luatype_t`.

Following code gives an example how to register a file and a function:

`
// Lua files and functions have to be registered before use
my_luavar.registerFile(LUA_FILE_NAME, {INT, FLOAT, FLOAT});
my_luavar.registerFunction(LUA_FUNCTION_NAME, {INT, FLOAT}, {FLOAT});

`

### Execute file/function

After file/function has been registered, it can be executed as part of the C++ program.
Following code gives an example how to execute previously registered file/function.

`
int var1 = 0;
float var2 = 0;
float var3 = 0;

// Execute file
if(EXIT_SUCCESS == my_luavar.exeFile(LUA_FILE_NAME, &var1, &var2, &var3))
	std::cout << "C++ : "
	<< "Var1 = " << var1 << " Var2 = " << var2 << " Var3 = " << var3 <<std::endl;

// Execute function
if(EXIT_SUCCESS == my_luavar.exeFun(LUA_FUNCTION_NAME, &var1, &var2, &var3))
	std::cout << "C++ : "
	<< "Var1 = " << var1 << " Var2 = " << var2 << " Var1 + Var2 = " << var3 <<std::endl;
`

### Setting variable

Global variable can be set using the `Lua::setVar` function. This function enables setting of any type variable onto Lua stack. This function takes two arguments:

- Variable name - is a std::string parameter that will name the variable in Lua. If this argument is non-empty string, the variable will be pushed as global. In a case the variable is empty string, the variable will be pushed to the stack without making the variable global.
- Value - value of the variable. Types supported:
	- Arithmetic cabable types
	- String
	- luaC_Function
	- boolean

Following code gives an example, how to push variable to Lua:

`
// Function for add operation
int add(lua_State *L)
{
        double n1;
        double n2;
	double res;

	// Following lines will get non-global variable from the 1st and 2nd place on the stack:
	my_luavar.getVar(EMPTY_STRING, n1, 1);
	my_luavar.getVar(EMPTY_STRING, n2, 2);

	res = n1 + n2;
        my_luavar.setVar(EMPTY_STRING, res);

        return 1; // Number of returned values
}

// Setting global C function in Lua
my_luavar.setVar(std::string("add"), add);

`

### Getting variable

We can get Lua variables using the `Lua::getVar` function. This function can get simple variables from the Lua stack. Tis function is not used to get tables, there is another function for that.

Following code gives and example, how to get variables from the Lua stack:

`
// Get global variables from Lua
my_luavar.getVar(std::string(VAR_X_NAME), x);
std::cout << "C++ : " << "X = " << x << std::endl;
my_luavar.getVar(std::string(VAR_Y_NAME), y);
std::cout << "C++ : " << "Y = " << y << std::endl;
my_luavar.getVar(std::string(VAR_Z_NAME), z);
std::cout << "C++ : " << "Z = " << z << std::endl;

`
