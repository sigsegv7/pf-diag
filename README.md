# PFDIAG

## Example QEMU page fault log (from -d int)

```
check_exception old: 0xffffffff new 0xe
    92: v=0e e=0010 i=0 cpl=0 IP=0038:000000000ddee029
```

In this case, e=0010 (0x10). So run the program
like so:

``./pfdiag 0x10``
