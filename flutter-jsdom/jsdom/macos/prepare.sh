ROOT=$(pwd)

if [ -L "libjsdom.dylib" ]; then
  rm libjsdom.dylib
fi
ln -s $ROOT/../../bridge/build/macos/lib/x86_64/libjsdom.dylib


if [ -L "libquickjs.dylib" ]; then
  rm libquickjs.dylib
fi
ln -s $ROOT/../../bridge/build/macos/lib/x86_64/libquickjs.dylib

