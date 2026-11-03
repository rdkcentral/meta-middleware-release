# To support layered ipk generation

RDK_MW_ARCH ??= "${MACHINE}"

MIDDLEWARE_ARCH = "${RDK_MW_ARCH}-middleware"
PACKAGE_EXTRA_ARCHS:append = " ${MIDDLEWARE_ARCH}"

##############################################
# OSS 4.15.0 integration in MTK
# MW realse used : 8.7.3.1 as base.
# Integared OSS 4.15.0 related changes
# PR: https://github.com/rdk-e/rdke-middleware-manifest/pull/9039
# Custom vendor ipks are used for this.
# To consume vendor ipks please update in MW build at UPDATE_LOCAL_CONF with VENDOR_IPK_ARTIFACTS_DIR_PATH="xumo-mt120v1-dbg/RDKEVD-10162-r1"
# Ticket: https://ccp.sys.comcast.net/browse/RDKEVD-10162
##############################################

RELEASE_NUM = "RDKEVD-10162-r1"

MW_IPK_PATH ?= "middleware-dbg/${RELEASE_NUM}"
MW_IPK_SERVER_PATH ?= "${RDK_ARTIFACTS_BASE_URL}/${MW_IPK_PATH}/${RDK_MW_ARCH}/ipks/${BUILD_VARIANT}"

IPK_FEED_URIS += " \ 
                ${MIDDLEWARE_ARCH}##${MW_IPK_SERVER_PATH} "

include ${@'oss_mw.inc' if 'STACK_LAYER_OSS_SUPPORT' in d.getVar('DISTRO_FEATURES').split() else ''}
