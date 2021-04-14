set(RUN_OPTIONS words 2 < input.OUT)
llvm_multisource(anagram)
llvm_test_data(anagram words input.OUT)

# Checked C header files
find_path(SAFEMM_HEADER safe_mm_checked.h)
target_include_directories(anagram PUBLIC ${SAFEMM_HEADER})
# Checked C library
find_library(LIB_SAFEMM safemm)
target_link_libraries(anagram ${LIB_SAFEMM})
