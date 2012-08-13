#!/bin/bash
mdir=`pwd`
# echo $cdir
# cdir=$makdir"/common"
# ndir=$makdir"/networktools"
# gdir=$makdir"/gamedata"
# maphdir=$makdir"/maphandling"
# mapcdir=$makdir"/mapcreator"
# servdir=$makdir"/server"
# echo $cdir
rm /tmp/build_oh.log
mkdir bin 2> /dev/null
cd common
# # make clean
echo "Building common-lib ..."
echo "\n>Building common-lib ..." > /tmp/build_oh.log
make >> /tmp/build_oh.log 2>> /tmp/build_oh.log 3>> /tmp/build_oh.log
if [ "$?" = 0 ]
then
cp -uv liboh_common.so.1 ../bin/lib/
echo "> Success!"
else
kdialog --error "`cat /tmp/build_oh.log`"
fi
# cd /usr/lib
# #pwd
# echo "Creating symbolic links in \"/usr/lib\" ..."
# sudo ln -s $mdir"/common/liboh_common.so" .
# sudo ln -s $mdir"/common/liboh_common.so.1" .
cd $mdir"/networktools"
# make clean
echo "Building networktools-lib ..."
echo "\n>Building networktools-lib ..." >> /tmp/build_oh.log
make >> /tmp/build_oh.log 2>> /tmp/build_oh.log 3>> /tmp/build_oh.log
if [ "$?" = 0 ]
then
cp -uv liboh_networktools.so.1 ../bin/lib/
echo "> Success!"
else
kdialog --error "`cat /tmp/build_oh.log`"
fi
# cd /usr/lib
# echo "Creating symbolic links in \"/usr/lib\" ..."
# sudo ln -s $mdir"/networktools/liboh_networktools.so.1" .
# sudo ln -s $mdir"/networktools/liboh_networktools.so" .
cd $mdir"/gamedata"
# make clean
echo "Building gamedata-lib ..."
echo "\n>Building gamedata-lib ..." >> /tmp/build_oh.log
make >> /tmp/build_oh.log 2>> /tmp/build_oh.log 3>> /tmp/build_oh.log
if [ "$?" = 0 ]
then
cp -uv liboh_gamedata.so.1 ../bin/lib/
echo "> Success!"
else
echo "> Problems occured ..."
kdialog --error "`cat /tmp/build_oh.log`"
fi
# cd /usr/lib
# echo "Creating symbolic links in \"/usr/lib\" ..."
# sudo ln -s $mdir"/gamedata/liboh_gamedata.so.1" .
# sudo ln -s $mdir"/gamedata/liboh_gamedata.so" .
cd $mdir"/maphandling"
# make clean
echo "Building maphandling-lib ..."
echo "\n>Building maphandling-lib ..." >> /tmp/build_oh.log
make >> /tmp/build_oh.log 2>> /tmp/build_oh.log 3>> /tmp/build_oh.log
if [ "$?" = 0 ]
then
cp -uv liboh_maphandling.so.1 ../bin/lib/
echo "> Success!"
else
kdialog --error "`cat /tmp/build_oh.log`"
fi
# cd /usr/lib
# echo "Creating symbolic links in \"/usr/lib\" ..."
# sudo ln -s $mdir"/maphandling/liboh_maphandling.so.1" .
# sudo ln -s $mdir"/maphandling/liboh_maphandling.so" .
cd $mdir"/defaultdata"
echo "Generating defaultdata ..."
echo "\n>Generating defaultdata ..." >> /tmp/build_oh.log
# make >> /tmp/build_oh.log 2>> /tmp/build_oh.log 3>> /tmp/build_oh.log
sh generate_data.sh  >> /tmp/build_oh.log
# cd /usr/lib
# echo "Creating symbolic links in \"/usr/lib\" ..."
# sudo ln -s $mdir"/defaultdata/liboh_defaultdata.so.1"
# sudo ln -s $mdir"/defaultdata/liboh_defaultdata.so"
# cd $mdir"/mapcreator"
# # make clean
# echo "Building mapcreator ..."
# make >> /tmp/build_oh.log 2>> /tmp/build_oh.log 3>> /tmp/build_oh.log
cd ../server
# make clean
echo "Building oh-server ..."
echo "\n>Building oh-server ..." >> /tmp/build_oh.log
make >> /tmp/build_oh.log 2>> /tmp/build_oh.log 3>> /tmp/build_oh.log
if [ "$?" = 0 ]
then
echo "> Success!"
else
kdialog --error "`cat /tmp/build_oh.log`"
fi
cd ../control_gui
# make clean
echo "Building servercontrol ..."
echo "\n>Building servercontrol ..." >> /tmp/build_oh_sc.log
make >> /tmp/build_oh.log 2>> /tmp/build_oh_sc.log 3>> /tmp/build_oh_sc.log
if [ "$?" = 0 ]
then
echo "> Success!"
else
kdialog --error "`cat /tmp/build_oh_sc.log`"
fi
cd ../oh_game
# make clean
echo "Building game ..."
echo "\n>Building game ..." >> /tmp/build_oh.log
# killall OpenHanse
# rm /tmp/make_oh_game.log
qmake >> /tmp/build_oh.log && make 2>> /tmp/build_oh.log >> /tmp/build_oh.log
if [ "$?" = 0 ]
then
# cp -rvu maps/ ../bin/
# # # # # xmessage -buttons Exit:0,StartOH:1 -center -file /tmp/build_oh.log 
echo "> Sucess!"
if [ "$?" = 1 ]
then
cd ../bin/
echo "\n\nBegin log:\n" >> debugging.log
date >> debugging.log
./OpenHanse 2>> debugging.log >> debugging.log
while [ "$?" = 3 ]
do
./OpenHanse 2>> debugging.log >> debugging.log
done
fi
else
echo "> Problems occured ..."
kdialog --error "`cat /tmp/build_oh.log`"
fi
# make >> /tmp/build_oh.log 2>> /tmp/build_oh.log 3>> /tmp/build_oh.log
grep -B 2 -A 5 "error" /tmp/build_oh.log
