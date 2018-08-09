#!/bin/sh

BOARD_DIR="$(dirname $0)"
BR_ROOT=$PWD
TARGET_DIR=$BR_ROOT/output/target

#need to overwrite mesa libs,so do the copy during post build.
for filename in `ls $BOARD_DIR/lib/gpu`
do
if test -e $TARGET_DIR/usr/lib/$filename
then
rm $TARGET_DIR/usr/lib/$filename
fi
done
cp -d $BOARD_DIR/lib/gpu/* $TARGET_DIR/usr/lib/

#for files in bin directory
for filename in `ls $BOARD_DIR/bin/`
do
if test -e $TARGET_DIR/usr/bin/$filename
then
rm $TARGET_DIR/usr/bin/$filename
fi
done
cp -d $BOARD_DIR/bin/* $TARGET_DIR/usr/bin/

#for files in sbin directory
for filename in `ls $BOARD_DIR/sbin/`
do
if test -e $TARGET_DIR/usr/sbin/$filename
then
rm -f $TARGET_DIR/usr/sbin/$filename
fi
done
cp -d $BOARD_DIR/sbin/* $TARGET_DIR/usr/sbin/

#for files in share directory
for filename in `ls $BOARD_DIR/share/`
do
if test -d $TARGET_DIR/usr/share/$filename
then
rm -r -f $TARGET_DIR/usr/share/$filename
fi
done
cp -r $BOARD_DIR/share/* $TARGET_DIR/usr/share/

#for files in pppd-lib directory
for filename in `ls $BOARD_DIR/pppd-lib/`
do
if test -d $TARGET_DIR/usr/lib/$filename
then
rm -r -f $TARGET_DIR/usr/lib/$filename
fi
done
cp -r $BOARD_DIR/pppd-lib/* $TARGET_DIR/usr/lib/

#for files in etc directory
for filename in `ls $BOARD_DIR/etc/`
do
if test -d $TARGET_DIR/etc/$filename
then
rm -r -f $TARGET_DIR/etc/$filename
fi
done
cp -r $BOARD_DIR/etc/* $TARGET_DIR/etc/
