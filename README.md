# LLVM test-suite for the Checked C Temporal Memory Safety Project

## Build and Run
### Build
1. Clone this repository.
2. Create a build directory in the same directory that contains this repo.
3. Go to the build directory and make a shell script for cmake:
   ```
   CHECKEDC_DIR=YOUR_CHECKEDC_PROJ_DIR
   CHECKEDC_INC=$CHECKEDC_DIR/misc/include
   CHECKEDC_LIB=$CHECKEDC_DIR/misc/lib

   CC=$CHECKEDC/build/bin/clang
   CXX=$CHECKEDC/build/bin/clang++

   rm -rf CMakeCache.txt

   cmake -DCMAKE_C_COMPILER=$CC \
        -DCMAKE_PREFIX_PATH="$CHECKEDC_INC;$CHECKEDC_LIB" \
        -C../test-suite/cmake/caches/O3.cmake \
        ../test-suite
   ```
4. Go to the target benchmark program's directory, add the following to the
   CMakeLists.txt:
   ```
   # Checked C header files
   find_path(SAFEMM_HEADER safe_mm_checked.h)
   target_include_directories(bh PUBLIC ${SAFEMM_HEADER})
   # Checked C library
   find_library(LIB_SAFEMM safemm)
   target_link_libraries(bh ${LIB_SAFEMM})
   ```
5. `make $(PROG)` (e.g., `make bh`)

### Run
Make a directory for experiment results.
In the build directory, run
`llvm-lit -v -j$(x) --filter $(PROG) -o $(RESULT_DIR)/$(PROG).json  .`

You can also first go to the result directory, then run
`llvm-lit -v -j$(x) --filter $(PROG) -o $(PROG).json $(BUILD_DIR)`

