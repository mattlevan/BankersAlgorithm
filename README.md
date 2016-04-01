# Banker's Algorithm
Project 4  
CSC 341: Operating Systems  
Dr. Bin Tang  
  
Matt Levan  
Bradley Taniguchi  

### Instructions
1. compile with `make` or `make app`
2. run with `./banker.o <int num first resource> <int num second> <int num third> <int runtime seconds>`
    example: `./banker.o 5 6 3 50` for a runtime of 50 seconds
---
### Screenshots
to be added...

--- 
### Prompt

Page 345.

Please submit your project as 
"LastNameOfFirstStudent_LastNameOfSecondStudent_proj4.zip", 
which includes the i) source codes, ii) a readme as how to execute 
your program, and iii) some screenshots of your successful execution.

To help us to test your program, please have your program print out in 
the format specified in the attached "banker_output", which is my output 
running for 50 seconds.

Let's focus on 5 customers and 3 resources, as specified in the book. 
Please use the attached "max_demand.txt" for the maximum demand of each 
process/customer; you can hard code this file name in your program.

---
### Max Demand

7,5,3  
3,2,2  
9,0,2  
2,2,2  
4,3,3  

Each process/customer sleeps for a random time (between 0 and 5) and 
then requests some number of instances for each resource type. Here, the 
number of instances of each type requested by a process should be a random
number between 0 and the number of remaining instances of that that type 
it needs. The the banker's algorithm will check if this request will be 
granted. If yes, then the process will be using granted resources for a 
random time between 0 and 5, and then releases those resources. If no, 
either because there is not enough resources for the request, in which
case the request is denied and it prints out "INSUFFICIENT RESOURCES", or 
banker's algorithm finds deadlock if accepting this request, in which 
case the request is also denied (instead of being told to wait as in the 
book), for the simplification of your implementation,

Instead of ./a.out 10 5 7, your program should take the command line 
arguments as follows: ./a.out 10 5 7 50, where 50 is the runtime of your 
program.

Please start early.
