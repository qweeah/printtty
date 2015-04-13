/*
 * printtty.c − Send output to the tty we're running on, regardless if it's
 * through X11, telnet, etc. We do this by printing the string to the tty
 * associated with the current task.
 * kernel version ealrier than 2.6.5 isn't supported
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
 /* For current */
#include <linux/tty.h>
 /* For the tty declarations */
#include <linux/version.h>
 /* For LINUX_VERSION_CODE...but definitely useless here! */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Peter Jay Salzman & Billy");

 /* TODO:any kernel pre-set const?  */
#define BUF_LEN 800 //length of buffer

/* 
 * This function will automatically add an line feed
 */
static void print_string(char *str)
{
	struct tty_struct *my_tty;

	my_tty = current->signal->tty;
	/*
	 * * If my_tty is NULL, the current task has no tty you can print to
	 * * (ie, if it's a daemon). If so, there's nothing we can do.
	 * */
	if (my_tty != NULL) {
		((my_tty->driver->ops)->write) (my_tty, /* The tty itself */
					        str, 	/* String */
						strlen(str));/* Length */

		((my_tty->driver->ops)->write) (my_tty, "\015\012", 2); /* Adding line feed  */
	}
}

/*
 * Since print_string has no return, printtty is 'void'
 */
void printtty(const char *format, ...)
{
	va_list arg;
	char msg_buf[BUF_LEN];

	va_start (arg, format);
	vsprintf(msg_buf, format, arg); //sprintf cannot be used here
	va_end (arg);

	print_string(msg_buf);
}
EXPORT_SYMBOL(printtty);

static int __init printtty_init(void)
{
	//print_string("Test printt module has been inserted!");
	int a=1;
	char b='2';
	char *c="3..OK!";
	printtty("Print TTY module has been inserted!");
	printtty("Let's count to 3, %d%c%s",a,b,c);
	return 0;
}
static void __exit printtty_exit(void)
{
	print_string("Print TTY module has been removed!");
}
module_init(printtty_init);
module_exit(printtty_exit);

