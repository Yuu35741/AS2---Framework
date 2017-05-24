/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <stdio.h>
#include "Board.h"
#include "Sound.h"
#include <random>
#include <stdlib.h>  
#include <d3d9.h>
class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
public:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void GetMouseLoc(Grid& grd, MainWindow & wnd, Grid::Location& loccapture)
	{
		loccapture.x = (wnd.mouse.GetPosX() - 1 - 30) / 90;
		loccapture.y = (wnd.mouse.GetPosY() - 1 - 30) / 70;
		loccapture.code = grd.loc[loccapture.x][loccapture.y].code;
	}
	void Initial(Grid& grd) {
		for (int i = 0; i < grd.GetWidth(); i++) {
			for (int j = 0; j < grd.GetHeight(); j++) {
				grd.loc[i][j].code = grd.rng(1,4);
				grd.loc[i][j].x = i;
				grd.loc[i][j].y = j;
			}
		}
	}
	void allCellrng(float var[7][7], int a, int b) {
		for (int y = 0; y < grd.GetHeight(); y++) {
			for (int x = 0; x < grd.GetWidth(); x++) {
				var[x][y] = grd.rng(a, b);
			}
		}
	}
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	Graphics::Bmp magikarpbmp[8];
	Graphics::AnimationTemplate magikarptemp;
	Graphics::Animation magikarp;
	D3DCOLOR* magikarpsur = (D3DCOLOR*)malloc(sizeof(D3DCOLOR) * 100 * 132 * 8);

	Graphics::Bmp legend[4];
	D3DCOLOR* legendsur = (D3DCOLOR*)malloc(sizeof(D3DCOLOR) * 96 * 96 * 4);

	Graphics::Bmp Ariabmp;
	D3DCOLOR* Ariasur = (D3DCOLOR*)malloc(sizeof(D3DCOLOR) * 260 * 292);

	Graphics::Bmp achievementbmp;
	D3DCOLOR achievementsur[384 * 36];

	Graphics::Bmp backgroundbmp;
	D3DCOLOR* backgroundgrid = (D3DCOLOR*)malloc(sizeof(D3DCOLOR) * 644 * 504);	

	Graphics::Bmp tempbmp;

	D3DCOLOR* surface1 = (D3DCOLOR*)malloc(sizeof(D3DCOLOR) * 158 * 108*4);
	Graphics::Bmp runningpikachubmp[4];
	Graphics::AnimationTemplate runningpikachutemp;
	Graphics::Animation runningpikachu;

	D3DCOLOR surface2[400*222];
	D3DCOLOR* surface4 = (D3DCOLOR*)malloc(sizeof(D3DCOLOR) * 960 * 720);
	D3DCOLOR surface3[400 * 267];

	D3DCOLOR transW = D3DCOLOR_XRGB(255, 255, 255);
	D3DCOLOR transB = D3DCOLOR_XRGB(0, 0, 0);
	Graphics::Bmp startscreen, gameoverscreen;
	Graphics::Bmp scorebmp;
	D3DCOLOR scoresur[140 * 44];
	Graphics::Bmp numberbmp[10];
	D3DCOLOR numbersur[24 * 32 * 10];
	bool startScreen = true, gameoverScreen = false;
	Sound gameoverSound;
	Grid grd;
	bool scorenorepeat = true;

	int move[7][7] = { 0 };
	int step = 6;
	bool once=true;
	int distance=70;
	int movetemp[5] = {0};
	bool swaptrigger = false;
	bool firstclick = true;
	bool next = true;
	bool booltemp[6] = { true };
	int codetemp;
	bool triggerscan = false;
	int score = 0;
	bool reverse = false;
	int droptemp[7][7] = { 0 };
	int dropdist=0;
	int nDigit =6;
	int scoredigit[6] = { 0 };
	bool achievement[5] = { false, false,false,false,false };
	bool triggertext = false;
	float moveachieve = 480.0f;
	bool one[5] = { true,true,true,true,true };
	bool two = true;
	int frameratedelay = 0;
	float accel[10] = { 0.0 };
	bool scoretrigger = false;
	bool test = true;
	bool norepeat[6] = { true,true,true,true,true,true };
	bool Mousemode = true;
	bool test1;
	/********************************/
};