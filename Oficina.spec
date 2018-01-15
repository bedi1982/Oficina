#
# spec file for package Oficina
#
# Copyright (c) 2018 - Sergio Rafael Lemke <srlemke@protonmail.com>
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

Name:           Oficina
License:        BSD 3-Clause
Group:          Productivity
Version:        0.2
Release:        1
Summary:        Mechanical Workshop
Url:            https://github.com/bedi1982/Oficina
Source:		Oficina-0.2.tar.bz2
Buildroot:      %{buildroot}/%{name/%{version}}
Buildrequires:	libqt5-qtbase-common-devel
Buildrequires:	libQt5Widgets-devel
Buildrequires:	libQt5Sql-devel

Requires: mysql

%description
Oficina - A mechanical workshop application.

Authors:
--------
Sergio Rafael Lemke <srlemke@protonmail.com>

%prep
%setup -q -n %name-%version

%build
qmake-qt5
make

%install
mkdir -p %{buildroot}%{_bindir}
mkdir -p %{buildroot}%{_datadir}/applications
mkdir -p %{buildroot}%{_datadir}/pixmaps

install -m 0755 Oficina.png %{buildroot}%{_datadir}/pixmaps
install -m 0755	Oficina %{buildroot}%{_bindir}
install -m 0755 Oficina.desktop %{buildroot}%{_datadir}/applications/

%files
%{_bindir}/Oficina
%{_datadir}/applications/Oficina.desktop
%{_datadir}/pixmaps/Oficina.png
