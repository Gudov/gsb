# Makefile generated by XPJ for LINUX32
-include Makefile.custom
ProjectName = SnippetUtils
SnippetUtils_cppfiles   += ./../../SnippetUtils/SnippetUtils.cpp

SnippetUtils_cpp_debug_dep    = $(addprefix $(DEPSDIR)/SnippetUtils/debug/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.P, $(SnippetUtils_cppfiles)))))
SnippetUtils_cc_debug_dep    = $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.debug.P, $(SnippetUtils_ccfiles)))))
SnippetUtils_c_debug_dep      = $(addprefix $(DEPSDIR)/SnippetUtils/debug/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.P, $(SnippetUtils_cfiles)))))
SnippetUtils_debug_dep      = $(SnippetUtils_cpp_debug_dep) $(SnippetUtils_cc_debug_dep) $(SnippetUtils_c_debug_dep)
-include $(SnippetUtils_debug_dep)
SnippetUtils_cpp_checked_dep    = $(addprefix $(DEPSDIR)/SnippetUtils/checked/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.P, $(SnippetUtils_cppfiles)))))
SnippetUtils_cc_checked_dep    = $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.checked.P, $(SnippetUtils_ccfiles)))))
SnippetUtils_c_checked_dep      = $(addprefix $(DEPSDIR)/SnippetUtils/checked/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.P, $(SnippetUtils_cfiles)))))
SnippetUtils_checked_dep      = $(SnippetUtils_cpp_checked_dep) $(SnippetUtils_cc_checked_dep) $(SnippetUtils_c_checked_dep)
-include $(SnippetUtils_checked_dep)
SnippetUtils_cpp_profile_dep    = $(addprefix $(DEPSDIR)/SnippetUtils/profile/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.P, $(SnippetUtils_cppfiles)))))
SnippetUtils_cc_profile_dep    = $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.profile.P, $(SnippetUtils_ccfiles)))))
SnippetUtils_c_profile_dep      = $(addprefix $(DEPSDIR)/SnippetUtils/profile/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.P, $(SnippetUtils_cfiles)))))
SnippetUtils_profile_dep      = $(SnippetUtils_cpp_profile_dep) $(SnippetUtils_cc_profile_dep) $(SnippetUtils_c_profile_dep)
-include $(SnippetUtils_profile_dep)
SnippetUtils_cpp_release_dep    = $(addprefix $(DEPSDIR)/SnippetUtils/release/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.P, $(SnippetUtils_cppfiles)))))
SnippetUtils_cc_release_dep    = $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.release.P, $(SnippetUtils_ccfiles)))))
SnippetUtils_c_release_dep      = $(addprefix $(DEPSDIR)/SnippetUtils/release/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.P, $(SnippetUtils_cfiles)))))
SnippetUtils_release_dep      = $(SnippetUtils_cpp_release_dep) $(SnippetUtils_cc_release_dep) $(SnippetUtils_c_release_dep)
-include $(SnippetUtils_release_dep)
SnippetUtils_debug_hpaths    := 
SnippetUtils_debug_hpaths    += ./../../../Source/Common/include
SnippetUtils_debug_hpaths    += ./../../../../PxShared/include
SnippetUtils_debug_hpaths    += ./../../../../PxShared/src/foundation/include
SnippetUtils_debug_hpaths    += ./../../../../PxShared/src/fastxml/include
SnippetUtils_debug_hpaths    += ./../../../../PxShared/src/pvd/include
SnippetUtils_debug_hpaths    += ./../../../Include
SnippetUtils_debug_hpaths    += ./../../../Include/utils
SnippetUtils_debug_hpaths    += ./../../../Source/Common/src
SnippetUtils_debug_lpaths    := 
SnippetUtils_debug_defines   := $(SnippetUtils_custom_defines)
SnippetUtils_debug_defines   += PX_PHYSX_STATIC_LIB
SnippetUtils_debug_defines   += _DEBUG
SnippetUtils_debug_defines   += PX_DEBUG=1
SnippetUtils_debug_defines   += PX_CHECKED=1
SnippetUtils_debug_defines   += PX_SUPPORT_PVD=1
SnippetUtils_debug_libraries := 
SnippetUtils_debug_common_cflags	:= $(SnippetUtils_custom_cflags)
SnippetUtils_debug_common_cflags    += -MMD
SnippetUtils_debug_common_cflags    += $(addprefix -D, $(SnippetUtils_debug_defines))
SnippetUtils_debug_common_cflags    += $(addprefix -I, $(SnippetUtils_debug_hpaths))
SnippetUtils_debug_common_cflags  += -m32
SnippetUtils_debug_common_cflags  += -Werror -m32 -fPIC -msse2 -mfpmath=sse -malign-double -fno-exceptions -fno-rtti -fvisibility=hidden -fvisibility-inlines-hidden
SnippetUtils_debug_common_cflags  += -Wall -Wextra -Wstrict-aliasing=2 -fdiagnostics-show-option
SnippetUtils_debug_common_cflags  += -Wno-invalid-offsetof -Wno-uninitialized -Wno-implicit-fallthrough
SnippetUtils_debug_common_cflags  += -Wno-missing-field-initializers
SnippetUtils_debug_common_cflags  += -g3 -gdwarf-2
SnippetUtils_debug_cflags	:= $(SnippetUtils_debug_common_cflags)
SnippetUtils_debug_cppflags	:= $(SnippetUtils_debug_common_cflags)
SnippetUtils_debug_lflags    := $(SnippetUtils_custom_lflags)
SnippetUtils_debug_lflags    += $(addprefix -L, $(SnippetUtils_debug_lpaths))
SnippetUtils_debug_lflags    += -Wl,--start-group $(addprefix -l, $(SnippetUtils_debug_libraries)) -Wl,--end-group
SnippetUtils_debug_lflags  += -lrt
SnippetUtils_debug_lflags  += -m32
SnippetUtils_debug_objsdir  = $(OBJS_DIR)/SnippetUtils_debug
SnippetUtils_debug_cpp_o    = $(addprefix $(SnippetUtils_debug_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.o, $(SnippetUtils_cppfiles)))))
SnippetUtils_debug_cc_o    = $(addprefix $(SnippetUtils_debug_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.o, $(SnippetUtils_ccfiles)))))
SnippetUtils_debug_c_o      = $(addprefix $(SnippetUtils_debug_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.o, $(SnippetUtils_cfiles)))))
SnippetUtils_debug_obj      = $(SnippetUtils_debug_cpp_o) $(SnippetUtils_debug_cc_o) $(SnippetUtils_debug_c_o)
SnippetUtils_debug_bin      := ./../../lib/linux32/libSnippetUtilsDEBUG.a

