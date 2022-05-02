# low-level-hooker
Hook linux kernel functions without using ftrace or kprobe.<br/>
**Note**: It's a learning project developed in two day. Things may not work properly in your environment.

## Usage

* Open `call_hooker.c`
* Define you hooked funtion prototype and required code inside it in similar way done for `hookers_piston` which is hook for `add_num`.
* Change the mentioned three line in `my_init()` according to your target and hook funtion.
* `test_export.c` contain example funtion `add_num()` which the current setup is hooking. `test_caller.c` is module that is calling `add_num()`.
* Compile the all the module using `make`
* Import `test_export.ko` then our hooking module `call_hooker.ko` then `test_caller.ko` to see results. Importing command - `insmod module_name`

### Testing
Tested on Debian Stretch
