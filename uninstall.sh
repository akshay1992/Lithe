#!/bin/bash

echo "Uninstalling Lithe..."

echo "Removing /usr/local/include/Lithe/"
rm -rf /usr/local/include/Lithe
echo "Removing /usr/local/lib/liblithe_core.a"
rm -r /usr/local/lib/liblithe_core.a

echo "Uninstall complete!"
