### openwrt插件安装


#### 方法一：
如果路由器是 Openwrt的Release版，可以直接通过命令行，如下安装：
```shell
#opkg  update
#opkg  install    xxx.ipk
#opkg  install  lrzsz      #举例,  安装lrzsz包
```

#### 方法二：
如果路由器不是Release版，往往上面命令执行失败。此时，需要自行下载 xxx.ipk包，上传到 路由器的/tmp目录，在进行安装。

1. 首先，确定路由器的体系结构， 输入如下命令：
```shell
root@OpenWrt:/tmp# opkg print-architecture
arch all 1
arch noarch 1
arch mipsel_24kc 10
```
上述为mt7621路由器上执行的结果， 体系结构为： mipsel_24kc

2. 确定下载的软件包分支。 有  18.06分支， 19.07分支， 21.02分支，和 master即snapshot分支。
以腾讯镜像为例，  base包的位置如下：
```text
master snapshot:
https://mirrors.cloud.tencent.com/openwrt/snapshots/packages/mipsel_24kc/base/


Openwrt-21.02:
https://mirrors.cloud.tencent.com/openwrt/releases/21.02.0-rc4/packages/mipsel_24kc/base/


Openwrt-19.07:
https://mirrors.cloud.tencent.com/openwrt/releases/19.07.8/packages/mipsel_24kc/base/


Openwrt-18.06:
https://mirrors.cloud.tencent.com/openwrt/releases/18.06.9/packages/mipsel_24kc/base/
```

这些base目录的上一级目录下，还有luci/packages/routing目录等，里面也有相应的xxx.ipk插件，请自行查看。
更老的版本，类似去找：
```text
https://mirrors.cloud.tencent.com/openwrt/
```

3. 安装示例
我们以安装tcpdump软件包为例，假定我们的路由器的Openwrt版本固件为snapshot分支， MT7621系统结构。
到snapshot的base下面，下载2个软件包： (经过尝试)

libpcap1_xxx.ipk
tcpdump_xxx.ipk

上传这2个软件包到路由器的/tmp目录下面(使用winscp上传，或者rz命令-需要lrzsz包)， 安装即可：
```shell
root@OpenWrt:/tmp# opkg install libpcap1_1.10.1-1_mipsel_24kc.ipk 
Package libpcap1 (1.10.1-1) installed in root is up to date.
root@OpenWrt:/tmp# opkg install tcpdump_4.9.3-3_mipsel_24kc\ \(1\).ipk 
Package tcpdump (4.9.3-3) installed in root is up to date.
root@OpenWrt:/tmp# 
```

#### 总结
这种方法，通常只能适用于软件包不是内核的情况。如果缺少内核包，例如 ：  kmod_xxx.ipk等，
这种情况一般需要固件把内核模块先编译进内核才行。然后就可以根据需要安装各种不同应用的ipk包了~
