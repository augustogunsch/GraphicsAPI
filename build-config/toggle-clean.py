import configparser

config = configparser.ConfigParser()
config.read("config.ini")

with open("config.ini", "w") as configfile:
    currentValue = config.getboolean("standard", "compile-all")
    config.set("standard", "compile-all", str(not currentValue))
    config.write(configfile)
    
    if(config.getboolean("standard", "wait")):
        input("Current value: {0}".format(not currentValue))