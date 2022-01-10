#!/usr/bin/env bash

rm -i Threads-new-CMake.tar.gz || true
tar --transform 's#^#Threads-CMakeProject/#' -cavf Threads-new-CMake.tar.gz *.txt *.cpp *.h *.sh
