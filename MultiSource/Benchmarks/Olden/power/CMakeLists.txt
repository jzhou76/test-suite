list(APPEND CPPFLAGS -DTORONTO)
list(APPEND LDFLAGS -lm)
set(FP_TOLERANCE 0.00001)
llvm_multisource(power)

# Checked C header files
find_path(SAFEMM_HEADER safe_mm_checked.h)
target_include_directories(power PUBLIC ${SAFEMM_HEADER})
# Checked C library
find_library(LIB_SAFEMM safemm)
target_link_libraries(power ${LIB_SAFEMM})
