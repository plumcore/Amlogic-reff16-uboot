/*
 * (C) Copyright 2006-2010
 * Amlogic .
 * Author :
 *  Jerry Yu <jerry.yu@amlogic.com>
 */

#ifndef __CONFIG_H
#define __CONFIG_H
//#define DEBUG 1
/*
 * High Level Configuration Options
 */
#define CONFIG_ARMCORTEXA9     1     /* This is an ARM V7 CPU core */
#define CONFIG_MESON           1     /* in a Amlogic Meson core */
#define CONFIG_MESON1          1     /* which is meson */

#define CONFIG_AML_MESION2C    1
//#define CONFIG_AML_MESION_2C    1    //M1,M3 style?

#define CONFIG_AML_DDR_PLL_FINE_TUNE 1

//#define CONFIG_NAND_AML_M2    1 

#define CONFIG_AMLROM_U_BOOT       1    /**
                                        Meson support Romboot mode
                                    */
#define CONFIG_BOARD_M2_SOCKET      1
#define BOARD_UART_PORT             UART_PORT_1
#define CONFIG_AML_DEF_UART         1
/**
 * NAND define
 *
 */

#define CONFIG_UCL      1

#define AMLOGIC_REBOOT_MODE

#define CONFIG_COLD_HEART	1	//for power saving
#ifdef CONFIG_COLD_HEART
#define CONFIG_COLD_HEART_STORE_ADDR 0x86000000
#define CONFIG_COLD_HEART_KEY 0x28D7F708

#define AML_REF_IR
#endif

#define CONFIG_AMLLVDS
#define CONFIG_SARADC   1


#define CONFIG_CMD_BL
#define CONFIG_CMD_BMP
#define CONFIG_AMLVIDEO
#define CONFIG_AMLOSD
#define CONFIG_CMD_OSD
#define LCD_BPP	LCD_COLOR24
#define FB_ADDR     0x85100000
#define OSD_WIDTH   1920
#define OSD_HEIGHT  1080
#define OSD_BPP     OSD_COLOR24


#include <asm/arch/cpu.h>   /* get chip and board defs */

/*
 * Display CPU and Board information
 */

/* Clock Defines */
#define CONFIG_SYS_CLK      600 /*600Mhz  a9 clk@todo redefine it later
                                 */
#define CONFIG_CRYSTAL_MHZ      24
#undef CONFIG_USE_IRQ              /* no support for IRQs */
#define CONFIG_MISC_INIT_R

#define CONFIG_CMDLINE_TAG      1   /* enable passing of ATAGs */
#define CONFIG_SETUP_MEMORY_TAGS    1
#define CONFIG_INITRD_TAG       1
#define CONFIG_REVISION_TAG     1
#define CONFIG_CMD_KGDB         1
//#define CONFIG_SERIAL_TAG       1
//#define CONFIG_CMD_NET            1
#define CONFIG_NET_MULTI        1
#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP

/*
 * Size of malloc() pool
 */
                        /* Sector */
#define CONFIG_SYS_MALLOC_LEN       (CONFIG_ENV_SIZE + (1 << 19))
#define CONFIG_SYS_GBL_DATA_SIZE    128 /* bytes reserved for */
                        /* initial data */
/*
 * Hardware drivers
 */



/*
 * select serial console configuration
 */
//#define CONFIG_CONS_INDEX     0
#undef CONFIG_CONS_INDEX

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE
#define CONFIG_BAUDRATE         115200
#define CONFIG_SYS_BAUDRATE_TABLE   {4800, 9600, 19200, 38400, 57600,\
                    115200}
#define CONFIG_MMC             1
//#define CONFIG_MMC_FORCE_1BIT_MODE  1
//#define CONFIG_OMAP3_MMC      1
#define CONFIG_DOS_PARTITION        1

//added by Elvis
#define SCAN_USB_PARTITION  1
#define CONFIG_SWITCH_BOOT_MODE
#define CONFIG_CMD_AUTOSCRIPT
#define CONFIG_AML_AUTOSCRIPT
#define AML_AUTOSCRIPT  "aml_autoscript"

/* USB
 * Enable CONFIG_MUSB_HCD for Host functionalities MSC, keyboard
 * Enable CONFIG_MUSB_UDD for Device functionalities.
 */
