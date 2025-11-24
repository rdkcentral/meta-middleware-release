# Creates /etc/authservice/config.json configuration file
# for authentication services with PARTNER_ID configuration
#
# Field values should be configured in product layer via BUILTIN_PARTNER_ID

python create_authservice_config(){
    import json
    import os

    # Get PARTNER_ID directly from product configuration  
    partner_id = d.getVar("BUILTIN_PARTNER_ID", True)
    if not partner_id:
        bb.note("BUILTIN_PARTNER_ID not defined - device will resolve PARTNER_ID at runtime")
        return
    
    config = {
        "partner_id": "%s" % partner_id
    }

    # Ensure the directory exists
    rootfs_dir = d.getVar("IMAGE_ROOTFS", True)
    build_path = os.path.join(rootfs_dir, "etc", "authservice")
    os.makedirs(build_path, exist_ok=True)

    # Write the JSON file
    config_path = os.path.join(build_path, "config.json")
    with open(config_path, "w") as json_file:
        json.dump(config, json_file, indent=2)
}
create_authservice_config[vardepsexclude] += "DATETIME"
ROOTFS_POSTPROCESS_COMMAND += 'create_authservice_config; '
