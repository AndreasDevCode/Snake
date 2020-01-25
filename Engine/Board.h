#pragma once
#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	void DrawBoard();
	const int GetGridWidth() const;
	const int GetGridHeight() const;
	const int GetSideFrame();
	const int GetTopFrame();
	bool IsInsideBoard(const Location& loc) const;

private:
	Color blue = Colors::Cyan;
	Graphics& gfx;
	static constexpr int dimension = 15;
	static constexpr int width = (Graphics::ScreenWidth / dimension) - 4;
	static constexpr int height = (Graphics::ScreenHeight/dimension) - 4;
	
};