clean_SnippetUtils_debug: 
	@$(ECHO) clean SnippetUtils debug
	@$(RMDIR) $(SnippetUtils_debug_objsdir)
	@$(RMDIR) $(SnippetUtils_debug_bin)
	@$(RMDIR) $(DEPSDIR)/SnippetUtils/debug

build_SnippetUtils_debug: postbuild_SnippetUtils_debug
postbuild_SnippetUtils_debug: mainbuild_SnippetUtils_debug
mainbuild_SnippetUtils_debug: prebuild_SnippetUtils_debug $(SnippetUtils_debug_bin)
prebuild_SnippetUtils_debug:

$(SnippetUtils_debug_bin): $(SnippetUtils_debug_obj) 
	mkdir -p `dirname ./../../lib/linux32/libSnippetUtilsDEBUG.a`
	@$(AR) rcs $(SnippetUtils_debug_bin) $(SnippetUtils_debug_obj)
	$(ECHO) building $@ complete!

SnippetUtils_debug_DEPDIR = $(dir $(@))/$(*F)
$(SnippetUtils_debug_cpp_o): $(SnippetUtils_debug_objsdir)/%.o:
	$(ECHO) SnippetUtils: compiling debug $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(SnippetUtils_debug_objsdir),, $@))), $(SnippetUtils_cppfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(SnippetUtils_debug_cppflags) -c $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(SnippetUtils_debug_objsdir),, $@))), $(SnippetUtils_cppfiles)) -o $@
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/SnippetUtils/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(SnippetUtils_debug_objsdir),, $@))), $(SnippetUtils_cppfiles))))))
	cp $(SnippetUtils_debug_DEPDIR).d $(addprefix $(DEPSDIR)/SnippetUtils/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(SnippetUtils_debug_objsdir),, $@))), $(SnippetUtils_cppfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(SnippetUtils_debug_DEPDIR).d >> $(addprefix $(DEPSDIR)/SnippetUtils/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(SnippetUtils_debug_objsdir),, $@))), $(SnippetUtils_cppfiles))))).P; \
	  rm -f $(SnippetUtils_debug_DEPDIR).d

