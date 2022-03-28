#!/bin/bash
set -e

TEST_FILE=$1
STANDALONE=${2:-1}

TEST=$2

# validate test target
if [[ -f "compiler_tests/${TEST_FILE}.c" ]]; then
  echo "Running test on \"compiler_tests/${TEST_FILE}.c\""
  echo "========================="
else
  echo "${TEST_FILE}.c is not a file."
  exit 1
fi

# Build bin/c_compiler 
if [[ ${STANDALONE} == 1 ]]; then
  make clean
  make
fi

make bin/c_compiler
# Compile test program using bin/c_compiler
bin/c_compiler -S "compiler_tests/${TEST_FILE}".c -o "bin/${TEST}".s 2>/dev/null
# Assemble generated assembly code via gcc
mips-linux-gnu-gcc -mfp32 -o "bin/${TEST}".o -c "bin/${TEST}".s
echo "Assembler:" mips-linux-gnu-gcc -mfp32 -o "bin/${TEST}".o -c "bin/${TEST}".s
# Link to main function and generate executable via gcc
mips-linux-gnu-gcc -mfp32 -static -o "bin/${TEST}".bin "bin/${TEST}".o "compiler_tests/${TEST_FILE}"_driver.c
echo "Linking:" mips-linux-gnu-gcc -mfp32 -static -o "bin/${TEST}".bin "bin/${TEST}".o "compiler_tests/${TEST_FILE}"_driver.c
# run executable on qemu-mips
set +e 
qemu-mips "bin/${TEST}".bin
echo qemu-mips "bin/${TEST}".bin
if (( $? == 0 )); then
  echo ✅ pass
  exit 0
else
  echo ❌ fail
  exit 1
fi
