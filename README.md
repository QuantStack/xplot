# ![xplot](http://quantstack.net/assets/images/xplot.svg)

[![Travis](https://travis-ci.org/QuantStack/xplot.svg?branch=master)](https://travis-ci.org/QuantStack/xplot)
[![Appveyor](https://ci.appveyor.com/api/projects/status/733j3qm6kn3sh0b4?svg=true)](https://ci.appveyor.com/project/QuantStack/xplot)
[![Documentation](http://readthedocs.org/projects/xplot/badge/?version=latest)](https://xplot.readthedocs.io/en/latest/?badge=latest)
[![Binder](https://img.shields.io/badge/launch-binder-brightgreen.svg)](https://beta.mybinder.org/v2/gh/QuantStack/xplot/0.4.1-binder?filepath=notebooks)
[![Join the Gitter Chat](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/QuantStack/Lobby?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

C++ backend for the bqplot 2-D plotting library

**xplot is an early developer preview, and is not suitable for general usage yet. Features and implementation are subject to change.**

## Usage

![xplot](xplot-screencast.gif)

## Dependencies

All the dependencies of xplot are available for the conda package manager.

| `xplot` | `xwidgets`  |  `xeus`         |
|---------|-------------|-----------------|
|  master |   ~0.8.2    |  >=0.11.0,<0.12 |
|  0.5.0  |   ~0.8.2    |  >=0.11.0,<0.12 |
|  0.4.1  |   ~0.8.1    |  >=0.11.0,<0.12 |
|  0.4.0  |   ~0.7.1    |  >=0.10.0,<0.11 |
|  0.3.0  |   ~0.6.0    |  >=0.8.0,<0.9   |
|  0.2.0  |   ~0.5.0    |  >=0.8.0,<0.9   |
|  0.1.0  |   ~0.4.0    |  >=0.7.0,<0.8   |

## Installation

`xplot` and its dependencies have been packaged for the conda package manager.

- To install the xeus-cling kernel, and xwidgets

```
conda install xplot xeus-cling -c QuantStack -c conda-forge
```

- To install the front-end components

```
conda install notebook bqplot -c QuantStack -c conda-forge
```

## License

We use a shared copyright model that enables all contributors to maintain the
copyright on their contributions.

This software is licensed under the BSD-3-Clause license. See the [LICENSE](LICENSE) file for details.
