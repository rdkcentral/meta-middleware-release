# Creates /etc/entservices/appGatewayConfig.json configuration file
#
# APP_GATEWAY_CFG_FILE should be configured in product layer.

python create_appgatewayconfig() {
    import os
    import shutil

    app_gateway_cfg_file = d.getVar("APP_GATEWAY_CFG_FILE", True)

    if not app_gateway_cfg_file:
        bb.warn("APP_GATEWAY_CFG_FILE is not set; skipping appGatewayConfig.json copy")
        return

    if not os.path.exists(app_gateway_cfg_file):
        bb.fatal("APP_GATEWAY_CFG_FILE (%s) does not exist on build host" % app_gateway_cfg_file)

    image_rootfs = d.getVar("IMAGE_ROOTFS", True)
    etc_app_gateway_dir = os.path.join(image_rootfs, "etc", "entservices")
    os.makedirs(etc_app_gateway_dir, exist_ok=True)

    # Copy product-specific appGatewayConfig.json into rootfs
    dest_config = os.path.join(etc_app_gateway_dir, "appGatewayConfig.json")
    shutil.copy(app_gateway_cfg_file, dest_config)
    bb.note("Copied APP_GATEWAY_CFG_FILE to %s" % dest_config)
}
ROOTFS_POSTPROCESS_COMMAND += 'create_appgatewayconfig; '
