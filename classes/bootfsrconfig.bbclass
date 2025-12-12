# Creates boot_FSR.platform file in the target image
# The boot_FSR.sh file triggered during boot to perform FSR based on boot_FSR.platform:
#
# BOOT_FSR_PLATFORM field should be configured in product layer.
python create_bootfsrconfig(){
    import shutil
    import os
    boot_fsr_platform = (d.getVar('BOOT_FSR_PLATFORM') or '').strip().lower()

    if boot_fsr_platform in ['flex', 'xumotv']:
        bb.warn("BOOT_FSR_PLATFORM is set, boot_FSR.platform file is included in the build!")
        output_dir = d.getVar("IMAGE_ROOTFS", True)
        build_path = os.path.join(output_dir, "etc", "migration")
        os.makedirs(build_path, exist_ok=True)
        output_file = os.path.join(build_path, "boot_FSR.platform")
        try:
            with open(output_file, "w", encoding="utf-8") as f:
                f.write(boot_fsr_platform + "\n")
            os.chmod(output_file, 0o644)  # config-style file
            bb.note("Wrote platform marker: %s -> %s" % (boot_fsr_platform, output_file))
        except Exception as e:
            bb.fatal("Failed to write platform marker '%s': %s" % (output_file, e))
    else: 
        bb.warn("BOOT_FSR_PLATFORM is not set for this platform !!!")
}

create_bootfsrconfig[vardepsexclude] += "DATETIME"
ROOTFS_POSTPROCESS_COMMAND += 'create_bootfsrconfig; '
