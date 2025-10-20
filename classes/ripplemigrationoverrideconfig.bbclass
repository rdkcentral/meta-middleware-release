# Creates configuration files for EntOS migration

# The ripple-cofnig.json file with the given configuration values:
#
# RIPPLE_MIGRATION_CFG_FILE field should be configured in product layer.

python create_ripplemigrationoverrideconfig(){
    import shutil
    import os
    ripplemigrationoverride_file = d.getVar("RIPPLE_MIGRATION_CFG_FILE", True)
    if ripplemigrationoverride_file:
        if os.path.exists(ripplemigrationoverride_file):
            output_dir = d.getVar("IMAGE_ROOTFS", True)
            build_path = os.path.join(output_dir, "etc", "ripple", "rdke")
            os.makedirs(build_path, exist_ok=True)
            output_file = os.path.join(build_path, "ripple.config.json")
            shutil.copy(ripplemigrationoverride_file, output_file)
            # Change file permission to 644 (rw-r--r--)
            os.chmod(output_file, 0o644)
        else:
            bb.fatal("%s is not available" % ripplemigrationoverride_file)
    else:
        bb.warn("RIPPLE_MIGRATION_CFG_FILE is not set, ripple migration override json file will not be included in the build!")
}
create_ripplemigrationoverrideconfig[vardepsexclude] += "DATETIME"
ROOTFS_POSTPROCESS_COMMAND += 'create_ripplemigrationoverrideconfig; '
