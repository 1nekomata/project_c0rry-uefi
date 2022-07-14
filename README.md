# c0rry-uefi

## What is this?
A UEFI Bootloader that was born from [project_c0rry](https://github.com/1nekomata/project_c0rry),
as I started to dislike developing a bootloader in BIOS and for now shifted my attention to UEFI.
Also this will probably contain more dumb features than [project_c0rry](https://github.com/1nekomata/project_c0rry).

## Building

`git submodule update`
 
`make`

Either move the resulting src/main.efi File to a FAT32 USB-Stick and Boot it with a UEFI Supporting PC/Laptop or run ./scripts/all.sh (root requiered! depends on sudo, qemu, parted, mkdosfs, losetup and mount!). 

## Credits

[POSIX-UEFI](https://gitlab.com/bztsrc/posix-uefi) by bzt. A "Dependency-free POSIX compatibility layer and build environment for UEFI"
