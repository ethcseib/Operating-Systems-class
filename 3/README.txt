Bugs/Limitations:
	Has problems if their are not pairs of withdraw and deposit threads.

Sample Output:

       Blocking thread because balance is 0

       Blocking thread because balance is 0

       At time 0, the balance before depositing thread 1105479424 is 0
       At time 0, the balance after depositing thread 1105479424 is 11

       At time 0, the balance before depositing thread 1097086720 is 11

       Waking up withdraw threads because balance is 11

       At time 0, the balance after depositing thread 1097086720 is 22

       At time 0, the balance for withdrawal thread 1122264832 is 22
       At time 0, the balance after withdrawal thread 1122264832 is 12

Output explanation:
       Blocking happens at the beginning of the program because I start the program by
       starting the withdraw threads then the deposit. This ensures blocking happens because
       initially the balance is zero. As shown by the "blocking thread" messge. The time is zero
       in some of the messages because this is the output from the beginning of the execution.
       The threads are woken up when the balance is greater than 10 as shown where the ouput
       says "waking up".

Design Overview:
       I created two functions to manipulate the balance through threads. These functions

       I then used 3 global variables throughout the program. One variable to hold the
       current amount of the balance. Another for the mutex to control access to this
       balance. The final one will wake up the asleep threads. These variables are the
       "balance", the "the_mutex" and the "condW".
