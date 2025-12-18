# To support layered ipk generation

RDK_MW_ARCH ??= "${MACHINE}"

MIDDLEWARE_ARCH = "${RDK_MW_ARCH}-middleware"
PACKAGE_EXTRA_ARCHS:append = " ${MIDDLEWARE_ARCH}"

#Add new OSS consumption distro for xione & xutom-tvs  until it is defaulted.
DISTRO_FEATURES:append:rdktv-us-armv7a = " STACK_LAYER_OSS_SUPPORT"
DISTRO_FEATURES:append:rdktv-us-armv8a = " STACK_LAYER_OSS_SUPPORT"
DISTRO_FEATURES:append:xione-uk = " STACK_LAYER_OSS_SUPPORT"
DISTRO_FEATURES:append:xione-alpaca-de = " STACK_LAYER_OSS_SUPPORT"
DISTRO_FEATURES:append:xione-de = " STACK_LAYER_OSS_SUPPORT"
DISTRO_FEATURES:append:xione-foxtel = " STACK_LAYER_OSS_SUPPORT"
DISTRO_FEATURES:append:xfinity-stream-box = " STACK_LAYER_OSS_SUPPORT"
DISTRO_FEATURES:append:wnc-xfinity-stream-box = " STACK_LAYER_OSS_SUPPORT"

RELEASE_NUM = "8.4.3.0"

MW_IPK_PATH ?= "middleware-rel/${RELEASE_NUM}"
MW_IPK_SERVER_PATH ?= "${RDK_ARTIFACTS_BASE_URL}/${MW_IPK_PATH}/${RDK_MW_ARCH}/ipks/${BUILD_VARIANT}"

IPK_FEED_URIS += " \ 
                ${MIDDLEWARE_ARCH}##${MW_IPK_SERVER_PATH} "

include ${@'oss_mw.inc' if 'STACK_LAYER_OSS_SUPPORT' in d.getVar('DISTRO_FEATURES').split() else ''}
