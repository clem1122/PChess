let rows = 8;
let cols = 8;
let squareSize;
let colors = ["#f3dbb4", "#b38c62"];
let FEN = "rnbqkbnrpppppppp................................PPPPPPPPRNBQKBNR";
let pieceImages = {};

function preload() {
  pieceImages['Q'] = loadImage("Images/Q.png");
  pieceImages['K'] = loadImage("Images/K.png");
  pieceImages['P'] = loadImage("Images/P.png");
  pieceImages['N'] = loadImage("Images/N.png");
  pieceImages['B'] = loadImage("Images/B.png");
  pieceImages['R'] = loadImage("Images/R.png");
  
  pieceImages['q'] = loadImage("Images/q.png");
  pieceImages['k'] = loadImage("Images/k.png");
  pieceImages['p'] = loadImage("Images/p.png");
  pieceImages['n'] = loadImage("Images/n.png");
  pieceImages['b'] = loadImage("Images/b.png");
  pieceImages['r'] = loadImage("Images/r.png");
}

function setup() {

    createCanvas(400, 400);
    squareSize = width / rows;
    
    for (let key in pieceImages) {
    	pieceImages[key].resize(squareSize, 0);
    }
    
    noStroke();
    drawChessboard();
    drawPieces();
    
    
}

function draw() {

}

function drawChessboard() {
    for (let i = 0; i < rows; i++) {
        for (let j = 0; j < cols; j++) {
            let x = j * squareSize;
            let y = i * squareSize;
            fill(colors[(i + j) % 2]);
            rect(x, y, squareSize, squareSize);
        }
    }
}

function drawPieces(){
	for (let i = 0; i < rows; i++) {
		    for (let j = 0; j < cols; j++) {
				let FENindex = i * 8 + j;
				if (FEN[FENindex] != '.') {
					let x = j * squareSize;
		            let y = i * squareSize;
					image(pieceImages[FEN[FENindex]], x, y);
				}
		    }
		}
}

