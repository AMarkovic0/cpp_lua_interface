#include "luaclass.hpp"

#define LUA_FILE "test.lua"
#define LUA_FUNCTION "addLua"
#define TEST_VAR1 "var1"
#define TEST_VAR2 "var2"
#define VAR_X_NAME "x"
#define VAR_Y_NAME "y"
#define VAR_Z_NAME "z"

int add(lua_State *L);

Lua my_luavar(DEBUG_MODE_OFF);

int main(int argc, char* argv[])
{
	int x;
	std::string y;
	bool z;

	int var1;
	float var2;
	float var3;

	my_luavar.registerFile(LUA_FILE, {INT, FLOAT, FLOAT});
	my_luavar.registerFunction(LUA_FUNCTION, {INT, FLOAT}, {FLOAT});

	my_luavar.setVar(std::string("add"), add);

	if(EXIT_SUCCESS == my_luavar.exeFile(LUA_FILE, &var1, &var2, &var3))
		std::cout << "C++ : " << "Var1 = " << var1 << " Var2 = " << var2 << " Var3 = " << var3 <<std::endl;

	if(EXIT_SUCCESS == my_luavar.exeFun(LUA_FUNCTION, &var1, &var2, &var3))
		std::cout << "C++ : " << "Var1 = " << var1 << " Var2 = " << var2 << " Var1 + Var2 = " << var3 <<std::endl;

	my_luavar.getVar(std::string(VAR_X_NAME), x);
	std::cout << "C++ : " << "X = " << x << std::endl;
	my_luavar.getVar(std::string(VAR_Y_NAME), y);
	std::cout << "C++ : " << "Y = " << y << std::endl;
	my_luavar.getVar(std::string(VAR_Z_NAME), z);
	std::cout << "C++ : " << "Z = " << z << std::endl;

	return 0;
}

int add(lua_State *L)
{
        double n1;
        double n2;
	double res;

	my_luavar.getVar(EMPTY_STRING, n1, 1);
	my_luavar.getVar(EMPTY_STRING, n2, 2);

	res = n1 + n2;
        my_luavar.setVar(EMPTY_STRING, res);

        return 1; // Number of returned values
}