/* #define CONFIG_MUSB_UDC      1 */
#define CONFIG_M2_USBPORT_BASE  0xC9040000
#define CONFIG_USB_STORAGE
#define CONFIG_USB_DWC_OTG_HCD


/* commands to include */
#include <config_cmd_default.h>

#define CONFIG_CMD_EXT2     /* EXT2 Support         */
//#define CONFIG_CMD_FAT        /* FAT support          */
//#define CONFIG_CMD_JFFS2  /* JFFS2 Support        */
//
//#define CONFIG_CMD_I2C        /* I2C serial bus support   */
//#define CONFIG_CMD_MMC        /* MMC support          */
//#define CONFIG_CMD_ONENAND    /* ONENAND support      */
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PING
#define CONFIG_CMD_USB
#define CONFIG_CMD_FAT

//
#undef CONFIG_CMD_ONENAND
#undef CONFIG_CMD_FLASH     /* flinfo, erase, protect   */
#undef CONFIG_CMD_FPGA      /* FPGA configuration Support   */
#undef CONFIG_CMD_IMI       /* iminfo           */
#undef CONFIG_CMD_IMLS      /* List all found images    */

#define CONFIG_SYS_NO_FLASH 1

/*
 * TWL4030
 */
//#define CONFIG_TWL4030_POWER      1


                            /* NAND devices */
#define CONFIG_JFFS2_NAND
/* nand device jffs2 lives on */
#define CONFIG_JFFS2_DEV        "nand0"
/* start of jffs2 partition */
#define CONFIG_JFFS2_PART_OFFSET    0x680000
#define CONFIG_JFFS2_PART_SIZE      0xf980000   /* sz of jffs2 part */

/* Environment information */
#define CONFIG_BOOTDELAY    1

#define CONFIG_BOOTFILE     uImage

#define CONFIG_EXTRA_ENV_SETTINGS \
    "loadaddr=0x82000000\0" \
    "usbtty=cdc_acm\0" \
    "mmcargs=setenv bootargs console=${console} root=/dev/mmcblk0p2 rw rootfstype=ext3 rootwait\0" \
    "loadbootscript=fatload mmc 0 ${loadaddr} boot.scr\0" \
    "bootscript=echo Running bootscript from mmc ...; source ${loadaddr}\0" \
    "loaduimage=fatload mmc 0 ${loadaddr} uImage\0" \
    "mmcboot=echo Booting from mmc ...; run mmcargs; bootm ${loadaddr}\0" \
    "boardname=m1_mbox_m1\0" \
    "chipname=7366m\0" \
    "machid=2958\0" \
    "ethact=Apollo EMAC\0" \
    "bootcmd=run nandboot\0" \
    "memsize=512M\0" \
    "recoverymode=0\0" \
    "gpuclock=187500k\0" \
    "logoaddr=800000\0" \
    "logosize=600000\0" \
    "recoveryboot=run recoveryargs; nand read ${loadaddr} 1000000 800000; bootm ${loadaddr}\0" \
    "recoveryargs=nand info;setenv bootargs mem=${memsize} recoverymode=${recoverymode} console=${console} board_ver=v2 logo=lvds1080p,loaded,osd1\0" \
    "nandboot=echo Booting from nand ...; run nandargs; nand read ${loadaddr} 1800000 400000; bootm ${loadaddr}\0" \
    "console=ttyS0,115200n8\0" \
    "cpuclock=600M\0" \
    "bootdelay=1\0" \
    "bootargs=mem=512M a9_clk=600M clk81=187500k mac=00:01:22:65:04:88 console=ttyS0,115200n8 board_ver=v2 logo=lvds1080p,loaded,osd1\0" \
    "nandargs=nand info;setenv bootargs mem=${memsize} a9_clk=${cpuclock} clk81=${gpuclock} quiet lpj=5980160 mac=${ethaddr} console=${console} board_ver=v2 logo=lvds1080p,loaded,osd1\0" \
    
#define CONFIG_BOOTCOMMAND \
    "run nandboot" \
    

