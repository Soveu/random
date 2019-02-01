struct Coord {
  int x,y;
}

struct Piece {
  Coord coord;
  std::function<std::vector<Coord>(ChessBoard*, Piece*)> possibleMoves;
  uint64_t info;
}

