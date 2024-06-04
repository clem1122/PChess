# PChess - A client/server package to play chess with friends

This project has the purpose of bringing a way to play chess remotely by simply connecting to a server in function. The project offers a complete and autonomous management of all chess rules as well as a graphic interface to play, with an intuitive system of point-and-click.

## Content of the project

The projetc contains the files :

- **client.cpp / client.h** and **server.cpp / server.h** to manage the client/server connection
- **game.cpp / game.h** to create the game object containing all the informations of the chess game
- **board.cpp / board.h** to manage the board object which contains all the game mechanics
- **piece.cpp / piece.h** to manage the piece object
- **move.cpp / move.h to** manage the move object, containing all the informations of a move of a piece from one square to another

## How to launch the game

### Create the server

To create the server, **download all the files of this project**. Then, **compile** everything :
```
make all
```
Then, run the *server* script.
```
./server
```
Your machine will then become the host of the game, and its IP will be used to reach the game.

Run a http python server to enable the graphic interface via your browser.
```
python3 -m http.server --bind 127.0.0.1 8050
```

### Access the game

You just have to run the *client* script :
```
./client [IP OF SERVER] [USERNAME]
```
You will be then given a *PLAYER_PORT* in your terminal. 
Open your browser and go to **http://127.0.0.1:8050**.
You have now access to the graphic interface.
Change the port at the left of the checkboard to match *PLAYER_PORT*.

It is possible to run a game in local with two *client* scripts and two browser tabs.

## How to play

### Color of players

The first player to connect plays as the White Player. He has to begin the game by playing a move.

### Make a move

To make a move, you juste have to click on one of your piece (the square become green) and click on an another square of the board. If the move is legal, then the pice will effectively move, and your opponent's turn begins. If you have selected a piece and want to play another, don't worry : you just have to double-click the other piece you want to play to select it.

### Terminal display

The terminal will be useful to gather information on the game. It will warn you when your move is illegal, as well as if you are in check or checkmate.

## Notes

### Promotion

For now, a promoted pawn becomes automatically a queen.

## Troubleshoot

### CORS

Cross-Origin Resource Sharing is a mechanism that allows web pages to request resources from another domain outside the domain from which the resource originated. 
It can be blocked by browsers due to security reasons. If you meet an error like ```Cross-Origin Request Blocked```, consider enabling it in your browser settings or changing of browser.
