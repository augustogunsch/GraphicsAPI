import configparser

config = configparser.ConfigParser()
config.read("config.ini")

with open("config.ini", "w") as configfile:
    currentValue = config.getboolean("standard", "wait")
    config.set("standard", "wait", str(not currentValue))
    config.write(configfile)
    
    if(config.getboolean("standard", "wait")):
        input("Current value: {0}".format(not currentValue))