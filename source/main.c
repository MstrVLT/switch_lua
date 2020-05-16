// Include the most common headers from the C standard library
#include <stdio.h>
#include <stdlib.h>


  #include <lua/lua.h>
  #include <lua/lualib.h>
  #include <lua/lauxlib.h>

#include <string.h>

// Include the main libnx system header, for Switch development
#include <switch.h>

// Main program entrypoint
int main(int argc, char* argv[])
{
    // This example uses a text console, as a simple way to output text to the screen.
    // If you want to write a software-rendered graphics application,
    //   take a look at the graphics/simplegfx example, which uses the libnx Framebuffer API instead.
    // If on the other hand you want to write an OpenGL based application,
    //   take a look at the graphics/opengl set of examples, which uses EGL instead.
    consoleInit(NULL);

    // initialization
    lua_State * L = luaL_newstate();    /* opens Lua */
    luaL_openlibs(L);                  /* opens the standard libraries */

    // execute script
    const char lua_script[] = "print('Hello World from lua!')";
    int load_stat = luaL_loadbuffer(L,lua_script,strlen(lua_script),lua_script);
    lua_pcall(L, 0, 0, 0);

    // cleanup
    lua_close(L);

    // Main loop
    while (appletMainLoop())
    {
        // Scan all the inputs. This should be done once for each frame
        hidScanInput();

        // hidKeysDown returns information about which buttons have been
        // just pressed in this frame compared to the previous one
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS)
            break; // break in order to return to hbmenu

        // Your code goes here

        // Update the console, sending a new frame to the display
        consoleUpdate(NULL);
    }

    // Deinitialize and clean up resources used by the console (important!)
    consoleExit(NULL);
    return 0;
}
