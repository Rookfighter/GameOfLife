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

# Information for getting Catch
CATCH_ARCH_NAME="Catch.zip"
CATCH_ARCH_PATH="$DEP_INSTALL_DIR/$CATCH_ARCH_NAME"
CATCH_EXTRACT_NAME="Catch-master"
CATCH_RESULT_NAME="Catch"
CATCH_RESULT_DIR="$DEP_INSTALL_DIR/$CATCH_RESULT_NAME"
CATCH_DONWLOAD_URL="https://github.com/philsquared/Catch/archive/master.zip"

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

if [ -d $CATCH_RESULT_DIR ]; then
    echo "-- $CATCH_RESULT_NAME already exists"
else
    echo "-- Getting $CATCH_RESULT_NAME"
    wget "$CATCH_DONWLOAD_URL" -O "$CATCH_ARCH_NAME"
    unzip -qq "$CATCH_ARCH_NAME"
    mv "$CATCH_EXTRACT_NAME" "$CATCH_RESULT_NAME"
    rm -f "$CATCH_ARCH_NAME"
fi

cd $CURRDIR
