list(APPEND CPPFLAGS -DTORONTO)
list(APPEND LDFLAGS -lm)
set(FP_TOLERANCE 0.001)
if(LARGE_PROBLEM_SIZE)
  set(RUN_OPTIONS 10 40 1)
elseif(EXTRA_LARGE_PROBLEM_SIZE)
  set(RUN_OPTIONS 11 40 1)
else()
  if(SMALL_PROBLEM_SIZE)
    set(RUN_OPTIONS 8 15 1)
  else()
    set(RUN_OPTIONS 9 20 1)
  endif()
endif()
llvm_multisource(health)

# Checked C header files
find_path(SAFEMM_HEADER safe_mm_checked.h)
target_include_directories(health PUBLIC ${SAFEMM_HEADER})
# Checked C library
find_library(LIB_SAFEMM safemm)
target_link_libraries(health ${LIB_SAFEMM})
