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

typedef std::pair<std::string, LuaFile*> luaFileNamePair_t;  // File Name vs File Instance
typedef std::map<std::string, LuaFile*> luaFilenameMap_t;

class Lua: protected Helper
{
	private:
	lua_State *L;
	luaFilenameMap_t files;
	luaFilenameMap_t::iterator filesIt;

	void _getVar(int position, std::va_list& valist, luatype_t type);

	public:
	Lua(bool debug);
	virtual ~Lua();

	bool registerFile(std::string fileName, luaTypeList_t outTypes);
	bool registerVar(const char* varName, luatype_t varType);
	bool regFunction(const char* funName,
			size_t inArgNum,
			size_t outArgNum,
			luatype_t inTypes[],
			luatype_t outTypes[]);

	void exefile(std::string fileName, ...);
	void getVar();
	void execfun();

	protected:
};

#endif // _LUACLASS_HPP_
