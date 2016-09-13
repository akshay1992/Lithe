#!/bin/bash

echo "== Installing Lithe =="
mkdir build
cd build
cmake ..
make
make install
popd

echo "-- Install complete --"