$(SnippetUtils_debug_cc_o): $(SnippetUtils_debug_objsdir)/%.o:
	$(ECHO) SnippetUtils: compiling debug $(filter %$(strip $(subst .cc.o,.cc, $(subst $(SnippetUtils_debug_objsdir),, $@))), $(SnippetUtils_ccfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(SnippetUtils_debug_cppflags) -c $(filter %$(strip $(subst .cc.o,.cc, $(subst $(SnippetUtils_debug_objsdir),, $@))), $(SnippetUtils_ccfiles)) -o $@
	mkdir -p $(dir $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(SnippetUtils_debug_objsdir),, $@))), $(SnippetUtils_ccfiles))))))
	cp $(SnippetUtils_debug_DEPDIR).d $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(SnippetUtils_debug_objsdir),, $@))), $(SnippetUtils_ccfiles))))).debug.P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(SnippetUtils_debug_DEPDIR).d >> $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(SnippetUtils_debug_objsdir),, $@))), $(SnippetUtils_ccfiles))))).debug.P; \
	  rm -f $(SnippetUtils_debug_DEPDIR).d

$(SnippetUtils_debug_c_o): $(SnippetUtils_debug_objsdir)/%.o:
	$(ECHO) SnippetUtils: compiling debug $(filter %$(strip $(subst .c.o,.c, $(subst $(SnippetUtils_debug_objsdir),, $@))), $(SnippetUtils_cfiles))...
	mkdir -p $(dir $(@))
	$(CC) $(SnippetUtils_debug_cflags) -c $(filter %$(strip $(subst .c.o,.c, $(subst $(SnippetUtils_debug_objsdir),, $@))), $(SnippetUtils_cfiles)) -o $@ 
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/SnippetUtils/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(SnippetUtils_debug_objsdir),, $@))), $(SnippetUtils_cfiles))))))
	cp $(SnippetUtils_debug_DEPDIR).d $(addprefix $(DEPSDIR)/SnippetUtils/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(SnippetUtils_debug_objsdir),, $@))), $(SnippetUtils_cfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(SnippetUtils_debug_DEPDIR).d >> $(addprefix $(DEPSDIR)/SnippetUtils/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(SnippetUtils_debug_objsdir),, $@))), $(SnippetUtils_cfiles))))).P; \
	  rm -f $(SnippetUtils_debug_DEPDIR).d

SnippetUtils_checked_hpaths    := 
SnippetUtils_checked_hpaths    += ./../../../Source/Common/include
SnippetUtils_checked_hpaths    += ./../../../../PxShared/include
SnippetUtils_checked_hpaths    += ./../../../../PxShared/src/foundation/include
SnippetUtils_checked_hpaths    += ./../../../../PxShared/src/fastxml/include
SnippetUtils_checked_hpaths    += ./../../../../PxShared/src/pvd/include
SnippetUtils_checked_hpaths    += ./../../../Include
SnippetUtils_checked_hpaths    += ./../../../Include/utils
SnippetUtils_checked_hpaths    += ./../../../Source/Common/src
SnippetUtils_checked_lpaths    := 
SnippetUtils_checked_defines   := $(SnippetUtils_custom_defines)
SnippetUtils_checked_defines   += PX_PHYSX_STATIC_LIB
SnippetUtils_checked_defines   += NDEBUG
SnippetUtils_checked_defines   += PX_CHECKED=1
SnippetUtils_checked_defines   += PX_SUPPORT_PVD=1
SnippetUtils_checked_libraries := 
SnippetUtils_checked_common_cflags	:= $(SnippetUtils_custom_cflags)
SnippetUtils_checked_common_cflags    += -MMD
SnippetUtils_checked_common_cflags    += $(addprefix -D, $(SnippetUtils_checked_defines))
SnippetUtils_checked_common_cflags    += $(addprefix -I, $(SnippetUtils_checked_hpaths))
SnippetUtils_checked_common_cflags  += -m32
SnippetUtils_checked_common_cflags  += -Werror -m32 -fPIC -msse2 -mfpmath=sse -malign-double -fno-exceptions -fno-rtti -fvisibility=hidden -fvisibility-inlines-hidden
SnippetUtils_checked_common_cflags  += -Wall -Wextra -Wstrict-aliasing=2 -fdiagnostics-show-option
SnippetUtils_checked_common_cflags  += -Wno-invalid-offsetof -Wno-uninitialized -Wno-implicit-fallthrough
SnippetUtils_checked_common_cflags  += -Wno-missing-field-initializers
SnippetUtils_checked_common_cflags  += -g3 -gdwarf-2 -O3 -fno-strict-aliasing
SnippetUtils_checked_cflags	:= $(SnippetUtils_checked_common_cflags)
SnippetUtils_checked_cppflags	:= $(SnippetUtils_checked_common_cflags)
SnippetUtils_checked_lflags    := $(SnippetUtils_custom_lflags)
SnippetUtils_checked_lflags    += $(addprefix -L, $(SnippetUtils_checked_lpaths))
SnippetUtils_checked_lflags    += -Wl,--start-group $(addprefix -l, $(SnippetUtils_checked_libraries)) -Wl,--end-group
SnippetUtils_checked_lflags  += -lrt
SnippetUtils_checked_lflags  += -m32
SnippetUtils_checked_objsdir  = $(OBJS_DIR)/SnippetUtils_checked
SnippetUtils_checked_cpp_o    = $(addprefix $(SnippetUtils_checked_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.o, $(SnippetUtils_cppfiles)))))
SnippetUtils_checked_cc_o    = $(addprefix $(SnippetUtils_checked_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.o, $(SnippetUtils_ccfiles)))))
SnippetUtils_checked_c_o      = $(addprefix $(SnippetUtils_checked_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.o, $(SnippetUtils_cfiles)))))
SnippetUtils_checked_obj      = $(SnippetUtils_checked_cpp_o) $(SnippetUtils_checked_cc_o) $(SnippetUtils_checked_c_o)
SnippetUtils_checked_bin      := ./../../lib/linux32/libSnippetUtilsCHECKED.a

