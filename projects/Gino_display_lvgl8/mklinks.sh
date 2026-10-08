#!/bin/sh
[ -e rt-thread ] || ln -s ../../rt-thread rt-thread
[ -e libraries ] || ln -s ../../libraries libraries
[ -d packages ] || mkdir packages
[ -e packages/LVGL-v8.3.11 ] || ln -s ../../../packages/LVGL-v8.3.11 packages/LVGL-v8.3.11
[ -e packages/gt911-latest ] || ln -s ../../../packages/gt911-latest packages/gt911-latest
