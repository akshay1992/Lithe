#!/bin/bash

echo "== Installing Lithe =="
mkdir build
pushd build
cmake ..
make
make install
popd

echo "-- Install complete --"
