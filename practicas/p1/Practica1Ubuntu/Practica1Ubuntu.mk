##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Practica1Ubuntu
ConfigurationName      :=Debug
WorkspacePath          :=/home/pinguino/UGR/SEGUNDO/2/IA/practicas/p1/Practica1Ubuntu
ProjectPath            :=/home/pinguino/UGR/SEGUNDO/2/IA/practicas/p1/Practica1Ubuntu
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=
Date                   :=04/01/17
CodeLitePath           :=/home/pinguino/.codelite
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
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
ObjectsFileList        :="Practica1Ubuntu.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -O0
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch). $(LibraryPathSwitch)Debug 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -Wall $(Preprocessors)
CFLAGS   :=   $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Srcs=CMakeFiles/feature_tests.c CMakeFiles/feature_tests.cxx Comportamientos_Jugador/aldeano.cpp Comportamientos_Jugador/perro.cpp Comportamientos_Jugador/jugador.cpp bin_src/juegoSG.cc bin_src/juego.cc src/modelos/retrato.cpp src/obj3dlib/file_ply_stl.cc src/obj3dlib/cubo3d.cc \
	src/obj3dlib/tetraedro3d.cc src/obj3dlib/luz.cpp src/obj3dlib/toro3d.cc src/obj3dlib/cono3dwire.cc src/obj3dlib/dodecaedro3d.cc src/obj3dlib/objeto3d.cc src/obj3dlib/esfera3d.cc src/obj3dlib/cono3d.cc src/obj3dlib/objrevolucion3d.cc src/obj3dlib/octaedro3d.cc \
	src/obj3dlib/icosaedro3d.cc src/motorlib/motor_juego.cpp src/motorlib/entidad.cpp src/motorlib/motor_grafico.cpp src/motorlib/mapa.cpp src/motorlib/monitor.cpp src/glui/glui_tree.cpp src/glui/glui_panel.cpp src/glui/glui_listbox.cpp src/glui/glui_checkbox.cpp \
	src/glui/glui_button.cpp src/glui/glui_statictext.cpp src/glui/glui_string.cpp src/glui/glui_textbox.cpp src/glui/glui.cpp src/glui/glui_mouse_iaction.cpp src/glui/algebra3.cpp src/glui/glui_rotation.cpp src/glui/glui_commandline.cpp src/glui/glui_radio.cpp \
	src/glui/glui_window.cpp src/glui/glui_column.cpp src/glui/glui_separator.cpp src/glui/glui_treepanel.cpp src/glui/glui_node.cpp src/glui/glui_filebrowser.cpp src/glui/glui_edittext.cpp src/glui/viewmodel.cpp src/glui/glui_bitmap_img_data.cpp src/glui/glui_list.cpp \
	src/glui/quaternion.cpp src/glui/glui_add_controls.cpp src/glui/glui_rollout.cpp src/glui/glui_control.cpp src/glui/arcball.cpp src/glui/glui_spinner.cpp src/glui/glui_bitmaps.cpp src/glui/glui_scrollbar.cpp src/glui/glui_translation.cpp src/comportamientos/puerta.cpp \
	src/comportamientos/comportamiento.cpp src/comportamientos/objeto.cpp CMakeFiles/FindOpenMP/ompver.cpp CMakeFiles/FindOpenMP/ompver.c src/modelos/perro/lomo.cpp src/modelos/perro/cabeza.cpp src/modelos/perro/perro.cpp src/modelos/item/item.cpp src/modelos/jugador/jugador3d.cpp src/modelos/jugador/quesito.cpp \
	src/modelos/puerta/puerta.cpp src/modelos/leo/brazo.cpp src/modelos/leo/leo.cpp src/modelos/leo/torso.cpp src/modelos/leo/pierna.cpp src/modelos/leo/cabeza.cpp src/modelos/leo/cintura.cpp src/modelos/aldeano/aldeano.cpp src/modelos/aldeano/brazo.cpp src/modelos/aldeano/torso.cpp \
	src/modelos/aldeano/pierna.cpp src/modelos/aldeano/cabeza.cpp src/modelos/aldeano/cintura.cpp src/modelos/arbol/arbol.cpp src/obj3dlib/jpeg_reader/jpg_readwrite.cpp src/obj3dlib/jpeg_reader/jpg_memsrc.cpp src/obj3dlib/jpeg_reader/jpg_imagen.cpp CMakeFiles/3.7.2/CompilerIdCXX/CMakeCXXCompilerId.cpp CMakeFiles/3.7.2/CompilerIdC/CMakeCCompilerId.c 

