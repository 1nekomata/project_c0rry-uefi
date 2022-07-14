#!/usr/bin/env bash
sudo qemu-system-x86_64 -cpu qemu64 -hda uefi.img \
  -drive if=pflash,format=raw,unit=0,file=/usr/share/ovmf/x64/OVMF_CODE.fd,readonly=on \
  -drive if=pflash,format=raw,unit=1,file=/usr/share/ovmf/x64/OVMF_VARS.fd \
  -net none