import configparser
import subprocess

makefileAgent = "mingw32-make"
buildRule = "build"
buildAllRule = "clean"

config = configparser.ConfigParser()

config.read("build-config/config.ini")

compileAll = config.getboolean("standard", "compile-all")
wait = config.getboolean("standard", "wait")

rule = buildRule
if(compileAll):
    rule = buildAllRule
    
retCode = subprocess.run("{0} {1}".format(makefileAgent, rule))
    
if(retCode.returncode != 0):
    print()
    input("Build failed (code: {}).".format(retCode.returncode))
elif(wait):
    input()