Objects0=$(IntermediateDirectory)/CMakeFiles_feature_tests.c$(ObjectSuffix) $(IntermediateDirectory)/CMakeFiles_feature_tests.cxx$(ObjectSuffix) $(IntermediateDirectory)/Comportamientos_Jugador_aldeano.cpp$(ObjectSuffix) $(IntermediateDirectory)/Comportamientos_Jugador_perro.cpp$(ObjectSuffix) $(IntermediateDirectory)/Comportamientos_Jugador_jugador.cpp$(ObjectSuffix) $(IntermediateDirectory)/bin_src_juegoSG.cc$(ObjectSuffix) $(IntermediateDirectory)/bin_src_juego.cc$(ObjectSuffix) $(IntermediateDirectory)/src_modelos_retrato.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_obj3dlib_file_ply_stl.cc$(ObjectSuffix) $(IntermediateDirectory)/src_obj3dlib_cubo3d.cc$(ObjectSuffix) \
	$(IntermediateDirectory)/src_obj3dlib_tetraedro3d.cc$(ObjectSuffix) $(IntermediateDirectory)/src_obj3dlib_luz.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_obj3dlib_toro3d.cc$(ObjectSuffix) $(IntermediateDirectory)/src_obj3dlib_cono3dwire.cc$(ObjectSuffix) $(IntermediateDirectory)/src_obj3dlib_dodecaedro3d.cc$(ObjectSuffix) $(IntermediateDirectory)/src_obj3dlib_objeto3d.cc$(ObjectSuffix) $(IntermediateDirectory)/src_obj3dlib_esfera3d.cc$(ObjectSuffix) $(IntermediateDirectory)/src_obj3dlib_cono3d.cc$(ObjectSuffix) $(IntermediateDirectory)/src_obj3dlib_objrevolucion3d.cc$(ObjectSuffix) $(IntermediateDirectory)/src_obj3dlib_octaedro3d.cc$(ObjectSuffix) \
	$(IntermediateDirectory)/src_obj3dlib_icosaedro3d.cc$(ObjectSuffix) $(IntermediateDirectory)/src_motorlib_motor_juego.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_motorlib_entidad.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_motorlib_motor_grafico.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_motorlib_mapa.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_motorlib_monitor.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_tree.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_panel.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_listbox.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_checkbox.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/src_glui_glui_button.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_statictext.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_string.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_textbox.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_mouse_iaction.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_algebra3.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_rotation.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_commandline.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_radio.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/src_glui_glui_window.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_column.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_separator.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_treepanel.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_node.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_filebrowser.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_edittext.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_viewmodel.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_bitmap_img_data.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_list.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/src_glui_quaternion.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_add_controls.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_rollout.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_control.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_arcball.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_spinner.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_bitmaps.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_scrollbar.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_glui_glui_translation.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_comportamientos_puerta.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/src_comportamientos_comportamiento.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_comportamientos_objeto.cpp$(ObjectSuffix) $(IntermediateDirectory)/CMakeFiles_FindOpenMP_ompver.cpp$(ObjectSuffix) $(IntermediateDirectory)/CMakeFiles_FindOpenMP_ompver.c$(ObjectSuffix) $(IntermediateDirectory)/src_modelos_perro_lomo.cpp$(ObjectSuffix) 

Objects1=$(IntermediateDirectory)/src_modelos_perro_cabeza.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_modelos_perro_perro.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_modelos_item_item.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_modelos_jugador_jugador3d.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_modelos_jugador_quesito.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/src_modelos_puerta_puerta.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_modelos_leo_brazo.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_modelos_leo_leo.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_modelos_leo_torso.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_modelos_leo_pierna.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_modelos_leo_cabeza.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_modelos_leo_cintura.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_modelos_aldeano_aldeano.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_modelos_aldeano_brazo.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_modelos_aldeano_torso.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/src_modelos_aldeano_pierna.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_modelos_aldeano_cabeza.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_modelos_aldeano_cintura.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_modelos_arbol_arbol.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_obj3dlib_jpeg_reader_jpg_readwrite.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_obj3dlib_jpeg_reader_jpg_memsrc.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_obj3dlib_jpeg_reader_jpg_imagen.cpp$(ObjectSuffix) $(IntermediateDirectory)/CMakeFiles_3.7.2_CompilerIdCXX_CMakeCXXCompilerId.cpp$(ObjectSuffix) $(IntermediateDirectory)/CMakeFiles_3.7.2_CompilerIdC_CMakeCCompilerId.c$(ObjectSuffix) 



Objects=$(Objects0) $(Objects1) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	@echo $(Objects1) >> $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:
##
## Clean
##
clean:
	$(RM) -r ./Debug/


