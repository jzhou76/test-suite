list(APPEND CPPFLAGS -DTORONTO)
list(APPEND LDFLAGS -lm)
if(LARGE_PROBLEM_SIZE)
  set(RUN_OPTIONS 3000000)
elseif(EXTRA_LARGE_PROBLEM_SIZE)
  set(RUN_OPTIONS 30000000)
else()
  set(RUN_OPTIONS 700000)
endif()
llvm_multisource(bisort)

# Checked C header files.
find_path(SAFEMM_HEADER safe_mm_checked.h)
target_include_directories(bisort PUBLIC ${SAFEMM_HEADER})
# Checked C library
find_library(LIB_SAFEMM safemm)
target_link_libraries(bisort ${LIB_SAFEMM})
