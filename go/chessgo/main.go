package main

type Vector2b struct{
	x	byte
	y	byte
}

type ChessPiece struct{
	Vector2b
	IsWhite	bool
}

type ChessInterface interface{
	CanMoveTo(v Vector2b) bool
	MoveTo(v Vector2b)
	BeatPiece()
	//TODO: pieces collision, function to actually move pieces
}

type King	ChessPiece
type Queen	ChessPiece
type Rook	ChessPiece
type Knight	ChessPiece
type Bishop	ChessPiece
type Pawn	ChessPiece

type ChessBoard [8][8]ChessInterface
type Round uint

type ChessInputHandlerFunc	func() (Vector2b, Vector2b)
type ChessOutputHandlerFunc	func(from Vector2b, cp ChessPiece, to Vector2b)

type ChessGame struct{
	cb	ChessBoard
	r	Round
	cih	ChessInputHandlerFunc
	coh	ChessOutputHandlerFunc
}

func MakeChessGame(cihf ChessInputHandlerFunc, cohf ChessOutputHandlerFunc) *ChessGame{
	return &ChessGame{
		cb = &ChessBoard{},
		r = 0,
		cih = cihf,
		coh = cohf
	}
}

func StartChessGame(cg *ChessGame) {
	for {
		vfrom, vto := cg.cih()
		if err == nil{
			break
		}

		cp := cg.cb[vfrom.x][vfrom.y]
		if cp == nil{
			//TODO: piece not selected error handler
		}

		canMove := cp.CanMoveTo(vto)
	}

}
