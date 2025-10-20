# Creates configuration files for EntOS migration

# The aisettings-migration-override.json file with the given configuration values:
#
# AISETTINGS_MIGRATION_CFG_FILE field should be configured in product layer.

python create_aimigrationoverrideconfig(){
    import shutil
    import os
    aimigrationoverride_file = d.getVar("AISETTINGS_MIGRATION_CFG_FILE", True)
    if aimigrationoverride_file: 
        if os.path.exists(aimigrationoverride_file):
            output_dir = d.getVar("IMAGE_ROOTFS", True)
            build_path = os.path.join(output_dir, "etc", "sky", "aisettings.overrides")
            os.makedirs(build_path, exist_ok=True)
            output_file = os.path.join(build_path, "post-migration-override.json")
            shutil.copy(aimigrationoverride_file, output_file)
            # Change file permission to 644 (rw-r--r--)
            os.chmod(output_file, 0o644)            
        else:
            bb.fatal("%s is not available" % aimigrationoverride_file)
    else: 
        bb.warn("AISETTINGS_MIGRATION_CFG_FILE is not set, aisettings migration override json file will not be included in the build!")
}
create_aimigrationoverrideconfig[vardepsexclude] += "DATETIME"
ROOTFS_POSTPROCESS_COMMAND += 'create_aimigrationoverrideconfig; '
