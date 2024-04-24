let rows = 8;
let cols = 8;
let squareSize;
let colors = ["#f3dbb4", "#b38c62"];
let selectedColor = "#98c47e";
let FEN = "rnbqkbnrpppppppp................................PPPPPPPPRNBQKBNR";
let pieceImages = {};
let selectedSquare = null;
let selectedPiece = null;
let port = "8080";
let url = "http://localhost:" + port;
let isWhite = true;
let Box;

function setPort(value) {
	port = value;
	url = "http://localhost:" + port;
	console.log("Port : " + port);
}

function updateValue() {
	port = Box.value();
	url = "http://localhost:" + port;
	console.log("Port : " + port);
}

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

    createCanvas(900, 900);
    Box = select('#valueBox');
    Box.input(updateValue);
    squareSize = width / rows;
    for (let key in pieceImages) {
    	pieceImages[key].resize(squareSize, 0);
    }
    
    noStroke();
    frameRate(50);

    
 
}

function draw() {
    httpGet(url, 'text', gotData);
    drawBoard();
}

function getColor(){
	sendData("colo");
	httpGet(url, 'text', gotData);
}

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
	width=400,height=100,left=100,top=100`;
	//open('/promotion', 'test', params);
	
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
		
			
			let endCoord = String.fromCharCode(97 + _col) + (8 - _row);
			
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
  console.log('Received data: <', data, '>');	
  if (data.length == 64){
  	

  	FEN = data;
  }
  else if (data.length == 1)
  {
  	console.log('Received other data: <', data, '>');
  }	
  

}

function sendData(data) {

   httpPost(url, 'text', data, function(response) {}, function(error) {console.error('Error sending data:', error);});
}








