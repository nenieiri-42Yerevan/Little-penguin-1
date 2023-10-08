# Little penguin 1
#### This projet, the 2nd project in the Kernel specialization of 42 school, is a series of challenges inspired by [Eudyptula](http://eudyptula-challenge.org/).

## Assignements
### ex00:
**Instructions**:
  - Download Linus' latest git tree from git.kernel.org, build, compile and boot it.
  - Enable CONFIG_LOCALVERSION_AUTO=y

----------

### ex01:
**Instructions**:
  - Build a "Hello World module" that outputs specific messages on load and unload.
    ```sh
    % sudo insmod main.ko
    % dmesg | tail -1
    [Wed May 13 12:59:18 2015] Hello world !
    % sudo rmmod main.ko
    % dmesg | tail -1
    [Wed May 13 12:59:24 2015] Cleaning up module.
    %
    ```
  - It must compile on any system

**Notes**:
  - If you want to record the "Hello world!\n" message to logs with the KERN_INFO option you need to decrease the console log level to 6 or smaller, to reach the above result (i.e. running ```insmod main.ko``` or ```rmmod main.ko``` without showing log message). For that, you need to do the following.

    The default console log level when the computer is rebooted or is turning on is always reset to this:
    ```sh
    % cat /proc/sys/kernel/printk
    7	4	1	7
    ```
    Where the first number is **Console log level**, 2 - **Default log level**, 3 - **Minimum log level**, 4 - **Boot-time default log level**.

    To change **Console log level** permanently we need to run:
    ```sh
    sudo echo 'LOGLEVEL="6"' >> /etc/sysconfig/console
    ```
    Now, the result always will be:
    ```sh
    % cat /proc/sys/kernel/printk
    6	4	1	7
    ```
    Alternatively for this method, you can increase the "Hello world !" message's log level from **KERN_INFO** to **KERN_DEBUG**. But I think the message is informative in nature and it is not a debugging message so this is not the preferred version.

    In ```/usr/src/<your_kernel_version>/include/linux/kern_levels.h``` file you can see the log levels and their descriptions:
    ```sh
    #define KERN_EMERG      "0"    // system is unusable
    #define KERN_ALERT      "1"    // action must be taken immediately
    #define KERN_CRIT       "2"    // critical conditions
    #define KERN_ERR        "3"    // error conditions
    #define KERN_WARNING    "4"    // warning conditions
    #define KERN_NOTICE     "5"    // normal but significant condition
    #define KERN_INFO       "6"    // informational
    #define KERN_DEBUG      "7"    // debug-level messages
    ```
  - The ```dmesg``` command prints the logs prefixed by a raw timestamp. Like this:
    ```sh
    % dmesg | tail -1
    [ 2523.841538 ] Hello world !
    ```
    Despite the goal here is to write a basic driver that is able to write a message, we can fake dmesg by modifying the ```.bashrc``` file and adding this line to achieve the desired results:
    ```sh
    alias dmesg="dmesg -T --color=always"
    ```
    Now, the result will be (thanks to the -T option):
    ```sh
    % dmesg | tail -1
    [Wed May 13 12:59:18 2023] Hello world !
    ```
  - ```__init``` and ```__exit``` keywords (from the ```<linux/init.h>```) put the functions in a specific section of the module binary. This section is unloaded after module initialization, in order to not waste RAM. It is not mandatory but it is a good practice for sure.
