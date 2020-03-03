#!/bin/bash

set -ex

os="$(uname -s | tr '[:upper:]' '[:lower:]')"
arch="amd64"

version=$(wget -qO- https://distfiles.rgm.io/avr-toolchain/LATEST/ | sed -n "s/.*avr-toolchain-${os}-${arch}-\(.*\)\.tar\.xz\.sha512.*/\1/p")

wget "https://distfiles.rgm.io/avr-toolchain/avr-toolchain-${version}/avr-toolchain-${os}-${arch}-${version}.tar.xz"{,.sha512}

sha512sum --check --status "avr-toolchain-${os}-${arch}-${version}.tar.xz.sha512"

tar -xvf "avr-toolchain-${os}-${arch}-${version}.tar.xz"

export PATH="$(pwd)/avr/bin:${PATH}"

if [[ "x${TARGET}" == "xdist-avr" ]]; then
    export AVR_RELEASE=1
else
    DEBUG="-debug"
fi

export FIRMWARE_NAME="${PN}-${PV}"

dir="${PN}-${PV}${DEBUG}"

make -C "${SRCDIR}" BUILDDIR="${BUILDDIR}/${dir}" all

cp ../LICENSE "${BUILDDIR}/${dir}/"

tar -cvzf "${dir}.tar.gz" -C "${BUILDDIR}" "${dir}/"
