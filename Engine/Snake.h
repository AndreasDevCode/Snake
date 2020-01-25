#pragma once

#include "Board.h"


class Snake
{

private:
	class Segment
	{
	public:
		void InitHead(const Location& loc);
		void InitBody(Color c);
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& brd) const; 
		const Location& GetLocation() const;
	private:

		Location loc;
		Color c;
	};
public:
	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc);
	void Grow();
	void Draw(Board& brd) const;
	Location GetNextHeadLocation(const Location& delta_loc) const;
	bool IsInTileExceptEnd(const Location& target) const;
	bool IsInTile(const Location& target) const;

private:
	static constexpr Color headColor = Colors::Yellow;
	
	static constexpr int nSegmentsMax = 100;
	static constexpr Color GreenLight = Colors::GreenLight;
	static constexpr Color Green = Colors::Green;
	static constexpr Color GreenDark = Colors::GreenDark;
	int color = 0;
	Color ColorArray[4] = {GreenDark,Green,GreenLight,Green};
	Segment segments[nSegmentsMax];
	int nSegments  = 1;

};

