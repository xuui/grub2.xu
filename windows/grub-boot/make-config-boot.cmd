rem BIOS.
..\grub-bin\grub-mkimage.exe --config=config-boot.cfg --directory=..\grub-bin\i386-pc --format=i386-pc --output=grub-i386-pc.img --prefix=/efi/grub biosdisk part_msdos fat ntfs search_fs_file
..\grub-bin\grub-mkimage.exe --config=config-boot_label.cfg --directory=..\grub-bin\i386-pc --format=i386-pc --output=grub-i386-pc_label.img --prefix=/efi/grub biosdisk part_msdos fat ntfs search_label
copy /b ..\grub-bin\i386-pc\boot.img+grub-i386-pc.img grub.mbr
copy /b ..\grub-bin\i386-pc\boot.img+grub-i386-pc_label.img grub_label.mbr


rem UEFI.
..\grub-bin\grub-mkimage.exe --config=config-boot.cfg --directory=..\grub-bin\i386-efi --format=i386-efi --output=grub-i386.efi --prefix=/efi/grub part_gpt part_msdos disk fat exfat ext2 ntfs appleldr hfs hfsplus iso9660 normal search search_fs_file search_fs_uuid search_label reboot halt ls echo cat chain configfile help linux linux16 loadenv loadbios multiboot multiboot2 all_video video_bochs video_cirrus efi_gop efi_uga gfxterm gfxterm_background gfxterm_menu gfxmenu gettext font jpeg png
..\grub-bin\grub-mkimage.exe --config=config-boot.cfg --directory=..\grub-bin\x86_64-efi --format=x86_64-efi --output=grub-x86_64.efi --prefix=/efi/grub part_gpt part_msdos disk fat exfat ext2 ntfs appleldr hfs hfsplus iso9660 normal search search_fs_file search_fs_uuid search_label reboot halt ls echo cat chain configfile help linux linux16 loadenv loadbios multiboot multiboot2 all_video video_bochs video_cirrus efi_gop efi_uga gfxterm gfxterm_background gfxterm_menu gfxmenu gettext font jpeg png
..\grub-bin\grub-mkimage.exe --config=config-boot_label.cfg --directory=..\grub-bin\i386-efi --format=i386-efi --output=grub-i386_label.efi --prefix=/efi/grub part_gpt part_msdos disk fat exfat ext2 ntfs appleldr hfs hfsplus iso9660 normal search search_fs_file search_fs_uuid search_label reboot halt ls echo cat chain configfile help linux linux16 loadenv loadbios multiboot multiboot2 all_video video_bochs video_cirrus efi_gop efi_uga gfxterm gfxterm_background gfxterm_menu gfxmenu gettext font jpeg png
..\grub-bin\grub-mkimage.exe --config=config-boot_label.cfg --directory=..\grub-bin\x86_64-efi --format=x86_64-efi --output=grub-x86_64_label.efi --prefix=/efi/grub part_gpt part_msdos disk fat exfat ext2 ntfs appleldr hfs hfsplus iso9660 normal search search_fs_file search_fs_uuid search_label reboot halt ls echo cat chain configfile help linux linux16 loadenv loadbios multiboot multiboot2 all_video video_bochs video_cirrus efi_gop efi_uga gfxterm gfxterm_background gfxterm_menu gfxmenu gettext font jpeg png




rem [BIOS MODULES]

rem [ISO MODULES]
rem [biosdisk part_msdos fat ntfs iso9660 udf normal search_fs_file search_label]

rem [UEFI MODULES]
rem []


