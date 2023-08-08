#!/bin/bash
rm -fr build
python3 setup.py build 
if [ "$?" != "0" ]; then
	exit -1
fi

sudo PYTHONPATH=$(readlink -f ./build/lib.linux-x86_64-3.6) python3

