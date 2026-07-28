# To support layered ipk generation

RDK_MW_ARCH ??= "${MACHINE}"

MIDDLEWARE_ARCH = "${RDK_MW_ARCH}-middleware"
PACKAGE_EXTRA_ARCHS:append = " ${MIDDLEWARE_ARCH}"

RELEASE_NUM = "RDKEVD-6147-mw-t3"

MW_IPK_PATH ?= "middleware-dbg/${RELEASE_NUM}"
MW_IPK_SERVER_PATH ?= "${RDK_ARTIFACTS_BASE_URL}/${MW_IPK_PATH}/${RDK_MW_ARCH}/ipks/${BUILD_VARIANT}"

IPK_FEED_URIS += " \
                ${MIDDLEWARE_ARCH}##${MW_IPK_SERVER_PATH} "

include ${@'oss_mw.inc' if 'STACK_LAYER_OSS_SUPPORT' in d.getVar('DISTRO_FEATURES').split() else ''}

CVE_LAYER_FEED_PATH += "${MIDDLEWARE_ARCH}##${RDK_ARTIFACTS_BASE_URL}/middleware-dbg/RDKEVD-6147-mw-t3/rdktv-us-armv8a/tarball/cve/debug/rdktv-us-armv8a-middleware.tgz;sha256sum=1cbb6d4534c7f18c699b642a9edece77575b25e387e9bcc19d4325969e346b18"
