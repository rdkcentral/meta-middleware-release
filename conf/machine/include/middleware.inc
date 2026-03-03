# To support layered ipk generation

RDK_MW_ARCH ??= "${MACHINE}"

MIDDLEWARE_ARCH = "${RDK_MW_ARCH}-middleware"
PACKAGE_EXTRA_ARCHS:append = " ${MIDDLEWARE_ARCH}"

# Conditional release number
# MW develop 13/03/2026 base:a50b698aa25ee8e3fa0ea5178db52024451b9345 + OSS 4.12.0 + custome vendor ipks with oss 4.12.0
# PR : https://github.com/rdk-e/rdke-middleware-manifest/pull/6745
# MW manifest SHA: fb70c483fe695075096a43425a71804cbeb46a36
# META_PATCHSET: meta-middleware-cspc-support 764115d981d17d36f2689d8831d9e5096649e16f |meta-middleware-development a6e6d197b195a33816ff268e421d071ec461d0f5| meta-rdk-video 347144511c9d04024a7a52c4ae413bbb1fd845a5
# Note: The RELEASE_NUM is same for all Xumotv platforms.
#       Deployed ipks for TV-US-Middleware, TV-US-Multilib-Multilib, TV-UK-Middleware, and TV-UK-Multilib-Multilib.

RELEASE_NUM = "RDKEVD-6153_OSS_4_12_0-r8"

MW_IPK_PATH = "middleware-dbg/${RELEASE_NUM}"
MW_IPK_SERVER_PATH ?= "${RDK_ARTIFACTS_BASE_URL}/${MW_IPK_PATH}/${RDK_MW_ARCH}/ipks/debug"

IPK_FEED_URIS += " \ 
                ${MIDDLEWARE_ARCH}##${MW_IPK_SERVER_PATH} "

include ${@'oss_mw.inc' if 'STACK_LAYER_OSS_SUPPORT' in d.getVar('DISTRO_FEATURES').split() else ''}
