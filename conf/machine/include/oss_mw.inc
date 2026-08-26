MW_EXTENSION = "-middleware"
MW_OSS = "${@get_oss_arch(d)}${MW_EXTENSION}"
PACKAGE_EXTRA_ARCHS:append = " ${MW_OSS} "
OPKG_ARCH_PRIORITY:${MW_OSS} = "205"
MW_OSS_IPK_PATH ?= "middleware-dbg/RDKEVD-6147-mw-cve"
MW_OSS_IPK_SERVER_PATH = "${RDK_ARTIFACTS_BASE_URL}/${MW_OSS_IPK_PATH}/${RDK_MW_ARCH}/${MW_OSS}/ipks/${BUILD_VARIANT}"
IPK_FEED_URIS += " ${MW_OSS}##${MW_OSS_IPK_SERVER_PATH} "

#CVE Feed Path

CVE_LAYER_FEED_PATH:append = " ${@bb.utils.contains('INHERIT', 'cve-check', '${MW_OSS}##${RDK_ARTIFACTS_BASE_URL}/${MW_OSS_IPK_PATH}/${RDK_MW_ARCH}/${CVE_PATH}/${BUILD_VARIANT}/${MW_OSS}.tgz', '', d)} "
