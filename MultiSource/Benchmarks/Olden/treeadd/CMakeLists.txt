list(APPEND CPPFLAGS -DTORONTO)
if(SMALL_PROBLEM_SIZE)
  set(RUN_OPTIONS 20)
else()
  set(RUN_OPTIONS 22)
endif()
llvm_multisource(treeadd)

# Checked C header files.
find_path(SAFEMM_HEADER safe_mm_checked.h)
target_include_directories(treeadd PUBLIC ${SAFEMM_HEADER})
# Checked C library
find_library(LIB_SAFEMM safemm)
target_link_libraries(treeadd ${LIB_SAFEMM})
