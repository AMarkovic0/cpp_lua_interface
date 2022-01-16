#include "luaclass.hpp"

#define LUA_FILE "test.lua"
#define TEST_VAR1 "var1"
#define TEST_VAR2 "var2"

int main(int argc, char* argv[])
{
	int var1;
	double var2;
	float var3;

	Lua my_luavar(DEBUG_MODE_ON);
	my_luavar.registerFile(LUA_FILE, {INT, DOUBLE, FLOAT});
	my_luavar.exefile(LUA_FILE, &var1, &var2, &var3);
	std::cout << "Var1 = " << var1 << " Var2 = " << var2 << " Var3 = " << var3 <<std::endl;

	return 0;
}
