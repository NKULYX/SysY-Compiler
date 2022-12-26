make run
arm-linux-gnueabihf-gcc -mcpu=cortex-a72 -o example.bin example.s
qemu-arm -L /usr/arm-linux-gnueabihf example.bin
echo $?

# arm-linux-gnueabihf-gcc standard.c -mcpu=cortex-a72 -S -o standard.s
# arm-linux-gnueabihf-gcc -mcpu=cortex-a72 -o standard.bin standard.s
# qemu-arm -L /usr/arm-linux-gnueabihf standard.bin
# echo $?