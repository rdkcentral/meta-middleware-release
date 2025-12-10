# Creates boot_FSR.sh file in the target image
# The boot_FSR.sh file triggered during boot to perform FSR based on XRE experience:
#
# BOOT_FSR_FILE field should be configured in product layer.
python create_bootfsrconfig(){
    import shutil
    import os
    boot_fsr_flag = (d.getVar('BOOT_FSR_FLAG') or '').strip().lower()
    boot_fsr_file = d.getVar('BOOT_FSR_CFG_FILE') or ''
    if boot_fsr_flag in ['true', 'yes', '1']:
        if os.path.exists(boot_fsr_file):
            bb.warn("BOOT_FSR_FLAG is set, boot_FSR.sh file is included in the build!")
            output_dir = d.getVar("IMAGE_ROOTFS", True)
            build_path = os.path.join(output_dir, "lib", "rdk")
            os.makedirs(build_path, exist_ok=True)
            output_file = os.path.join(build_path, "boot_FSR.sh")
            bb.warn("%s file is installed" % boot_fsr_file")
            shutil.copy(boot_fsr_file, output_file)
            # Change file permission to 777 (rwxrwxrwx)
            os.chmod(output_file, 0o777)
        else:
            bb.fatal("%s flag is not enabled" % boot_fsr_flag)
    else: 
        bb.warn("BOOT_FSR_FLAG is not set, boot_FSR.sh file will not be included in the build!")
}
BOOT_FSR_CFG_FILE = "${MANIFEST_PATH_MW_RELEASE}/conf/include/boot_FSR.sh"
create_bootfsrconfig[vardepsexclude] += "DATETIME"
ROOTFS_POSTPROCESS_COMMAND += 'create_bootfsrconfig; '
