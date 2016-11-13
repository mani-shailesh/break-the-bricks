# Break the Bricks
[![license](https://img.shields.io/github/license/mashape/apistatus.svg?maxAge=2592000)](https://github.com/mani-shailesh/break-the-bricks/blob/master/LICENSE.md)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/f2d2879819fa40688154d9fe5829e058)](https://www.codacy.com/app/shailesh-pandey/break-the-bricks?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=mani-shailesh/break-the-bricks&amp;utm_campaign=Badge_Grade)
[![Category](https://img.shields.io/badge/Category-Coursework-ff69b4.svg)](https://github.com/mani-shailesh/break-the-bricks)  

## Description
Traditional 'Break the Bricks' game implemented using OpenGL

## Build instructions
cd into the directory containing this file.
This directory should also contain src/ makefile and assets/

To run the program, type 'make' in the terminal.

## Game Description and Rules

The basic gameplay of 'Break the Bricks' involves the following key rules/steps:  

1. The main objective of the game is to break all the bricks in as minimum time as possible.
3. The ball starts with a random velocity and gains speed in proportion to the number of bricks destroyed.
4. The scoreboard shows the time taken by the player to reach the current state.
5. The player can resize the game window as per her convenience. The elements of the playground will resize in the same ratio.
6. The horizontal velocity of the ball depends on the distance of the point of collision from the centre of the platorm.
   This gives control of the ball to the user.


## Controls  

1. Left Arrow : Move the platform towards left  
2. Right Arrow : Move the platform towards right  
3. Space : Pause/Resume the game  
4. R : Restart the game (Press 'R' key twice in a succession)  
5. F : Toggle fullscreen  
6. Q : Quit  

## Features

1. Completely scalable at different screen sizes and resolutions.
2. Uses textures to make the game feel real.	
3. Display text on screen and updates it to show current time etc.
4. Well structured and engineered code structure.
5. Does automatic error handling like create missing directories etc.
