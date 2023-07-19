## Openwrt rootfs源码目录结构

rootfs目录结构
Openwrt的系统目录结构遵循FHS（filesystem Hierarchy Standard 文件系统层次结构标准），很多linux系统发行版本也遵循这个标准。

openwrt 目录有重要性排序、并且跟他的挂载顺序对应

系统包括 bin、sbin、dev、proc、sys、tmp、usr七个重要的目录

bin、sbin 都是放置的二进制执行文件
bin目录主要放置一些系统必备执行程序
sbin目录放置的是超级用户指令、主要放置一些系统管理的必备程序，当前目录下的指令只有管理员才能使用。

按照重要程度排序 bin>sbin>xx_/bin>xx_sbin

其中/proc /sys目录是系统内核创建的，里面包括许多系统内核配置，运行中的进程的pid等等、其实/sys跟 /proc都是都是起的一样的作用，/sys目录是新的标准，为了兼容性原因保留了/proc目录。

/dev 目录也是内核创建的，包括了一些硬件信息，例如插入usb、ttl、硬盘这些设备都会在/dev上创建一个对应的文件，挂载磁盘的source也是用的/dev目录下的对应文件。 有个现象是、在这么多内核创建的目录中只有这个目录包含大些的名称。

/usr 用户的目录相对来说不是那么重要的目录，挂载顺序靠后，放置的文件比较杂乱

/tmp 是一个临时文件目录，是挂载到内存中的，读写速度快，程序运行中产生的临时文件很多可能都选择放到这里，没有这个目录可能会导致程序出错。

/var variable的缩写，变量的意思。放置的是零时文件/例如变量、系统日志、pid等、也可以是程序根据uci生成的配置文件。

/lib library的缩写，库

/mnt 是mount point 的缩写，名为挂载点。外置硬盘一般都会挂载到这个目录。

以上只是FHS的标准，并不是强制要求，并不是所有程序都会遵循这个标准。

源码目录结构

源码分为 config、packages、script、include、toolchain、tools、target、
这些目录都是编译前的目录

package : 放置软件包源码，makefile文件
toolchain： 用于防治交叉工具链的源码和Makefile文件
target: 放置跟平台相关的代码、新设备的适配、gpio的开发就会修改这个目录的文件
tools： 用于放置用于开发和构建openwrt的工具、包括一些常用的linux命令、xz、make、zip、sed等
toolchain： 用于放置交叉工具链的源码和Makefile文件

在执行./scripts/feeds update -a之后会生成 feeds目录，并下载。/feeds.default.conf中配置的仓库
执行./scripts/feeds install -a之后 软件包才会在make menuconifg的菜单中看到。

编译过程
在开始编译时，系统会优先下载编译所需的文件存放到 ./dl目录

然后开始编译工具所需的工具、以及交叉工具链存放到/staging_dir目录

然后开始编译系统内核、软件包等 存放到/build_dir目录

最后将编译好的软件包和打包好的固件存放到/bin目录
