## Producer Consumer Problem:

The producer generates items and puts items onto the table. The consumer will pick up items.
The table can only hold two items at the same time. When the table is completed, the producer
will wait. When there are no items, the consumer will wait. We use semaphores to synchronize
the producer and the consumer. Mutual exclusion should be considered. We use threads in
the producer program and consumer program. Shared memory is used for the “table”

## Must Install for the program to run correctly:
```bash
sudo apt update && sudo apt install g++
```
## To Build program:
```bash
git clone https://github.com/vortexxxxxxxxxxxx/Misc-School-Work/tree/main/Operating%20Systems%20Fall%202025/OS_producer_consumer_problem.git
cd OS_producer_consumer_program
chmod +x run.sh
./run.sh run
```
run.sh is used to compile and clean the program. you must clean or else the producer consumer progam will run infenitely
```bash
./run.sh

help      Display this help message
run       Build and launch producer & consumer
clean     Terminate producers/consumers and remove shared buffer
```

## Example:
Terminal output 1:
```bash
mkeffer4@gamer:~/OS2025/OS_producer_consumer_problem$ ./run.sh run; sleep 5; ./run.sh clean
[*] Starting Compilation of Producer and Consumer
[*] Executing Producer and Consumer:
[*] Produced: 237
[*] Consumed: 237
[*] Produced: 145
[*] Consumed: 145
[*] Produced: 301
[*] Consumed: 301
[*] Produced: 89
[*] Consumed: 89
```
Terminal output 2:
```bash
mkeffer4@gamer:~/OS2025/OS_producer_consumer_problem$ ./run.sh run; sleep 5; ./run.sh clean
[*] Starting Compilation of Producer and Consumer...
[*] Executing Producer and Consumer...
[*] Produced: 42
[*] Consumed: 42
[*] Produced: 173
[*] Produced: 215       
[*] Consumed: 173
[*] Consumed: 215
[*] Produced: 88
[*] Consumed: 88
[*] Produced: 156
```
