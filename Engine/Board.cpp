#include "Board.h"
#include <assert.h>
Board::Board(Graphics & gfx)
	:
	gfx(gfx)
{

}

void Board::DrawCell(const Location& loc, Color c){
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y <= height);
	gfx.DrawRectDim(loc.x*dimension+GetSideFrame(), loc.y*dimension+GetTopFrame(), dimension-2, dimension-2,c);
}

const int Board::GetGridWidth() const {
	return width;
}
const int Board::GetGridHeight() const {
	return height;
}

bool Board::IsInsideBoard(const Location & loc) const
{
	return loc.x  < width && loc.x >= 0 && loc.y < height && loc.y >= 0  ;
}
const int Board::GetSideFrame() {
	return (gfx.ScreenWidth - width * dimension) / 2;
}
const int Board::GetTopFrame() {
	return (gfx.ScreenHeight - height * dimension) / 2;
}
void Board::DrawBoard() {
	for (int i = GetSideFrame(); i <= gfx.ScreenWidth - GetSideFrame(); i++) {
		gfx.PutPixel(i, GetTopFrame()+1, blue);
		gfx.PutPixel(i, GetTopFrame(), blue);
		gfx.PutPixel(i, gfx.ScreenHeight-GetTopFrame()-1, blue);
		gfx.PutPixel(i, gfx.ScreenHeight-GetTopFrame(), blue);
	}
	for (int j = GetTopFrame(); j <= gfx.ScreenHeight - GetTopFrame(); j++) {
		gfx.PutPixel(GetSideFrame(), j, blue);
		gfx.PutPixel(GetSideFrame()+1, j, blue);
		gfx.PutPixel(gfx.ScreenWidth-GetSideFrame()-1, j, blue);
		gfx.PutPixel(gfx.ScreenWidth-GetSideFrame(), j, blue);
	}

}

