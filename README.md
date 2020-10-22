# qsettings2json

Convert QSettings-generated files to JSON. Compatible with quasselcore.conf and many others.

## Build

```
git clone ...
cd qsettings2json
qmake
make
```

## Usage

```
qsettings2json FILE
```

If the file is not compatible, the exit status will be non-zero.

If an empty object is printed, this usually means the file was incompatible. However, the exit status will still be `0`.
