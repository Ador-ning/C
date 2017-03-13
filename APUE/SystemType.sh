#!/bin/zsh

case $(uname -s) in
  "Darwin")
    PLATFORM="macos"
    ;;
  "Linux")
    PLATFORM="linux"
    ;;
  "FreeBSD")
    PLATFORM="freebsd"
    ;;
  "SunOS")
    PLATFORM="solaris"
    ;;
  *)

    echo "unknown platform" >&2
    exit 1
    ;;
esac

echo $PLATFORM
exit 0
