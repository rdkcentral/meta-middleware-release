python create_appinfra_version_file() {
	import os
	import shutil

	rootfs = d.getVar("IMAGE_ROOTFS", True)
	output_file = os.path.join(rootfs, "etc/appinfraversion.txt")
	opt_output_file = os.path.join(rootfs, "opt/appinfraversion.txt")
	input_files = [
		os.path.join(rootfs, "etc/appgatewayversion.txt"),
		os.path.join(rootfs, "etc/appgatewaycpcversion.txt"),
		os.path.join(rootfs, "etc/appmanagersversion.txt"),
	]

	os.makedirs(os.path.dirname(output_file), exist_ok=True)
	os.makedirs(os.path.dirname(opt_output_file), exist_ok=True)

	with open(output_file, "w") as out_f:
		for in_file in input_files:
			if os.path.exists(in_file):
				with open(in_file, "r") as in_f:
					content = in_f.read()
					if content:
						out_f.write(content)
						if not content.endswith("\n"):
							out_f.write("\n")

	shutil.copy2(output_file, opt_output_file)

	for in_file in input_files:
		if os.path.exists(in_file):
			os.remove(in_file)
}

ROOTFS_POSTPROCESS_COMMAND += 'create_appinfra_version_file; '