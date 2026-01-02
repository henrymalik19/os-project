# Make & Clean Folder
rm -rf build/*
mkdir -p build

# Build Assembly
riscv64-unknown-elf-as -march=rv64ima_zicsr -mabi=lp64 src/start.S -o build/start.o
riscv64-unknown-elf-as -march=rv64ima_zicsr -mabi=lp64 src/trap_entry.S -o build/trap_entry.o

# # Build C Files
riscv64-unknown-elf-gcc -c -mcmodel=medany -ffreestanding -nostdlib -nostartfiles -fno-builtin -fno-stack-protector -mabi=lp64 -march=rv64ima_zicsr src/proc.c -o build/proc.o
riscv64-unknown-elf-gcc -c -mcmodel=medany -ffreestanding -nostdlib -nostartfiles -fno-builtin -fno-stack-protector -mabi=lp64 -march=rv64ima_zicsr src/timer.c -o build/timer.o
riscv64-unknown-elf-gcc -c -mcmodel=medany -ffreestanding -nostdlib -nostartfiles -fno-builtin -fno-stack-protector -mabi=lp64 -march=rv64ima_zicsr src/trap.c -o build/trap.o
riscv64-unknown-elf-gcc -c -mcmodel=medany -ffreestanding -nostdlib -nostartfiles -fno-builtin -fno-stack-protector -mabi=lp64 -march=rv64ima_zicsr src/commands.c -o build/commands.o
riscv64-unknown-elf-gcc -c -mcmodel=medany -ffreestanding -nostdlib -nostartfiles -fno-builtin -fno-stack-protector -mabi=lp64 -march=rv64ima_zicsr src/console.c -o build/console.o
riscv64-unknown-elf-gcc -c -mcmodel=medany -ffreestanding -nostdlib -nostartfiles -fno-builtin -fno-stack-protector -mabi=lp64 -march=rv64ima_zicsr src/sbi.c -o build/sbi.o
riscv64-unknown-elf-gcc -c -mcmodel=medany -ffreestanding -nostdlib -nostartfiles -fno-builtin -fno-stack-protector -mabi=lp64 -march=rv64ima_zicsr src/string.c -o build/string.o
riscv64-unknown-elf-gcc -c -mcmodel=medany -ffreestanding -nostdlib -nostartfiles -fno-builtin -fno-stack-protector -mabi=lp64 -march=rv64ima_zicsr src/main.c -o build/main.o

# Link Files
riscv64-unknown-elf-ld -T linker.ld build/start.o build/trap_entry.o build/proc.o build/timer.o build/trap.o build/commands.o build/console.o build/sbi.o build/string.o build/main.o -o build/kernel.elf