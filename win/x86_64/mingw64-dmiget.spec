#
# spec file for package mingw64-dmiget
#
# Copyright (c) 2015 SUSE LINUX GmbH, Nuernberg, Germany.
# Copyright (C) <2008> <Banco do Brasil S.A.>
#
# All modifications and additions to the file contributed by third parties
# remain the property of their copyright owners, unless otherwise agreed
# upon. The license for this file, and modifications and additions to the
# file, is the same license as for the pristine package itself (unless the
# license for the pristine package is not an Open Source License, in which
# case the license is the MIT License). An "Open Source License" is a
# license that conforms to the Open Source Definition (Version 1.9)
# published by the Open Source Initiative.

# Please submit bugfixes or comments via http://bugs.opensuse.org/
#

%define __strip %{_mingw64_strip}
%define __objdump %{_mingw64_objdump}
%define __find_requires %{_mingw64_findrequires}
%define __find_provides %{_mingw64_findprovides}
%define _use_internal_dependency_generator to 0
%define __os_install_post %{_mingw64_debug_install_post} \
                          %{_mingw64_install_post}

Summary:		Get DMI information using URL format
Name:			mingw64-dmiget
Version:		1.0
Release:		0
License:		LGPL-3.0
Source:			dmiget-%{version}.tar.xz
BuildArch:		noarch

URL:			https://github.com/PerryWerneck/dmiget.git

Group:			Development/Libraries/C and C++
BuildRoot:		/var/tmp/%{name}-%{version}

BuildRequires:	autoconf >= 2.61
BuildRequires:	automake
BuildRequires:	libtool
BuildRequires:	coreutils

BuildRequires:	mingw64-cross-binutils
BuildRequires:	mingw64-cross-gcc-c++ >= 9.0
BuildRequires:	mingw64-cross-pkg-config
BuildRequires:	mingw64-filesystem

%description
Tool to get information from DMI table using an url-like format.

%define MAJOR_VERSION %(echo %{version} | cut -d. -f1)
%define MINOR_VERSION %(echo %{version} | cut -d. -f2 | cut -d+ -f1)
%define _libvrs %{MAJOR_VERSION}_%{MINOR_VERSION}

%package -n mingw64-libdmiget%{_libvrs}
Summary:    Core library for %{name}
Group:      Development/Libraries/C and C++

%description -n mingw64-libdmiget%{_libvrs}
C++ library to get DMI information using an URL-like format.

%{_mingw64_debug_package}

%package devel
Summary:    C++ development files for lib%{name}
Group:      Development/Libraries/C and C++
Requires:	mingw64-libdmiget%{_libvrs} = %{version}

%description devel
Header files for the %{name} library.

#---[ Build & Install ]-----------------------------------------------------------------------------------------------

%prep
%setup -n dmiget-%{version}

NOCONFIGURE=1 \
	./autogen.sh

%{_mingw64_configure}

%build
make all %{?_smp_mflags}

%install
%{_mingw64_make} DESTDIR=%{buildroot} install

%files
%doc README.md
%license LICENSE
%defattr(-,root,root)
%dir %{_mingw64_sbindir}
%{_mingw64_sbindir}/dmiget.exe

%files -n mingw64-libdmiget%{_libvrs}
%defattr(-,root,root)
%doc README.md
%license LICENSE
%{_mingw64_bindir}/*.dll

%files devel
%doc README.md
%license LICENSE
%defattr(-,root,root)
%{_mingw64_libdir}/pkgconfig/*.pc
%{_mingw64_libdir}/*.a
%dir %{_mingw64_includedir}/dmiget
%{_mingw64_includedir}/dmiget/*.h

%exclude %{_mingw64_datadir}/dmiget

%changelog


