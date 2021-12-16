#include <linux/hugetlb.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>	
#include <linux/seq_file.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Modulo que muestra la informacion del cpu");
MODULE_AUTHOR("Byron Antonio Orellana Alburez");

struct task_struct *process, *child_process;
struct list_head *hijos;

static int memo_info_proc_show(struct seq_file *file, void *v) {
    long totMemo;
    #define TASK_RUNNING            0
    #define TASK_INTERRUPTIBLE      1
    #define TASK_UNINTERRUPTIBLE    2
    #define TASK_ZOMBIE             4
    #define TASK_STOPPED            8

    seq_printf(file,"\t'TASK RUNNING': %d,\n",TASK_RUNNING);
    for_each_process(process) {
        if(process->mm) {
            totMemo= get_mm_rss(process->mm);
        }
        seq_printf(file, "{\n");
        seq_printf(file,"\t'Memoria': %lu,\n",totMemo/1024);
        seq_printf(file,"\t'Proceso': %s,\n",process->comm);
        seq_printf(file,"\t'Usuario': %d,\n",process->real_cred->uid);
        seq_printf(file,"\t'PID': %d,\n",process->pid);
        seq_printf(file,"\t'Childs': [\n");
        list_for_each(hijos, &(process->children)) {
            child_process= list_entry(hijos, struct task_struct, sibling);
            seq_printf(file, "\t{\n");
            seq_printf(file,"\t\t'ProcesoHijo': %s,\n",child_process->comm);
            seq_printf(file,"\t\t'PIDhijo': %d,\n",child_process->pid);
            seq_printf(file, "\t}\n");
        }
        seq_printf(file,"\t]\n");
        seq_printf(file, "},\n");
    }
    return 0;
}
static int memo_open(struct inode *inode, struct file *file) {
    return single_open(file,memo_info_proc_show,NULL);
}

static struct proc_ops operaciones= {
    .proc_open= memo_open,
    .proc_read= seq_read 
};

static int _insert(void) {
    printk(KERN_INFO "Nombre: Byron Antonio Orellana Alburez\n");
    proc_create("cpu_201700733",0,NULL, &operaciones);
    return 0;
}

static void _remove(void) {
    printk(KERN_INFO "Diciembre 2021\n");
    remove_proc_entry("cpu_201700733",NULL);
}

module_init(_insert);
module_exit(_remove);