# PresidentialDebate
A project for the UMass course CS230

Youtube Link: https://youtu.be/DdRWbp93RgA

Project Summary: 
In this project we needed to create 200 threads that represent phone calls to a debate. With these threads we would need to simulate a presidential debate with call coming in.
In this deabte we have 5 phone lines and 2 operators taking questions from people who are calling. We would need to use thread synchronization so that all the threads can be calling
at once, and there won't be any issues when many phone calls are made. We are given a time for how long the debate lasts, so the operators will only take phone calls in that time
and stop taking phone call once that time is exceeded. 

Main Implementation:
In my implementation I first intialized binary semaphore for the connected_lock, and a counting semaphore for the operators. I did this as, there should only be 1 phonecall (thread) 
that can get connect into a line at a time, and because only one thread should be able to change the connected global variable at a time, so that there isn't any issues with multiple
threads trying to get or update the data from that variable. We use a counting semaphore for the operators as there are 2 operators conducting the debate, which means that we can
allow at most 2 phonecalls to be answered at a time. A counting semaphore can do this as it allows a certain amount of threads to access a part of the code at the same time
so that 2 threads can be asking questions on their phonecalls at the same time. After I ran a for-loop that created 200 threads which ran the phonecall thread function after they are 
created, they we each have there own callID parameter passed in. After the for-loop ends, I would create a timer thread that would keep track of the time for the debate. I would take
an argument variable, and convert it into an int. The timer thread would take the argument variable and run the timer thread function. After this the main thread would wait for the
timer thread to terminate with pthread_join(). After the main thread joins back with the timer thread, I destroy the semaphores and call exit() to terminate the process, which will
end up terminating all of the threads. 

Implementaion of Phonecalls: 
In the phonecall Thread function I first casted the parameter (void * vargp) into an int so I could use it as the callID for the thread. After I created a while loop, where 
the thread would be waiting to connect to a phone line. In this while loop, I implemented a sem_wait so that only 1 thread could access the connected variable in the while at a time, 
so that there wouldn't be any bugs when more than 1 thread could update the connected variable at a time. Then I had the thread connect to a phone line if there were less than 5 threads 
already connected to the phone line, I would increment connected and sem_post so that another thread could try to connect after this thread did. If there were 5 or more lines connected 
than the I would run sem_post so that another thread could try an connect, and then would make the current thread sleep for one second. After a thread connected to a call I would call
sem_wait for the operators, so that the thread would need to wait for one of the 2 operators to be open. If an operator was open it would join the call with that operator, and I would
call sleep(1), to simulate the thread asking a question. Once the thread finished the call, I wouldd call sem_post on the operator so that another thread could join in a call with 
an operator. After this I called sem_wait on the connected lines, so that only one thread could access that part of the code at a time, so that I could decremnt the connected global 
variable so other thread to connect to one of the 5 lines after the current thread was done with the call. After I would call sem_post so another thread could access that part of the
code. After this the thread would hang up.

Implementation of Timer thread function:
In the timer thread function, I took that paratmer that was passed in. I converted the paramter to an int, so that it could be used to tell how many seconds the thread should run for.
After I call sleep() with the converted int passed in so the thread would sleep for the alloted time. After it would finish with the function. 
