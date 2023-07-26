#!/usr/bin/python
#-*- coding: utf-8

from setuptools import setup, Extension
import platform
import os
import glob

include_dirs = ['src/libdmiget/include']
library_dirs = []
extra_link_args = []
library_names = [ ]
src_files = [ ]

for filename in glob.glob("src/libdmiget/*.cc"):
	src_files.append(filename)
	
for filename in glob.glob("src/libdmiget/decoders/*.cc"):
	src_files.append(filename)

for filename in glob.glob("src/python/*.cc"):
	src_files.append(filename)

for filename in glob.glob("src/python/*.c"):
	src_files.append(filename)

if platform.system() == 'Windows':
	
	for filename in glob.glob("src/libdmiget/os/windows/*.cc"):
		src_files.append(filename)

else:

	for filename in glob.glob("src/libdmiget/os/linux/*.cc"):
		src_files.append(filename)

smbios = Extension(
		'smbios',
		include_dirs = include_dirs,
		libraries = library_names,
		library_dirs=library_dirs,
		extra_link_args=extra_link_args,
		sources=src_files
)

package_version='0.1'
with open(r'configure.ac', 'r') as fp:
    lines = fp.readlines()
    for line in lines:
        if line.find('AC_INIT') != -1:
            package_version = line.split('[')[2].split(']')[0].strip()
            break;
            
setup ( name = 'smbios',
	version = package_version,
	description = 'Python library to read data from SMBIOS/DMI.',
	author = 'Perry Werneck',
	author_email = 'perry.werneck@gmail.com',
	url = 'https://github.com/PerryWerneck/dmiget',
	long_description = '''
This is an extension allowing smibios/dmi read for python applications.
''',
	ext_modules = [ smbios ])
