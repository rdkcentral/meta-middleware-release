# To support layered ipk generation

RDK_MW_ARCH ??= "${MACHINE}"

MIDDLEWARE_ARCH = "${RDK_MW_ARCH}-middleware"
PACKAGE_EXTRA_ARCHS:append = " ${MIDDLEWARE_ARCH}"

#Add new OSS consumption distro till it is defaulted
DISTRO_FEATURES:append:xione-bcm-flex2 = " STACK_LAYER_OSS_SUPPORT"
DISTRO_FEATURES:append:xione-bcm-xoe = " STACK_LAYER_OSS_SUPPORT"
DISTRO_FEATURES:append:xione-bcm-uk = " STACK_LAYER_OSS_SUPPORT"

RELEASE_NUM = "8.4.4.1_B1"

MW_IPK_PATH ?= "middleware-dbg/${RELEASE_NUM}"
MW_IPK_SERVER_PATH ?= "${RDK_ARTIFACTS_BASE_URL}/${MW_IPK_PATH}/${RDK_MW_ARCH}/ipks/${BUILD_VARIANT}"

IPK_FEED_URIS += " \ 
                ${MIDDLEWARE_ARCH}##${MW_IPK_SERVER_PATH} "

include ${@'oss_mw.inc' if 'STACK_LAYER_OSS_SUPPORT' in d.getVar('DISTRO_FEATURES').split() else ''}
