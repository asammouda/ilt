#include <linux/interrupt.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/ioport.h>
#include <asm/io.h>


static irqreturn_t exemple_handler(int irq, void * ident)
{
	if ((inb(0x379) & 0x40) == 0)
		return IRQ_NONE;
	return IRQ_WAKE_THREAD;
}


static irqreturn_t exemple_thread(int irq, void * ident)
{
	static int valeur = 0;
	outb(valeur, 0x378);
	valeur = 0xFF - valeur;
	return IRQ_HANDLED;
}


static int __init exemple_init (void)
{
	int erreur;
	
	if (request_region(0x378, 3, THIS_MODULE->name) == NULL)
		return -EBUSY;

	erreur = request_threaded_irq(7, exemple_handler,
	                              exemple_thread, IRQF_SHARED,
	                              THIS_MODULE->name, THIS_MODULE->name);
	if (erreur != 0) {
		release_region(0x378, 3);
		return erreur;
	}
	outb(0x10, 0x37A);
	return 0; 
}

static void __exit exemple_exit (void)
{
	outb(0, 0x37A);
	free_irq(7, THIS_MODULE->name);
	release_region(0x378, 3);
}

module_init(exemple_init);
module_exit(exemple_exit);
MODULE_LICENSE("GPL");

