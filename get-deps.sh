#!/bin/sh

CURRDIR=$PWD
BASEDIR=$(cd "$(dirname "$0")"; pwd)
echo $BASEDIR

DEP_INSTALL_DIR="$BASEDIR/lib"

# Information for getting SFML
SFML_ARCH_NAME="SFML-2.2.tar.gz"
SFML_ARCH_PATH="$DEP_INSTALL_DIR/$SFML_ARCH_NAME"
SFML_RESULT_NAME="SFML-2.2"
SFML_RESULT_DIR="$DEP_INSTALL_DIR/$SFML_RESULT_NAME"
SFML_DONWLOAD_URL="www.sfml-dev.org/files/SFML-2.2-linux-gcc-64-bit.tar.gz"

# Information for getting TGUI
TGUI_ARCH_NAME="TGUI.zip"
TGUI_ARCH_PATH="$DEP_INSTALL_DIR/$TGUI_ARCH_NAME"
TGUI_EXTRACT_NAME="TGUI-0.6.6-2"
TGUI_RESULT_NAME="TGUI"
TGUI_RESULT_DIR="$DEP_INSTALL_DIR/$TGUI_RESULT_NAME"
TGUI_DONWLOAD_URL="https://github.com/texus/TGUI/archive/v0.6.6-2.zip"

# Information for getting Catch
CATCH_ARCH_NAME="Catch.zip"
CATCH_ARCH_PATH="$DEP_INSTALL_DIR/$CATCH_ARCH_NAME"
CATCH_EXTRACT_NAME="Catch-master"
CATCH_RESULT_NAME="Catch"
CATCH_RESULT_DIR="$DEP_INSTALL_DIR/$CATCH_RESULT_NAME"
CATCH_DONWLOAD_URL="https://github.com/philsquared/Catch/archive/master.zip"

# Information for getting Easylogging++
EASYLOG_ARCH_NAME="Easylogging++.tar.gz"
EASYLOG_ARCH_PATH="$DEP_INSTALL_DIR/$EASYLOG_ARCH_NAME"
EASYLOG_RESULT_NAME="Easylogging++"
EASYLOG_RESULT_DIR="$DEP_INSTALL_DIR/$EASYLOG_RESULT_NAME"
EASYLOG_DONWLOAD_URL="https://github.com/easylogging/easyloggingpp/releases/download/v9.80/easyloggingpp_v9.80.tar.gz"

echo "Getting dependencies"
mkdir -p $DEP_INSTALL_DIR
cd $DEP_INSTALL_DIR

if [ -d $SFML_RESULT_DIR ]; then
    echo "-- $SFML_RESULT_NAME already exists"
else
    echo "-- Getting $SFML_RESULT_NAME"
    wget "$SFML_DONWLOAD_URL" -O "$SFML_ARCH_NAME"
    tar xzf "$SFML_ARCH_NAME"
    rm -f "$SFML_ARCH_NAME"
fi

if [ -d $TGUI_RESULT_DIR ]; then
    echo "-- $TGUI_RESULT_NAME already exists"
else
    echo "-- Getting $TGUI_RESULT_NAME"
    wget "$TGUI_DONWLOAD_URL" -O "$TGUI_ARCH_NAME"
    unzip -qq "$TGUI_ARCH_NAME"
    mv "$TGUI_EXTRACT_NAME" "$TGUI_RESULT_NAME"
    rm -f "$TGUI_ARCH_NAME"
    cd "$TGUI_RESULT_NAME"
    mkdir -p build
    cd build
    cmake .. -DSFML_ROOT="$SFML_RESULT_DIR"
    make -j 8
    cd "$DEP_INSTALL_DIR"
fi

if [ -d $CATCH_RESULT_DIR ]; then
    echo "-- $CATCH_RESULT_NAME already exists"
else
    echo "-- Getting $CATCH_RESULT_NAME"
    wget "$CATCH_DONWLOAD_URL" -O "$CATCH_ARCH_NAME"
    unzip -qq "$CATCH_ARCH_NAME"
    mv "$CATCH_EXTRACT_NAME" "$CATCH_RESULT_NAME"
    rm -f "$CATCH_ARCH_NAME"
fi

if [ -d $EASYLOG_RESULT_DIR ]; then
    echo "-- $EASYLOG_RESULT_NAME already exists"
else
    echo "-- Getting $EASYLOG_RESULT_NAME"
    wget "$EASYLOG_DONWLOAD_URL" -O "$EASYLOG_ARCH_NAME"
    mkdir -p "$EASYLOG_RESULT_NAME"
    tar xzf "$EASYLOG_ARCH_NAME" -C "$EASYLOG_RESULT_NAME"
    rm -f "$EASYLOG_ARCH_NAME"
fi

cd $CURRDIR
