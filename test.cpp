#include "luaclass.hpp"

#define LUA_FILE "test.lua"
#define TEST_VAR1 "var1"
#define TEST_VAR2 "var2"

luaTypenameMap_t testOutput;

int main(int argc, char* argv[])
{
	testOutput[TEST_VAR1] = NUMBER;
	testOutput[TEST_VAR2] = NUMBER;

	Lua my_luavar(DEBUG_MODE_ON);
	my_luavar.registerFile(LUA_FILE, testOutput);
	my_luavar.exefile(LUA_FILE);
	return 0;
}
