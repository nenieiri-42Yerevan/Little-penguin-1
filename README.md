# Little penguin 1
#### This project is the 2nd project in the Kernel specialization of 42 School. It is a series of challenges inspired by [Eudyptula](http://eudyptula-challenge.org/).

## Assignements
  - [ex00](#ex00)
  - [ex01](#ex01)
  - [ex02](#ex02)
  - [ex03](#ex03)
  - [ex04](#ex04)
  - [ex05](#ex05)
  - [ex06](#ex06)
  - [ex07](#ex07)
  - [ex08](#ex08)
  - [ex09](#ex09)
  - [Useful links](#useful-links)

----------

### ex00:
**Instructions**:
  - Download Linus' latest git tree from git.kernel.org, build, compile and boot it.
  - Enable CONFIG_LOCALVERSION_AUTO=y
  
**Notes**:
  - ```CONFIG_LOCALVERSION``` and ```CONFIG_LOCALVERSION_AUTO``` in the ```.config``` file and ```EXTRAVERSION``` in the ```Makefile``` are used to specify version information for the kernel.
  - With the ```CONFIG_LOCALVERSION``` option, you can set a custom string that will be appended to the kernel version (like the ```EXTRAVERSION``` in the ```Makefile```), allowing you to identify custom builds.
  - You can find the ```CONFIG_LOCALVERSION_AUTO``` option in the menuconfig through this path:
    ```
    General setup  --->
      [ ] Automatically append version information to the version string
    ```
  - For ```CONFIG_LOCALVERSION_AUTO=y``` to work properly the kernel directory must contain the ```.git``` folder.
  - After the build and boot of the kernel with new configs you can see the ```CONFIG_LOCALVERSION_AUTO=y``` result with the ```uname -r``` command or in the first lines in ```/var/log/kern.log``` file (which we need to include to our repo as the task requires).

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

**Useful commands**:
```sh
insmod main.ko
```
```sh
lsmod
```
```sh
modinfo main.ko
```
```sh
rmmod main.ko
```
```sh
dmesg
dmesg -T
dmesg --color=always
dmesg | tail -1
```

----------

### ex02:
**Instructions**:
  - Take the same kernel git tree as in ex00 and modify it to have -thor_kernel in the version string
  - Make a patch for the change, it has to be compliant with Linux standards

**Notes**:
  - [Documentation](https://docs.kernel.org/process/submitting-patches.html)
  - You can check your patches with the patch style checker: ```scripts/checkpatch.pl```.
  - [How to Patch Linux Kernel](https://www.youtube.com/watch?v=okIVM66euT4)
  - [Best Practices to Getting Your Patches Accepted](https://www.youtube.com/watch?v=wjAJ50GqCP4)
  - See also ```man patch```

----------

### ex03:
**Instructions**:
  -  Take a given file and modify it to match the Linux coding style.

**Notes**
  - [Linux coding style](https://docs.kernel.org/process/coding-style.html)
  - For checking coding style use this command:
    ```sh
    /usr/src/<kernel>/scripts/checkpatch.pl main.c -no-tree -file --strict
    ```

----------

### ex04:
**Instructions**:
  - Take the kernel module written for [ex01](ex01/) and modify it so that when any USB keyboard is plugged in, the module will be automatically loaded
  - Write a rules file for hotplug userspace tools, if needed.

**Notes**
  - [Linux Device Drivers, 3rd edition (chapter 14)](https://static.lwn.net/images/pdf/LDD3/ch14.pdf)
  - Udev is a device manager that dynamically manages device nodes in the /dev/ directory. The ```/etc/udev/rules.d/``` directory is where you can define custom rules for udev to follow.

     A brief explanation of what you can do with this directory:
     - Device Naming: You can create rules that specify the names of device nodes. For example, you can set a specific name for a particular USB device or network interface.
     - Permissions: You can use udev rules to set the permissions on device nodes. This allows you to control which users or groups have access to a device.
     - Triggering Actions: Udev rules can be used to trigger certain actions when a specific device is connected or disconnected. For instance, you can run a script or a program when a particular USB device is plugged in.
     - Attributes and Labels: You can use rules to set or modify device attributes and labels. This is useful for making devices easily identifiable.

----------

### ex05:
**Instructions**:
  - Take the kernel module written for [ex01](ex01/) and modify it to be a misc char device driver.
  - The misc device should be created with a dynamic minor number.
  - The misc device node should show up in /dev/fortytwo.
  - The misc device should be registered when the module is loaded, and unregistered when it is unloaded.
  - Make it behave specifically on reads and writes.

**Notes**
  - [Major and Minor numbers](https://embetronicx.com/tutorials/linux/device-drivers/character-device-driver-major-number-and-minor-number/)
  - [Creating Device File](https://embetronicx.com/tutorials/linux/device-drivers/device-file-creation-for-character-drivers/)
  - [File Operations](https://embetronicx.com/tutorials/linux/device-drivers/cdev-structure-and-file-operations-of-character-drivers/)
  - [Real Device Driver](https://embetronicx.com/tutorials/linux/device-drivers/linux-device-driver-tutorial-programming/)
  - [Misc Device Driver](https://embetronicx.com/tutorials/linux/device-drivers/misc-device-driver/)
  - For testing, you can use the ```test.c``` file or these commands:
    - ```cat < /dev/fortytwo```
    - ```echo -n vismaily > /dev/fortytwo```

----------

### ex06:
**Instructions**:
  - Download the linux-next kernel, build it, compile it, and boot it.

**Notes**
  - [Linux-next](https://git.kernel.org/pub/scm/linux/kernel/git/next/linux-next.git/)

----------

### ex07:
**Instructions**:
  - Write a kernel module that uses debugfs.
  - You have to create a subdirectory in which you can find 3 special files handled by your driver.
  - They all must have specific access rights and behavior.

**Notes**
  - To create a directory in /sys/kernel/debug we first need to mount debugfs using this command:
    ```sh
    mount -t debugfs none /sys/kernel/debug/
    ```
  - [Kernel documentation about debugfs](https://docs.kernel.org/filesystems/debugfs.html)
  - [Jiffies](https://litux.nl/mirror/kerneldevelopment/0672327201/ch10lev1sec3.html)
  - [Mutex](https://embetronicx.com/tutorials/linux/device-drivers/linux-device-driver-tutorial-mutex-in-linux-kernel/)

----------

### ex08:
**Instructions**:
  - Take a given file, fix the coding style, and fix the code's behavior.

**Notes**
  - [Linux coding style](https://www.kernel.org/doc/html/v4.10/process/coding-style.html)
  - For checking coding style use this command:
    ```sh
    /usr/src/<kernel>/scripts/checkpatch.pl main.c -no-tree -file --strict
    ```

----------

### ex09:
**Instructions**:
  - Write a kernel module that exposes a file called mymounts on the root of the procfs.
  - It has to list mount points on the system and their associated names.

**Notes**
  - [Procfs](https://embetronicx.com/tutorials/linux/device-drivers/procfs-in-linux/)
  - [Linked lists in the kernel](https://www.oreilly.com/library/view/linux-device-drivers/0596000081/ch10s05.html)
  - [Linked lists in the kernel (Tutorial 1)](https://embetronicx.com/tutorials/linux/device-drivers/linux-device-driver-tutorial-part-17-linked-list-in-linux-kernel/)
  - [Linked lists in the kernel (Tutorial 2)](https://embetronicx.com/tutorials/linux/device-drivers/example-linked-list-in-linux-kernel/)
  - [Linked lists in the kernel (detailed implementation)](https://kernelnewbies.org/FAQ/LinkedLists)
  - [list_for_each_entry](https://stackoverflow.com/questions/16230524/explain-list-for-each-entry-and-list-for-each-entry-safe)
  - [Mounts](https://www.oreilly.com/library/view/understanding-the-linux/0596002130/ch12s04.html)
  - [Documentation of seq_file](https://www.kernel.org/doc/html/latest/filesystems/seq_file.html)

----------

## Useful links
[__1) Coding style__](https://www.kernel.org/doc/html/v4.10/process/coding-style.html) <br>
[__2) printk__](https://www.kernel.org/doc/html/next/core-api/printk-basics.html) <br>
[__3) Linux Device Drivers, 3rd edition (chapter 14)__](https://static.lwn.net/images/pdf/LDD3/ch14.pdf) <br>
[__4) Linux Device Driver Tutorials__](https://embetronicx.com/linux-device-driver-tutorials/) <br>
[__5) The Linux Kernel documentation__](https://docs.kernel.org/index.html) <br>
[__6) Building External Modules (documentation)__](https://docs.kernel.org/kbuild/modules.html) <br>
