/* This file is part of T-Rekt NX!

Copyright (C) 2018/2019 Manuel Rodríguez Matesanz
>    This program is free software: you can redistribute it and/or modify
>    it under the terms of the GNU General Public License as published by
>    the Free Software Foundation, either version 3 of the License, or
>    (at your option) any later version.
>
>    This program is distributed in the hope that it will be useful,
>    but WITHOUT ANY WARRANTY; without even the implied warranty of
>    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
>    GNU General Public License for more details.
>
>    You should have received a copy of the GNU General Public License
>    along with this program.  If not, see <http://www.gnu.org/licenses/>.
>    See LICENSE for information.
*/

// Include cout library
#include <iostream>

// Include the main libnx system header, for Switch development
#include <switch.h>
#include "SDL_Helper.hpp"
#include "Colors.h"
#include "Settings.hpp"
#include "SceneManager.hpp"
#include <sys\stat.h>
#include "Filepaths.h"

// Main program entrypoint
int main(int argc, char* argv[])
{
	consoleInit(NULL);
	Result rc = setInitialize();
	if (R_FAILED(rc))
	{
		consoleExit(NULL);
		return 0;
	}

	rc = plInitialize();

	if (R_FAILED(rc))
	{
		setExit();
		consoleExit(NULL);
		return 0;
	}

	rc = romfsInit();

	if (R_FAILED(rc))
	{
		plExit();
		setExit();
		consoleExit(NULL);
		return 0;
	}

	mkdir(DATA_FOLDER, 0777);

	SDL_Helper * helper = new SDL_Helper();
	helper->SDL_HelperInit();
	
	SceneManager::Instance()->Start(helper);

	// Main loop
	while (appletMainLoop())
	{
		helper->SDL_ClearScreen(BLACK);
		helper->SDL_DrawRect(0, 0, SWITCH_SCREEN_WIDTH, SWITCH_SCREEN_HEIGHT, WHITE);
		
		SceneManager::Instance()->Update();

		if (SceneManager::Instance()->IsOut())
			break; // break in order to return to hbmenu

		helper->SDL_Renderdisplay();
	}

	consoleExit(NULL);
	setExit();
	plExit();
	romfsExit();
	SceneManager::Instance()->Exit();
	helper->SDL_Exit();
	delete(helper);

	return 0;
}