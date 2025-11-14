# To support layered ipk generation

RDK_MW_ARCH ??= "${MACHINE}"

MIDDLEWARE_ARCH = "${RDK_MW_ARCH}-middleware"
PACKAGE_EXTRA_ARCHS:append = " ${MIDDLEWARE_ARCH}"

RELEASE_NUM = "8.4.1.1"

MW_IPK_PATH ?= "middleware-rel/${RELEASE_NUM}"
MW_IPK_SERVER_PATH ?= "https://partners.artifactory.comcast.com/artifactory/middleware-dbg/RDKEVD-4161/rdktv-us-armv8a/ipks/debug"

IPK_FEED_URIS += " \ 
                ${MIDDLEWARE_ARCH}##${MW_IPK_SERVER_PATH} "

include ${@'oss_mw.inc' if 'STACK_LAYER_OSS_SUPPORT' in d.getVar('DISTRO_FEATURES').split() else ''}
