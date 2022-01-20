#include "luaclass.hpp"

#define LUA_FILE "test.lua"
#define LUA_FUNCTION "add"
#define TEST_VAR1 "var1"
#define TEST_VAR2 "var2"
#define VAR_X_NAME "x"

int main(int argc, char* argv[])
{
	int x;
	int var1;
	float var2;
	float var3;

	Lua my_luavar(DEBUG_MODE_ON);

	my_luavar.registerFile(LUA_FILE, {INT, FLOAT, FLOAT});
	my_luavar.registerFunction(LUA_FUNCTION, {INT, FLOAT}, {FLOAT});

	my_luavar.exeFile(LUA_FILE, &var1, &var2, &var3);
	my_luavar.getVar(std::string(VAR_X_NAME), x);

	std::cout << "Var1 = " << var1 << " Var2 = " << var2 << " Var3 = " << var3 <<std::endl;
	std::cout << "X = " << x << std::endl;

	my_luavar.exeFun(LUA_FUNCTION, &var1, &var2, &var3);
	std::cout << "Var1 = " << var1 << " Var2 = " << var2 << " Var3 = " << var3 <<std::endl;

	return 0;
}
