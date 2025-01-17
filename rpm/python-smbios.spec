#
# spec file for package python-smbios
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

%define skip_python2 1

%{?!python_module:%define python_module() python-%{**} python3-%{**}}

Summary:		Python module to get data from smbios
Name:			python-smbios
Version: 1.2.7
Release:		0
License:		GPL-2.0
Source:			dmiget-%{version}.tar.xz
URL:			https://github.com/PerryWerneck/dmiget
Group:			Development/Libraries/Python

BuildRoot:		/var/tmp/%{name}-%{version}

BuildRequires:	autoconf >= 2.61
BuildRequires:	automake
BuildRequires:	binutils
BuildRequires:	coreutils
BuildRequires:	gcc-c++
BuildRequires:	m4
BuildRequires:	pkgconfig
BuildRequires:	fdupes
BuildRequires:	%{pythons}
BuildRequires:	libtool

BuildRequires:  python-rpm-macros
BuildRequires:	pkgconfig(python3)

BuildRequires:	%{python_module devel}
BuildRequires:	%{python_module setuptools}

%python_subpackages

%description
This is an extension allowing smbios access for python applications.

%prep

%setup -n dmiget-%{version}

NOCONFIGURE=1 ./autogen.sh

%configure

%build
%python_build

%install
%python_install
%fdupes %buildroot

%files %python_files
%defattr(-,root,root)

# https://en.opensuse.org/openSUSE:Packaging_for_Leap#RPM_Distro_Version_Macros
%doc README.md
%license LICENSE

%{python_sitearch}/*.so
%{python_sitearch}/*-info

%exclude %{python_sitearch}/include/*
%exclude %{python_sitearch}/libdmiget/*
%exclude %{python_sitearch}/python/*.c
%exclude %{python_sitearch}/python/*.cc
%exclude %{python_sitearch}/python/node/*
%exclude %{python_sitearch}/python/value/*



%changelog

