#!/usr/bin/env bash

dd if=/dev/zero of=uefi.img bs=512 count=93750

parted uefi.img -s -a minimal mklabel gpt
parted uefi.img -s -a minimal mkpart EFI FAT16 2048s 93716s
parted uefi.img -s -a minimal toggle 1 boot

sudo losetup --offset 1048576 --sizelimit 46934528 /dev/loop10 uefi.img

sudo mkdosfs -F 32 /dev/loop10

sudo mount /dev/loop10 /mnt

ln -s /mnt