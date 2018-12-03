## 1. Process, Threads, and Pthreads
1. ***Stack segment***: a block of memory when a function is called to allocates locations for  ***parameters, local variables, static link, dynamic link*** and ***return address.*** <br>
**Static link**: a location whose content shows how to access to the local variables and global variables.内容是怎样进入本地和全局变量<br>
**Dynamic link** : a location whose content shows how many locations should be removed from top of the stack when the execution of the calling function is over. 单个一个运行结束后，有多少个地址应该在栈顶端被移除。<br>
**Return address** : a location whose content shows where the control of execution should go to execute the insturcion after the call of the function. 一个地址包含：收到call时 控制运行哪里的地址。<br><br>
2. ***Heap segment***: a block of memory which is needed when a program allocates space dynamically(e.g. by malloc). 程序分配动态空间。<br>
Security information: for example information about which hardware and software a process can access.<br>
The ***state*** of the process. ***ready, waiting***, 进程在ready等待 CPU运行？ 进程waiting从键盘被读一个值？信息就像寄存器，在I/O file 中读/写记号。这个信息需要储存进程的状态。例如，一个寄存器的内容是15，进程就会储存15在内存地址中或者一个进程即将从一个文件里读第三个字符在第四行。 当CPU要离开这个进程走到下一个进程时，这个信息必须保存。最终CPU会回来继续运行这个进程，这是的CPU加载这个寄存器15并且分配读记号能够继续读第三个字符第四行。<br><br>
3. **Thread** : are similar to processes but they share most of the resources above. The resources the threads do not share are the program counters and the stack. 程序计数器和栈不分享. Processes can execute different programms, while threads execute the same program but each of them a different part of a program. 例如，2个线程call 2 个不同的方程，这就是为什么线程不分享counter，每个方程需要不同的stack，这是为什么线程不分享stack.<br>
The threads API we are using here is from POSIX(Portable Operating System Interface) threads and the sofeware is called pthread.<br><br>
4. The following figure shows how the function main forks and why we need to join them:<br>
![fok image](https://github.com/Mira-Qiu/Shared-memory-architecture/blob/master/1.1.png?raw=true)<br>
<br>

## 2. Examples

[Example1](https://github.com/Mira-Qiu/Shared-memory-architecture/blob/master/a1.c)<br>
* Compile: <strong> gcc -g -Wall a.c -lpthread</strong><br>
* Run : <strong> ./a.out</strong><br>
<ul>a. <code>pthread* thread_handles</code>: Declares variable to be able to point to an array of type pthread_t. (**C structure** describes the thread properties)<br>
b. <code>thread_handles = malloc(thread_count*sizeof(pthread_t))</code>: creates an array 5 elements of type pthread_t.<br>
c. <code>pthread_create(&thread_handles[thread],NULL,Hello,(void)*thread)</code>: create thread and stores them in the array <code>thread_handles</code>.
  <ul>c.1 <code>NULL</code>: 是一个参数指向一个<code>pthread_attr_t</code> structure里面的内容决定线程的属性。大多数时间为空.<br>
    c.2 <code>Hello</code>: function Hello.<br></ul>
d. <code>pthread_join(thread_handles[thread],NULL);</code>: this fuction waits for the threads to terminate. Null is the status of the thread when it terminates. For example,if the thread was canceled, the value of this argument is : PTHREAD_CANCELED.<br>
  e. <code>free(thread_handles)</code>: de-allocates the space allocated by <code>malloc(thread_count*sizeof(pthread_t))</code> in heap segment.<br>
</ul>

[Example2](https://github.com/Mira-Qiu/Shared-memory-architecture/blob/master/Example2.c) <br>
<ul>The program function take 3 parameters <br>
<code>record_type *data = (record_type)*args</code> means take a number of bytes from the first byte of <code>args</code>.How many bytes? That many of the sizeof the record <code>record_type</code>. The size of thsi record is 12 (4bytes for rank, 4 bytes for a and 4 bytes for b) and the variable data points to this record.<br></ul>

## 3. Matrix-vector multiplications
[Example3](https://github.com/Mira-Qiu/Shared-memory-architecture/blob/master/Example3-Matrix-VectorMulti.c)<br>
<ul>The parallel program makes a vector y of size n by multiplying an m\*n matrix a and a Vector x of size n. Each thread multiplies its rows to the vector.<br>
<code>local_m = m/thread_count</code>: local_m is 2. 前两行给thread0， 第二个2行给thread1， 第三个2行给thread2. 也就是说每个thread运行找到2个y值。 This program was easy to hanle because no two threads write to the same location and there is no thread that reads from a location while the other thread read from the location.<br>
</ul>

## 4. Critical sections
***Critical Section*** :a segment of the program that only one thread at any time must enter to this segment to execute it.只有一个线程在任意时间必须进入这个片段并运行它。<br>

[Example4.c](https://github.com/Mira-Qiu/Shared-memory-architecture/blob/master/Example4_calculate_Pi.c)<br>
* 每个线程运行20000条，the value of the global varibale **sum** is the result of all 100,000 terms.<br>
* Problem: The variable **sum** is shared by all threads. **The section: sum += factor/(2\*i+1) in the above program is called a critical sections**<br>

## 5. Busy-Waiting

* The critical section has only one line: sum += 2. When the value of: flag is 1 thread 1 (my_rank=1) passes the while-loop and enters to the critical section. But thread 0 has to sit on the while-loop doing nothing. Once thread 1 finishes the critical section it changes the value of: flag to 0 (flag = (flag + 1) % thread_count). Now thread 0 can go to the critical section but thread 1 has to wait on the while-loop. Clearly this is a busy waiting approach.<br>
* Unfortunately, if thread 0 runs on a much faster processor than thread 1, or if we had a conditional statement as part of the critical-section to terminate one of the threads the other one sits on the while-loop forever. <br>
* Note that this method requires two threads strictly alternate in entering the critical section. What happen if one thread needs a long time to execute its other code that is not part of the critical section? Why the other one has to wait on the while-loop? This is not a fair approach.<br>

# 6. Mutexes
* A better approach to the problem critical section.<br>
* Excludes the other threads from entering CS while one thread is inside CS:
<code> pthread_mutex_lock(&mutex);</code><br>

# 7. Producer-Consumer synchronization and semaphores
*  To impose order on the threads.<br>
<code>sem_t sem_name</code> : a semaphore variable.<br>
<code>int sem_init(sem_t *sem_name,int pshared, unsigned int value)</code> : <br>
  sem_name : points to a semaphore object to initialize.<br>
  pshared : is a flag inidicating this semaphore is to be shared between the threads, or between processes. 0 -> shared between the threads.<br>
  value : is an initial value to set the semaphore to. 0 -> sem_name is locked.<br>
  <code>int sem_wait(sem_t *sem_name)</code>: 
  If value of semaphore is  ZERO, then the calling thread blocks(waits). <br>
  If the value of the semaphore is greater than ZERO this value is decremented ( by 1) and the calling thread proceeds(does not wait). <br>
  One of the blocked threads wakeds up when another thread calls: <code>sem_post</code>.<br>
  <code>int sem_post(sem_t* sem_name) </code> : This is the prototype. this call increments the value of the semaphore and wakes up a blocked thread waiting on this semaphore, if any. <br>
<br>
Every sending thread calls sem_post once. Since the value of the semaphore is 0, the system wakes up a receiving thread that is waiting on it. Since the value of the semaphore is 0, the system wakes up a receiving thread that is waiting on it. The receiving thread of the rank: 0 was waiting on: <code>sem_wait(&sem_name[0])</code>. Now it does not wait anymore and execute the next instruction which is: printf("%s\n", messages[0]). Since the sending thread already filled message[0] with a message we do not get a No message message from this thread. <br>

# 8. Barriers and conditional variables

* Synchronize threas method: busy-waiting(not recommend), muxes, semaphores and/or condition-variables.<br>
* <strong>Note</strong>: in general we cannot use pthread_join as a barrier since this function waits until all the threads terminate. we may have a situation where all threads had to do something reach to a point of the program and from this point continue for more work<br>
* Obviously busy-waiting loop waste the time of CPUs. this loop does not let the processors to execute some other usefule tasks in the system. But semaphores and mutex do. <strong>Note</strong>: unlike busy-waiting a thread who is waiting on a mutex or a semaphore relinquished the CPU.<br>
