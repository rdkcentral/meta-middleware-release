# To support layered ipk generation

RDK_MW_ARCH ??= "${MACHINE}"

MIDDLEWARE_ARCH = "${RDK_MW_ARCH}-middleware"
PACKAGE_EXTRA_ARCHS:append = " ${MIDDLEWARE_ARCH}"

# Conditional release number
# MW 8.5.2.0 + OSS 4.12.0 + custome vendor ipks with oss 4.12.0
# PR : https://github.com/rdk-e/rdke-middleware-manifest/pull/6564
# MW manifest SHA: 97d934e31d51eaffaf49a953df4a821e0e2ca389
# META_PATCHSET: meta-middleware-cspc-support 8ab0cbd6347144c5c380be9a465672080c7d6333|meta-middleware-development 6363d6097bf89bd4d43f4b453b018fe6c2485e29
# Note:the RELEASE_NUM is same for all Xumotv platforms except TV-UK-middleware multi-lib, since that is not deployed yet.

RELEASE_NUM = "RDKEVD-6153_OSS_4_12_0_nml-r5"

MW_IPK_PATH ?= "middleware-dbg/${RELEASE_NUM}"
MW_IPK_SERVER_PATH ?= "${RDK_ARTIFACTS_BASE_URL}/${MW_IPK_PATH}/${RDK_MW_ARCH}/ipks/${BUILD_VARIANT}"

IPK_FEED_URIS += " \ 
                ${MIDDLEWARE_ARCH}##${MW_IPK_SERVER_PATH} "

include ${@'oss_mw.inc' if 'STACK_LAYER_OSS_SUPPORT' in d.getVar('DISTRO_FEATURES').split() else ''}
