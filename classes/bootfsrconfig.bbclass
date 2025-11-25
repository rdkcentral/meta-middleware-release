# Creates boot_FSR.sh file in the target image

# The boot_FSR.sh file triggered during boot to perform FSR based on XRE experience:
#
# BOOT_FSR_FILE field should be configured in product layer.

python create_bootfsrconfig(){
    import shutil
    import os
    boot_fsr_file = d.getVar("BOOT_FSR_FILE", True)
    if boot_fsr_file: 
        if os.path.exists(boot_fsr_file):
            output_dir = d.getVar("IMAGE_ROOTFS", True)
            build_path = os.path.join(output_dir, "lib", "rdk")
            os.makedirs(build_path, exist_ok=True)
            output_file = os.path.join(build_path, "boot_FSR.sh")
            shutil.copy(boot_fsr_file, output_file)
            # Change file permission to 777 (rwxrwxrwx)
            os.chmod(output_file, 0o777)
        else:
            bb.fatal("%s is not available" % boot_fsr_file)
    else: 
        bb.warn("BOOT_FSR_FILE is not set, boot_FSR.sh file will not be included in the build!")
}
create_bootfsrconfig[vardepsexclude] += "DATETIME"
ROOTFS_POSTPROCESS_COMMAND += 'create_bootfsrconfig; '