#define CONFIG_AUTO_COMPLETE    1
/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_LONGHELP     /* undef to save memory */
#define CONFIG_SYS_HUSH_PARSER      /* use "hush" command parser */
#define CONFIG_SYS_PROMPT_HUSH_PS2  "> "
#define CONFIG_SYS_PROMPT       "M2_SOCKET# "
#define CONFIG_SYS_CBSIZE       256 /* Console I/O Buffer Size */
/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE       (CONFIG_SYS_CBSIZE + \
                    sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS      16  /* max number of command */
                        /* args */
/* Boot Argument Buffer Size */
#define CONFIG_SYS_BARGSIZE     (CONFIG_SYS_CBSIZE)

#define CONFIG_SYS_LOAD_ADDR    0
/*
 * clk , timer setting 
 */
#define CONFIG_SYS_HZ           1000
#define CONFIG_HARDWARE_FIN     24000000 // 24Mhz crystal .
/*-----------------------------------------------------------------------
 * Stack sizes
 *
 * The stack sizes are set up in start.S using the settings below
 */

#define CONFIG_STACKSIZE    (128 << 10) /* regular stack 128 KiB */
#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ    (4 << 10)   /* IRQ stack 4 KiB */
#define CONFIG_STACKSIZE_FIQ    (4 << 10)   /* FIQ stack 4 KiB */
#endif

/*-----------------------------------------------------------------------
 * Physical Memory Map
 */
    //#define DDR3_9_9_9
#define DDR3_7_7_7
    //above setting must be set for ddr_set __ddr_setting in file
    //board/amlogic/aml_tv_m2c_2pc_4l_refe09/firmware/timming.c 
    
    //note: please DO NOT remove following check code
#if !defined(DDR3_9_9_9) && !defined(DDR3_7_7_7)
	#error "Please set DDR3 property first in file aml_tv_m2c_2pc_4l_refe09.h\n"
#endif
    
    //#define M2C_DDR3_1GB
#define M2C_DDR3_512M
    //above setting will affect following:
    //board/amlogic/aml_tv_m2c_2pc_4l_refe09/firmware/timming.c
    //arch/arm/cpu/aml_meson/m2/mmutable.s
    
    //note: please DO NOT remove following check code
#if !defined(M2C_DDR3_1GB) && !defined(M2C_DDR3_512M)
	#error "Please set DDR3 capacity first in file aml_tv_m2c_2pc_4l_refe09.h\n"
#endif
    
#define CONFIG_NR_DRAM_BANKS    1   /* CS1 may or may not be populated */
#define PHYS_MEMORY_START    0x80000000 // from 500000
#if defined(M2C_DDR3_1GB)
	#define PHYS_MEMORY_SIZE     0x40000000 // 1GB
#elif defined(M2C_DDR3_512M)
	#define PHYS_MEMORY_SIZE     0x20000000 // 512M
#else
	#error "Please define DDR3 memory capacity in file aml_tv_m2c_2pc_4l_refe09.h\n"
#endif
#define CONFIG_SYS_MEMTEST_START    0x80000000  /* memtest works on */      
#define CONFIG_SYS_MEMTEST_END      0x07000000  /* 0 ... 120 MB in DRAM */  
//#define CONFIG_DDR_TYPE DDR_W972GG6JB
//#define CONFIG_DDR_TYPE DDR_K4T1G164QE
#define CONFIG_DDR_TYPE DDR_V59C1G02168QBP25A


#define DDR_TYPE_IDENTIFY  "ddr type: V59C1G02168QBP25A\n"

/* SDRAM Bank Allocation method */
#define SDRC_R_B_C      1

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */

/* **** PISMO SUPPORT *** */

/* Configure the PISMO */
#define PISMO1_NAND_SIZE        GPMC_SIZE_128M
#define PISMO1_ONEN_SIZE        GPMC_SIZE_128M

#define CONFIG_SYS_MAX_FLASH_SECT   520 /* max number of sectors */
                        /* on one chip */
#define CONFIG_SYS_MAX_FLASH_BANKS  2   /* max number of flash banks */
#define CONFIG_SYS_MONITOR_LEN      (256 << 10) /* Reserve 2 sectors */

#define CONFIG_SYS_FLASH_BASE       boot_flash_base

/* Monitor at start of flash */
//#define CONFIG_ENV_IS_NOWHERE 1
//#define CONFIG_SYS_MONITOR_BASE       CONFIG_SYS_FLASH_BASE
//#define CONFIG_SYS_ONENAND_BASE       ONENAND_MAP
//
//#define CONFIG_ENV_IS_IN_ONENAND  1
//#define ONENAND_ENV_OFFSET        0x260000 /* environment starts here */
//#define SMNAND_ENV_OFFSET     0x260000 /* environment starts here */
//
//#define CONFIG_SYS_ENV_SECT_SIZE  boot_flash_sec
//#define CONFIG_ENV_OFFSET     boot_flash_off
//#define CONFIG_ENV_ADDR           boot_flash_env_addr

#define CONFIG_SPI_BOOT 1
//#define CONFIG_NAND_BOOT 1

#ifdef CONFIG_SPI_BOOT
    #define CONFIG_ENV_OVERWRITE
    #define CONFIG_ENV_IS_IN_SPI_FLASH
    #define CONFIG_CMD_SAVEENV
    #define CONFIG_ENV_SIZE             0x2000
    #define CONFIG_ENV_SECT_SIZE        0x1000
	#define CONFIG_ENV_MAC_OFFSET        0x60000
#ifdef CONFIG_UCL
    #define CONFIG_ENV_OFFSET           0x3e000
#else
    #define CONFIG_ENV_OFFSET           0x1f0000
#endif
#elif defined CONFIG_NAND_BOOT
    #define CONFIG_ENV_IS_IN_AML_NAND
    #define CONFIG_CMD_SAVEENV
    #define CONFIG_ENV_OVERWRITE
    #define CONFIG_ENV_SIZE         0x2000
    #define CONFIG_ENV_OFFSET       0x3e000
    #define CONFIG_ENV_BLOCK_NUM    2
#else
#define CONFIG_SYS_ENV_IS_NOWHERE 1
#endif
/* Monitor at start of flash */


/*-----------------------------------------------------------------------
 * CFI FLASH driver setup
 */
/* timeout values are in ticks */
#define CONFIG_SYS_FLASH_ERASE_TOUT (100 * CONFIG_SYS_HZ)
#define CONFIG_SYS_FLASH_WRITE_TOUT (100 * CONFIG_SYS_HZ)

/* Flash banks JFFS2 should use */
#define CONFIG_SYS_MAX_MTD_BANKS    (CONFIG_SYS_MAX_FLASH_BANKS + \
                    CONFIG_SYS_MAX_NAND_DEVICE)
