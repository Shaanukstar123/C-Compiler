#!/bin/bash
OUT=$1
TEST_DRIVER=$2

echo "Assembling output"
mips-linux-gnu-gcc -mfp32 -static -o "bin/${OUT}.o" -c "out/${OUT}.s"

echo "Linking with driver program"
mips-linux-gnu-gcc -mfp32 -static -o "bin/${OUT}.bin" "bin/${OUT}.o" "compiler_tests/${TEST_DRIVER}"
set +e 
qemu-mips "bin/${OUT}".bin
RESULT=${?}
set -e
echo qemu-mips "bin/${OUT}".bin
if [[ ${RESULT} -eq 0 ]] ; then
  echo ✅ pass
  exit 0
else
  echo ❌ fail
  exit 1
fi
