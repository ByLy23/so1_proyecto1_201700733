#include <linux/hugetlb.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>	
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Modulo que muestra la informacion de la memoria RAM");
MODULE_AUTHOR("Byron Antonio Orellana Alburez");

// static struct proc_dir_entry *ent;

static int memo_info_proc_show(struct seq_file *memory, void *v) {
    struct sysinfo info;
    unsigned long pages[NR_LRU_LISTS];
    int lru;
#define K(x) ((x) << (PAGE_SHIFT - 10))
    si_meminfo(&info);
    for (lru= LRU_BASE; lru< NR_LRU_LISTS; lru++)
        pages[lru] = global_numa_state(NR_LRU_BASE + lru);
    seq_printf(memory,"{\n");
    seq_printf(memory,"\"ram\": %8lu,\n",K(info.totalram));
    seq_printf(memory,"\"free\": %8lu,\n",K(info.freeram));
    seq_printf(memory,"\"buffer\": %8lu,\n",K(info.bufferram));
    seq_printf(memory,"\"shared\": %8lu,\n",K(info.sharedram));
    seq_printf(memory,"\"high\": %8lu,\n",K(info.totalhigh));
    seq_printf(memory,"\"freehigh\": %8lu,\n",K(info.freehigh));
    seq_printf(memory,"\"mem_unit\": %8lu,\n",K(info.mem_unit));
    seq_printf(memory,"\"used\": %8lu,\n",(K(info.totalram)-(K(info.freeram)+K(info.bufferram))));
    seq_printf(memory,"\"avg\": %8lu,\n",(((K(info.totalram)-K(info.freeram)-K(info.bufferram))/1024)*100)/(K(info.totalram)/1024));
    seq_printf(memory,"}\n");
#undef K
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