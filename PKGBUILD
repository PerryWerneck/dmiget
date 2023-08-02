# Maintainer: Perry Werneck <perry.werneck@gmail.com>

pkgname=dmiget

pkgver=1.1
pkgrel=0
pkgdesc="Get DMI information using URL format"
url="https://github.com/PerryWerneck/dmiget"
arch=(i686 x86_64)
license=(GPL)
depends=(openssl)
makedepends=(autoconf automake make python)
checkdepends=()

#groups=(gnome)

source=($pkgname-$pkgver.tar.xz)
sha256sums=('SKIP')

provides=($pkgname) 
conflicts=($pkgname)

prepare() {
  cd $pkgname-$pkgver
  mkdir -p scripts
  touch scripts/config.rpath
  NOCONFIGURE=1 ./autogen.sh
  ./configure --prefix=/usr
}

build() {
  cd $pkgname-$pkgver
  make all
}

package() {
  cd $pkgname-$pkgver
  DESTDIR="$pkgdir" make install
}


