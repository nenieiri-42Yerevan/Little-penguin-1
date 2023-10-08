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
  - If you want to record the "Hello world!\n" message to logs with the KERN_INFO option you need to change the console log level to 6 or smaller, to reach the above result (i.e. running ```insmod main.ko``` or ```rmmod main.ko``` without showing log message). For that, you need to do the following.

    The default loglevel is:
    ```sh
    % cat /proc/sys/kernel/printk
    7	4	1	7
    ```
    To change this behavior we need to run:
    ```sh
    sudo echo 'LOGLEVEL="6"' >> /etc/sysconfig/console
    ```
    Now, the result will be:
    ```sh
    % cat /proc/sys/kernel/printk
    6	4	1	7
    ```
