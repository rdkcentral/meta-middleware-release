# To support layered ipk generation

RDK_MW_ARCH ??= "${MACHINE}"

MIDDLEWARE_ARCH = "${RDK_MW_ARCH}-middleware"
PACKAGE_EXTRA_ARCHS:append = " ${MIDDLEWARE_ARCH}"

RELEASE_NUM = "8.6.2.0"

MW_IPK_PATH ?= "middleware-rel/${RELEASE_NUM}"
#MW_IPK_SERVER_PATH ?= "${RDK_ARTIFACTS_BASE_URL}/${MW_IPK_PATH}/${RDK_MW_ARCH}/ipks/${BUILD_VARIANT}"
MW_IPK_SERVER_PATH ?= "${RDK_ARTIFACTS_BASE_URL}/middleware-dbg/RDKOSS-974-test1/${RDK_MW_ARCH}/ipks/${BUILD_VARIANT}"
CVE_LAYER_FEED_PATH += " ${MIDDLEWARE_ARCH}##${RDK_ARTIFACTS_BASE_URL}/middleware-dbg/RDKOSS-974-test1/${RDK_MW_ARCH}/tarball/cve/debug/xione-uk-middleware.tgz;sha256sum=d9528e3f484cfc645be27f4ef1424681dd8b48f8055f0e76148f52bb460fe759"

IPK_FEED_URIS += " \ 
                ${MIDDLEWARE_ARCH}##${MW_IPK_SERVER_PATH} "

include ${@'oss_mw.inc' if 'STACK_LAYER_OSS_SUPPORT' in d.getVar('DISTRO_FEATURES').split() else ''}
