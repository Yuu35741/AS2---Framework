/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Bitmap.h"
Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	grd(wnd),
	gameoverSound(L"gameover.wav")
{	
	grd.curLoc = { 3,3 };
	grd.selLoc = { 7,7 };
	allCellrng(grd.speed, 1, 4);
	Initial(grd);
	grd.preLoc = { 8,8};
	Load("images\\achievement.bmp", 384, 36, achievementsur, &achievementbmp, transB);
	Load("images\\score.bmp", 140, 44, scoresur, &scorebmp, transB);
	Load("images\\pikachu.bmp",92,72, &grd.surface[92*72], &tempbmp, transB);
	Load("images\\bullbasaur.bmp", 92, 72, &grd.surface[92*72*2], &tempbmp, transB);
	Load("images\\charmander.bmp", 92, 72, &grd.surface[92 * 72 * 3], &tempbmp, transB);
	Load("images\\squirtle.bmp", 92, 72, &grd.surface[92 * 72 * 4], &tempbmp, transB);
	Load("images\\grid.bmp", 644, 504, backgroundgrid, &backgroundbmp, transW);
	Load("images\\gameover.bmp", 400, 267, surface3, &gameoverscreen, transB);
	Load("images\\startscreen.bmp", 960, 720, surface4, &startscreen,transB);
	Load("images\\legend\\ice.bmp", 96, 96, &legendsur[0], &legend[0], transB);
	Load("images\\legend\\thunder.bmp", 96, 96, &legendsur[96*96], &legend[1], transB);
	Load("images\\legend\\fire.bmp", 96, 96, &legendsur[96*96*2], &legend[2], transB);
	Load("images\\legend\\lugia.bmp", 96, 96, &legendsur[96*96*3], &legend[3], transB);
	LoadAnimation(&magikarptemp, magikarpbmp, magikarpsur, "images\\magikarp\\magikarp", 100, 132, 8, 5, transB);
	Animating(&magikarptemp, &magikarp, 750, 530);
	LoadAnimation(&runningpikachutemp , runningpikachubmp, surface1, "images\\runningpikachu\\runningpikachu", 152, 108, 4, 5, transB);
	Animating(&runningpikachutemp, &runningpikachu,400,300);
	for (int i = 0; i < 10; i++) {
		char temp[64];
		sprintf(temp, "images\\number\\%d.bmp", i);
		Load(temp, 24, 32, &numbersur[24 * 32 * i], &numberbmp[i], transB);
	}
}

