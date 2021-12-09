#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
/* for copy_from_user */
#include <asm/uaccess.h>	
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Modulo que muestra la informacion de la memoria RAM");
MODULE_AUTHOR("Byron Antonio Orellana Alburez");

static int memo_info_proc_show(struct seq_file *memory, void *v) {
    struct sysinfo info;
    seq_printf(memory,info.totalram);
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
    proc_create("memo_201700733",0,NULL, &operaciones);
    printk(KERN_INFO "Carnet: 201700733\n");
    return 0;
}

static void _remove(void) {
    remove_proc_entry("memo_201700733", NULL);
    printk(KERN_INFO "Sistemas Operativos 1 Seccion no se ahorita xd\n");
}

module_init(_insert);
module_exit(_remove);