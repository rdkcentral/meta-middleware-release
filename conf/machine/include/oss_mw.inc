MW_EXTENSION = "-middleware"
MW_OSS = "${@get_oss_arch(d)}${MW_EXTENSION}"
PACKAGE_EXTRA_ARCHS:append = " ${MW_OSS} "
OPKG_ARCH_PRIORITY:${MW_OSS} = "205"
#MW_OSS_IPK_PATH ?= "middleware-rel/${RELEASE_NUM}"
#MW_OSS_IPK_SERVER_PATH = "${RDK_ARTIFACTS_BASE_URL}/${MW_OSS_IPK_PATH}/${RDK_MW_ARCH}/${MW_OSS}/ipks/${BUILD_VARIANT}"
<<<<<<< HEAD
MW_OSS_IPK_SERVER_PATH = "https://partners.artifactory.comcast.com/artifactory/middleware-dbg/RDKEMW-13582_aamp_Multilib_polaris/rdktv-us-armv8a/ipks/debug"
=======
#MW_OSS_IPK_SERVER_PATH = "https://partners.artifactory.comcast.com/artifactory/middleware-dbg/RDKEMW-13582_aamp_Multilib_polaris/rdktv-us-armv8a/ipks/debug"
MW_OSS_IPK_SERVER_PATH = "middleware-dbg/RDKEMW-13582_aamp_Multilib_polaris"
>>>>>>> e74cdfe (Adding the new IPK path)
IPK_FEED_URIS += " ${MW_OSS}##${MW_OSS_IPK_SERVER_PATH} "
