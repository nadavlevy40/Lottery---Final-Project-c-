

![3](https://user-images.githubusercontent.com/69619783/201052121-d1f27735-a4a4-432c-b4bc-001b6e9f8e18.jpg)



# Lottery Final Project
My final project of the course "Advenced Programming In C " - Lottery Machine .

## Overview
The project is a game simulating a lottery. The user can participate in the lottery by choosing numbers for their columns, and then the program will randomly generate the winner column and check the user's columns for hits. The program also allows the user to save the game data to a binary file, and load the data from the file for the next time the game is played.


## Game Play :

. The user first choose to enter number of participants or to view the last lottery results which can be read from binary file
. Each participant choose whether make a manual lottery card or randomize
. The program randomize a random lottery card , then calculate each of the participants strikes.
. The last results are saving into a binary file which can be read afterwards .

## Rules:

* The user can choose up to 5 columns, each containing 15 numbers between 1 and 90.
* The program will randomly generate the winner column, also containing 15 numbers between 1 and 90.
* The user's hits will be calculated by comparing the numbers in their columns to the numbers in the winner column. If a number appears in both the user's column     and the winner column, it is considered a hit.
* The user can save their game data to a binary file and load it for the next time the game is played.

## Examples:

The user starts a new game and chooses to participate with 3 columns. They enter the numbers [22, 45, 77, 3, 9, 15, 63, 81, 90] for their first column, [2, 15, 24, 33, 56, 74, 85] for their second column, and [1, 10, 21, 35, 50, 70, 80, 90] for their third column. The program generates the winner column [22, 3, 15, 63, 9, 81, 90, 45, 77] and calculates the user's hits. The user has 3 hits in their first column, 1 hit in their second column, and 2 hits in their third column.


## Data Structures Used:

1. Linked lists: The program uses linked lists to store the user's columns and the game data.

2. Binary files: The program uses a binary file to store the game data for future use.


Have fun!

