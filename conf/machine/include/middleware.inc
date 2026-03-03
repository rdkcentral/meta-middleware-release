# To support layered ipk generation

RDK_MW_ARCH ??= "${MACHINE}"

MIDDLEWARE_ARCH = "${RDK_MW_ARCH}-middleware"
PACKAGE_EXTRA_ARCHS:append = " ${MIDDLEWARE_ARCH}"

# Conditional release number
RELEASE_REV = "r5"

RELEASE_NUM_ML  = "RDKEVD-6153_OSS_4_12_0_ml-${RELEASE_REV}"
RELEASE_NUM_NML = "RDKEVD-6153_OSS_4_12_0_nml-${RELEASE_REV}"

RELEASE_NUM = "${@ d.getVar('RELEASE_NUM_ML') \
    if d.getVar('RDK_MW_ARCH') == 'rdktv-us-armv8a' \
    else d.getVar('RELEASE_NUM_NML') }"

MW_IPK_PATH ?= "middleware-dbg/${RELEASE_NUM}"
MW_IPK_SERVER_PATH ?= "${RDK_ARTIFACTS_BASE_URL}/${MW_IPK_PATH}/${RDK_MW_ARCH}/ipks/${BUILD_VARIANT}"

IPK_FEED_URIS += " \ 
                ${MIDDLEWARE_ARCH}##${MW_IPK_SERVER_PATH} "

include ${@'oss_mw.inc' if 'STACK_LAYER_OSS_SUPPORT' in d.getVar('DISTRO_FEATURES').split() else ''}