#define CONFIG_SYS_JFFS2_MEM_NAND
/* use flash_info[2] */
#define CONFIG_SYS_JFFS2_FIRST_BANK CONFIG_SYS_MAX_FLASH_BANKS
#define CONFIG_SYS_JFFS2_NUM_BANKS  1

#ifndef __ASSEMBLY__
extern unsigned int boot_flash_base;
extern volatile unsigned int boot_flash_env_addr;
extern unsigned int boot_flash_off;
extern unsigned int boot_flash_sec;
extern unsigned int boot_flash_type;
#endif

/*----------------------------------------------------------------------------
 * SMSC9115 Ethernet from SMSC9118 family
 *----------------------------------------------------------------------------
 */
#if defined(CONFIG_CMD_NET)

#define CONFIG_AML_ETHERNET
#define CONFIG_HOSTNAME             arm_m2_socket
#define CONFIG_ETHADDR              00:01:22:65:04:88   /* Ethernet address */
#define CONFIG_IPADDR               10.68.12.117             /* Our ip address */
#define CONFIG_GATEWAYIP            10.68.12.1          /* Our getway ip address */
#define CONFIG_SERVERIP             10.68.8.117        /* Tftp server ip address */
#define CONFIG_NETMASK              255.255.255.0
#endif /* (CONFIG_CMD_NET) */

/*
 * BOOTP fields
 */

#define CONFIG_BOOTP_SUBNETMASK     0x00000001
#define CONFIG_BOOTP_GATEWAY        0x00000002
#define CONFIG_BOOTP_HOSTNAME       0x00000004
#define CONFIG_BOOTP_BOOTPATH       0x00000010


#define CONFIG_LZO   1
#define CONFIG_LZMA  1
#define CONFIG_CACHE_L2X0 1
//#define CONFIG_SYS_NO_DCACHE 1
//#define CONFIG_SYS_NO_ICACHE 1
//#define CONFIG_MTD_DEBUG 1
//#define CONFIG_MTD_DEBUG_VERBOSE 0

#ifdef CONFIG_NAND_BOOT
#define CONFIG_AMLROM_NANDBOOT 1
#endif
#define CONFIG_ENABLE_ARMCC_DEBUGROM 1
#define CONFIG_PREBOOT "mw c1104238 51001;"
#endif /* __CONFIG_H */
