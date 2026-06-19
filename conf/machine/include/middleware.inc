# To support layered ipk generation

RDK_MW_ARCH ??= "${MACHINE}"

MIDDLEWARE_ARCH = "${RDK_MW_ARCH}-middleware"
PACKAGE_EXTRA_ARCHS:append = " ${MIDDLEWARE_ARCH}"

RELEASE_NUM = "RDKEVD-8015-r0"

# MW from develop (8.6.2.0 ++) + integrated OSS 4.13.0 + vendor ipks(with OSS 4.13.0)
# ++ there are 2 dependent meta MW layer changes from
# 1. meta-rdk(PR#655) bce224d22d32648ca98e7135a206f4b17cf3cd7b and
# 2. meta-rdk-video(PR#2662) c900e4998d3ab4ea680c6b7422b40cd046e56430
# MW base SHA used from develop: c99b6593a362a223e95603cafc787b90885b04bc
# MW PR: https://github.com/rdk-e/rdke-middleware-manifest/pull/7783
# MW PR#7783 SHA used in deploying ipks: 68d084d638757c655a99555eaf170ab652bca3a5

MW_IPK_PATH ?= "middleware-dbg/${RELEASE_NUM}"
MW_IPK_SERVER_PATH ?= "${RDK_ARTIFACTS_BASE_URL}/${MW_IPK_PATH}/${RDK_MW_ARCH}/ipks/${BUILD_VARIANT}"

IPK_FEED_URIS += " \ 
                ${MIDDLEWARE_ARCH}##${MW_IPK_SERVER_PATH} "

include ${@'oss_mw.inc' if 'STACK_LAYER_OSS_SUPPORT' in d.getVar('DISTRO_FEATURES').split() else ''}

