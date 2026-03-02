# Creates /etc/entservices/ttsConfig.json configuration files
# for tts plugin from entservices component 
# with the given configuration values:
# Field : Value
#   - endpoint: TEXTTOSPEECH_ENDPOINT
#   - secureendpoint: TEXTTOSPEECH_SECURE_ENDPOINT
#   - localendpoint: TEXTTOSPEECH_LOCAL_ENDPOINT
#   - speechrate: TEXTTOSPEECH_SPEECHRATE
#   - satplugincallsign: TEXTTOSPEECH_SATPLUGINCALLSIGN
#   - language: TEXTTOSPEECH_LANGUAGE
#   - volume: TEXTTOSPEECH_VOLUME
#   - rate: TEXTTOSPEECH_RATE
#   - en-US: TEXTTOSPEECH_VOICE_FOR_EN
#   - es-MX: TEXTTOSPEECH_VOICE_FOR_ES
#   - fr-CA: TEXTTOSPEECH_VOICE_FOR_FR
#   - en-GB: TEXTTOSPEECH_VOICE_FOR_GB
#   - de-DE: TEXTTOSPEECH_VOICE_FOR_DE
#   - it-IT: TEXTTOSPEECH_VOICE_FOR_IT
#   - en-US: TEXTTOSPEECH_LOCALVOICE_FOR_EN
#   - es-MX: TEXTTOSPEECH_LOCALVOICE_FOR_ES
#   - fr-CA: TEXTTOSPEECH_LOCALVOICE_FOR_FR
#   - en-GB: TEXTTOSPEECH_LOCALVOICE_FOR_GB
#   - de-DE: TEXTTOSPEECH_LOCALVOICE_FOR_DE
#   - it-IT: TEXTTOSPEECH_LOCALVOICE_FOR_IT
# Field values should be configured in product layer.

python create_ttsconfig(){
    import json
    import os

    def get(var, default=""):
        return d.getVar(var, True) or default

    config = {
        "endpoint": get("TEXTTOSPEECH_ENDPOINT"),
        "secureendpoint": get("TEXTTOSPEECH_SECURE_ENDPOINT"),
        "endpoint_type": get("TEXTTOSPEECH_ENDPOINT_TYPE"),
        "localendpoint": get("TEXTTOSPEECH_LOCAL_ENDPOINT"),
        "speechrate": get("TEXTTOSPEECH_SPEECHRATE"),
        "satplugincallsign": get("TEXTTOSPEECH_SATPLUGINCALLSIGN"),
        "language": get("TEXTTOSPEECH_LANGUAGE"),
        "volume": get("TEXTTOSPEECH_VOLUME", 100),
        "rate": get("TEXTTOSPEECH_RATE", 50),

        "voices": {
            "en-US": get("TEXTTOSPEECH_VOICE_FOR_EN"),
            "es-MX": get("TEXTTOSPEECH_VOICE_FOR_ES"),
            "fr-CA": get("TEXTTOSPEECH_VOICE_FOR_FR"),
            "en-GB": get("TEXTTOSPEECH_VOICE_FOR_GB"),
            "de-DE": get("TEXTTOSPEECH_VOICE_FOR_DE"),
            "it-IT": get("TEXTTOSPEECH_VOICE_FOR_IT"),
        },

        "local_voices": {
            "en-US": get("TEXTTOSPEECH_LOCALVOICE_FOR_EN"),
            "es-MX": get("TEXTTOSPEECH_LOCALVOICE_FOR_ES"),
            "fr-CA": get("TEXTTOSPEECH_LOCALVOICE_FOR_FR"),
            "en-GB": get("TEXTTOSPEECH_LOCALVOICE_FOR_GB"),
            "de-DE": get("TEXTTOSPEECH_LOCALVOICE_FOR_DE"),
            "it-IT": get("TEXTTOSPEECH_LOCALVOICE_FOR_IT"),
        }
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
