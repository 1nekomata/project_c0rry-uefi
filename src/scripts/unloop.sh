#!/usr/bin/env bash
rm ./mnt
sudo umount /mnt
sudo losetup -d /dev/loop10