#!/usr/bin/python
#-*- coding: utf-8

from setuptools import setup, Extension
import platform
import os

include_dirs = ['src/include']
library_dirs = []
extra_link_args = []

src_files = [
	'src/libdmiget/decoders/tools.cc',
	'src/libdmiget/decoders/decode.cc',
	'src/libdmiget/os/linux/node.cc',
	'src/libdmiget/string.cc',
	'src/libdmiget/constants.cc',
	'src/libdmiget/factory.cc',
	'src/libdmiget/table.cc',
	'src/libdmiget/value.cc'
]

library_names = [
]

if platform.system() == 'Windows':
	src_files.append('src/libdmiget/os/windows/file.cc')
	src_files.append('src/libdmiget/os/windows/table.cc')
else:
	src_files.append('src/libdmiget/os/linux/reader.cc')
	src_files.append('src/libdmiget/os/linux/table.cc')
	src_files.append('src/libdmiget/os/linux/value.cc')
	src_files.append('src/libdmiget/os/linux/file.cc')

pydmiget = Extension(
		'pydmiget',
		include_dirs = include_dirs,
		libraries = library_names,
		library_dirs=library_dirs,
		extra_link_args=extra_link_args,
		sources=src_files
)

package_version='1.0'
with open(r'configure.ac', 'r') as fp:
    lines = fp.readlines()
    for line in lines:
        if line.find('AC_INIT') != -1:
            package_version = line.split('[')[2].split(']')[0].strip()
            break;
            
setup ( name = 'pydmiget',
	version = package_version,
	description = 'DMI library for python.',
	author = 'Perry Werneck',
	author_email = 'perry.werneck@gmail.com',
	url = 'https://github.com/PerryWerneck/dmiget',
	long_description = '''
This is an extension allowing python application to read data from dmitable using dmi://section/name
''',
	ext_modules = [ dmi ])

