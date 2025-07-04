# qsettings2json

## Deprecated

Please use `kconfig-to-json` from [Deltona](https://github.com/Tatsh/deltona)
([PyPI](https://pypi.org/project/deltona/)).

## Original text

![CI](https://github.com/Tatsh/qsettings2json/workflows/CI/badge.svg)

Convert QSettings-generated files to JSON. Compatible with `quasselcore.conf` and many others.

## Build

```shell
git clone ...
cd qsettings2json
qmake
make
```

## Usage

```shell
qsettings2json FILE
```

If the file is not compatible, the exit status will be non-zero.

If an empty object is printed, this usually means the file was incompatible. However, the exit status will still be `0`.
