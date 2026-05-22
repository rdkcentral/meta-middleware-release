# To support layered ipk generation

RDK_MW_ARCH ??= "${MACHINE}"

MIDDLEWARE_ARCH = "${RDK_MW_ARCH}-middleware"
PACKAGE_EXTRA_ARCHS:append = " ${MIDDLEWARE_ARCH}"

# MW from develop( 8.6.1.0 ++) + integrated OSS 4.13.0 + vendor ipks(with OSS 4.13.0)
# ++ there are 2 dependent meta MW layer changes from 
# 1. meta-rdk(PR#655) bce224d22d32648ca98e7135a206f4b17cf3cd7b(ported: 127c80ba28d74baa99301fc0cc81a018589c4f88) and
# 2. meta-rdk-video(PR#2662) c900e4998d3ab4ea680c6b7422b40cd046e56430 (ported: 90a2b017c749536be2bfb710e48e1d2ed36ce39c)
# MW base SHA used from develop: 1fc963fed124bc77188498da844f61fa160a5162
# MW base SHA used from develop: 245fa07e7d0890b30761b8e43034481b2b9a8748
# MW PR: https://github.com/rdk-e/rdke-middleware-manifest/pull/7486
# MW PR#7486 SHA used in deploying ipks: c47deb28dea199862e657f9115b6a27f31cbed1b

RELEASE_NUM = "RDKEVD-7510-r0"

MW_IPK_PATH ?= "middleware-dbg/${RELEASE_NUM}"
MW_IPK_SERVER_PATH ?= "${RDK_ARTIFACTS_BASE_URL}/${MW_IPK_PATH}/${RDK_MW_ARCH}/ipks/debug"

IPK_FEED_URIS += " \ 
                ${MIDDLEWARE_ARCH}##${MW_IPK_SERVER_PATH} "

include ${@'oss_mw.inc' if 'STACK_LAYER_OSS_SUPPORT' in d.getVar('DISTRO_FEATURES').split() else ''}
