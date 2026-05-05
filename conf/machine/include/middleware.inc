# Support layered IPK generation

RDK_MW_ARCH ??= "${MACHINE}"
MIDDLEWARE_ARCH = "${RDK_MW_ARCH}-middleware"
PACKAGE_EXTRA_ARCHS:append = " ${MIDDLEWARE_ARCH}"

RELEASE_NUM = "8.6.1.0"

MW_IPK_PATH = "middleware-dbg/RDKEMW-15137"
MW_IPK_SERVER_PATH = "${RDK_ARTIFACTS_BASE_URL}/${MW_IPK_PATH}/${MACHINE}/ipks/debug"

IPK_FEED_URIS += "${MIDDLEWARE_ARCH}##${MW_IPK_SERVER_PATH}"

include ${@'oss_mw.inc' if 'STACK_LAYER_OSS_SUPPORT' in (d.getVar('DISTRO_FEATURES') or '').split() else ''}
