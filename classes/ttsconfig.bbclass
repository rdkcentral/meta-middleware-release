# Creates /etc/entservices/ttsConfig.json configuration files
# for tts plugin from entservices component 
# with the given configuration values:
# Field : Value
#   - cloud_url: TEXTTOSPEECH_ENDPOINT
#   - cloud_secure_url: TEXTTOSPEECH_SECURE_ENDPOINT
#   - local_url: TEXTTOSPEECH_LOCAL_ENDPOINT
#   - language: TEXTTOSPEECH_LANGUAGE
#   - en_voice: TEXTTOSPEECH_VOICE_FOR_EN
#   - rate: TEXTTOSPEECH_SPEECHRATE
#   - url_type: TEXTTOSPEECH_ENDPOINT_TYPE
#   - sat_callsign: TEXTTOSPEECH_SATPLUGINCALLSIGN
#   - en_local_voice: TEXTTOSPEECH_LOCALVOICE_FOR_EN
#   - es_local_voice: TEXTTOSPEECH_LOCALVOICE_FOR_ES
#   - fr_local_voice: TEXTTOSPEECH_LOCALVOICE_FOR_FR
#
# Field values should be configured in product layer.

python create_ttsconfig(){
    import json
    import os

    def get(var):
        return d.getVar(var, True) or ""

    config = {
        "cloud_url": get("TEXTTOSPEECH_ENDPOINT"),
        "cloud_secure_url": get("TEXTTOSPEECH_SECURE_ENDPOINT"),
        "local_url": get("TEXTTOSPEECH_LOCAL_ENDPOINT"),
        "language": get("TEXTTOSPEECH_LANGUAGE"),
        "en_voice": get("TEXTTOSPEECH_VOICE_FOR_EN"),
        "rate": get("TEXTTOSPEECH_SPEECHRATE"),
        "url_type": get("TEXTTOSPEECH_ENDPOINT_TYPE"),
        "sat_callsign": get("TEXTTOSPEECH_SATPLUGINCALLSIGN"),
        "en_local_voice": get("TEXTTOSPEECH_LOCALVOICE_FOR_EN"),
        "es_local_voice": get("TEXTTOSPEECH_LOCALVOICE_FOR_ES"),
        "fr_local_voice": get("TEXTTOSPEECH_LOCALVOICE_FOR_FR"),
    }

    # Ensure the directory exists
    rootfs_dir = d.getVar("IMAGE_ROOTFS", True)
    build_path = os.path.join(rootfs_dir, "etc", "entservices")
    os.makedirs(build_path, exist_ok=True)

    # Write the JSON file
    config_path = os.path.join(build_path, "ttsConfig.json")
    with open(config_path, "w") as json_file:
        json.dump(config, json_file, indent=2)
}
create_ttsconfig[vardepsexclude] += "DATETIME"
ROOTFS_POSTPROCESS_COMMAND += 'create_ttsconfig; '
