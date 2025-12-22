# To support layered ipk generation

RDK_MW_ARCH ??= "${MACHINE}"

MIDDLEWARE_ARCH = "${RDK_MW_ARCH}-middleware"
PACKAGE_EXTRA_ARCHS:append = " ${MIDDLEWARE_ARCH}"

# Base MW tag used = 8.4.2.1
# https://github.com/rdk-e/rdke-middleware-manifest/commits/bbe259ee6f4d4f58c6fe68cd20b0cd46818736c0
# MW IPKs deployed = MW 8.4.2.1 + OSS 4.9.0
# https://github.com/rdk-e/rdke-middleware-manifest/pull/5822  commit id a8d5c94a89bc34e278af3302c20a5b8c9bf7eca1

RELEASE_NUM = "RDKEVD-3974-MW-8-4-2-1-r0"

MW_IPK_PATH ?= "middleware-dbg/${RELEASE_NUM}"
MW_IPK_SERVER_PATH ?= "${RDK_ARTIFACTS_BASE_URL}/${MW_IPK_PATH}/${RDK_MW_ARCH}/ipks/${BUILD_VARIANT}"

IPK_FEED_URIS += " \ 
                ${MIDDLEWARE_ARCH}##${MW_IPK_SERVER_PATH} "

include ${@'oss_mw.inc' if 'STACK_LAYER_OSS_SUPPORT' in d.getVar('DISTRO_FEATURES').split() else ''}
