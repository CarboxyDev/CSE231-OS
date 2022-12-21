### Primitives used for functionality
    struct task_struct -> This holds the data about a process like the pid, userid, etc.
    find_task_by_pid(pid)
    task_pid(struct task_struct* data)
    task_uid(struct task_struct* data)
    task_tgid(struct task_struct* data)
    get_task_comm(struct task_struct* data)
    syscall_regfunc()
    syscall_unregfunc()
    module_init()
    module_exit()


### Explanation

I had to define a syscall which takes one parameter: the pid of a process. This required defining a syscall with SYSCALL_DEFINE1 where the 1 stands for the number of arguments (which in this case is 1). In the syscall, I got access to the task_struct from the pid. In order to only use the syscall when the module is loaded, the program had to register and unregister the syscall once the kernel module was loaded and unloaded respectively.