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

Summary:		Get DMI information using URL format
Name:			mingw64-dmiget
Version: 1.2.6
Release:		0
License:		LGPL-3.0
Source:			dmiget-%{version}.tar.xz
BuildArch:		noarch

URL:			https://github.com/PerryWerneck/dmiget.git

Group:			Development/Libraries/C and C++
BuildRoot:		/var/tmp/%{name}-%{version}

BuildRequires:  mingw64-cross-meson
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

%package devel
Summary:	C++ development files for lib%{name}
Group:		Development/Libraries/C and C++
Requires:	mingw64-libdmiget%{_libvrs} = %{version}
Provides:	mingw64(lib::libdmiget.a)

%description devel
Header files for the %{name} library.

#---[ Build & Install ]-----------------------------------------------------------------------------------------------

%prep
%autosetup
%_mingw64_meson

%build
%_mingw64_meson_build

%install
%_mingw64_meson_install

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
%defattr(-,root,root)
%doc README.md
%license LICENSE
%{_mingw64_libdir}/pkgconfig/*.pc
%{_mingw64_libdir}/*.a
%dir %{_mingw64_includedir}/dmiget
%dir %{_mingw64_includedir}/dmiget/smbios
%{_mingw64_includedir}/dmiget/smbios/*.h

%exclude %{_mingw64_datadir}/dmiget

%changelog


