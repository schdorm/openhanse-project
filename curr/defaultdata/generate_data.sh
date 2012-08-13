#!/bin/sh
cd img
rcc -binary images.qrc -no-compress -o images.rcc
cp images.rcc ../../bin/data/
cd ../audio
rcc -binary music.qrc -no-compress -o music.rcc
cp music.rcc ../../bin/data/
rcc -binary sounds.qrc -no-compress -o sounds.rcc
cp sounds.rcc ../../bin/data/
cd ../data
rcc -binary data.qrc -threshold 90 -compress 9 -o data.rcc
cp data.rcc ../../bin/data/