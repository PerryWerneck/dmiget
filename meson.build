# Maintainer: Perry Werneck <perry.werneck@gmail.com>

# SPDX-License-Identifier: LGPL-3.0-or-later 

# Copyright (C) 2024 Perry Werneck <perry.werneck@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

project(
	'dmiget', 
	['c', 'cpp'],
	version: '1.2.6',
	default_options : ['c_std=c11', 'cpp_std=c++17'],
	license: 'GPL-3.0-or-later',
)

project_description = 'Library and application to read data from SMBIOS/DMI'

#
# Versioning
#
pkg_version = meson.project_version()
version_array = pkg_version.split('.')
pkg_major_version = version_array[0].to_int()
pkg_minor_version = version_array[1].to_int()
pkg_micro_version = version_array[2].to_int()

#libversion = '@0@.@1@'.format(pkg_major_version,pkg_minor_version)

#
# Compiler flags
#
cxx = meson.get_compiler('cpp')
cc = meson.get_compiler('c')
enable_debug = get_option('debug') or get_option('buildtype').contains('debug')

compiler_flags_common = [
  '-fvisibility=hidden',
  '-DHAVE_CONFIG_H=1',
  '-ggdb3',
  '-ffat-lto-objects',
  '-fPIC',
	]

if enable_debug
  compiler_flags_common += [
	  '-DDEBUG=1'
  ]
else
  compiler_flags_common += [
	'-DNDEBUG=1'
  ]
endif

add_project_arguments(cxx.get_supported_arguments(compiler_flags_common), language: 'cpp')
add_project_arguments(cc.get_supported_arguments(compiler_flags_common), language: 'c')

#
# Configuration
#

app_conf = configuration_data()
app_conf.set_quoted('PACKAGE_NAME', meson.project_name())
app_conf.set_quoted('PACKAGE_VERSION', meson.project_version())
app_conf.set_quoted('PACKAGE_DESCRIPTION', project_description)
app_conf.set('PACKAGE_VERSION_MAJOR', pkg_major_version)
app_conf.set('PACKAGE_VERSION_MINOR', pkg_minor_version)
app_conf.set('PACKAGE_VERSION_MICRO', pkg_micro_version)

app_conf.set('PRODUCT_NAME', meson.project_name())
app_conf.set('PRODUCT_VERSION', meson.project_version())

if cxx.compiles('#include <unistd.h>', name : 'unistd.h')
  app_conf.set('HAVE_UNISTD_H', 1)
endif

config_src = [
  configure_file(
      output : 'config.h', 
      configuration : app_conf
  )
]

#
# Dependencies
#
lib_deps = [
]

app_src = [ 
  'src/dmiget/dmiget.cc' 
]

lib_src = [
  'src/libdmiget/data.cc',
  'src/libdmiget/decoders/baseboard.cc',
  'src/libdmiget/decoders/bios.cc',
  'src/libdmiget/decoders/chassis.cc',
  'src/libdmiget/decoders/integer.cc',
  'src/libdmiget/decoders/memory.cc',
  'src/libdmiget/decoders/probes.cc',
  'src/libdmiget/decoders/processor.cc',
  'src/libdmiget/decoders/string.cc',
  'src/libdmiget/decoders/system.cc',
  'src/libdmiget/decoders/tools.cc',
  'src/libdmiget/decoders/value.cc',
  'src/libdmiget/decoders/table.cc',
  'src/libdmiget/decoders/tpm.cc',
  'src/libdmiget/node/foreach.cc',
  'src/libdmiget/node/iterator.cc',
  'src/libdmiget/node/next.cc',
  'src/libdmiget/node/node.cc',
  'src/libdmiget/value/abstract.cc',
  'src/libdmiget/value/decoded.cc',
  'src/libdmiget/value/iterator.cc',
  'src/libdmiget/value/memsize.cc',
  'src/libdmiget/value/oemstring.cc',
  'src/libdmiget/value/url.cc',
]

