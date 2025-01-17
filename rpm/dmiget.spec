#
# spec file for package dmiget
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
Name:			dmiget
Version: 1.2.6
Release:		0
License:		LGPL-3.0
Source:			%{name}-%{version}.tar.xz

URL:			https://github.com/PerryWerneck/dmiget.git

Group:			Development/Libraries/C and C++
BuildRoot:		/var/tmp/%{name}-%{version}

BuildRequires:	binutils
BuildRequires:	coreutils

%if "%{_vendor}" == "debbuild"
BuildRequires:  meson-deb-macros
BuildRequires:  python3-dev
%else
BuildRequires:	gcc-c++ >= 5
%endif

BuildRequires:  meson >= 0.61.4

%description
Tool to get information from DMI table using an url-like format.

%define MAJOR_VERSION %(echo %{version} | cut -d. -f1)
%define MINOR_VERSION %(echo %{version} | cut -d. -f2 | cut -d+ -f1)
%define _libvrs %{MAJOR_VERSION}

%package -n lib%{name}%{_libvrs}
Summary:    Core library for %{name}
Group:      Development/Libraries/C and C++

%if "%{_vendor}" == "debbuild"
Provides:   lib%{name}%{_libvrs} = %{version}
%endif

%description -n lib%{name}%{_libvrs}
C++ library to get DMI information using an URL-like format.

%package devel
Summary:    C++ development files for lib%{name}
Requires:   lib%{name}%{_libvrs} = %{version}
Group:      Development/Libraries/C and C++

%if "%{_vendor}" == "debbuild"
Provides:  libdmiget-dev
%endif

%description devel
Header files for the %{name} library.

#---[ Build & Install ]-----------------------------------------------------------------------------------------------

%prep
%autosetup
%meson

%build
%meson_build

%install
%meson_install

%files
%defattr(-,root,root)
%{_sbindir}/dmiget

%files -n lib%{name}%{_libvrs}
%defattr(-,root,root)
%doc README.md
%license LICENSE
%{_libdir}/lib*.so.%{MAJOR_VERSION}

%files devel
%defattr(-,root,root)
%{_libdir}/lib*.so
%{_libdir}/lib*.a
%dir %{_includedir}/%{name}
%dir %{_includedir}/%{name}/smbios
%{_includedir}/%{name}/smbios/*.h
%{_libdir}/pkgconfig/*.pc

%post -n lib%{name}%{_libvrs} -p /sbin/ldconfig
%postun -n lib%{name}%{_libvrs} -p /sbin/ldconfig

%changelog


