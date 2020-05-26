import configparser

config = configparser.ConfigParser()

config["standard"] = {
    "compile-all" : False,
    "wait" : False
}

with open("config.ini", "w") as configfile:
    config.write(configfile)