includes_dir = include_directories('src/include')

#
# SDK
# https://mesonbuild.com/Pkgconfig-module.html
#
pkg = import('pkgconfig')

if host_machine.system() == 'windows'

  # https://mesonbuild.com/Windows-module.html
  windows = import('windows')
  resources = windows.compile_resources(
    configure_file(
      input : 'src/libdmiget/os/windows/resources.rc.in',
      output : 'resources.rc',
      configuration : app_conf
    )
  )

  lib_src += resources
  app_src += resources

  pkg.generate(
    name: meson.project_name(),
    description: project_description,
    extra_cflags: [ '-I${includedir}/dmiget' ],
    libraries: [ '-ldmiget.dll' ]
  )

  pkg.generate(
    name: meson.project_name() + '-static',
    description: project_description,
    extra_cflags: [ '-I${includedir}/dmiget' ],
    libraries: [ '-ldmiget' ]
  )

  lib_src += [
    'src/libdmiget/os/windows/data.cc',
    'src/libdmiget/os/windows/fromfile.cc',
  ]

	lib_deps += [
	]

else

  pkg.generate(
    name: meson.project_name(),
    description: project_description,
    extra_cflags: [ '-I${includedir}/dmiget' ],
    libraries: [ '-ldmiget' ]
  )

  pkg.generate(
    name: meson.project_name() + '-static',
    description: project_description,
    extra_cflags: [ '-I${includedir}/dmiget' ],
    libraries: [ '-l:libdmiget.a' ]
  )

  lib_src += [
    'src/libdmiget/os/linux/factory.cc',
    'src/libdmiget/os/linux/sysfs.cc',
  ]
	lib_deps += [
	]
endif

#
# Targets
#
if cxx.get_id() == 'msvc'

  static = static_library(
    meson.project_name(), 
    config_src + lib_src,
    install: true,
    dependencies: lib_deps,
    include_directories: includes_dir
  )

  shared_library(
    meson.project_name(), 
    config_src + lib_src,
    install: true,
    dependencies: lib_deps,
    include_directories: includes_dir
  )

  executable(
    meson.project_name(),
    config_src + [ 'src/dmiget/dmiget.cc' ],
    install: true,
    link_with : static,
    install_dir: get_option('bindir'),
    include_directories: includes_dir
  )

else

  dynamic = shared_library(
    meson.project_name(), 
    config_src + lib_src,
    install: true,
    gnu_symbol_visibility: 'hidden',
    dependencies: lib_deps,
    soversion: pkg_major_version,
    include_directories: includes_dir
  )

  static = static_library(
    meson.project_name(), 
    config_src + lib_src,
    install: true,
    dependencies: lib_deps,
    include_directories: includes_dir
  )

  executable(
    meson.project_name(),
    config_src + app_src,
    install: true,
    link_with : dynamic,
    install_dir: get_option('sbindir'),
    include_directories: includes_dir
  )
  
endif

#
# Check for python
#
if not meson.is_cross_build()
  py = dependency('python3',required:false,method : 'pkg-config')
  if py.found()
    import('python').find_installation().extension_module(
      'smbios',
      config_src + [ 
        'src/python/init.c',
        'src/python/memsize.cc',
        'src/python/moduleinfo.cc',
        'src/python/node/methods.cc',
        'src/python/node/type.c',
        'src/python/tools.cc',
        'src/python/value/methods.cc',
        'src/python/value/type.c'
      ],
      install_tag: 'python',
      install: true,
      dependencies: lib_deps + [ py ],
      link_with : static,
      include_directories: includes_dir
    )
  endif
endif

install_headers(
  'src/include/smbios/defs.h', 
  'src/include/smbios/memsize.h', 
  'src/include/smbios/node.h', 
  'src/include/smbios/smbios.h', 
  'src/include/smbios/value.h',
  subdir: 'dmiget/smbios'  
)


