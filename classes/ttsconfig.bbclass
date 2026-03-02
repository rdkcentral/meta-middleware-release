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
            "endpoint": get("TEXTTOSPEECH_ENDPOINT"),
            "secureendpoint": get("TEXTTOSPEECH_SECURE_ENDPOINT"),
            "endpoint_type": get("TEXTTOSPEECH_ENDPOINT_TYPE"),
            "localendpoint": get("TEXTTOSPEECH_LOCAL_ENDPOINT"),
            "speechrate": get("TEXTTOSPEECH_SPEECHRATE"),
            "satplugincallsign": get("TEXTTOSPEECH_SATPLUGINCALLSIGN"),
            "language": get("TEXTTOSPEECH_LANGUAGE"),
            "volume": int(get("TEXTTOSPEECH_VOLUME", 100)),
            "rate": int(get("TEXTTOSPEECH_RATE", 50)),

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
