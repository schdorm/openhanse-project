#!/bin/bash

qmake oh_gamedata.pro > /tmp/make_oh_gamedata.log 
make 2>> /tmp/make_oh_gamedata.log >> /tmp/make_oh_gamedata.log 

if [ "$?" = 0 ]
then
kdialog --msgbox "`cat /tmp/make_oh_gamedata.log`"

else
kdialog --error "`cat /tmp/make_oh_gamedata.log`"
fi