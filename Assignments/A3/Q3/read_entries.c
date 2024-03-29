#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/pid.h>
#include <linux/sched.h>
#include <linux/module.h>



SYSCALL_DEFINE1(read_entries, pid_t, procid) {
    struct task_struct *data = find_task_by_pid(procid);

    if (data == NULL) {
        printk("Invalid pid provided.\n");
        return -EINVAL;
    }
    // the code below runs when the provided pid is valid and a task_struct has been assigned
    printk("Start of info ---------------------------------------------\n");
    printk("\nInformation about the provided process ID is given below:\n");
    printk("pid       -> %ld\n", task_pid(data));
    printk("userid    -> %ld\n", task_uid(data));
    printk("pgid      -> %ld\n", task_tgid(data));
    printk("cmd path  -> %s\n", get_task_comm(data));
    
    printk("\nEnd of info ---------------------------------------\n");

    return 0; // in syscalls, 0 indicates successfull execution of the syscall

}


static int __init read_entries_init(void) {
    printk("Module read_entries initialized.");
    /*
    int ret = sys_create_call(read_entries, __NR_read_entries);
    if (ret < 0) {
        printk("Unable to register the syscall.\n");
        return ret;
    }*/

    printk("Syscall successfully registered.\n");
    return 0;
}

static void __exit read_entries_exit(void) {
    printk("Module read_entries uninitialized.");
    /*sys_delete_call(__NR_read_entries);*/
    printk("Syscall successfully unregistered.\n");
}

module_init(read_entries_init);
module_exit(read_entries_exit);
