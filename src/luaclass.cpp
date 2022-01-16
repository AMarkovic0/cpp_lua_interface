#include "luaclass.hpp"

LuaFile::LuaFile(std::string fileName, luaTypeList_t outTypes)
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
	dbg("Destroying all object in the Lua state. Closing Lua state.");
	lua_close(this->L);
}

bool Lua::registerFile(std::string fileName, luaTypeList_t outTypes)
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
	std::va_list valist;

	LuaFile* file = this->files.find(fileName)->second;
	if(0 == luaL_dofile(this->L, fileName.c_str()))
	{
		this->dbg("File has been executed.");
	}
	else
	{
		this->dbg("File execution failed");
	}

	va_start(valist, fileName);
	file->outTypesIt = file->outTypes.begin();
	for(int cnt = -(file->outArgNum); cnt < 0; cnt++)
	{
		std::advance(file->outTypesIt, cnt + file->outArgNum);
		this->_getVar(cnt, valist, *(file->outTypesIt));
		file->outTypesIt = file->outTypes.begin();
	}
	va_end(valist);
}

void Lua::_getVar(int position, std::va_list& valist, luatype_t type)
{
	if(lua_isnumber(this->L, position) || lua_isboolean (this->L, position))
	{
		if(type == INT)
		{
			*(va_arg(valist, int*)) = lua_tonumber(this->L, position);
			return;
		}
		if(type == FLOAT)
		{
			*(va_arg(valist, float*)) = lua_tonumber(this->L, position);
			return;
		}
		if(type == DOUBLE)
		{
			*(va_arg(valist, double*)) = lua_tonumber(this->L, position);
			return;
		}
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
