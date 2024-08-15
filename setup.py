#!/usr/bin/python
#-*- coding: utf-8

from setuptools import setup, Extension
import platform
import os
import glob
import sysconfig

include_dirs = ['src/include']
library_dirs = []
extra_link_args = []
library_names = [ ]
src_files = [ ]
extra_compile_args = [ ]

for filename in glob.glob("src/libdmiget/*.cc"):
	src_files.append(filename)
	
for filename in glob.glob("src/libdmiget/node/*.cc"):
	src_files.append(filename)
	
for filename in glob.glob("src/libdmiget/value/*.cc"):
	src_files.append(filename)
	
for filename in glob.glob("src/libdmiget/decoders/*.cc"):
	src_files.append(filename)

for filename in glob.glob("src/python/*.cc"):
	src_files.append(filename)

for filename in glob.glob("src/python/*.c"):
	src_files.append(filename)

for filename in glob.glob("src/python/value/*.c"):
	src_files.append(filename)

for filename in glob.glob("src/python/value/*.cc"):
	src_files.append(filename)

for filename in glob.glob("src/python/node/*.c"):
	src_files.append(filename)

for filename in glob.glob("src/python/node/*.cc"):
	src_files.append(filename)

package_version='0.1'
with open(r'configure.ac', 'r') as fp:
    lines = fp.readlines()
    for line in lines:
        if line.find('AC_INIT') != -1:
            package_version = line.split('[')[2].split(']')[0].strip()
            break;
            
package_version += '.5'

extra_compile_args.append('-DPACKAGE_VERSION=\"' + package_version + '\"')
            
if platform.system() == 'Windows':
	
	for filename in glob.glob("src/libdmiget/os/windows/*.cc"):
		src_files.append(filename)

else:

	extra_compile_args.append('-DHAVE_UNISTD_H')

	for filename in glob.glob("src/libdmiget/os/linux/*.cc"):
		src_files.append(filename)

smbios = Extension(
		'smbios',
		include_dirs = include_dirs,
		libraries = library_names,
		library_dirs=library_dirs,
		extra_link_args=extra_link_args,
		extra_compile_args=extra_compile_args,
		sources=src_files
)

setup ( name = 'smbios',
	version = package_version,
	description = 'Python library to read data from SMBIOS/DMI.',
	author = 'Perry Werneck',
	author_email = 'perry.werneck@gmail.com',
	url = 'https://github.com/PerryWerneck/dmiget',
	long_description_content_type = 'text/markdown',
	long_description = '''
## About

This library allow python applications an easy way to read data from system's SMBios without the need of dmidecode. 

## Installation

### PyPI

```shell
pip install smbios
```

### Linux packages

You can get linux packages (RPM, Deb, arch) from Suse's [Open Build Service](https://software.opensuse.org/download.html?project=home:PerryWerneck:python&package=python-smbios)

## Usage

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
''',
	ext_modules = [ smbios ])

