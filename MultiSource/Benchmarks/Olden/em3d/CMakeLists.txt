list(APPEND CPPFLAGS -DTORONTO)
if(SMALL_PROBLEM_SIZE)
  set(RUN_OPTIONS 256 250 35)
elseif(EXTRA_LARGE_PROBLEM_SIZE)
  set(RUN_OPTIONS 2048 2000 250)
else()
  set(RUN_OPTIONS 1024 1000 125)
endif()
llvm_multisource(em3d)

# Checked C header files.
find_path(SAFEMM_HEADER safe_mm_checked.h)
target_include_directories(em3d PUBLIC ${SAFEMM_HEADER})
# Checked C library
find_library(LIB_SAFEMM safemm)
target_link_libraries(em3d ${LIB_SAFEMM})
