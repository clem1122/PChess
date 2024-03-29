let pieceImages = {};
let isWhite = true;

function preload() {
  pieceImages['Q'] = loadImage("Images/Q.png");
  pieceImages['N'] = loadImage("Images/N.png");
  pieceImages['B'] = loadImage("Images/B.png");
  pieceImages['R'] = loadImage("Images/R.png");
  
  pieceImages['q'] = loadImage("Images/q.png");
  pieceImages['n'] = loadImage("Images/n.png");
  pieceImages['b'] = loadImage("Images/b.png");
  pieceImages['r'] = loadImage("Images/r.png");
}

function setup() {
    createCanvas(900, 900);
    squareSize = 100;
    for (let key in pieceImages) {
    	pieceImages[key].resize(squareSize, 0);
    }
    
    noStroke();
    frameRate(10);

    
 
}

function draw() {
	let x = 0;
	for (let img in pieceImages) {
		image(pieceImages[img], x, 0);
		x += 100;
	}
}

/*

function drawBoard() {
    for (let i = 0; i < rows; i++) {
        for (let j = 0; j < cols; j++) {
            let x = j * squareSize;
            let y = i * squareSize;
            fill(colors[(i + j) % 2]);
            if (selectedSquare != null) {
		        let {row, col} = selectedSquare;
		        if(row == i && col == j) {
			        
		        	fill(selectedColor)
		        }
            }
            rect(x, y, squareSize, squareSize);
            
        }
    }
    drawPieces();
}

function drawPieces(){
	for (let i = 0; i < rows; i++) {
		    for (let j = 0; j < cols; j++) {
				let FENindex = isWhite ? i * 8 + j : 63 - (i * 8 + j);
				if (FEN[FENindex] != '.') {
					let x = j * squareSize;
		            let y = i * squareSize;
					image(pieceImages[FEN[FENindex]], x, y);
				}
		    }
		}
}




function mousePressed() {

	let params = `scrollbars=no,resizable=no,status=no,location=no,toolbar=no,menubar=no,
	width=600,height=300,left=100,top=100`;

	open('/promotion', 'test', params);
	let _col = floor(mouseX / squareSize);
	let _row = floor(mouseY / squareSize);

	if (_col >= 0 && _col < 8 && _row >= 0 && _row < 8) {
	
		let FENindex = isWhite ? _row * 8 + _col : 63 - (_row * 8 + _col);
		if(selectedPiece == null) {
			if (FEN[FENindex] != '.') {
				selectedPiece = FEN[FENindex];
				console.log(selectedPiece);
			}
			selectedSquare = { row: _row, col: _col };
		} else {
		
			
			let endCoord = String.fromCharCode(97 + _col) + (8 -_row);
			
			let {row, col} = selectedSquare;
			
			let startCoord = String.fromCharCode(97 + col) + (8 - row);
			let move = startCoord + endCoord;
			
			selectedPiece = null;
			selectedSquare = null;
			sendData(move);
			
		}
		
		
		
		
    	drawBoard();
	}
}


// Callback function to handle the response from the server
function gotData(data) {
  // Print the received data to the console
  
  if (data.length == 64){
  	console.log('Received data: <', data, '>');	
  	FEN = data;
  }

}

function sendData(data) {

   httpPost(url, 'text', data, function(response) {}, function(error) {console.error('Error sending data:', error);});
}


*/





