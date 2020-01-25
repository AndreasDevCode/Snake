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
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	snake({ 2,2 }),
	goal(rng,brd,snake)
	//test test test
{

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
	if (startGame) {
		if (!gameIsOver) {
			Location temp = delta_loc;
			
			if (wnd.kbd.KeyIsPressed(VK_UP)) {
				delta_loc = { 0,-1 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
				delta_loc = { 0,1 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
				delta_loc = { -1,0 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
				delta_loc = { 1,0 };
			}
			if (temp.x == delta_loc.x*(-1) && temp.y == delta_loc.y*(-1)) {
				delta_loc = temp;
			}
			snakeMoveCounter++;
			if (snakeMoveCounter >= snakeMovePeriod) {
				snakeMoveCounter = 0;
				Location next = snake.GetNextHeadLocation(delta_loc);
				if (!brd.IsInsideBoard(next) || snake.IsInTileExceptEnd(next)) {
					gameIsOver = true;
				}
				else {
					const bool eating = next == goal.GetLocation();
					if (eating) {
						growCounter++;
						if (growCounter >= 2 && snakeMovePeriod >= 2) {
							growCounter = 0;
							snakeMovePeriod--;
						}
						snake.Grow();
					}
					snake.MoveBy(delta_loc);
					if (eating) {
						goal.Respawn(rng, brd, snake);
					}
				}
			}
		}
	}
	else {
		startGame = wnd.kbd.KeyIsPressed(VK_RETURN);
	}
	
}

void Game::ComposeFrame()
{
	if (startGame) {
		brd.DrawBoard();
		snake.Draw(brd);

		goal.Draw(brd);

		if (gameIsOver) {
			SpriteCodex::DrawGameOver(gfx.ScreenWidth / 2 - 41, gfx.ScreenHeight / 2 - 31, gfx);
			if (wnd.kbd.KeyIsPressed(VK_ESCAPE)) {
				exit(1);
			}
		}
		
	}else{
		SpriteCodex::DrawTitle(gfx.ScreenWidth / 2 - 106, gfx.ScreenHeight / 2 - 80, gfx);
	}
	
	
}
