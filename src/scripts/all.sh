#!/usr/bin/env bash
./scripts/loop.sh
sudo mv main.efi mnt
./scripts/unloop.sh
./scripts/qemu.sh