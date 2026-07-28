# To support layered ipk generation

RDK_MW_ARCH ??= "${MACHINE}"

MIDDLEWARE_ARCH = "${RDK_MW_ARCH}-middleware"
PACKAGE_EXTRA_ARCHS:append = " ${MIDDLEWARE_ARCH}"

RELEASE_NUM = "RDKEVD-6147-mw-cve"

MW_IPK_PATH ?= "middleware-dbg/${RELEASE_NUM}"
MW_IPK_SERVER_PATH ?= "${RDK_ARTIFACTS_BASE_URL}/${MW_IPK_PATH}/${RDK_MW_ARCH}/ipks/${BUILD_VARIANT}"

IPK_FEED_URIS += " \
                ${MIDDLEWARE_ARCH}##${MW_IPK_SERVER_PATH} "

include ${@'oss_mw.inc' if 'STACK_LAYER_OSS_SUPPORT' in d.getVar('DISTRO_FEATURES').split() else ''}

CVE_PATH = "tarball/cve"
MW_CVE_SHA:prod-variant ?= "9fe7e309eb872e5a884421a18efb1c0c56dd02ce8e88bb2cd2fcfaa94c069e7a"
MW_CVE_SHA:prodlog-variant ?= "c9f4f44bac6829c77787322aa37c14b2a9338c5d7ef4c498e5ad1ab7a035a469"
MW_CVE_SHA = "24d5e1cd5d1d9b892b136ee837bc8825d38494fc4a08ffb72331d166e5c3ee34"
CVE_LAYER_FEED_PATH:append = " ${@bb.utils.contains('INHERIT', 'cve-check', '${MIDDLEWARE_ARCH}##${RDK_ARTIFACTS_BASE_URL}/${MW_IPK_PATH}/${RDK_MW_ARCH}/${CVE_PATH}/${BUILD_VARIANT}/${MIDDLEWARE_ARCH}.tgz;sha256sum=${MW_CVE_SHA}', '', d)} "
