# break-the-bricks
Traditional 'Break the Bricks' game implemented using OpenGL

## Build instructions

cd into the directory containing this file.
This directory should also contain src/ makefile and assets/

To run the program, type 'make' in the terminal.

**************************************************BREAK THE BRICKS************************************************

Basic Description and Rules of the Game:-  
The basic gameplay of 'Break The Bricks' involves the following key rules/steps:-  
1. The main objective of the game is to break all the bricks in as minimum time as possible.  
2. The game involves some assumptions which are as follows:-  
	(a) The collisions between the ball and any other surface (bricks, platform and walls) are perfectly elastic.  
3. The ball starts with a random velocity and gains speed in proportion to the number of bricks destroyed.  
4. The scoreboard shows the time taken by the player to reach the current state.  
5. The player can resize the game window as per her convenience. The elements of the playground will resize in the same ratio.  
6. The horizontal velocity of the ball depends on the distance of the point of collision from the centre of the platorm.  
   This gives control of the ball to the user.  


Controls of the Game:-  
1. Left Arrow:- Move the platform towards left  
2. Right Arrow:- Move the platform towards right  
3. Space:- Pause/Resume the game  
4. R:- Restart the game (Press 'R' key twice in a succession)  
5. F:- Toggle fullscreen  
6. Q:- Quit  

Features:

	1.	Completely scalable at different screen sizes and resolutions.
	2.	Uses textures to make the game feel real.	
	3.	Display text on screen and updates it to show current time etc.
	4.	Well structured and engineered code structure.
	5.	Does automatic error handling like create missing directories etc.
  
  
Important Notes:-  
1. The game starts from a paused state after a reset. The timer is also reset to 0.  
The user needs to press Spacebar to restart the game.