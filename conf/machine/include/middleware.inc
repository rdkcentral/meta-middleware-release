# To support layered ipk generation

RDK_MW_ARCH ??= "${MACHINE}"

MIDDLEWARE_ARCH = "${RDK_MW_ARCH}-middleware"
PACKAGE_EXTRA_ARCHS:append = " ${MIDDLEWARE_ARCH}"

#MW is taken from develop(8.7.2.0 ++) 15th September 2026
#Base develop SHA used from develop is 0c07d7779f8e07f7ed7ca2e2062af01cf24a0751
#MW PR is https://github.com/rdk-e/rdke-middleware-manifest/pull/8600
#MW SHA used for deploying MW ipks is 2772bd74d007ce6817eac0b51c94bf98b4673ffe
#Vendor ipks consumed in MW are from release/8.7-3.0.0

RELEASE_NUM = "RDKEVD-9291-r0"

MW_IPK_PATH ?= "middleware-dbg/${RELEASE_NUM}"
MW_IPK_SERVER_PATH ?= "${RDK_ARTIFACTS_BASE_URL}/${MW_IPK_PATH}/${RDK_MW_ARCH}/ipks/${BUILD_VARIANT}"

IPK_FEED_URIS += " \ 
                ${MIDDLEWARE_ARCH}##${MW_IPK_SERVER_PATH} "

include ${@'oss_mw.inc' if 'STACK_LAYER_OSS_SUPPORT' in d.getVar('DISTRO_FEATURES').split() else ''}
