#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Basic Driver PCIHello");
MODULE_AUTHOR("Patrick Schaumont");

//-- Hardware Handles

static void *hexport;     // handle to 32-bit output PIO 7-seg display (4 on the right)
static void *hex_display; // handle to 32-bit output PIO 7-seg display (4 on the left)
static void *redlight;    // handle to 16-bit output PIO (Red Leds)
static void *greenlight;  // handle to 16-bit output PIO (Green Leds)
static void *inport;      // handle to 16-bit input PIO  (18 Switches)
static void *pushbutton;  // handle to 16-bit input PIO  (4 PushButtons)

//-- Char Driver Interface
static int   access_count =  0;
static int   MAJOR_NUMBER = 91;

static int     char_device_open    ( struct inode * , struct file *);
static int     char_device_release ( struct inode * , struct file *);
static ssize_t char_device_read    ( struct file * , char *,       size_t , loff_t *);
static ssize_t char_device_write   ( struct file * , const char *, size_t , loff_t *);

static struct file_operations file_opts = {
      .read = char_device_read,
      .open = char_device_open,
     .write = char_device_write,
   .release = char_device_release
};

static int char_device_open(struct inode *inodep, struct file *filep) {
   access_count++;
   printk(KERN_ALERT "altera_driver: opened %d time(s)\n", access_count);
   return 0;
}

static int char_device_release(struct inode *inodep, struct file *filep) {
   printk(KERN_ALERT "altera_driver: device closed.\n");
   return 0;
}

static ssize_t char_device_read(struct file *filep, char *buf, size_t type, loff_t *off) {
  long int switches;
  long int buttons;


  // Mudança de variavel len para type para escolhermos onde a entrada sera lida
  // type = 0 -> switches
  // type = 1 -> botoes


    if(type == 0)
    {
      switches = ioread32(inport);
      printk(KERN_ALERT "altera_driver: read %ld bytes\n", switches);

      put_user((switches) & 0xFF, buf++);
      put_user((switches >> 8) & 0xFF, buf++);
      put_user((switches >> 16) & 0xFF, buf++);

      /*put_user(switches & 0xFF, buf++);
      put_user((switches >> 8) & 0xFF, buf++);
      put_user((switches >> 16) & 0xFF, buf++);
      put_user((switches >> 24) & 0xFF, buf++);*/
    }
    else if(type == 1)
    {
      buttons = ioread32(pushbutton);
      put_user(buttons & 0xFF, buf++);
      put_user((buttons >> 8) & 0xFF, buf++);
      

    }

  return 4;
}

static ssize_t char_device_write(struct file *filep, const char *buf, size_t type, loff_t *off) {
  char *ptr = (char *) buf;
  //  printk(KERN_ALERT "altera_driver: write %d bytes\n", len);

  // Mudança de variavel len para type para escolhermos onde a saida sera exibida
  // type = 0 -> display de 4 digitos
  // type = 1 -> displays separados
  // type = 2 -> leds vermelhos
  // type = 3 -> leds verdes

  unsigned k = *((int *) ptr);

  if(type == 0)
    iowrite32(k, hexport);
  else if(type == 1)
    iowrite32(k, hex_display);
  else if (type == 2)
    iowrite32(k, redlight);
  else if (type == 3)
    iowrite32(k, greenlight);
  
  return 4;
}

//-- PCI Device Interface

static struct pci_device_id pci_ids[] = {
  { PCI_DEVICE(0x1172, 0x0004), },
  { 0, }
};
MODULE_DEVICE_TABLE(pci, pci_ids);

static int pci_probe(struct pci_dev *dev, const struct pci_device_id *id);
static void pci_remove(struct pci_dev *dev);

static struct pci_driver pci_driver = {
  .name     = "alterahello",
  .id_table = pci_ids,
  .probe    = pci_probe,
  .remove   = pci_remove,
};

static unsigned char pci_get_revision(struct pci_dev *dev) {
  u8 revision;

  pci_read_config_byte(dev, PCI_REVISION_ID, &revision);
  return revision;
}

static int pci_probe(struct pci_dev *dev, const struct pci_device_id *id) {
  int vendor;
  int retval;
  unsigned long resource;

  retval = pci_enable_device(dev);
  
  if (pci_get_revision(dev) != 0x01) {
    printk(KERN_ALERT "altera_driver: cannot find pci device\n");
    return -ENODEV;
  }

  pci_read_config_dword(dev, 0, &vendor);
  printk(KERN_ALERT "altera_driver: Found Vendor id: %x\n", vendor);

  resource = pci_resource_start(dev, 0);
  printk(KERN_ALERT "altera_driver: Resource start at bar 0: %lx\n", resource);

  hexport = ioremap_nocache(resource + 0XC000, 0x20);
  hex_display = ioremap_nocache(resource + 0XC020, 0x20);
  redlight = ioremap_nocache(resource + 0XC0A0, 0x20);
  greenlight = ioremap_nocache(resource + 0XC0C0, 0x20);
  inport  = ioremap_nocache(resource + 0XC060, 0x20);
  pushbutton = ioremap_nocache(resource + 0XC080, 0x20);

  return 0;
}

static void pci_remove(struct pci_dev *dev) {
  iounmap(hexport);
  iounmap(hex_display);
  iounmap(redlight);
  iounmap(greenlight);
  iounmap(inport);
  iounmap(pushbutton);
}


//-- Global module registration

static int __init altera_driver_init(void) {
   int t = register_chrdev(MAJOR_NUMBER, "de2i150_altera", &file_opts);
   t = t | pci_register_driver(&pci_driver);

   if(t<0)
      printk(KERN_ALERT "altera_driver: error: cannot register char or pci.\n");
   else
     printk(KERN_ALERT "altera_driver: char+pci drivers registered.\n");

   return t;
}

static void __exit altera_driver_exit(void) {
  printk(KERN_ALERT "Goodbye from de2i150_altera.\n");

  unregister_chrdev(MAJOR_NUMBER, "de2i150_altera");
  pci_unregister_driver(&pci_driver);
}

module_init(altera_driver_init);
module_exit(altera_driver_exit);
