# To support layered ipk generation

RDK_MW_ARCH ??= "${MACHINE}"

MIDDLEWARE_ARCH = "${RDK_MW_ARCH}-middleware"
PACKAGE_EXTRA_ARCHS:append = " ${MIDDLEWARE_ARCH}"

RELEASE_NUM = "8.6.3.0"

MW_IPK_PATH ?= "middleware-rel/${RELEASE_NUM}"
MW_IPK_SERVER_PATH ?= "${RDK_ARTIFACTS_BASE_URL}/${MW_IPK_PATH}/${RDK_MW_ARCH}/ipks/${BUILD_VARIANT}"

IPK_FEED_URIS += " \ 
                ${MIDDLEWARE_ARCH}##${MW_IPK_SERVER_PATH} "

include ${@'oss_mw.inc' if 'STACK_LAYER_OSS_SUPPORT' in d.getVar('DISTRO_FEATURES').split() else ''}

#The following section will be only enabled if CVE_CHECK is set

# Check whether CVE-check is globally inherited
CVE_CHECK_ENABLED = "${@bb.utils.contains('INHERIT', 'cve-check', '1', '0', d)}"

# Conditionally include CVE-specific configuration
CVE_CONF_INCLUDE = "${@bb.utils.contains('CVE_CHECK_ENABLED', '1', 'conf/dynamic_sha.inc', '', d)}"
include ${CVE_CONF_INCLUDE}

# CVE configuration section, equivalent to: if (CVE_CHECK_ENABLED)
python __anonymous() {
    if d.getVar("CVE_CHECK_ENABLED") == "1":
        if not d.getVar("CVE_LAYER_COMMON_PATH_MIDDLEWARE"):
            d.setVar("CVE_LAYER_COMMON_PATH_MIDDLEWARE", "${MW_IPK_PATH}")

        d.setVar("CVE_FEED_URL_MIDDLEWARE", "${MIDDLEWARE_ARCH}##${RDK_ARTIFACTS_BASE_URL}/${CVE_LAYER_COMMON_PATH_MIDDLEWARE}/xione-uk/tarball/cve/${BUILD_VARIANT}/${MIDDLEWARE_ARCH}.tgz")
        d.appendVar("CVE_LAYER_FEED_PATH", " ${CVE_FEED_URL_MIDDLEWARE};sha256sum=${MIDDLEWARE_ARCH_SHA256SUM}")

}

