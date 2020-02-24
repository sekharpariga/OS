import os
import re

def updateFile(fileName, grepStr):

    sourceFile = os.path.join(os.environ["SourcePath"],"develop/global/src/", fileName)
    envBuildNum = os.environ["BuildNum"]
    pattern = grepStr + "\=[\d]+"
    substitute = grepStr + "=" + envBuildNum
    tempFile = sourceFile + "1"

    os.chmod(sourceFile, 0755)

    with open(sourceFile,'r') as fin, open(tempFile,'w') as fout :
        for line in fin:
            patResult=re.sub(pattern,substitute,line)
            fout.write(patResult)

    os.remove(sourceFile)
    os.rename(tempFile,sourceFile)



def main():

    updateFile("SConstruct","point")
    updateFile("VERSION","ADLMSDK_VERSION_POINT")


main()
