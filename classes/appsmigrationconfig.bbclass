# Creates configuration files for EntOS migration

# The appsmigrationdata.json file with the given configuration values:
#
# APPS_MIGRATION_DATA field should be configured in product layer.

python create_appsmigrationconfig(){
    import shutil
    import os
    appsmigrationdata_file = d.getVar("APPS_MIGRATION_CFG_FILE", True)
    if appsmigrationdata_file: 
        if os.path.exists(appsmigrationdata_file):
            output_dir = d.getVar("IMAGE_ROOTFS", True)
            build_path = os.path.join(output_dir, "etc", "migration")
            os.makedirs(build_path, exist_ok=True)
            output_file = os.path.join(build_path, "entos_apps_migration.json")
            shutil.copy(appsmigrationdata_file, output_file)
        else:
            bb.fatal("%s is not available" % appsmigrationdata_file)
    else: 
        bb.warn("APPS_MIGRATION_CFG_FILE is not set, apps migration json file will not be included in the build!")
}
create_appsmigrationconfig[vardepsexclude] += "DATETIME"
ROOTFS_POSTPROCESS_COMMAND += 'create_appsmigrationconfig; '
