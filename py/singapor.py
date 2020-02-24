# Refactor code: Not timed (good to get it back within 24 hours) 
# Please make the following code as 'nice' as possible # Functionality should remain mostly untouched.
# Please do not be constrained by the existing code (i.e. you don't have # to keep the same function names, structure) 
# Aim for production quality 'best-practice/clean' code

import os
import re


# #SCONSTRUCT file interesting line
# config.version = Version( 
#     major=15,
#     minor=0,
#     point=6,
#     patch=0
# )

srcPath = "develop/global/src/"
envBuildNum = os.environ["BuildNum"]

def updateSconstruct():
    sconstruct = os.path.join(os.environ["SourcePath"], srcPath,"SConstruct")
    sconstruct1 = os.path.join(os.environ["SourcePath"],srcPath,"SConstruct1")
    os.chmod(sconstruct, 0755)
    fin = open(sconstruct, 'r')
    fout = open(sconstruct1, 'w')

    for line in fin:
        pattern=re.sub("point\=[\d]+","point="+ envBuildNum,line)
        fout.write(pattern)
    fin.close()
    fout.close()
    os.remove(sconstruct)
    os.rename(sconstruct1,sconstruct)

# # VERSION file interesting line
# ADLMSDK_VERSION_POINT=6
def updateVersion():
    version = os.path.join(os.environ["SourcePath"],srcPath,"VERSION")
    version1 = os.path.join(os.environ["SourcePath"],srcPath,"VERSION1")
    os.chmod(version, 0755)
    fin = open(version, 'r')
    fout = open(version1, 'w')

    for line in fin:
        pattern=re.sub("ADLMSDK_VERSION_POINT\=[\d]+","ADLMSDK_VERSION_POINT="+ envBuildNum,line)
        fout.write(pattern)
    fin.close()
    fout.close()
    os.remove(version)
    os.rename(version1,version)


def main():
            updateSconstruct()
            updateVersion()


main()
