#ifndef _LUACLASS_HPP_G
#define _LUACLASS_HPP_

#include<lua.hpp>
#include<iostream>
#include<cstdarg>
#include<map>
#include<list>

#define DEBUG_MODE_ON 1
#define DEBUG_MODE_OFF 0

typedef enum luaTypes
{
	INT = 1,
	FLOAT = 2,
	DOUBLE = 3,
	STRING = 4,
	BOOLEAN = 5
}luatype_t;

class Helper
{
	private:
	bool luaDebug = DEBUG_MODE_OFF;

	protected:
	void setDbgMode(bool onOff);
	void dbg(const char* str);
};

typedef std::list<luatype_t> luaTypeList_t;

class LuaFile
{
	public:
	std::string fileName;
	size_t outArgNum;
	luaTypeList_t outTypes;
	luaTypeList_t::iterator outTypesIt;

	LuaFile(std::string fileName, luaTypeList_t outTypes);
};

class LuaFun
{
	public:
	std::string funName;
	size_t inArgNum;
	size_t outArgNum;
	luaTypeList_t inTypes;
	luaTypeList_t::iterator inTypesIt;
	luaTypeList_t outTypes;
	luaTypeList_t::iterator outTypesIt;

	LuaFun(std::string funName, luaTypeList_t inTypes, luaTypeList_t outTypes);
};

typedef std::pair<std::string, LuaFile*> luaFileNamePair_t; // File Name vs File Instance
typedef std::map<std::string, LuaFile*> luaFileNameMap_t;
typedef std::pair<std::string, LuaFun*> luaFunctionNamePair_t; // Function Name vs Function Instance
typedef std::map<std::string, LuaFun*> luaFunctionNameMap_t;

class Lua: protected Helper
{
	private:
	lua_State *L;
	luaFileNameMap_t files;
	luaFileNameMap_t::iterator filesIt;
	luaFunctionNameMap_t functions;
	luaFunctionNameMap_t::iterator functionsIt;

	// This function is used just to get variable in case of multiple return arguments
	void _getVar(int position, std::va_list& valist, luatype_t type);
	// This function is used just to set variable in case of multiple return arguments
	void _setVar(std::va_list& valist, luatype_t type);

	public:
	Lua(bool debug);
	virtual ~Lua();

	bool registerFile(std::string fileName, luaTypeList_t outTypes);
	bool registerFunction(std::string funName, luaTypeList_t inTypes, luaTypeList_t outTypes);

	int exeFile(std::string fileName, ...);
	int exeFun(std::string funName, ...);
	template<class T> void getVar(std::string varName, T& ret)
	{
		int position = -1;
		lua_getglobal(this->L, varName.c_str());
		if(lua_isnumber(this->L, position) || lua_isboolean (this->L, position))
		{
			this->dbg("Getting lua number from the stack");
			ret = lua_tonumber(this->L, position);
			return;
		}
		if(lua_isfunction(this->L, position))
		{
			// Not implemented
		}
		if(lua_isnoneornil(this->L, position))
		{
			dbg("None or Nil value read from the Lua stack.");
			return;
		}
		if(lua_isstring(this->L, position))
		{
			return;
		}
		if(lua_istable(this->L, position))
		{
			return;
		}
		if(lua_isthread(this->L, position))
		{
			// Not implemented
		}
		if(!lua_isuserdata(this->L, position))
		{
			// Not implemented
		}
	}

	protected:
};

#endif // _LUACLASS_HPP_
