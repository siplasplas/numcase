cmake_minimum_required(VERSION 3.17)
project(example)

set(CMAKE_CXX_STANDARD 14)

add_definitions("-Werror=return-type")

#set(LDIR ../lib/)
set(LDIR lib/)

add_executable(example main.cpp ${LDIR}Dekker.cpp ${LDIR}Func.cpp
        ${LDIR}Poly.cpp ${LDIR}Chebyshev.cpp
        ${LDIR}ChebyshevGauss.cpp ${LDIR}ChebyshevGauss.h
        ${LDIR}LeastSquares.cpp ${LDIR}LeastSquares.h
        ${LDIR}LeastSquaresPoly.cpp ${LDIR}LeastSquaresPoly.h
        ${LDIR}Remez.cpp ${LDIR}Vector.cpp ${LDIR}Matrix.cpp
        ${LDIR}Newton.cpp ${LDIR}NewtonMulti.cpp lib/prec.h)

target_include_directories(example PUBLIC ${LDIR})

target_link_libraries(example mpfr)