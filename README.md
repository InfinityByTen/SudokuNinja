# SudokuNinja

A C++ project to solve a standard 9x9 sudoku, including faulty ones that may allow for multiple solutions.
Implements heuristic methods and dfs-based brute search for faulty and tougher cases. 

This was developed during my junior year (2011) in college when I was learning the language and programming.  
This is my style of learning: pick up a tough challenge and learn on the way. 

Here's the original README (inclusive of naivety) below: 

NOTE: The original package was compiled in windows and had an .exe executable. Now, the user, must compile and run ;)

=====================================================================================
                       SUDOKU NINJA V1.0 BETA
=====================================================================================
                  Designed and Developed by ASEEM DUA.

*************************************************************************************
Sample*.txt

These are a few samples of the sudoku puzzle to give you a headstart.
You can create your own puzzle file (sourced from wherever you may please).
The method to create a puzzle file is explained below.


Sudoku Ninja.exe

This the actual application. You just need to run it once you have a puzzle file ready. 

Leave the rest to the Sudoku Ninja !!! 


***************************************************************************************


///////////////////////////////////////////////////////////////////////////////////////


HoW TO CREATE A SUDOKU PUZZLE FILE & USE THE APP ?

1. SOURCE A GENUINE SUDOKU PUZZLE FROM ANYWHERE. GENUINE IMPLIES IT SHOULDN'T BE
   INCORRECT IN ITSELF, eg. Duplicacy in rows, colums or 3x3 boxes.

2. REPLACE EACH BLACK BY A "." AND LEAVE THE NUMBERS AS IT IS.

3. TYPE ALL OF THEM IN A *.txt FILE WITHOUT LEAVING ANY SPACE.

eg. WHAT IN THE REAL WORLD WOULD LOOK LIKE :-
	
	-------------------------------
	| 8  _  _ | _  5  _ | _  _  3 |
	| _  _  _ | 4  6  _ | 7  _  _ |
	| _  _  _ | 1  _  _ | 4  _  9 |
	-------------------------------
	| _  8  1 | _  _  _ | _  7  4 |
	| 5  _  _ | _  _  _ | _  _  6 |
	| 7  3  _ | _  _  _ | 8  1  _ |
	-------------------------------
	| 4  _  8 | _  _  6 | _  _  _ |
	| _  _  2 | _  4  9 | _  _  _ |
	| 1  _  _ | _  2  _ | _  _  8 |
	-------------------------------

    SHOULD BE WRITTEN IN THE SUDOKU FILE AS

	8...5...3
	...46.7..
	...1..4.9
	.81....74
	5.......6
	73....81.
	4.8..6...
	..2.49...
	1...2...8
	
    ALL OF IT IN LEFT INDENTATION WITHOUT ANY SPACES ANYWHERE.

4. SAVE THE FILE AND KEEP IT IN THE SAME FOLDER AS THE Sudoku Ninja.exe FILE.

5. RUN THE .exe FILE !!!
		
/////////////////////////////////////////////////////////////////////////////