clean_SnippetUtils_checked: 
	@$(ECHO) clean SnippetUtils checked
	@$(RMDIR) $(SnippetUtils_checked_objsdir)
	@$(RMDIR) $(SnippetUtils_checked_bin)
	@$(RMDIR) $(DEPSDIR)/SnippetUtils/checked

build_SnippetUtils_checked: postbuild_SnippetUtils_checked
postbuild_SnippetUtils_checked: mainbuild_SnippetUtils_checked
mainbuild_SnippetUtils_checked: prebuild_SnippetUtils_checked $(SnippetUtils_checked_bin)
prebuild_SnippetUtils_checked:

$(SnippetUtils_checked_bin): $(SnippetUtils_checked_obj) 
	mkdir -p `dirname ./../../lib/linux32/libSnippetUtilsCHECKED.a`
	@$(AR) rcs $(SnippetUtils_checked_bin) $(SnippetUtils_checked_obj)
	$(ECHO) building $@ complete!

SnippetUtils_checked_DEPDIR = $(dir $(@))/$(*F)
$(SnippetUtils_checked_cpp_o): $(SnippetUtils_checked_objsdir)/%.o:
	$(ECHO) SnippetUtils: compiling checked $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(SnippetUtils_checked_objsdir),, $@))), $(SnippetUtils_cppfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(SnippetUtils_checked_cppflags) -c $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(SnippetUtils_checked_objsdir),, $@))), $(SnippetUtils_cppfiles)) -o $@
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/SnippetUtils/checked/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(SnippetUtils_checked_objsdir),, $@))), $(SnippetUtils_cppfiles))))))
	cp $(SnippetUtils_checked_DEPDIR).d $(addprefix $(DEPSDIR)/SnippetUtils/checked/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(SnippetUtils_checked_objsdir),, $@))), $(SnippetUtils_cppfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(SnippetUtils_checked_DEPDIR).d >> $(addprefix $(DEPSDIR)/SnippetUtils/checked/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(SnippetUtils_checked_objsdir),, $@))), $(SnippetUtils_cppfiles))))).P; \
	  rm -f $(SnippetUtils_checked_DEPDIR).d

$(SnippetUtils_checked_cc_o): $(SnippetUtils_checked_objsdir)/%.o:
	$(ECHO) SnippetUtils: compiling checked $(filter %$(strip $(subst .cc.o,.cc, $(subst $(SnippetUtils_checked_objsdir),, $@))), $(SnippetUtils_ccfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(SnippetUtils_checked_cppflags) -c $(filter %$(strip $(subst .cc.o,.cc, $(subst $(SnippetUtils_checked_objsdir),, $@))), $(SnippetUtils_ccfiles)) -o $@
	mkdir -p $(dir $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(SnippetUtils_checked_objsdir),, $@))), $(SnippetUtils_ccfiles))))))
	cp $(SnippetUtils_checked_DEPDIR).d $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(SnippetUtils_checked_objsdir),, $@))), $(SnippetUtils_ccfiles))))).checked.P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(SnippetUtils_checked_DEPDIR).d >> $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(SnippetUtils_checked_objsdir),, $@))), $(SnippetUtils_ccfiles))))).checked.P; \
	  rm -f $(SnippetUtils_checked_DEPDIR).d