void backGround(Grid& grd,Graphics& gfx) {
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		startScreen = false;
	}
	if (startScreen)
	{
		UpdateAnimation(&runningpikachu);
	}

	if (startScreen == false && gameoverScreen == false) {
		int temp = score;
		int count = 1;
		temp = temp / 10;
		scoredigit[0] = 0;
		while (temp != 0) {
			temp = temp / 10;
			count++;
		}
		temp = score / 10;
		nDigit = count;
		for (int i = 1; i <= count; i++) {
			scoredigit[i] = (temp % 10); temp = (temp - temp % 10) / 10;
		}
	}

	if (score >= 2000) {
		achievement[0] = true;
		if (one[0]) {
			triggertext = true;
			one[0] = false;
		}
	}
	if (score >= 4000) {
		achievement[1] = true;
		if (one[1]) {
			triggertext = true;
			one[1] = false;
		}
	}
	if (score >= 6000) {
		achievement[2] = true;
		if (one[2]) {
			triggertext = true;
			one[2] = false;
		}
	}
	if (score >= 8000) {
		achievement[3] = true;
		if (one[3]) {
			triggertext = true;
			one[3] = false;
		}
	}
	if (score >= 10000) {
		achievement[4] = true;
		if (one[4]) {
			triggertext = true;
			one[4] = false;
		}
	}

	if (triggertext) {
		if (moveachieve >= 4 && two) {
			moveachieve -= accel[0];
			accel[0] += 0.1f;
		}
		if (moveachieve <= 4 || two == false) {
			if (frameratedelay < 30) frameratedelay++;
			if (frameratedelay == 30) {
				moveachieve += accel[1];
				accel[1] += 0.3f;
				two = false;
			}
		}
		if (moveachieve > 484 && two == false)
		{
			triggertext = false;
			moveachieve = 480.0f;
			two = true;
			accel[0] = 0.0f;
			accel[1] = 0.0f;
			frameratedelay = 0;
		}
	}

	if (startScreen == false && gameoverScreen == false) {
		for (int y = grd.GetHeight() - 1; y >= step; y--) {
			for (int x = 0; x < grd.GetWidth(); x++) {
				if (move[x][y] <= ((grd.loc[x][y].y + 1)*grd.GetgridY() - 2)) {
					move[x][y] += grd.speed[x][y];
					grd.speed[x][y] += 0.5f;
				}
				else {
					move[x][y] = (grd.loc[x][y].y + 1)*grd.GetgridY();
				}
			}
		}

		if (move[1][step] >= (grd.loc[1][step].y - 2)*grd.GetgridY() && step >0 ) step--;

		if (move[0][2] == 3 * grd.GetgridY()) triggerscan = true;
	}






	if (startScreen == false && gameoverScreen == false)
	{
		if (wnd.kbd.KeyIsPressed(VK_SPACE) && norepeat[5]) {
			Mousemode = !Mousemode;
			norepeat[5] = false;
		}
		if (!(wnd.kbd.KeyIsPressed(VK_SPACE))) norepeat[5] = true;
		if (Mousemode)
			GetMouseLoc(grd, wnd, grd.curLoc);
		else {
			grd.MoveUp(wnd, grd, norepeat[1]);
			grd.MoveDown(wnd, grd, norepeat[2]);
			grd.MoveLeft(wnd, grd, norepeat[3]);
			grd.MoveRight(wnd, grd, norepeat[4]);
		}



		if ((wnd.mouse.LeftIsPressed()) && test)
		{
			test = false;
			next = !next;
			if (firstclick == false) {
				grd.preLoc = grd.selLoc;
			}
			grd.selLoc = grd.curLoc;
			if (firstclick == false) {
				if (grd.selLoc.x >= 0 && grd.selLoc.x < 7 && grd.selLoc.y >= 0 && grd.selLoc.y < 7)
					if (grd.preLoc.x >= 0 && grd.preLoc.x < 7 && grd.preLoc.y >= 0 && grd.preLoc.y < 7 && next) {
						if ((grd.selLoc.x == grd.preLoc.x && abs(grd.selLoc.y - grd.preLoc.y) == 1) || (grd.selLoc.y == grd.preLoc.y && abs(grd.selLoc.x - grd.preLoc.x) == 1))
							swaptrigger = true;
					}
			}
		}
		if (!(wnd.mouse.LeftIsPressed())) {
			test = true;
			firstclick = false;
		}



		if (swaptrigger) {
			if (distance > 0 && movetemp[0] < distance) movetemp[0] += 10;
			if (distance < 0 && movetemp[0] > distance) movetemp[0] -= 10;
			if (movetemp[0] == (distance - distance % 10)) {
				if (grd.preLoc.y > grd.selLoc.y) {
					for (int i = grd.preLoc.y; i > grd.selLoc.y; i--) {
						grd.loc[grd.preLoc.x][i].code = grd.loc[grd.preLoc.x][i - 1].code;
					}
				}
				if (grd.preLoc.y < grd.selLoc.y) {
					for (int i = grd.preLoc.y; i < grd.selLoc.y; i++) {
						grd.loc[grd.preLoc.x][i].code = grd.loc[grd.preLoc.x][i + 1].code;
					}
				}
				if (grd.preLoc.x > grd.selLoc.x) {
					for (int i = grd.preLoc.x; i > grd.selLoc.x; i--) {
						grd.loc[i][grd.preLoc.y].code = grd.loc[i - 1][grd.preLoc.y].code;
					}
				}
				if (grd.preLoc.x < grd.selLoc.x) {
					for (int i = grd.preLoc.x; i < grd.selLoc.x; i++) {
						grd.loc[i][grd.preLoc.y].code = grd.loc[i + 1][grd.preLoc.y].code;
					}
				}
				grd.loc[grd.selLoc.x][grd.selLoc.y].code = grd.preLoc.code;
				swaptrigger = false;
				for (int i = 0; i < 5; i++) movetemp[i] = 0;
				grd.preLoc = { 8,8 };
				grd.selLoc = { 7,7 };

			}
			if (grd.selLoc.y != grd.preLoc.y) {
				if (movetemp[1] < 72) movetemp[1] -= 10 / abs(grd.selLoc.y - grd.preLoc.y);
				if (movetemp[2] < 72) movetemp[2] += 10 / abs(grd.selLoc.y - grd.preLoc.y);
			}
			if (grd.selLoc.x != grd.preLoc.x) {
				if (movetemp[3] < 92) movetemp[3] -= 10 / abs(grd.selLoc.x - grd.preLoc.x);
				if (movetemp[4] < 92) movetemp[4] += 10 / abs(grd.selLoc.x - grd.preLoc.x);
			}
		}
	}

	if (wnd.kbd.KeyIsPressed(VK_ESCAPE) && norepeat)
	{
		gameoverScreen = true;
		norepeat[0] = false;
		gameoverSound.Play();
		startScreen = false;
	}
	if (!(wnd.kbd.KeyIsPressed(VK_ESCAPE))) norepeat[0] = true;
}

