#include "utils.h"
#include "hwinit.h"
#include "lib/printk.h"
#include "display/video_fb.h"

#include "fuse.h"
#include "hwinit/btn.h"


void puts_nl(const char *s)
{
  printk("%s\n", s);
}

static void reset_using_pmc()
{
    volatile uint32_t *reset;

    reset = (uint32_t *)0x7000e400;
    *reset |= (1 << 4);
}

int main(void) {
    u32 *lfb_base;

    nx_hwinit();
    display_init();

    // Set up the display, and register it as a printk provider.
    lfb_base = display_init_framebuffer();
    video_init(lfb_base);


    puts_nl("                                        +   /\\ ");
    puts_nl("                           +              .'  '.   *");
    puts_nl("                                  *      /======\\      +");
    puts_nl("                                        ;:.  _   ;");
    puts_nl("                                        |:. (_)  |");
    puts_nl("                                        |:.  _   |");
    puts_nl("                              +         |:. (_)  |          *");
    puts_nl("                                        ;:.      ;");
    puts_nl("                                      .' \\:.    / `.");
    puts_nl("                                     / .-'':._.'`-. \\ ");
    puts_nl("                                     |/    /||\\    \\|");
    puts_nl("                                   _..--\"\"\"````\"\"\"--.._");
    puts_nl("                             _.-'``                    ``'-._");
    puts_nl("                           -'                                '-");
    puts_nl("                    __      __                 _ _       _              _ ");
    puts_nl("                   / /      \\ \\               (_) |     | |            | |");
    puts_nl("                  | |_ __ ___| |  _____      ___| |_ ___| |__   ___  __| |");
    puts_nl("                 / /| '__/ _ \\\\ \\/ __\\ \\ /\\ / / | __/ __| '_ \\ / _ \\/ _` |");
    puts_nl("                 \\ \\| | |  __// /\\__ \\\\ V  V /| | || (__| | | |  __/ (_| |");
    puts_nl("                  | |_|  \\___| | |___/ \\_/\\_/ |_|\\__\\___|_| |_|\\___|\\__,_|");
    puts_nl("                   \\_\\      /_/                                           ");
    puts_nl(" + GRAnimated for editing the payload!");

    // Say hello.
    printk("\n\n\n");
    printk(" If you are seeing this,\n");
    printk(" You have successfully started the exploit!\n\n");

    // Read the fuses.


    // Print the fuses.
    printk(" This unit's SBK/DK is: %08x%08x%08x%08x / %08x!\n\n",
        FUSE_CHIP_REGS->FUSE_PRIVATE_KEY[0],
        FUSE_CHIP_REGS->FUSE_PRIVATE_KEY[1],
        FUSE_CHIP_REGS->FUSE_PRIVATE_KEY[2],
        FUSE_CHIP_REGS->FUSE_PRIVATE_KEY[3],
        FUSE_CHIP_REGS->FUSE_DEVICE_KEY
        );

    printk(" This unit's bootrom patch version is: %01x!\n\n",
        FUSE_CHIP_REGS->FUSE_SOC_SPEEDO_1
        );

    printk(" This unit's burned fuse number is: %01x!\n\n",
        FUSE_CHIP_REGS->FUSE_RESERVED_ODM[7]
        );

    printk(" This unit's configuration is: %01x!\n\n",
        FUSE_CHIP_REGS->FUSE_RESERVED_ODM[4]
        );

    printk(" This SW config is: %08x!\n\n",
        FUSE_CHIP_REGS->FUSE_RESERVED_SW
        );

    if (retail_type == 4) { /* Standard retail unit, IS_RETAIL | 0. */
        printk(" This unit is a retail unit.\n\n");
    } else if (retail_type == 3) { /* Standard dev unit, 0 | DEV_UNIT. */
        printk(" This unit is a dev unit.\n\n");
    }

    // credits
    printk(" vulnerability discovered & responsibly reported by @ktemkin\n");
    printk(" Kate Temkin -- k@ktemkin.com\n");
    printk(" script edited by @granimated\n");
    printk(" GRAnimated -- https://youtube.com/granimated\n");

    // Wait for the power button, and then reset.
    while(btn_read() != BTN_POWER);

    // Reset.
    reset_using_pmc();

    /* Do nothing for now */
    return 0;
}
