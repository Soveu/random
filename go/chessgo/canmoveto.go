package main

import "math"

//TODO: pieces collision
func (p *Queen) CanMoveTo(v Vector2b) bool{
	deltaX := math.Abs(p.x - v.x)
	if deltaX == 0{
		return true
	}

	deltaY := math.Abs(p.y - v.y)
	if deltaY == 0{
		return true
	}

	return deltaY == deltaX
}

func (p *King) CanMoveTo(v Vector2b) bool{
	deltaX := math.Abs(p.x - v.x)
	deltaY := math.Abs(p.y - v.y)

	return deltaX < 2 && deltaY < 2
}

func (p *Rook) CanMoveTo(v Vector2b) bool{
	deltaX := p.x - v.x
	deltaY := p.y - v.y

	return deltaX == 0 || deltaY == 0
}

func (p *Knight) CanMoveTo(v Vector2b) bool{
	deltaX := math.Abs(p.x - v.x)
	deltaY := math.Abs(p.y - v.y)

	if deltaX > 0 && deltaY > 0{
		return deltaX + deltaY == 3
	}

	return false
}

func (p *Bishop) CanMoveTo(v Vector2b) bool{
	deltaX := math.Abs(p.x - v.x)
	deltaY := math.Abs(p.y - v.y)

	return deltaX == deltaY
}

func (p *Pawn) CanMoveTo(v Vector2b) bool{
	deltaX := p.x - v.x
	deltaY := p.y - v.y

	//starting pawn can move 2 fields forward
	if (p.IsWhite && p.y == 0) || (!p.IsWhite && p.y ==8) {
		return deltaX == 0 && deltaY <= 2
	}

	return deltaX == 0 && deltaY == 1
}
