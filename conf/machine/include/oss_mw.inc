MW_EXTENSION = "-middleware"
MW_OSS = "${@get_oss_arch(d)}${MW_EXTENSION}"
PACKAGE_EXTRA_ARCHS:append = " ${MW_OSS} "
OPKG_ARCH_PRIORITY:${MW_OSS} = "205"
MW_OSS_IPK_PATH ?= "middleware-rel/${RELEASE_NUM}"
MW_OSS_IPK_SERVER_PATH = "${RDK_ARTIFACTS_BASE_URL}/${MW_OSS_IPK_PATH}/${RDK_MW_ARCH}/${MW_OSS}/ipks/${BUILD_VARIANT}"
IPK_FEED_URIS += " ${MW_OSS}##${MW_OSS_IPK_SERVER_PATH} "

OSS = "${@get_oss_arch(d)}-oss"
PACKAGE_EXTRA_ARCHS:append = " ${OSS} "
OPKG_ARCH_PRIORITY:${OSS} = "205"
#OSS_IPK_PATH ?= "middleware-rel/${RELEASE_NUM}"
OSS_IPK_SERVER_PATH = "https://partners.artifactory.comcast.com/artifactory/rdk-oss-rel/4.9.0/rdk-arm64/ipks/"
IPK_FEED_URIS += " ${OSS}##${OSS_IPK_SERVER_PATH} "




