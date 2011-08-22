ADD_EXECUTABLE(igtlSocketTest   igtlSocketTest.cxx)

INCLUDE_DIRECTORIES( ${OpenIGTLink_SOURCE_DIR}/Source )

TARGET_LINK_LIBRARIES(igtlSocketTest OpenIGTLink)

ADD_TEST(igtlSocketTest ${OpenIGTLink_EXECUTABLE_PATH}/igtlSocketTest)

ADD_SUBDIRECTORY( igtlutil )
