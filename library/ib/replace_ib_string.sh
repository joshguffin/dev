#!/bin/bash

CWD=`pwd`
TOKEN=`basename $CWD`

if [ $TOKEN != "ib" ]; then
	echo "Must be run from ib directory of library"
	exit 1
fi

find ./ -type f -exec sed -i 's/#include <string>/#include <string>/' {} \;
find ./ -type f -exec sed -i 's/std::string/std::string/g' {} \;

rm -f IBString.h
touch IBString.h


