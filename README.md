# Make Grub.

文档环境基于 Ubuntu 20.04   
官方源码地址：git clone https://git.savannah.gnu.org/git/grub.git

## 编译
安装编译所需要的支持库
```
sudo apt install -y \
 build-essential g++-multilib g++-9-multilib gcc-multilib gcc-9-multilib gcc-9-locales gnu-standards lib32stdc++6-9-dbg libx32stdc++6-9-dbg \
 make gettext automake autogen automake autoconf autoconf-archive autopoint autotools-dev libtool m4 flex bison binutils pkg-config \
 libdevmapper-dev libpciaccess-dev libpciaccess0 libusb-dev libfreetype-dev libfreetype6-dev libsdl2-dev \
 unifont ttf-unifont unifont-bin xorriso
 python qemu qemu-system-x86 \
gfxboot gfxboot-dev libzfs2linux libzfslinux-dev liblzma5 liblzma-dev libefiboot1 fuse libfuse-dev fonts-dejavu ttf-dejavu \
libpth20 libpth-dev libintl-perl libintl-xs-perl libiconv-hook-dev libiconv-hook1 \
linux-libc-dev libgusb-dev libltdl-dev libgcrypt20 libgcrypt20-dev \

```

执行下面命令生成编译配置
```
./linguas.sh
./bootstrap
```

比如我的用户目录为 /home/xu ，就可以直接使用下面的命令，如果不是那就自己更改路径后执行。


编译 BIOS 启动：
```
./configure --target=i386 --with-platform=pc \
--prefix=/home/xu/grub2-bin --bindir=/home/xu/grub2-bin --sbindir=/home/xu/grub2-bin --libdir=/home/xu/grub2-bin \
--sysconfdir=/home/xu/grub2-bin/etc --localstatedir=/home/xu/grub2-bin/var --datarootdir=/home/xu/grub2-bin/share \
--enable-largefile=yes --enable-liblzma=yes
make && make install && make clean
```

编译 UEFI 32bit 启动：
```
./configure --target=i386 --with-platform=efi \
--prefix=/home/xu/grub2-bin --bindir=/home/xu/grub2-bin --sbindir=/home/xu/grub2-bin --libdir=/home/xu/grub2-bin \
--sysconfdir=/home/xu/grub2-bin/etc --localstatedir=/home/xu/grub2-bin/var --datarootdir=/home/xu/grub2-bin/share \
--enable-largefile=yes --enable-liblzma=yes
make && make install && make clean
```

编译 UEFI 64bit 启动：
```
./configure --target=x86_64 --with-platform=efi \
--prefix=/home/xu/grub2-bin --bindir=/home/xu/grub2-bin --sbindir=/home/xu/grub2-bin --libdir=/home/xu/grub2-bin \
--sysconfdir=/home/xu/grub2-bin/etc --localstatedir=/home/xu/grub2-bin/var --datarootdir=/home/xu/grub2-bin/share \
--enable-largefile=yes --enable-liblzma=yes
make && make install && make clean
```

multiboot
pv-grub-menu

```
./configure --target=ia64 --with-platform=efi \
--prefix=/home/xu/grub2-bin --bindir=/home/xu/grub2-bin --sbindir=/home/xu/grub2-bin --libdir=/home/xu/grub2-bin \
--sysconfdir=/home/xu/grub2-bin/etc --localstatedir=/home/xu/grub2-bin/var --datarootdir=/home/xu/grub2-bin/share \
--enable-largefile=yes --enable-liblzma=yes
make && make install && make clean
```

## 生成引导文件

生成引导文件需要使用编译好的 grub-mkimage 这个命令行工具。

如果要定制 grub 的文件位置，那么用一下面内容保存为 config_boot.cfg 文件作为默认菜单来嵌入启动文件。并自行修改本章节的路径，如：/boot/grub。

以搜索 /boot/grub/grub.cfg 文件为引导识别
```
search.file /boot/grub/grub.cfg root
set prefix=/boot/grub
```

如果想用磁盘标签做引导识别请把 search.file 改为 search.fs_label ，然后下面的 search_fs_file 模块替换成 search_label
```
search.fs_label /boot/grub/grub.cfg root
set prefix=/boot/grub
```

用磁盘的 UUID 作为引导识别
```
search.fs_uuid XXXX-XXXX root
set prefix=/boot/grub
```

把下面的 search_fs_file 模块替换成 search_label 。只是这样做了后不能随便格式化磁盘了。


### 制作引导文件

由于 MBR 分区的限制引导区只有63个扇区。BIOS 启动文件的大小只能限制在32k 以内，否则文件过大就会引导失败。   
而UEFI 则没有这个文件大小限制。一般按需要定制模块到文件里面。也可以把所有模块都包含进来。

BIOS：
```
./grub-mkimage --compression=xz \
 --format=i386-pc \
 --config=../config/boot_compile.cfg \
 --directory=./i386-pc \
 --output=../grub-i386-pc.img \
 --prefix=/boot/grub \
 biosdisk part_msdos fat ntfs search_fs_file
copy /b boot.img+grub-i386-pc.img grub.mbr
```

UEFI 32bit：
```
./grub-mkimage --compression=xz \
 --format=i386-efi \
 --config=../config/efi_compile.cfg \
 --directory=./i386-efi \
 --output=../grubia32.efi \
 --prefix=/efi/grub \
 part_gpt part_msdos disk fat ntfs xfs appleldr hfs iso9660 normal search_fs_file search_fs_uuid search_label configfile linux linux16 chain loopback echo efi_gop efi_uga video_bochs video_cirrus file gfxmenu gfxterm gfxterm_background gfxterm_menu halt reboot help jpeg ls png true
copy grubia32.efi bootia32.efi
```

UEFI 64bit：
```
./grub-mkimage --compression=xz \
 --format=x86_64-efi \
 --config=../config/efi_compile.cfg \
 --directory=./x86_64-efi \
 --output=../grubx64.efi \
 --prefix=/efi/grub \
 part_gpt part_msdos disk fat ntfs xfs appleldr hfs iso9660 normal search_fs_file search_fs_uuid search_label configfile linux linux16 chain loopback echo efi_gop efi_uga video_bochs video_cirrus file gfxmenu gfxterm gfxterm_background gfxterm_menu halt reboot help jpeg ls png true
copy grubx64.efi bootx64.efi
```

### 扩展 core.img
UEFI 32bit：
```
./grub-mkimage.exe --config=config_boot.cfg --directory=grub/i386-efi --format=i386-efi --output=../grub-i386.efi --prefix=/boot/grub part_gpt part_msdos disk fat exfat ext2 ntfs appleldr hfs hfsplus iso9660 normal search search_fs_file search_fs_uuid search_label reboot halt ls echo cat chain configfile help linux linux16 loadenv loadbios multiboot multiboot2 all_video video_bochs video_cirrus efi_gop efi_uga gfxterm gfxterm_background gfxterm_menu gfxmenu gettext font jpeg png

```

UEFI 64bit：
```
./grub-mkimage.exe --config=config_boot.cfg --directory=grub/x86_64-efi --format=x86_64-efi --output=../grub-x86_64.efi --prefix=/boot/grub part_gpt part_msdos disk fat exfat ext2 ntfs appleldr hfs hfsplus iso9660 normal search search_fs_file search_fs_uuid search_label reboot halt ls echo cat chain configfile help linux linux16 loadenv loadbios multiboot multiboot2 all_video video_bochs video_cirrus efi_gop efi_uga gfxterm gfxterm_background gfxterm_menu gfxmenu gettext font jpeg png

```
