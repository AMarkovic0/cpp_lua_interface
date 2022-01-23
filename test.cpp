#include "luaclass.hpp"

#define LUA_FILE "test.lua"
#define LUA_FUNCTION_NAME "addLua"
#define TEST_VAR1 "var1"
#define TEST_VAR2 "var2"
#define VAR_X_NAME "x"
#define VAR_Y_NAME "y"
#define VAR_Z_NAME "z"
#define TABLE_NAME "tb1"
#define TABLE_SIZE 5

int add(lua_State *L);
int tb(lua_State *L);

Lua my_luavar(DEBUG_MODE_OFF);

int main(int argc, char* argv[])
{
	int x;
	std::string y;
	bool z;

	int var1 = 0;
	float var2 = 0;
	float var3 = 0;

	std::string key[] = {"KEY1", "KEY2", "KEY3", "KEY4", "KEY5"};

	my_luavar.registerFile(LUA_FILE, {INT, FLOAT, FLOAT});
	my_luavar.registerFunction(LUA_FUNCTION_NAME, {INT, FLOAT}, {FLOAT});

	my_luavar.setVar(std::string("add"), add);
	my_luavar.setVar(std::string("tb"), tb);

	my_luavar.makeTable();
	for(int i = 0; i < TABLE_SIZE; i++)
		my_luavar.insertTable(key[i], i);
	my_luavar.setGlobalTable(std::string(TABLE_NAME));

	if(EXIT_SUCCESS == my_luavar.exeFile(LUA_FILE, &var1, &var2, &var3))
		std::cout << "C++ : " << "Var1 = " << var1 << " Var2 = " << var2 << " Var3 = " << var3 <<std::endl;

	if(EXIT_SUCCESS == my_luavar.exeFun(LUA_FUNCTION_NAME, &var1, &var2, &var3))
		std::cout << "C++ : " << "Var1 = " << var1 << " Var2 = " << var2 << " Var1 + Var2 = " << var3 <<std::endl;

	my_luavar.getVar(std::string(VAR_X_NAME), x);
	std::cout << "C++ : " << "X = " << x << std::endl;
	my_luavar.getVar(std::string(VAR_Y_NAME), y);
	std::cout << "C++ : " << "Y = " << y << std::endl;
	my_luavar.getVar(std::string(VAR_Z_NAME), z);
	std::cout << "C++ : " << "Z = " << z << std::endl;

	int a = 0;
	my_luavar.getTable(TABLE_NAME);
	for(int i = 0; i < 3; i++)
	{
		my_luavar.getTableValue(key[i], a);
		std::cout << "C++ : " << key[i] << " : " << a << std::endl;
	}

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

int tb(lua_State *L)
{
	my_luavar.makeTable();
	for(int i = 0; i < TABLE_SIZE; i++)
		my_luavar.insertTable(i+1, i);

        return 1; // Number of returned values
}


