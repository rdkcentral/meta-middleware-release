# To support layered ipk generation

RDK_MW_ARCH ??= "${MACHINE}"

MIDDLEWARE_ARCH = "${RDK_MW_ARCH}-middleware"
PACKAGE_EXTRA_ARCHS:append = " ${MIDDLEWARE_ARCH}"


# Conditional release number
# MW base : 8.5.3.0  + OSS 4.12.2 + custome vendor ipks(07/04/2026) with oss 4.12.2
# PR : https://github.com/rdk-e/rdke-middleware-manifest/pull/6985
# MW manifest SHA: 905b0e466c5264adb1a23eb6f43f1be04a4811d2
# Deployed ipks for tv-us-middleware-mtk

RELEASE_NUM = "RDKEVD-6333_OSS_4_12_2-r4"

MW_IPK_PATH ?= "middleware-dbg/${RELEASE_NUM}"
MW_IPK_SERVER_PATH ?= "${RDK_ARTIFACTS_BASE_URL}/${MW_IPK_PATH}/${RDK_MW_ARCH}/ipks/debug"

IPK_FEED_URIS += " \ 
                ${MIDDLEWARE_ARCH}##${MW_IPK_SERVER_PATH} "

include ${@'oss_mw.inc' if 'STACK_LAYER_OSS_SUPPORT' in d.getVar('DISTRO_FEATURES').split() else ''}