$(SnippetUtils_checked_c_o): $(SnippetUtils_checked_objsdir)/%.o:
	$(ECHO) SnippetUtils: compiling checked $(filter %$(strip $(subst .c.o,.c, $(subst $(SnippetUtils_checked_objsdir),, $@))), $(SnippetUtils_cfiles))...
	mkdir -p $(dir $(@))
	$(CC) $(SnippetUtils_checked_cflags) -c $(filter %$(strip $(subst .c.o,.c, $(subst $(SnippetUtils_checked_objsdir),, $@))), $(SnippetUtils_cfiles)) -o $@ 
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/SnippetUtils/checked/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(SnippetUtils_checked_objsdir),, $@))), $(SnippetUtils_cfiles))))))
	cp $(SnippetUtils_checked_DEPDIR).d $(addprefix $(DEPSDIR)/SnippetUtils/checked/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(SnippetUtils_checked_objsdir),, $@))), $(SnippetUtils_cfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(SnippetUtils_checked_DEPDIR).d >> $(addprefix $(DEPSDIR)/SnippetUtils/checked/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(SnippetUtils_checked_objsdir),, $@))), $(SnippetUtils_cfiles))))).P; \
	  rm -f $(SnippetUtils_checked_DEPDIR).d

SnippetUtils_profile_hpaths    := 
SnippetUtils_profile_hpaths    += ./../../../Source/Common/include
SnippetUtils_profile_hpaths    += ./../../../../PxShared/include
SnippetUtils_profile_hpaths    += ./../../../../PxShared/src/foundation/include
SnippetUtils_profile_hpaths    += ./../../../../PxShared/src/fastxml/include
SnippetUtils_profile_hpaths    += ./../../../../PxShared/src/pvd/include
SnippetUtils_profile_hpaths    += ./../../../Include
SnippetUtils_profile_hpaths    += ./../../../Include/utils
SnippetUtils_profile_hpaths    += ./../../../Source/Common/src
SnippetUtils_profile_lpaths    := 
SnippetUtils_profile_defines   := $(SnippetUtils_custom_defines)
SnippetUtils_profile_defines   += PX_PHYSX_STATIC_LIB
SnippetUtils_profile_defines   += NDEBUG
SnippetUtils_profile_defines   += PX_PROFILE=1
SnippetUtils_profile_defines   += PX_SUPPORT_PVD=1
SnippetUtils_profile_libraries := 
SnippetUtils_profile_common_cflags	:= $(SnippetUtils_custom_cflags)
SnippetUtils_profile_common_cflags    += -MMD
SnippetUtils_profile_common_cflags    += $(addprefix -D, $(SnippetUtils_profile_defines))
SnippetUtils_profile_common_cflags    += $(addprefix -I, $(SnippetUtils_profile_hpaths))
SnippetUtils_profile_common_cflags  += -m32
SnippetUtils_profile_common_cflags  += -Werror -m32 -fPIC -msse2 -mfpmath=sse -malign-double -fno-exceptions -fno-rtti -fvisibility=hidden -fvisibility-inlines-hidden
SnippetUtils_profile_common_cflags  += -Wall -Wextra -Wstrict-aliasing=2 -fdiagnostics-show-option
SnippetUtils_profile_common_cflags  += -Wno-invalid-offsetof -Wno-uninitialized -Wno-implicit-fallthrough
SnippetUtils_profile_common_cflags  += -Wno-missing-field-initializers
SnippetUtils_profile_common_cflags  += -O3 -fno-strict-aliasing
SnippetUtils_profile_cflags	:= $(SnippetUtils_profile_common_cflags)
SnippetUtils_profile_cppflags	:= $(SnippetUtils_profile_common_cflags)
SnippetUtils_profile_lflags    := $(SnippetUtils_custom_lflags)
SnippetUtils_profile_lflags    += $(addprefix -L, $(SnippetUtils_profile_lpaths))
SnippetUtils_profile_lflags    += -Wl,--start-group $(addprefix -l, $(SnippetUtils_profile_libraries)) -Wl,--end-group
SnippetUtils_profile_lflags  += -lrt
SnippetUtils_profile_lflags  += -m32
SnippetUtils_profile_objsdir  = $(OBJS_DIR)/SnippetUtils_profile
SnippetUtils_profile_cpp_o    = $(addprefix $(SnippetUtils_profile_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.o, $(SnippetUtils_cppfiles)))))
SnippetUtils_profile_cc_o    = $(addprefix $(SnippetUtils_profile_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.o, $(SnippetUtils_ccfiles)))))
SnippetUtils_profile_c_o      = $(addprefix $(SnippetUtils_profile_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.o, $(SnippetUtils_cfiles)))))
SnippetUtils_profile_obj      = $(SnippetUtils_profile_cpp_o) $(SnippetUtils_profile_cc_o) $(SnippetUtils_profile_c_o)
SnippetUtils_profile_bin      := ./../../lib/linux32/libSnippetUtilsPROFILE.a

