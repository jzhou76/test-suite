list(APPEND CPPFLAGS -DTORONTO)
if(LARGE_PROBLEM_SIZE)
  set(RUN_OPTIONS 11)
else()
  if(SMALL_PROBLEM_SIZE)
    set(RUN_OPTIONS 9)
  else()
    set(RUN_OPTIONS 10)
  endif()
endif()
llvm_multisource(perimeter)

# Checked C header files.
find_path(SAFEMM_HEADER safe_mm_checked.h)
target_include_directories(perimeter PUBLIC ${SAFEMM_HEADER})
# Checked C library
find_library(LIB_SAFEMM safemm)
target_link_libraries(perimeter ${LIB_SAFEMM})
