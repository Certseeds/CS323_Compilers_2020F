# LAB 12 - Exploiting binaries on Linux

Install [pwndbg](https://github.com/pwndbg/pwndbg) GDB plugin for better debugging functionality.
```bash
git clone https://github.com/pwndbg/pwndbg
cd pwndbg
./setup.sh
```

On your working machine, install the [pwntools](https://github.com/Gallopsled/pwntools):
```bash
python3 -m pip install --upgrade pwntools
```

Two CTF challenges listen on:
+ `stack_hack`: 10.20.38.233:23454
+ `heap_hack`: 10.20.38.233:23455

**Note that the online-challenges will terminate after 5-seconds inactivation.**