clean_SnippetUtils_profile: 
	@$(ECHO) clean SnippetUtils profile
	@$(RMDIR) $(SnippetUtils_profile_objsdir)
	@$(RMDIR) $(SnippetUtils_profile_bin)
	@$(RMDIR) $(DEPSDIR)/SnippetUtils/profile

build_SnippetUtils_profile: postbuild_SnippetUtils_profile
postbuild_SnippetUtils_profile: mainbuild_SnippetUtils_profile
mainbuild_SnippetUtils_profile: prebuild_SnippetUtils_profile $(SnippetUtils_profile_bin)
prebuild_SnippetUtils_profile:

$(SnippetUtils_profile_bin): $(SnippetUtils_profile_obj) 
	mkdir -p `dirname ./../../lib/linux32/libSnippetUtilsPROFILE.a`
	@$(AR) rcs $(SnippetUtils_profile_bin) $(SnippetUtils_profile_obj)
	$(ECHO) building $@ complete!

SnippetUtils_profile_DEPDIR = $(dir $(@))/$(*F)
$(SnippetUtils_profile_cpp_o): $(SnippetUtils_profile_objsdir)/%.o:
	$(ECHO) SnippetUtils: compiling profile $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(SnippetUtils_profile_objsdir),, $@))), $(SnippetUtils_cppfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(SnippetUtils_profile_cppflags) -c $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(SnippetUtils_profile_objsdir),, $@))), $(SnippetUtils_cppfiles)) -o $@
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/SnippetUtils/profile/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(SnippetUtils_profile_objsdir),, $@))), $(SnippetUtils_cppfiles))))))
	cp $(SnippetUtils_profile_DEPDIR).d $(addprefix $(DEPSDIR)/SnippetUtils/profile/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(SnippetUtils_profile_objsdir),, $@))), $(SnippetUtils_cppfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(SnippetUtils_profile_DEPDIR).d >> $(addprefix $(DEPSDIR)/SnippetUtils/profile/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(SnippetUtils_profile_objsdir),, $@))), $(SnippetUtils_cppfiles))))).P; \
	  rm -f $(SnippetUtils_profile_DEPDIR).d

$(SnippetUtils_profile_cc_o): $(SnippetUtils_profile_objsdir)/%.o:
	$(ECHO) SnippetUtils: compiling profile $(filter %$(strip $(subst .cc.o,.cc, $(subst $(SnippetUtils_profile_objsdir),, $@))), $(SnippetUtils_ccfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(SnippetUtils_profile_cppflags) -c $(filter %$(strip $(subst .cc.o,.cc, $(subst $(SnippetUtils_profile_objsdir),, $@))), $(SnippetUtils_ccfiles)) -o $@
	mkdir -p $(dir $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(SnippetUtils_profile_objsdir),, $@))), $(SnippetUtils_ccfiles))))))
	cp $(SnippetUtils_profile_DEPDIR).d $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(SnippetUtils_profile_objsdir),, $@))), $(SnippetUtils_ccfiles))))).profile.P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(SnippetUtils_profile_DEPDIR).d >> $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(SnippetUtils_profile_objsdir),, $@))), $(SnippetUtils_ccfiles))))).profile.P; \
	  rm -f $(SnippetUtils_profile_DEPDIR).d

