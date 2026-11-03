# To support layered ipk generation

RDK_MW_ARCH ??= "${MACHINE}"

MIDDLEWARE_ARCH = "${RDK_MW_ARCH}-middleware"
PACKAGE_EXTRA_ARCHS:append = " ${MIDDLEWARE_ARCH}"

##############################################
# MW latest release used : 8.7.3.1 as base for OSS 4.15.0 integration.
# Integrated OSS 4.15.0 related changes in MW manifest.
# MW PR: https://github.com/rdk-e/rdke-middleware-manifest/pull/9039
# Included changes from following dependent PRs during middleware integration. (as mentioned on OSS release notes)
#     https://github.com/rdkcentral/meta-rdk/pull/1243/
#     https://github.com/rdkcentral/rdke-middleware-generic-manifest/pull/2368
# Custom vendor ipks are used for this.
# To consume vendor ipks please update in MW build at "UPDATE_LOCAL_CONF" field with VENDOR_IPK_ARTIFACTS_DIR_PATH="xumo-mt120v1-dbg/RDKEVD-10162-r1"
# In the MW build updated the following meta layer versions to match with vendor. Applied the same in build through "META_PATCHSET" field.
#     meta-rdk-halif-headers refs/tags/5.1.0 | meta-stack-layering-support refs/tags/5.0.4
# Ticket: https://ccp.sys.comcast.net/browse/RDKEVD-10162
##############################################

RELEASE_NUM = "RDKEVD-10162-r4"

MW_IPK_PATH ?= "middleware-dbg/${RELEASE_NUM}"
MW_IPK_SERVER_PATH ?= "${RDK_ARTIFACTS_BASE_URL}/${MW_IPK_PATH}/${RDK_MW_ARCH}/ipks/${BUILD_VARIANT}"

IPK_FEED_URIS += " \ 
                ${MIDDLEWARE_ARCH}##${MW_IPK_SERVER_PATH} "

include ${@'oss_mw.inc' if 'STACK_LAYER_OSS_SUPPORT' in d.getVar('DISTRO_FEATURES').split() else ''}
