list(APPEND CPPFLAGS -DTORONTO)
if(LARGE_PROBLEM_SIZE)
  set(RUN_OPTIONS 4000)
else()
  set(RUN_OPTIONS 1000)
endif()
llvm_multisource(mst)

# Checked C header files
find_path(SAFEMM_HEADER safe_mm_checked.h)
target_include_directories(mst PUBLIC ${SAFEMM_HEADER})
# Checked C library
find_library(LIB_SAFEMM safemm)
target_link_libraries(mst ${LIB_SAFEMM})
