#!/bin/bash
set -e
TEST=$1
qemu-mips "bin/${TEST}".bin
echo qemu-mips "bin/${TEST}".bin
if (( $? == 0 )); then
  echo ✅ pass
  exit 0
else
  echo ❌ fail
  exit 1
fi
