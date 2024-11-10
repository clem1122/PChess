#include <pybind11/pybind11.h>
#include "piece.h"

namespace py = pybind11;

PYBIND11_MODULE(PChess, m){
	m.doc() = "PChess library";
	
	py::class_<Piece>(m, "Piece")
		.def(py::init<>())
		.def("type", &Piece::type);


}