$(SnippetUtils_profile_c_o): $(SnippetUtils_profile_objsdir)/%.o:
	$(ECHO) SnippetUtils: compiling profile $(filter %$(strip $(subst .c.o,.c, $(subst $(SnippetUtils_profile_objsdir),, $@))), $(SnippetUtils_cfiles))...
	mkdir -p $(dir $(@))
	$(CC) $(SnippetUtils_profile_cflags) -c $(filter %$(strip $(subst .c.o,.c, $(subst $(SnippetUtils_profile_objsdir),, $@))), $(SnippetUtils_cfiles)) -o $@ 
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/SnippetUtils/profile/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(SnippetUtils_profile_objsdir),, $@))), $(SnippetUtils_cfiles))))))
	cp $(SnippetUtils_profile_DEPDIR).d $(addprefix $(DEPSDIR)/SnippetUtils/profile/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(SnippetUtils_profile_objsdir),, $@))), $(SnippetUtils_cfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(SnippetUtils_profile_DEPDIR).d >> $(addprefix $(DEPSDIR)/SnippetUtils/profile/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(SnippetUtils_profile_objsdir),, $@))), $(SnippetUtils_cfiles))))).P; \
	  rm -f $(SnippetUtils_profile_DEPDIR).d

SnippetUtils_release_hpaths    := 
SnippetUtils_release_hpaths    += ./../../../Source/Common/include
SnippetUtils_release_hpaths    += ./../../../../PxShared/include
SnippetUtils_release_hpaths    += ./../../../../PxShared/src/foundation/include
SnippetUtils_release_hpaths    += ./../../../../PxShared/src/fastxml/include
SnippetUtils_release_hpaths    += ./../../../../PxShared/src/pvd/include
SnippetUtils_release_hpaths    += ./../../../Include
SnippetUtils_release_hpaths    += ./../../../Include/utils
SnippetUtils_release_hpaths    += ./../../../Source/Common/src
SnippetUtils_release_lpaths    := 
SnippetUtils_release_defines   := $(SnippetUtils_custom_defines)
SnippetUtils_release_defines   += PX_PHYSX_STATIC_LIB
SnippetUtils_release_defines   += NDEBUG
SnippetUtils_release_defines   += PX_SUPPORT_PVD=0
SnippetUtils_release_libraries := 
SnippetUtils_release_common_cflags	:= $(SnippetUtils_custom_cflags)
SnippetUtils_release_common_cflags    += -MMD
SnippetUtils_release_common_cflags    += $(addprefix -D, $(SnippetUtils_release_defines))
SnippetUtils_release_common_cflags    += $(addprefix -I, $(SnippetUtils_release_hpaths))
SnippetUtils_release_common_cflags  += -m32
SnippetUtils_release_common_cflags  += -Werror -m32 -fPIC -msse2 -mfpmath=sse -malign-double -fno-exceptions -fno-rtti -fvisibility=hidden -fvisibility-inlines-hidden
SnippetUtils_release_common_cflags  += -Wall -Wextra -Wstrict-aliasing=2 -fdiagnostics-show-option
SnippetUtils_release_common_cflags  += -Wno-invalid-offsetof -Wno-uninitialized -Wno-implicit-fallthrough
SnippetUtils_release_common_cflags  += -Wno-missing-field-initializers
SnippetUtils_release_common_cflags  += -O3 -fno-strict-aliasing
SnippetUtils_release_cflags	:= $(SnippetUtils_release_common_cflags)
SnippetUtils_release_cppflags	:= $(SnippetUtils_release_common_cflags)
SnippetUtils_release_lflags    := $(SnippetUtils_custom_lflags)
SnippetUtils_release_lflags    += $(addprefix -L, $(SnippetUtils_release_lpaths))
SnippetUtils_release_lflags    += -Wl,--start-group $(addprefix -l, $(SnippetUtils_release_libraries)) -Wl,--end-group
SnippetUtils_release_lflags  += -lrt
SnippetUtils_release_lflags  += -m32
SnippetUtils_release_objsdir  = $(OBJS_DIR)/SnippetUtils_release
SnippetUtils_release_cpp_o    = $(addprefix $(SnippetUtils_release_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.o, $(SnippetUtils_cppfiles)))))
SnippetUtils_release_cc_o    = $(addprefix $(SnippetUtils_release_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.o, $(SnippetUtils_ccfiles)))))
SnippetUtils_release_c_o      = $(addprefix $(SnippetUtils_release_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.o, $(SnippetUtils_cfiles)))))
SnippetUtils_release_obj      = $(SnippetUtils_release_cpp_o) $(SnippetUtils_release_cc_o) $(SnippetUtils_release_c_o)
SnippetUtils_release_bin      := ./../../lib/linux32/libSnippetUtils.a

