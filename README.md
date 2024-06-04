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

To create the server, you just have to **download all the files of this project**. Then, you have to **compile** everything using the command **make all**. Finally, you juste have to launch the file *server*. Your machine will then become the host of the game, and its IP will be used to reach the game.

### Access the game

To create the server, you just have to **download all the files of this project**. Then, you have to **compile** everything using the command **make all**. Finaly, you juste have to launch the file *client* through your terminal with the 2 following attributes :
    - the **address IP** of the server
    - a **username**

You will be then given a port in your terminal. Let's name this port *PORT_NAME* Open your browser and go to **localhost:PORT_NAME** or **127.0.0.1.PORT_NAME**. Your browser is now listening to the java script of the server and you have access to the graphic interface.

## How to play

### Color of players

The first player to connect plays as the White Player. He has to begin the game by playing a move.

### Make a move

To make a move, you juste have to click in one of your piece (the square under it will become green) and click on an another square of the board. If the move is legal, then the pice will efectively move, and your opponent's turn begins. If you have selected a piece and wante to play another, don't worry : you just have to double-click the other piece you want to play to select it.

### Terminal display

The terminal will be useful to gather information on the game. It will warn you when your move is illegal (and why), as well as if your check or checkmate.

## Notes

### Promotion

A promoted pawn becomes automatically a queen.
