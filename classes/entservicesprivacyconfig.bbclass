# Creates /etc/entservices/privacyConfig.json configuration files
# for Privacy plugin from entservices compontent 
# with the given configuration values:
# Field : Value
#   - ess_url: ESS_URL
#   - ess_client_id: ESS_CLIENT_ID
#
# Field values should be configured in product layer.

python create_entservicesprivacyconfig(){
    import json
    import os

    # Buid privacyConfig.json payload
    ess_url = d.getVar("ESS_URL", True) or ""
    ess_client_id = d.getVar("ESS_CLIENT_ID", True) or "default"

    config = {
        "ess_url": "%s"%ess_url,
        "ess_client_id": "%s"%ess_client_id
    }

    # Ensure the directory exists
    rootfs_dir = d.getVar("IMAGE_ROOTFS", True)
    build_path = os.path.join(rootfs_dir, "etc", "entservices")
    os.makedirs(build_path, exist_ok=True)

    # Write the JSON file
    config_path = os.path.join(build_path, "privacyConfig.json")
    with open(config_path, "w") as json_file:
        json.dump(config, json_file, indent=2)
}
create_entservicesprivacyconfig[vardepsexclude] += "DATETIME"
ROOTFS_POSTPROCESS_COMMAND += 'create_entservicesprivacyconfig; '
