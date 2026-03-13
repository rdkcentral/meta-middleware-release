# Creates /etc/mediarite/mediarite-product.cfg configuration files

# This class generates the mediarite-product.cfg file based on the product configuration.

# Field values should be configured in product layer.

python create_mediariteproductconfig(){
    import os

    config = {}

    # Add all Mediarite specific variables that start with MRITE_ to the config
    for var in d.keys():
        if var.startswith("MRITE_"):
            value = d.getVar(var, True)
            if value:
                config[var[len("MRITE_"):]] = value

    # If DEFAULT_REGION_ALPHA2 is not already set, add DEFAULT_REGION_ALPHA2 based on COUNTRY_CODE
    if "DEFAULT_REGION_ALPHA2" not in config:
        country_code = d.getVar("COUNTRY_CODE", True) or ""
        if country_code:
            config["DEFAULT_REGION_ALPHA2"] = country_code.upper()

    if not config:
        return

    # Ensure the directory exists
    rootfs_dir = d.getVar("IMAGE_ROOTFS", True)
    build_path = os.path.join(rootfs_dir, "etc", "mediarite")
    os.makedirs(build_path, exist_ok=True)

    # Write the CFG file
    config_path = os.path.join(build_path, "mediarite-product.cfg")
    with open(config_path, "w") as file:
        file.write("[YConfig]\n")
        for key in sorted(config):
            value = config[key]
            file.write(f"{key}={value}\n")
    os.chmod(config_path, 0o644)
}
create_mediariteproductconfig[vardepsexclude] += "DATETIME"
ROOTFS_POSTPROCESS_COMMAND += 'create_mediariteproductconfig; '