clean_SnippetUtils_release: 
	@$(ECHO) clean SnippetUtils release
	@$(RMDIR) $(SnippetUtils_release_objsdir)
	@$(RMDIR) $(SnippetUtils_release_bin)
	@$(RMDIR) $(DEPSDIR)/SnippetUtils/release

build_SnippetUtils_release: postbuild_SnippetUtils_release
postbuild_SnippetUtils_release: mainbuild_SnippetUtils_release
mainbuild_SnippetUtils_release: prebuild_SnippetUtils_release $(SnippetUtils_release_bin)
prebuild_SnippetUtils_release:

$(SnippetUtils_release_bin): $(SnippetUtils_release_obj) 
	mkdir -p `dirname ./../../lib/linux32/libSnippetUtils.a`
	@$(AR) rcs $(SnippetUtils_release_bin) $(SnippetUtils_release_obj)
	$(ECHO) building $@ complete!

SnippetUtils_release_DEPDIR = $(dir $(@))/$(*F)
$(SnippetUtils_release_cpp_o): $(SnippetUtils_release_objsdir)/%.o:
	$(ECHO) SnippetUtils: compiling release $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(SnippetUtils_release_objsdir),, $@))), $(SnippetUtils_cppfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(SnippetUtils_release_cppflags) -c $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(SnippetUtils_release_objsdir),, $@))), $(SnippetUtils_cppfiles)) -o $@
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/SnippetUtils/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(SnippetUtils_release_objsdir),, $@))), $(SnippetUtils_cppfiles))))))
	cp $(SnippetUtils_release_DEPDIR).d $(addprefix $(DEPSDIR)/SnippetUtils/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(SnippetUtils_release_objsdir),, $@))), $(SnippetUtils_cppfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(SnippetUtils_release_DEPDIR).d >> $(addprefix $(DEPSDIR)/SnippetUtils/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(SnippetUtils_release_objsdir),, $@))), $(SnippetUtils_cppfiles))))).P; \
	  rm -f $(SnippetUtils_release_DEPDIR).d

$(SnippetUtils_release_cc_o): $(SnippetUtils_release_objsdir)/%.o:
	$(ECHO) SnippetUtils: compiling release $(filter %$(strip $(subst .cc.o,.cc, $(subst $(SnippetUtils_release_objsdir),, $@))), $(SnippetUtils_ccfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(SnippetUtils_release_cppflags) -c $(filter %$(strip $(subst .cc.o,.cc, $(subst $(SnippetUtils_release_objsdir),, $@))), $(SnippetUtils_ccfiles)) -o $@
	mkdir -p $(dir $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(SnippetUtils_release_objsdir),, $@))), $(SnippetUtils_ccfiles))))))
	cp $(SnippetUtils_release_DEPDIR).d $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(SnippetUtils_release_objsdir),, $@))), $(SnippetUtils_ccfiles))))).release.P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(SnippetUtils_release_DEPDIR).d >> $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(SnippetUtils_release_objsdir),, $@))), $(SnippetUtils_ccfiles))))).release.P; \
	  rm -f $(SnippetUtils_release_DEPDIR).d

$(SnippetUtils_release_c_o): $(SnippetUtils_release_objsdir)/%.o:
	$(ECHO) SnippetUtils: compiling release $(filter %$(strip $(subst .c.o,.c, $(subst $(SnippetUtils_release_objsdir),, $@))), $(SnippetUtils_cfiles))...
	mkdir -p $(dir $(@))
	$(CC) $(SnippetUtils_release_cflags) -c $(filter %$(strip $(subst .c.o,.c, $(subst $(SnippetUtils_release_objsdir),, $@))), $(SnippetUtils_cfiles)) -o $@ 
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/SnippetUtils/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(SnippetUtils_release_objsdir),, $@))), $(SnippetUtils_cfiles))))))
	cp $(SnippetUtils_release_DEPDIR).d $(addprefix $(DEPSDIR)/SnippetUtils/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(SnippetUtils_release_objsdir),, $@))), $(SnippetUtils_cfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(SnippetUtils_release_DEPDIR).d >> $(addprefix $(DEPSDIR)/SnippetUtils/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(SnippetUtils_release_objsdir),, $@))), $(SnippetUtils_cfiles))))).P; \
	  rm -f $(SnippetUtils_release_DEPDIR).d

clean_SnippetUtils:  clean_SnippetUtils_debug clean_SnippetUtils_checked clean_SnippetUtils_profile clean_SnippetUtils_release
	rm -rf $(DEPSDIR)

export VERBOSE
ifndef VERBOSE
.SILENT:
endif
