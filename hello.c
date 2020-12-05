#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>

#include <linux/types.h>

#include <linux/slab.h>

#include <linux/ktime.h>

struct personal_list_head {
struct personal_list_head *next;
ktime_t time;
};

MODULE_AUTHOR("Samutin Oleksii <samutin63@gmail.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static struct personal_list_head *header;

static uint numberOfRepeats = 1;
module_param(numberOfRepeats,uint,S_IRUGO);
MODULE_PARM_DESC(numberOfRepeats, "The amount of times to print hello world");

static int __init initter(void)
{
  uint i = 0;
  struct personal_list_head *first_variable, *second_variable;

  printk(KERN_INFO "numberOfRepeats: %d\n", numberOfRepeats);

  if(numberOfRepeats == 0) {
    printk(KERN_WARNING "The numberOfRepeats is 0");
  }else if(numberOfRepeats >=5 && numberOfRepeats <= 10) {
    printk(KERN_WARNING "The numberOfRepeats is between 5 and 10");
  } else if(numberOfRepeats > 10) {
    printk(KERN_ERR "The numberOfRepeats is greater than 10");
    return -EINVAL;
  }

  header = kmalloc(sizeof(struct personal_list_head *), GFP_KERNEL);
  first_variable = header;
  
  for(i = 0; i < numberOfRepeats; i++){
  first_variable->next = kmalloc(sizeof(struct personal_list_head), GFP_KERNEL);
    first_variable->time = ktime_get();
    pr_info("Hello World!");
    second_variable = first_variable;
    first_variable = first_variable->next;
    }
    if (numberOfRepeats != 0) {
      kfree(second_variable->next);
      second_variable->next = NULL;

  }
  printk(KERN_INFO "numberOfRepeats: %d\n", numberOfRepeats);
  return 0;
}

static void __exit exitter(void)
{
  struct personal_list_head *variable;
  while (header != NULL && numberOfRepeats != 0) {
    variable = header;
    pr_info("Time : %lld", variable->time);
    header = variable->next;
    kfree(variable);
  }
  if (numberOfRepeats == 0) {
    pr_info("Time is 0 because print wasn't used");
  }
  pr_info("");
}

module_init(initter);
module_exit(exitter);




 
