#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/trueos.kernel isodir/boot/trueos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "trueos" {
	multiboot /boot/trueos.kernel
}
EOF
grub-mkrescue -o trueos.iso isodir
