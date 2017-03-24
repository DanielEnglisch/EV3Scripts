##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=EV3Scripts
ConfigurationName      :=Debug
WorkspacePath          :=/root/Documents/Workspace
ProjectPath            :=/root/Documents/Workspace/EV3Scripts
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=root
Date                   :=24/03/17
CodeLitePath           :=/root/.codelite
LinkerName             :=/usr/bin/arm-linux-gnueabi-g++
SharedObjectLinkerName :=/usr/bin/arm-linux-gnueabi-g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="EV3Scripts.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -L./ -lev3dev -static
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/arm-linux-gnueabi-ar rcu
CXX      := /usr/bin/arm-linux-gnueabi-g++
CC       := /usr/bin/arm-linux-gnueabi-gcc
CXXFLAGS :=  -std=c++14 $(Preprocessors)
CFLAGS   :=   $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/arm-linux-gnueabi-as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/Valentin.cpp$(ObjectSuffix) $(IntermediateDirectory)/LineFollow.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

PostBuild:
	@echo Executing Post Build commands ...
	uploadev3 192.168.1.103
	@echo Done

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:
	@echo Executing Pre Build commands ...
	git config credential.helper cache
	@echo Done


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/root/Documents/Workspace/EV3Scripts/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/Valentin.cpp$(ObjectSuffix): Valentin.cpp $(IntermediateDirectory)/Valentin.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/root/Documents/Workspace/EV3Scripts/Valentin.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Valentin.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Valentin.cpp$(DependSuffix): Valentin.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Valentin.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Valentin.cpp$(DependSuffix) -MM Valentin.cpp

$(IntermediateDirectory)/Valentin.cpp$(PreprocessSuffix): Valentin.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Valentin.cpp$(PreprocessSuffix) Valentin.cpp

$(IntermediateDirectory)/LineFollow.cpp$(ObjectSuffix): LineFollow.cpp $(IntermediateDirectory)/LineFollow.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/root/Documents/Workspace/EV3Scripts/LineFollow.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/LineFollow.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/LineFollow.cpp$(DependSuffix): LineFollow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/LineFollow.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/LineFollow.cpp$(DependSuffix) -MM LineFollow.cpp

$(IntermediateDirectory)/LineFollow.cpp$(PreprocessSuffix): LineFollow.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/LineFollow.cpp$(PreprocessSuffix) LineFollow.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


