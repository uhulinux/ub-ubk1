QT5DIR=/usr/lib/qt5

export PATH="$PATH:$QT5DIR/bin"
export QT5DIR

if [[ ($UID = 82 || $UID = 0) && -z $PKG_CONFIG_PATH ]]; then
PKG_CONFIG_PATH=$(pkg-config --variable pc_path pkg-config)
export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:$QT5DIR/lib/pkgconfig
fi

