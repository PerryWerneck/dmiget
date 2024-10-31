project(
	'dmiget', 
	['c', 'cpp'],
	version: '1.2.2',
	default_options : ['c_std=c11', 'cpp_std=c++17'],
	license: 'GPL-3.0-or-later',
)

project_description = 'Library and application to read data from SMBIOS/DMI'
library_name = meson.project_name()

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

if cxx.get_id() == 'msvc'
  # Avoiding error 'LNK1149: output filename matches input filename'
  library_name = 'lib' + meson.project_name()
endif

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
# SDK
#
sdk_conf = configuration_data()
sdk_conf.set('PACKAGE_NAME', meson.project_name())
sdk_conf.set('PACKAGE_VERSION', meson.project_version())
sdk_conf.set('PACKAGE_DESCRIPTION', project_description)
sdk_conf.set('PACKAGE_VERSION_MAJOR', pkg_major_version)
sdk_conf.set('PACKAGE_VERSION_MINOR', pkg_minor_version)
sdk_conf.set('PACKAGE_VERSION_MICRO', pkg_micro_version)
sdk_conf.set('prefix',get_option('prefix'))
sdk_conf.set('exec_prefix',get_option('prefix'))
sdk_conf.set('includedir',get_option('includedir'))
sdk_conf.set('libdir',get_option('libdir'))

if host_machine.system() == 'windows'
  sdk_conf.set('REQUIRES','')
  sdk_conf.set('DYNLIBS','-ldmiget.dll')
  sdk_conf.set('STATICLIBS','-ldmiget')
else
  sdk_conf.set('REQUIRES','')
  sdk_conf.set('DYNLIBS','-ldmiget')
  sdk_conf.set('STATICLIBS','-l:libdmiget.a')
endif

configure_file(
  input : 'sdk/dynamic.pc.in',
  output : meson.project_name() + '.pc',
  install: true,
  install_dir: get_option('libdir') + '/pkgconfig',
  configuration : sdk_conf
)

configure_file(
  input : 'sdk/static.pc.in',
  output : meson.project_name() + '-static.pc',
  install: true,
  install_dir: get_option('libdir') + '/pkgconfig',
  configuration : sdk_conf
)

includes_dir = include_directories('src/include')

#
# Dependencies
#
lib_deps = [
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

if host_machine.system() == 'windows'
  lib_src += [
    'src/libdmiget/os/windows/data.cc',
    'src/libdmiget/os/windows/fromfile.cc',
  ]
	lib_deps += [
	]
else
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
  library_name, 
  config_src + lib_src,
	install: true,
	dependencies: lib_deps,
	include_directories: includes_dir
)

#
# Check for python
#
py = dependency('python3',required:false)
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

executable(
	'dmiget',
	config_src + [ 'src/dmiget/dmiget.cc' ],
  install: true,
	link_with : dynamic,
  install_dir: get_option('sbindir'),
	include_directories: includes_dir
)

install_headers(
  'src/include/smbios/defs.h', 
  'src/include/smbios/memsize.h', 
  'src/include/smbios/node.h', 
  'src/include/smbios/smbios.h', 
  'src/include/smbios/value.h',
  subdir: 'dmiget/smbios'  
)


