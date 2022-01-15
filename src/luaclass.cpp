#include "luaclass.hpp"

LuaFile::LuaFile(std::string fileName, luaTypenameMap_t outTypes)
{
	this->fileName = fileName;
	this->outArgNum = outTypes.size();
	this->outTypes = outTypes;
}

Lua::Lua(bool debug = DEBUG_MODE_OFF)
{
	this->setDbgMode(debug);
	this->L = luaL_newstate();
	this->dbg("Lua VM has been created");
	luaL_openlibs(this->L);
	this->dbg("Lua standard library has been loaded");
}

Lua::~Lua()
{
}

bool Lua::registerFile(std::string fileName, luaTypenameMap_t outTypes)
{
	this->files[fileName] = new LuaFile(fileName, outTypes);
}

bool Lua::registerVar(const char* varName, luatype_t varType)
{
}

bool Lua::regFunction(const char* funName,
			size_t inArgNum,
			size_t outArgNum,
			luatype_t inTypes[],
			luatype_t outTypes[])
{
}

void Lua::exefile(std::string fileName, ...)
{
	LuaFile* file = this->files.find(fileName)->second;
	if(0 == luaL_dofile(this->L, fileName.c_str()))
	{
		this->dbg("File has been executed.");
	}
	else
	{
		this->dbg("File execution failed");
	}

	for(int cnt = -(file->outArgNum); cnt < 0; cnt++)
	{
		std::cout << lua_tonumber(this->L, cnt) << std::endl;
	}
}

void Helper::setDbgMode(bool onOff)
{
	if(onOff)
	{
		this->luaDebug = DEBUG_MODE_ON;
	}
	else
	{
		this->luaDebug = DEBUG_MODE_OFF;
	}
}

void Helper::dbg(const char* str)
{
	if(this->luaDebug)
		std::cout << str << std::endl;
}
