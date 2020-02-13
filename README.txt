Ethan Seiber

Design Overview:
       Created a typedef struct for passing parameters to threads.

       Created the function FillParameters to avoid race conditions when looking at the 3*3 subgrids.

       The program consists of three driving loops: an input loop that reads a sudoku table from a file,
       a row and column checking loop, then a loop for checking 3*3 subgrids for correctness.

       Used a global variable called check that threads have access to. This variable is used to signal
       whether the sudoku table provided is correct.

       There are a total of 3 sudoku table checking functions. One function for checking the table
       columns, another for the rows and lastly one for checking a subgrid.
       
       Designed the program to be used specifically for a 9*9 sudoku table and thus doesn't scale. 

Known Bugs:
      There are no known bugs and all things were implemented that needed to be.
