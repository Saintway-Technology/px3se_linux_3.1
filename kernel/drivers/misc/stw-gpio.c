#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <linux/of_gpio.h>


MODULE_LICENSE("GPL");


struct device * pdevice;

int wakein;
int dtr;
int rst;
int disable;

int gps_pwr;


int get_gps_gpio(struct device_node *np)
{
	
	unsigned long gpios;
        gps_pwr = of_get_named_gpio_flags(np, "gps_pwr", 0,(enum of_gpio_flags *)&gpios);
	gpio_request(gps_pwr,NULL);
	gpio_direction_output(gps_pwr, 1);
        gpio_set_value(gps_pwr, 1);	
	return 0;
}

int get_gprs_gpio(struct device_node *np)
{
	unsigned long gpios;
	
        wakein = of_get_named_gpio_flags(np, "wakein", 0,(enum of_gpio_flags *)&gpios);
        dtr = of_get_named_gpio_flags(np, "dtr", 0,(enum of_gpio_flags *)&gpios);
        rst = of_get_named_gpio_flags(np, "rst", 0,(enum of_gpio_flags *)&gpios);
        disable = of_get_named_gpio_flags(np, "disable", 0,(enum of_gpio_flags *)&gpios);
	
	gpio_request(wakein,NULL);
	gpio_direction_output(wakein, 0);
        gpio_set_value(wakein, 0);	

	gpio_request(dtr,NULL);
	gpio_direction_output(dtr, 0);
        gpio_set_value(dtr, 0);	

	gpio_request(rst,NULL);
	gpio_direction_output(rst, 1);
        gpio_set_value(rst, 1);	

	gpio_request(disable,NULL);
	gpio_direction_output(disable, 0);
        gpio_set_value(disable, 0);

	msleep(200);
	
	gpio_direction_output(rst, 0);
        gpio_set_value(rst, 0);	
	
	return 0;	
}

int demo_probe(struct platform_device * pdevice) 
{

	struct device_node *np = pdevice->dev.of_node;

	printk("probe ok!\n");
	get_gprs_gpio(np);
	get_gps_gpio(np);

	return 0;
}

int demo_remove(struct platform_device * pdevice)
{
	printk("%s,%d\n", __func__, __LINE__);	
	
	return 0;
}


struct of_device_id  idts[] = {
	{.compatible = "stw,gpio"},
//	{.compatible = "stw,cif_pwr"},
	{/*Nothing  to be done.*/},
};

struct platform_driver pdriver = {
	.probe = demo_probe,
	.remove = demo_remove,
	.driver = {
		.name = "stw_gpio",
		.of_match_table = idts,
		.owner  = THIS_MODULE,
	},
};

module_platform_driver(pdriver);
