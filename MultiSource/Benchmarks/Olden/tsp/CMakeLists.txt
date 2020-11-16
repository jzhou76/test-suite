list(APPEND CPPFLAGS -DTORONTO)
list(APPEND LDFLAGS -lm)
if(LARGE_PROBLEM_SIZE)
  set(RUN_OPTIONS 2048000)
else()
  if(SMALL_PROBLEM_SIZE)
    set(RUN_OPTIONS 102400)
  else()
    set(RUN_OPTIONS 1024000)
  endif()
endif()
llvm_multisource(tsp)

# Checked C header files
find_path(SAFEMM_HEADER safe_mm_checked.h)
target_include_directories(tsp PUBLIC ${SAFEMM_HEADER})
# Checked C library
find_library(LIB_SAFEMM safemm)
target_link_libraries(tsp ${LIB_SAFEMM})
