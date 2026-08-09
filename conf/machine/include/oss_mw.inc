MW_EXTENSION = "-middleware"
MW_OSS = "${@get_oss_arch(d)}${MW_EXTENSION}"
PACKAGE_EXTRA_ARCHS:append = " ${MW_OSS} "
OPKG_ARCH_PRIORITY:${MW_OSS} = "205"
MW_OSS_IPK_PATH ?= "middleware-rel/${RELEASE_NUM}"
MW_OSS_IPK_SERVER_PATH = "${RDK_ARTIFACTS_BASE_URL}/${MW_OSS_IPK_PATH}/${RDK_MW_ARCH}/${MW_OSS}/ipks/${BUILD_VARIANT}"
CVE_LAYER_FEED_PATH += " ${MW_OSS}##${RDK_ARTIFACTS_BASE_URL}/${MW_OSS_IPK_PATH}/${RDK_MW_ARCH}/tarball/cve/debug/${MW_OSS}-middleware.tgz;sha256sum=${MW_OSS_SHA256SUM}"
IPK_FEED_URIS += " ${MW_OSS}##${MW_OSS_IPK_SERVER_PATH} "

include conf/dynamic_sha.inc
