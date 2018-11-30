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
<ul>a. <code>pthread* thread_handles</code>: Declares variable to be able to point to an array of type pthread_t. (**C structure** describes the thread properties)<br>
b. <code>thread_handles = malloc(thread_count*sizeof(pthread_t))</code>: creates an array 5 elements of type pthread_t.<br>
c. <code>pthread_create(&thread_handles[thread],NULL,Hello,(void)*thread)</code>: create thread and stores them in the array <code>thread_handles</code>.
  <ul>c.1 <code>NULL</code>: 是一个参数指向一个<code>pthread_attr_t</code> structure里面的内容决定线程的属性。大多数时间为空.<br>
    c.2 <code>Hello</code>: function Hello.<br></ul>
d. <code>pthread_join(thread_handles[thread],NULL);</code>: this fuction waits for the threads to terminate. Null is the status of the thread when it terminates. For example,if the thread was canceled, the value of this argument is : PTHREAD_CANCELED.<br>
  e. <code>free(thread_handles)</code>: de-allocates the space allocated by <code>malloc(thread_count*sizeof(pthread_t))</code> in heap segment.<br>
</ul>
[Example2](https://github.com/Mira-Qiu/Shared-memory-architecture/blob/master/Example2.c) The program function take 3 parameters <br>
<ul><code>record_type *data = (record_type)*args</code> means take a number of bytes from the first byte of <code>args</code>.How many bytes? That many of the sizeof the record <code>record_type</code>. The size of thsi record is 12 (4bytes for rank, 4 bytes for a and 4 bytes for b) and the variable data points to this record.<br></ul>

## 3. Matrix-vector multiplications






    
    
