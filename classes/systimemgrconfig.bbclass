# Generates /etc/systimemgr.conf based on active override.
#
# Supported overrides:
#   - ntp-dtt-rdkdefault
#   - ntp-dtt-drm-tee

python create_systimemgrconfig() {
    import os

    overrides = (d.getVar("OVERRIDES", True) or "").split(":")
    rootfs_dir = d.getVar("IMAGE_ROOTFS", True)

    content = None
    remove_secure_conf = False

    if "ntp-dtt-drm-tee" in overrides:
        content = """timesrc  ntp /ntp
timesrc dtt /dtt
timesrc drm /drm
timesync tee /tee
"""
        remove_secure_conf = True
    elif "ntp-dtt-rdkdefault" in overrides:
        content = """timesrc  ntp /ntp
timesrc dtt /dtt
timesync rdkdefault /clock_time
"""

    if content is None:
        bb.note("No supported systimemgr override active; skipping systimemgr.conf generation")
        return

    dest_dir = os.path.join(rootfs_dir, "etc")
    os.makedirs(dest_dir, exist_ok=True)

    dest_path = os.path.join(dest_dir, "systimemgr.conf")
    with open(dest_path, "w", encoding="utf-8") as f:
        f.write(content)

    os.chmod(dest_path, 0o644)

    if remove_secure_conf:
        secure_conf = os.path.join(
            rootfs_dir,
            "lib",
            "systemd",
            "system",
            "systimemgr.service.d",
            "secure.conf"
        )

        if os.path.exists(secure_conf):
            os.remove(secure_conf)

        service_dir = os.path.dirname(secure_conf)
        if os.path.isdir(service_dir) and not os.listdir(service_dir):
            os.rmdir(service_dir)
}

create_systimemgrconfig[vardepsexclude] += "DATETIME"
ROOTFS_POSTPROCESS_COMMAND += 'create_systimemgrconfig; '
