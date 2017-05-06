#include "WProgram.h"

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
// Dummy declaration of _open and _write
int _open()
{
   return 0;
}

int _write()
{
   return 0;
}
}

// Implementation of the function 'led' for Lua to control the pin 13
static int l_led(lua_State *L)
{
   int d = (int)lua_tonumber(L, 1);
   digitalWriteFast(13, d);
   lua_pushnumber(L, d);
   return 1;
}

// Implementation of the function 'delay' for Lua
static int l_delay(lua_State *L)
{
   int d = (int)lua_tonumber(L, 1);
   delay(d);
   lua_pushnumber(L, d);
   return 1;
}

extern "C" int main(void)
{
   // Sets the pin 13 as output
   pinMode(13, OUTPUT);

   // Creates and initializes the Lua machine
   lua_State *L = luaL_newstate();
   luaL_openlibs(L);

   // Register the functions 'led' and 'delay'
   lua_pushcfunction(L, l_led);
   lua_setglobal(L, "led");
   lua_pushcfunction(L, l_delay);
   lua_setglobal(L, "delay");

   // Loads the blink program
   luaL_loadstring(L,
                   "\n\
      state = 1\n\
      while true do\n\
         led(state)\n\
         delay(200)\n\
         if state > 0 then state = 0 else state = 1 end\n\
      end\n\
      ");

   // Calls the loaded program
   lua_pcall(L, 0, 0, 0);
}
