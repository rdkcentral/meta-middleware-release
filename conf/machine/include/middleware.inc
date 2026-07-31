# To support layered ipk generation

RDK_MW_ARCH ??= "${MACHINE}"

MIDDLEWARE_ARCH = "${RDK_MW_ARCH}-middleware"
PACKAGE_EXTRA_ARCHS:append = " ${MIDDLEWARE_ARCH}"


# MW from develop( 8.6.3.0 ++) + integrated OSS 4.14.0 + vendor ipks(with OSS 4.14.0)
# ++ there are 1 dependent meta MW layer changes from
# Need to add meta-rdk-bluetooth(1.1.0) in middleware's submanifest rdke-middleware-generic-manifest/middleware-generic.xml
# MW base SHA used from develop: 34b0b44a785e0c85e321158f345259d465da5cd9 29th July
# MW PR: https://github.com/rdk-e/rdke-middleware-manifest/pull/8077
# sky-it : MW PR#8077 SHA used in deploying ipks: 92c65f3a848c9cd3edd211373b9a7de2805f1bcc
# All other platforms: MW PR#8077 SHA used in deploying ipks: c9defd623b39b25fcabf3d84b4963f704830fc99


RELEASE_NUM = "RDKEVD-8621-r0"

MW_IPK_PATH ?= "middleware-dbg/${RELEASE_NUM}"
MW_IPK_SERVER_PATH ?= "${RDK_ARTIFACTS_BASE_URL}/${MW_IPK_PATH}/${RDK_MW_ARCH}/ipks/${BUILD_VARIANT}"

IPK_FEED_URIS += " \ 
                ${MIDDLEWARE_ARCH}##${MW_IPK_SERVER_PATH} "

include ${@'oss_mw.inc' if 'STACK_LAYER_OSS_SUPPORT' in d.getVar('DISTRO_FEATURES').split() else ''}
