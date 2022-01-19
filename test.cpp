#include "luaclass.hpp"

#define LUA_FILE "test.lua"
#define TEST_VAR1 "var1"
#define TEST_VAR2 "var2"
#define VAR_X_NAME "x"

int main(int argc, char* argv[])
{
	int x;
	int var1;
	double var2;
	float var3;

	Lua my_luavar(DEBUG_MODE_ON);

	my_luavar.registerFile(LUA_FILE, {INT, DOUBLE, FLOAT});

	my_luavar.exefile(LUA_FILE, &var1, &var2, &var3);
	my_luavar.getVar(std::string(VAR_X_NAME), x);

	std::cout << "Var1 = " << var1 << " Var2 = " << var2 << " Var3 = " << var3 <<std::endl;
	std::cout << "X = " << x << std::endl;

	return 0;
}
