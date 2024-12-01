#!/bin/bash

out_sample="./stdout-sample.txt"
out="./stdout.txt"

err_sample="./stderr-sample.txt"
err="./stderr.txt"

./dnd 1> ./stdout.txt 2> ./stderr.txt

if [[ -z $(cmp "$out" "$out_sample") ]]; then
  echo "stdout: MATCH"
else
  meld "$out" "$out_sample"
fi

if [[ -z $(cmp "$err" "$err_sample") ]]; then
  echo "stderr: MATCH"
else
  meld "$err" "$err_sample"
fi
