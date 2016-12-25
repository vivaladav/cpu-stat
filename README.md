# cpu-stat
a simple program for visualizing CPU statitics on Linux systems.


## Usage

**Print options**

| flag | description | default |
| ---- | ------------| ------- |
| -a \| --all | print active time percentage for all CPUs, starting with total | - |
| -c \<cpu\> | print stats only for selected CPU. | - |
| -f \| --full-state | print time percentage of all states | - |
| -p \<precision\> | set the decimal precision of printed numbers  | 2 |
|  -s \<state\> |  print time percentage for specific state [0-9]  | - |
| -v \| --verbose | enable verbose mode | - |

**Other options**

| flag | description | default |
| ---- | ------------| ------- |
| -d \<time\> | set delay time (in ms) between 2 snapshots of CPU data  | 100 |
| -h \| --help  | print help  | - |
| --version |  print the version number  | - |

## Examples

Print percentage of active time for total CPU:
```
$ cpu-stat
2.50
```

Print percentage of idle time (state 3) for CPU 2 wiht 4 digits as decimal precision:
```
$ cpu-stat -s 3 -c 2 -p 4
100.0000
```

Print percentage of active time for all CPUs in verboses mode (with labels):
```
$ cpu-stat -a -v
tot] 5.00%
  0] 0.00%
  1] 0.00%
  2] 20.00%
  3] 0.00%
```

Print perentage of all states for all CPUs in verbose mode (with labels):
```
$ cpu-stat -a -v -f
tot] usr:   0.00% | sys:   0.00% | nic:   0.00% | idl: 100.00% | iow:   0.00% | hir:   0.00% | sir:   0.00% | ste:   0.00% | gue:   0.00% | gun:   0.00% | 
  0] usr:   0.00% | sys:   0.00% | nic:   0.00% | idl: 100.00% | iow:   0.00% | hir:   0.00% | sir:   0.00% | ste:   0.00% | gue:   0.00% | gun:   0.00% | 
  1] usr:   0.00% | sys:   0.00% | nic:   0.00% | idl: 100.00% | iow:   0.00% | hir:   0.00% | sir:   0.00% | ste:   0.00% | gue:   0.00% | gun:   0.00% | 
  2] usr:   0.00% | sys:   0.00% | nic:   0.00% | idl: 100.00% | iow:   0.00% | hir:   0.00% | sir:   0.00% | ste:   0.00% | gue:   0.00% | gun:   0.00% | 
  3] usr:   0.00% | sys:   0.00% | nic:   0.00% | idl:  90.91% | iow:   9.09% | hir:   0.00% | sir:   0.00% | ste:   0.00% | gue:   0.00% | gun:   0.00% |
```
