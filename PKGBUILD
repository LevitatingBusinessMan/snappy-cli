#Maintainer: Rein Fernhout (LevitatingBusinessMan) <public@reinfernhout.xyz>

pkgname=snappy-cli
pkgver=27319b2
arch=("x86_64")
pkgrel=1
pkgdesc="A cli utility for compressing files via snappy"
license=("MIT")
makedepends=("git")
url="https://github.com/LevitatingBusinessMan/snappy-cli"
source=("git+https://github.com/LevitatingBusinessMan/snappy-cli.git")
sha256sums=("SKIP")

pkgver() {
	cd "${srcdir}/${pkgname}"
	git rev-parse --short HEAD
}

build() {
    cd "${srcdir}/${pkgname}"
    make
}

package() {
 	cd "${srcdir}/${pkgname}"
    DESTDIR="$pkgdir" make install
}
