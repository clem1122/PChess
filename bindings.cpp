#include <pybind11/pybind11.h>
#include "piece.h"
#include "board.h"
#include <string>

namespace py = pybind11;

PYBIND11_MODULE(PChess, m)
{
	m.doc() = "PChess library";

	py::class_<Piece>(m, "Piece")
		.def(py::init<>())
		.def(py::init<const char, std::string, bool>())
		.def("type", &Piece::type)
		.def("coord", &Piece::coord)
		.def("isWhite", &Piece::isWhite);

	py::class_<Board>(m, "Board")
		.def(py::init<>())
		.def(py::init<std::string>())
		.def("FEN", &Board::FEN)
		.def("pieces", &Board::pieces, py::return_value_policy::reference)
		.def("valhalla_pieces", &Board::valhalla_pieces, py::return_value_policy::reference)
		.def("piece_on_square", &Board::piece_on_square)
		.def("en_passant_coord", &Board::en_passant_coord)
		.def("valhalla_FEN", &Board::valhalla_FEN)
		.def("special_rules", &Board::specialRulesData)
		.def("create_move", &Board::create_move)
		.def("play_move", &Board::playMove)
		.def("play", &Board::play)
		.def("print", &Board::print)
		.def("print_valhalla", &Board::valhalla_print)
		.def("index_to_coord", &Board::indextoCoord)
		.def("coord_to_index", &Board::coordtoIndex)
		.def("valhalla_index_to_coord", &Board::valhalla_index_to_coord)
		.def("valhalla_coord_to_index", &Board::valhalla_coord_to_index)
		.def("threats", &Board::threatSquares)
		.def("playable", &Board::playableSquares)
		.def("controlled", &Board::controlledSquares);

	py::class_<Move>(m, "Move")
		.def(py::init<>())
		.def(py::init<std::string, std::string, Piece, bool, bool, bool, bool>())
		.def("start", &Move::start)
		.def("end", &Move::end)
		.def("moving_piece", &Move::movingPiece)
		.def("isCapture", &Move::isCapture)
		.def("isPromoting", &Move::isPromotion)
		.def("isCastling", &Move::isCastling)
		.def("isEnPassant", &Move::isEnPassant);
}
