# Stamps /etc/rfcdefaults/socprovisioning.ini with product-layer values
# at image assembly time (ROOTFS_POSTPROCESS_COMMAND).
#
# Field values should be configured in product layers via BitBake variables:
#   SocProvisioningActivation, SocProvisioningRenewal,
#   SocProvisioningNameSpaceUri, SocProvisioningNameSpacePrefix,
#   SocProvisioningAuthMessage, SocProvisioningdisableCredentialsPrefetchCaching,
#   SocProvisioningbackoffIntervalMax

python create_socprovisioning_config() {
    import os

    fields = {
        "SocProvisioning.Activation": d.getVar("SocProvisioningActivation"),
        "SocProvisioning.Renewal": d.getVar("SocProvisioningRenewal"),
        "SocProvisioning.NameSpaceUri": d.getVar("SocProvisioningNameSpaceUri"),
        "SocProvisioning.NameSpacePrefix": d.getVar("SocProvisioningNameSpacePrefix"),
        "SocProvisioning.AuthMessage": d.getVar("SocProvisioningAuthMessage"),
        "SocProvisioning.disableCredentialsPrefetchCaching":
            d.getVar("SocProvisioningdisableCredentialsPrefetchCaching"),
        "SocProvisioning.backoffIntervalMax":
            d.getVar("SocProvisioningbackoffIntervalMax"),
    }

    # Only proceed if at least one URL is defined
    has_urls = any(fields.get(k) for k in [
        "SocProvisioning.Activation", "SocProvisioning.Renewal"])
    if not has_urls:
        bb.note("No SocProvisioning URLs defined in product layer - "
                "device will use middleware defaults")
        return

    rootfs = d.getVar("IMAGE_ROOTFS")
    ini_path = os.path.join(rootfs, "etc", "rfcdefaults", "socprovisioning.ini")

    if not os.path.exists(ini_path):
        bb.warn("socprovisioning.ini not found at %s - skipping" % ini_path)
        return

    # Read existing INI, replace values where product layer defines them
    with open(ini_path, "r", encoding="utf-8") as f:
        lines = f.readlines()

    with open(ini_path, "w", encoding="utf-8") as f:
        for line in lines:
            replaced = False
            for field, value in fields.items():
                prefix = "Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.%s=" % field
                if value and line.startswith(prefix):
                    f.write("%s%s\n" % (prefix, value))
                    replaced = True
                    break
            if not replaced:
                f.write(line)
    os.chmod(ini_path, 0o644)
}
do_rootfs[vardeps] += " \
    SocProvisioningActivation \
    SocProvisioningRenewal \
    SocProvisioningNameSpaceUri \
    SocProvisioningNameSpacePrefix \
    SocProvisioningAuthMessage \
    SocProvisioningdisableCredentialsPrefetchCaching \
    SocProvisioningbackoffIntervalMax \
"
ROOTFS_POSTPROCESS_COMMAND += 'create_socprovisioning_config; '