void Game::ComposeFrame()
{
	if (startScreen == false && gameoverScreen == false)
	{
		gfx.PrintBmp(50, 580, &scorebmp);
		for (int i = 0; i < nDigit; i++) {
			gfx.PrintBmp(200 + nDigit*24 - 24 -24*i, 580, &numberbmp[scoredigit[i]]);
		}
		if (triggertext) {
			gfx.PrintBmp(100 - moveachieve, 650, &achievementbmp);
		}
		if (achievement[0]) gfx.PrintBmp(750, 50, &legend[0]);
		if (achievement[1]) gfx.PrintBmp(750, 170, &legend[1]);
		if (achievement[2]) gfx.PrintBmp(750, 290, &legend[2]);
		if (achievement[3]) gfx.PrintBmp(750, 410, &legend[3]);
		if (achievement[4]) {
			gfx.DrawAnimation(&magikarp);
			UpdateAnimation(&magikarp);
		}
		gfx.PrintBmp(30, 30, &backgroundbmp);
		grd.CreateGrid(grd, gfx, move, step, triggerscan, dropdist, score, scoretrigger);
		if (swaptrigger) {
			if (grd.selLoc.x == grd.preLoc.x) {
				if (grd.selLoc.y - grd.preLoc.y > 0)
				{
					for (int i = grd.preLoc.y; i <= grd.selLoc.y; i++) {
						grd.HightLighttrans(grd.loc[grd.preLoc.x][i], gfx, backgroundbmp);
					}
				}
				if (grd.selLoc.y - grd.preLoc.y < 0)
				{
					for (int i = grd.selLoc.y; i <= grd.preLoc.y; i++) {
						grd.HightLighttrans(grd.loc[grd.preLoc.x][i], gfx, backgroundbmp);
					}
				}
			}
			if (grd.selLoc.y == grd.preLoc.y) {
				if (grd.selLoc.x - grd.preLoc.x > 0)
				{
					for (int i = grd.preLoc.x; i <= grd.selLoc.x; i++) {
						grd.HightLighttrans(grd.loc[i][grd.preLoc.y], gfx, backgroundbmp);
					}
				}
				if (grd.selLoc.x - grd.preLoc.x < 0)
				{
					for (int i = grd.selLoc.x; i <= grd.preLoc.x; i++) {
						grd.HightLighttrans(grd.loc[i][grd.preLoc.y], gfx,backgroundbmp);
					}
				}
			}
			grd.Swap(grd, grd.preLoc, grd.selLoc, gfx, distance, movetemp);
		}
		else {
			grd.HightLight(grd.curLoc, gfx);
			grd.HightLight(grd.selLoc, gfx);
		}
	}
	else if (startScreen && gameoverScreen == false) 
	{
		gfx.PrintBmp(0, 0, &startscreen);
		gfx.DrawAnimation(&runningpikachu);
	}
	if (startScreen == false && gameoverScreen)
	{
		gfx.PrintBmp(280, 226, &gameoverscreen);
	}
	//gfx.DrawRect(30, 50, 630, 560, Colors::White);	
	//gfx.PrintBmp(300, 300, &dude);   
}
