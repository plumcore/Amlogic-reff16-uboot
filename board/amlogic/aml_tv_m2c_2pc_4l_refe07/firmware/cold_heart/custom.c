/*

typedef  struct {
    char             *platform_name;
    unsigned int  pin_mux;
    unsigned int  bit;
}pin_config_t;

static  pin_config_t  pin_config[]={
        {
            .platform_name="8626",
            .pin_mux=1,
            .bit=(1<<31),
        },
        {
            .platform_name="6236",
            .pin_mux=5,
            .bit=(1<<31),
        },
        {
            .platform_name="8726",
            .pin_mux=5,
            .bit=(1<<31),
        },
        {
            .platform_name="7366",
            .pin_mux=10,
            .bit=(1<<12),
        },
};
*/
#define IR_CONTROL_HOLD_LAST_KEY   (1<<6)

#ifdef AML_REF_IR
/*****************************************************************
**
** func : ir_remote_init
**       in this function will do pin configuration and and initialize for
**       IR Remote hardware decoder mode .
**
********************************************************************/
static int ir_remote_init(void)
{
    unsigned int control_value,status,data_value;
    int i;

    setbits_le32(P_PERIPHS_PIN_MUX_10, (1<<13)); //和具体芯片相关
    //step 1 :set reg IR_DEC_CONTROL
        control_value = 3<<28|(0xFA0 << 12) |0x13;

        WRITE_MPEG_REG(IR_DEC_REG0, control_value);
        //control_value = READ_MPEG_REG(IR_DEC_REG1);
        control_value = 0xfbe40;
        WRITE_MPEG_REG(IR_DEC_REG1, control_value | IR_CONTROL_HOLD_LAST_KEY);

        status = READ_MPEG_REG(IR_DEC_STATUS);
        data_value = READ_MPEG_REG(IR_DEC_FRAME);
		
    //step 2 : request nec_remote irq  & enable it
    return 0;
}

void ir_remote_irq_handler(void *data)
{
	unsigned int status,scan_code;
	unsigned char key_code;
	unsigned long *cold_heart_status = 0x49001ffc;
	scan_code=READ_MPEG_REG(IR_DEC_FRAME);
	status=READ_MPEG_REG(IR_DEC_STATUS);
	key_code = (scan_code>>16)&0xff;
	
	if((key_code == 0x0a)|| (key_code == 0xd7))
	{
		serial_puts("key:");
		serial_put_char(key_code);

		*cold_heart_status = 0x5a5a5a5a;
		
		chip_reset();
	}
	//serial_put_dword(scan_code);
	//serial_put_dword(status);

	WRITE_CBUS_REG(0x2691, 1<<15);
	asm volatile ("wfi");

}


#elif defined(SKYWORTH_IR)

static int ir_remote_init(void)
{
    unsigned int control_value,status,data_value;
    int i;

    setbits_le32(P_PERIPHS_PIN_MUX_10, (1<<12)); //和具体芯片相关
    //step 1 :set reg IR_DEC_CONTROL
        control_value = 3<<28|(0xFA0 << 12) |0x13;

        WRITE_MPEG_REG(IR_DEC_REG0, control_value);
        //control_value = READ_MPEG_REG(IR_DEC_REG1);
        control_value = 0xfbe50;
        WRITE_MPEG_REG(IR_DEC_REG1, control_value | IR_CONTROL_HOLD_LAST_KEY);

		WRITE_MPEG_REG(IR_DEC_LDR_ACTIVE, 0x00f800ca);
		WRITE_MPEG_REG(IR_DEC_LDR_IDLE, 0x00f800ca);
		WRITE_MPEG_REG(IR_DEC_LDR_REPEAT, 0x00f800ca);

        status = READ_MPEG_REG(IR_DEC_STATUS);
        data_value = READ_MPEG_REG(IR_DEC_FRAME);

    //step 2 : request nec_remote irq  & enable it
    return 0;
}

void ir_remote_irq_handler(void *data)
{
	unsigned int status,scan_code;
	unsigned char key_code;
	unsigned long *cold_heart_status = 0x49001ffc;
	scan_code=READ_MPEG_REG(IR_DEC_FRAME);
	status=READ_MPEG_REG(IR_DEC_STATUS);
	key_code = (scan_code>>16)&0xff;
	
	if((key_code == 0x0c) || (key_code == 0x12) || (key_code == 0x13))
	{
		serial_puts("key:");
		serial_put_char(key_code);

		*cold_heart_status = 0x5a5a5a5a;
		
		chip_reset();
	}
	//serial_put_dword(scan_code);
	//serial_put_dword(status);
}


#endif

void gpio_0_irq_handler(void *data)
{
	disable_interrupts();
	unsigned long *cold_heart_status = 0x49001ffc;
	serial_puts("Power Key");
	*cold_heart_status = 0x5a5a5a5a;
	chip_reset();
	enable_interrupts();
}

void init_custom_trigger(void)
{
	ir_remote_init();
}

void enable_custom_trigger(void)
{
	meson_ack_irq(INT_GPIO_0);
	
	irq_install_handler(INT_GPIO_0, gpio_0_irq_handler, NULL);     // enable GPIO_0 interrupt
	irq_install_handler(INT_REMOTE, ir_remote_irq_handler, NULL);     // enable remote interrupt
}

