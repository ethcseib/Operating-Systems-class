--Program Information--
  Name: Cody Gonsowski & Ethan Seiber
  Date: 1/23/2020
  Assignment: Assignment #1
  Program Title: The Unix Shell
  Files required: shell.c, Queue.h/c, GlobalVars.txt

--Design Overview--
  Took advantage of queues in order to execute commands concurrently.

  Kept queue implementations in separate files to increase readability.

  Created a GlobalVars.txt file to store global instructions such as
  preprocessing statements and varaibles to be used by other files. This was
  mostly to have these instructions to play nice with the makefile.

  The main or driving function of the program can be seen as broken in two
  halves. One half is used for batch file processing while the other is the
  interactive mode that will take input from the user. Each mode will strip
  away excess semicolons except for semicolons that have any white space
  between them. They will still be stripped away, but the white space is still
  a command it just does nothing so it will be executed. Any white space before
  and after a command will also be stripped away before execution.

--Known Bugs/Problems--
  The only known bug is if you have a command typo in your batch file this
  will initially cause the commands after to be executed twice. Any more typos
  than this will crash the program.
