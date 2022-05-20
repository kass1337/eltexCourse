#include <linux/module.h>
#include <linux/kobject.h>
#include <linux/init.h>

#include <linux/printk.h>
#include <linux/sysfs.h>

#include <linux/tty.h>          		/* For fg_console, MAX_NR_CONSOLES */
#include <linux/kd.h>           		/* For KDSETLED */
#include <linux/console_struct.h>       /* For vc_cons */
#include <linux/vt_kern.h>              /* For fg_console, MAX_NR_CONSOLES */


#include <linux/timer.h>
#include <linux/vt.h>
#include <linux/configfs.h>

MODULE_DESCRIPTION("Example module illustrating the use of Keyboard LEDs.");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");

struct timer_list my_timer;
struct tty_driver *my_driver;
static int kbledstatus = 0;

#define BLINK_DELAY   HZ/5
#define RESTORE_LEDS  0xFF

static struct kobject *number_kobject;
static int number = 0;

static void my_timer_func(struct timer_list *ptr) {
    int *pstatus = &kbledstatus;
    if (*pstatus == number)
        *pstatus = RESTORE_LEDS;
    else
        *pstatus = number;

    (my_driver->ops->ioctl) (vc_cons[fg_console].d->port.tty, KDSETLED, *pstatus);
    my_timer.expires = jiffies + BLINK_DELAY;
    add_timer(&my_timer);
}

// Функция активируется каждый раз при попытке чтения
static ssize_t number_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) {
    return sprintf(buf, "%d\n", number);
}

// Функция активируется каждый раз при попытке записи
static ssize_t number_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count) {
    sscanf(buf, "%du", &number);

    // При записи в файл удаляется старый таймер, и устанавливается новый с параметрами, полученными из файла
    del_timer(&my_timer);
    timer_setup(&my_timer, my_timer_func, 0);
    my_timer.expires = jiffies + BLINK_DELAY;
    add_timer(&my_timer);

    return count;
}

static struct kobj_attribute number_attribute = __ATTR(number, 0660, number_show, number_store);


static int __init mymodule_init (void) {

    // Создаётся "папка" в sys/kernel/ с названием "MyKeyboardLEDs"
    number_kobject = kobject_create_and_add("MyKeyboardLEDs", kernel_kobj);
    if(!number_kobject) {
        return -ENOMEM;
    }

    // Создаётся "файл" в папке sys/kernel/MyKeyboardLEDs/ с названием "number" (Название вытягивается из аттрибута)
    int error = 0;
    error = sysfs_create_file(number_kobject, &number_attribute.attr);
    if (error) {
        printk(KERN_ALERT "Failed to create file in /sys/kernel/MyKeyboardLEDs \n");
    }


    int i;
    printk(KERN_INFO "kbleds: loading\n");
    printk(KERN_INFO "kbleds: fgconsole is %x\n", fg_console);
    for (i = 0; i < MAX_NR_CONSOLES; i++) {
        if (!vc_cons[i].d)
            break;
        printk(KERN_INFO "poet_atkm: console[%i/%i] #%i, tty %lx\n", i,
               MAX_NR_CONSOLES, vc_cons[i].d->vc_num,
               (unsigned long)vc_cons[i].d->port.tty);
    }

    printk(KERN_INFO "kbleds: finished scanning consoles\n");
    my_driver = vc_cons[fg_console].d->port.tty->driver;
    printk(KERN_INFO "kbleds: tty driver magic %x\n", my_driver->magic);

    // Первая установка таймера
    timer_setup(&my_timer, my_timer_func, 0);
    my_timer.expires = jiffies + BLINK_DELAY;
    add_timer(&my_timer);

    printk(KERN_INFO "Module initialized successfully \n");
    return error;
}

static void __exit mymodule_exit (void) {
    del_timer(&my_timer);
    (my_driver->ops->ioctl) (vc_cons[fg_console].d->port.tty, KDSETLED, RESTORE_LEDS);

    kobject_put(number_kobject);

    printk(KERN_INFO "Module uninitialized successfully \n");
}

module_init(mymodule_init);
module_exit(mymodule_exit);