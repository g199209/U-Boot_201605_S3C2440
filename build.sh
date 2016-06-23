#!/bin/bash

make smdk2440_defconfig
make all
cp ./u-boot.bin /mnt/hgfs/Uboot/u-boot.bin
