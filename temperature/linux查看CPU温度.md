### linux查看CPU温度

Linux内核中一般都带有CPU温度检测的驱动，与CPU相关的设备文件/sys、/proc中。

系统CPU温度对象的虚拟文件在/sys/devices/virtual/thermal/thermal_zone0中，我们该目录下的temp文件就可以得到CPU的温度。比如：
```shell
root@orangepir1plus-lts:~# cat /sys/devices/virtual/thermal/thermal_zone0/temp
52500
```

这里的52500代表的是52.500℃。
