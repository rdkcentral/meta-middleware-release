# MW_DEV builds compile middleware from source, so skip the prebuilt IPK feed
include ${@'middleware-feed.inc' if d.getVar('MW_LAYER_BUILD_TYPE') != 'MW_DEV' else ''}
