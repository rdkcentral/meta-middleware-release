MW_EXTENSION = "-middleware"
MW_OSS = "${@get_oss_arch(d)}${MW_EXTENSION}"
PACKAGE_EXTRA_ARCHS:append = " ${MW_OSS} "
OPKG_ARCH_PRIORITY:${MW_OSS} = "205"
MW_OSS_IPK_PATH ?= "middleware-rel/${RELEASE_NUM}"
MW_OSS_IPK_SERVER_PATH ?= "${RDK_ARTIFACTS_BASE_URL}/${MW_OSS_IPK_PATH}/${RDK_MW_ARCH}/${MW_OSS}/ipks/${BUILD_VARIANT}"
IPK_FEED_URIS += " ${MW_OSS}##${MW_OSS_IPK_SERVER_PATH} "


#The following section will be only enabled if CVE_CHECK is set

# Check whether CVE-check is globally inherited
CVE_CHECK_ENABLED = "${@bb.utils.contains('INHERIT', 'cve-check', '1', '0', d)}"

# Conditionally include CVE-specific configuration needed for SHA
CVE_CONF_INCLUDE = "${@bb.utils.contains('CVE_CHECK_ENABLED', '1', 'conf/dynamic_sha.inc', '', d)}"
include ${CVE_CONF_INCLUDE}

# CVE configuration section, equivalent to: if (CVE_CHECK_ENABLED)
python __anonymous() {
    if d.getVar("CVE_CHECK_ENABLED") == "1":
        if not d.getVar("CVE_LAYER_COMMON_PATH_MIDDLEWARE"):
            d.setVar("CVE_LAYER_COMMON_PATH_MIDDLEWARE", "${MW_OSS_IPK_PATH}")

        d.setVar("CVE_FEED_URL_MWOSS", "${MW_OSS}##${RDK_ARTIFACTS_BASE_URL}/${CVE_LAYER_COMMON_PATH_MIDDLEWARE}/xione-uk/tarball/cve/${BUILD_VARIANT}/${MW_OSS}.tgz")
        d.appendVar("CVE_LAYER_FEED_PATH", " ${CVE_FEED_URL_MWOSS};sha256sum=${MW_OSS_SHA256SUM}")

}
