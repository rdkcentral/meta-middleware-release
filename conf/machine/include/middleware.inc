# To support layered ipk generation

RDK_MW_ARCH ??= "${MACHINE}"

MIDDLEWARE_ARCH = "${RDK_MW_ARCH}-middleware"
PACKAGE_EXTRA_ARCHS:append = " ${MIDDLEWARE_ARCH}"


# Conditional release number
# MW develop 07/04/2026 base:a97848cb0d8575bf3004091191a01d5ecdf169ef  + OSS 4.12.2 + custome vendor ipks(07/04/2026) with oss 4.12.2
# PR : https://github.com/rdk-e/rdke-middleware-manifest/pull/6886
# MW manifest SHA: fbe409eb94037b4571f2430c6f5201f607b4d3cb
# META_PATCHSET: meta-rdk-video 1afcacb1ed4bba0aec1e72e4399f05699c114e0a
# Deployed ipks for tv-us-middleware-mtk

RELEASE_NUM = "RDKEVD-6333_OSS_4_12_2-r3"

MW_IPK_PATH ?= "middleware-dbg/${RELEASE_NUM}"
MW_IPK_SERVER_PATH ?= "${RDK_ARTIFACTS_BASE_URL}/${MW_IPK_PATH}/${RDK_MW_ARCH}/ipks/debug"

IPK_FEED_URIS += " \ 
                ${MIDDLEWARE_ARCH}##${MW_IPK_SERVER_PATH} "

include ${@'oss_mw.inc' if 'STACK_LAYER_OSS_SUPPORT' in d.getVar('DISTRO_FEATURES').split() else ''}
