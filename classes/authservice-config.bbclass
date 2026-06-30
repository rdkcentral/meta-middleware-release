# AuthService configuration at image assembly time (ROOTFS_POSTPROCESS_COMMAND).
#
# 1. Creates /etc/authservice/config.json with BUILTIN_PARTNER_ID
# 2. Stamps /etc/rfcdefaults/authservice.ini with AuthServiceHost
#
# Both values should be configured in product layers.

python create_authservice_config() {
    import json
    import os

    rootfs = d.getVar("IMAGE_ROOTFS")

    # --- Part 1: /etc/authservice/config.json (PARTNER_ID) ---
    partner_id = d.getVar("BUILTIN_PARTNER_ID")
    if partner_id:
        build_path = os.path.join(rootfs, "etc", "authservice")
        os.makedirs(build_path, exist_ok=True)
        config_path = os.path.join(build_path, "config.json")
        with open(config_path, "w", encoding="utf-8") as f:
            json.dump({"partner_id": partner_id}, f, indent=2)
        os.chmod(config_path, 0o644)

    # --- Part 2: /etc/rfcdefaults/authservice.ini (AuthServiceHost) ---
    auth_host = d.getVar("AuthServiceHost")
    if not auth_host:
        return

    ini_path = os.path.join(rootfs, "etc", "rfcdefaults", "authservice.ini")
    if not os.path.exists(ini_path):
        bb.warn("authservice.ini not found at %s" % ini_path)
        return

    with open(ini_path, "r", encoding="utf-8") as f:
        lines = f.readlines()

    prefix = "Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.AuthService.Host="
    with open(ini_path, "w", encoding="utf-8") as f:
        for line in lines:
            if line.startswith(prefix):
                f.write("%s%s\n" % (prefix, auth_host))
            else:
                f.write(line)
    os.chmod(ini_path, 0o644)
}
create_authservice_config[vardepsexclude] += "DATETIME"
ROOTFS_POSTPROCESS_COMMAND += 'create_authservice_config; '
