# OperatingSystems_01
Topic : Producer and Consumer problem 
The producer generates items and puts items onto the table. The consumer 
will pick up items. The table can only hold two items at the same time. 
When the table is complete, the producer will wait. When there are no 
items, the consumer will wait. We use semaphores to synchronize producer 
and consumer.  Mutual exclusion should be considered. We use threads in 
the producer program and consumer program. Shared memory is used for 
the “table”. 

To run the code using Linux commands : 
$ gcc producer.c -pthread -lrt -o producer 
$ gcc consumer.c -pthread -lrt -o consumer 
$ ./producer & ./consumer &  

The output should be: 
- The Producer will generate items and place them on the table.
- The Consumer will pick up the items from the table.
- If the table is full, the Producer will wait until space is available.
- If the table is empty, the Consumer will wait until items are available.
