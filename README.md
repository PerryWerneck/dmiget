# Linux/Windows tool and library to get DMI data

![Platform: Linux/Windows](https://img.shields.io/badge/Platform-Linux/Windows-blue.svg)
[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
![CodeQL](https://github.com/PerryWerneck/dmiget/workflows/CodeQL/badge.svg?branch=master)
[![build result](https://build.opensuse.org/projects/home:PerryWerneck:udjat/packages/dmiget/badge.svg?type=percent)](https://build.opensuse.org/package/show/home:PerryWerneck:udjat/dmiget)
[![PyPI version](https://badge.fury.io/py/smbios.svg)](https://badge.fury.io/py/smbios)

## Installation

### Packages

You can download installation package for supported linux distributions in [Open Build Service](https://software.opensuse.org/download.html?project=home%3APerryWerneck%3Audjat&package=dmiget)

[<img src="https://raw.githubusercontent.com/PerryWerneck/pw3270/develop/branding/obs-badge-en.svg" alt="Download from open build service" height="80px">](https://software.opensuse.org/download.html?project=home%3APerryWerneck%3Audjat&package=dmiget)
[<img src="https://github.com/PerryWerneck/PerryWerneck/blob/master/badges/msys-msvc-python-badge.svg" alt="Download from githut" height="80px">](https://github.com/PerryWerneck/dmiget/releases)
[<img src="https://raw.githubusercontent.com/PerryWerneck/PerryWerneck/master/badges/pypi-badge.svg" alt="Download from pypi" height="80px">](https://pypi.org/project/smbios)

## Examples:

### Command line

```shell
dmiget
```

```shell
dmiget dmi:///bios/vendor
```

### Python

```python
import smbios
value = smbios.Value('chassis','serial')
print(value)
```

```python
import smbios
value = smbios.Value('dmi:///chassis/serial')
print(value)
```

```python
import smbios
value = smbios.memsize()
print(value)
print(int(value))
```

```python
import smbios
for node in smbios.nodes():
	print(node)
	for value in node.values():
		print('	{}: {}'.format(value.description,value))
```

### C++

```C
#include <smbios/node.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	Node node{"chassis"};
	cout << node.name() << " - " << node << endl;
	cout << node["manufacturer"] << endl;
	return 0;
}
```



	


