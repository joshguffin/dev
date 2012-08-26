#!/bin/bash

CWD=`pwd`
TOKEN=`basename $CWD`

if [ $TOKEN != "ib" ]; then
	echo "Must be run from ib directory of library"
	exit 1
fi

find ./ -type f -exec sed -i 's/#include <string>/#include <string>/' {} \;
find ./ -type f -exec sed -i 's/std::string/std::string/g' {} \;

sed -i 's/typedef std::string std::string;//' IBString.h
sed -i 's/#ifdef IB_USE_STD_STRING/#define IB_USE_STD_STRING\n#ifdef IB_USE_STD_STRING/' IBString.h 

