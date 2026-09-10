# To support layered ipk generation

RDK_MW_ARCH ??= "${MACHINE}"

MIDDLEWARE_ARCH = "${RDK_MW_ARCH}-middleware"
PACKAGE_EXTRA_ARCHS:append = " ${MIDDLEWARE_ARCH}"

RELEASE_NUM = "8.7.2.0"

MW_IPK_PATH ?= "middleware-dbg/rdkevd-1128_test_iw_mware"
MW_IPK_SERVER_PATH ?= "${RDK_ARTIFACTS_BASE_URL}/${MW_IPK_PATH}/sky-llama-panel/ipks/debug"

IPK_FEED_URIS += " \ 
                ${MIDDLEWARE_ARCH}##${MW_IPK_SERVER_PATH} "

include ${@'oss_mw.inc' if 'STACK_LAYER_OSS_SUPPORT' in d.getVar('DISTRO_FEATURES').split() else ''}
