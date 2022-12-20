#!/bin/bash

cd /root/helios/.arman/linux-6.0.9
make mrproper
cp /root/helios/linux-6.0.9/.config /root/helios/.arman/linux-6.0.9
cd /root/helios/.arman/linux-6.0.9
make