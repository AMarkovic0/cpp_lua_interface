#ifndef _LUACLASS_HPP_G
#define _LUACLASS_HPP_

#include<lua.hpp>
#include<iostream>
#include<map>

#define DEBUG_MODE_ON 1
#define DEBUG_MODE_OFF 0

typedef enum luaTypes
{
	NUMBER = 1,
	STRING = 2,
	TABLE = 3,
	FUNCTION = 4
}luatype_t;

typedef std::pair<std::string, luatype_t> luaTypenamePair_t; // Names vs types
typedef std::map<std::string, luatype_t> luaTypenameMap_t;

class Helper
{
	private:
	bool luaDebug = DEBUG_MODE_OFF;

	protected:
	void setDbgMode(bool onOff);
	void dbg(const char* str);
};

class LuaFile
{
	public:
	std::string fileName;
	size_t outArgNum;
	luaTypenameMap_t outTypes;
	luaTypenameMap_t::iterator outTypesIt;

	LuaFile(std::string fileName, luaTypenameMap_t outTypes);
};

typedef std::pair<std::string, LuaFile*> luaFileNamePair_t;  // File Name vs File Instance
typedef std::map<std::string, LuaFile*> luaFilenameMap_t;

class Lua: protected Helper
{
	private:
	lua_State *L;
	luaFilenameMap_t files;
	luaFilenameMap_t::iterator filesIt;

	public:
	Lua(bool debug);
	virtual ~Lua();

	bool registerFile(std::string fileName, luaTypenameMap_t outTypes);
	bool registerVar(const char* varName, luatype_t varType);
	bool regFunction(const char* funName,
			size_t inArgNum,
			size_t outArgNum,
			luatype_t inTypes[],
			luatype_t outTypes[]);

	void exefile(std::string fileName, ...);
	void execfun();

	protected:
};

#endif // _LUACLASS_HPP_
