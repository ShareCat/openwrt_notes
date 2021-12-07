### Ext4 vs SquashFS

```text
https://openwrt.org/docs/techref/filesystems
http://www.linux-mag.com/id/7357/
https://en.wikipedia.org/wiki/Ext4
```

The main difference is that you must used a compressed file system on most embedded devices, because they do not have enough space to hold the file system uncompressed.

#### SquashFS
SquashFS is a read only compressed filesystem. While gzip is available, at OpenWrt it uses LZMA for the compression. Since SquashFS is a read only filesystem, it doesn't need to align the data, allowing it to pack the files tighter thus taking up significantly less space than JFFS2 (20-30% savings over a JFFS2 filesystem)!

(+) taking up as little space as possible
(+) allowing the implementation of an idiot proof FailSafe for recovery, since it is not possible to write to it
(-) read only
(-) waste space, since each time a file contained on it is modified, actually a copy of it is being copied to the second (JFFS2) partition
Kernel documentation on SquashFS
SquashFs Performance Comparisons
There is a generic problem when running SquashFS on NAND: The issue is that SquashFS has no bad block management at all and requires all blocks on order; but for proper NAND bad block management you also need to be able to skip bad blocks and occasionally relocate blocks (see squashfs and NAND flash). That's why raw SquashFS is a bad idea on NAND (it works if you use a FTL like UBIFS).

#### ext2
Ext2/3/4 is used on x86, x86-64 and for some arch with SD-card rootfs
Kernel documentation on ext2
(+) a program (opkg in particularly) knows how much space is left!
(+) good ol' veteran FOSS file system
(-) no journaling
(-) no wear leveling
(-) no transparent compression

#### OverlayFS
Used to merge two filesystems, one read-only and the other writable. flash.layout explains how this is used in OpenWrt.

Overlayfs documentation
https://dev.openwrt.org/browser/trunk/target/linux/generic/patches-2.6.38/209-overlayfs.patch?rev=26213
Debating overlayfs on LWN.net
Was mainlined in Linux kernel 3.18
Overlayfs's support for inotify mechanisms is not complete yet. Events like IN_CLOSE_WRITE cannot be notified to listening process.

#### tmpfs
Kernel documentation on tmpfs
/tmp resides on a tmpfs-partition and /var is a symlink to it; /dev resides on a little tmpfs partition of its own
(+) no wear leveling
(-) volatile (doesn't survive a reboot)

#### JFFS2
JFFS2 is a writable compressed filesystem with journaling and wear leveling using LZMA for the compression.

(+) is writable, has journaling and wear leveling
(+) is cool
(-) is compressed, so a program (opkg in particular) cannot know in advance how much space a package will occupy
(+) is compressed, so a program (which is preinstalled) takes much less space, so effectively you have more space
It was replaced with UBIFS.

#### UBIFS
UBIFS is a file system for raw flash. It is used in OpenWrt NAND targets since :FIXME: around r40364
Kernel documentation on UBIFS
UBIFS File Encryption how does UBIFS understand what a “file” is? Isn't a file
UBIFS File Encryption v1 on LWN.net
UBIFS File Encryption v2 on LWN.net
UBIFS Supports OverlayFS In Linux 4.9, Readying UBI For MLC Support

#### Other filesystems
OpenWrt does not use other filesystems as rootfs. It supports several filesystems attached to via various mechanisms like USB, SATA or network. For a list see storage.